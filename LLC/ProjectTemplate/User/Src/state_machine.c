#include "main.h"
#include "state_machine.h"

/* NULL */
static void state_null_entry(void);
static void state_null_run(void);
static void state_null_exit(void);

/* STANDBY */
static void state_standby_entry(void);
static void state_standby_run(void);
static void state_standby_exit(void);

/* PRECHARGE */
static void state_precharge_entry(void);
static void state_precharge_run(void);
static void state_precharge_exit(void);

/* SOFTSTART */
static void state_softstart_entry(void);
static void state_softstart_run(void);
static void state_softstart_exit(void);

/* NORMAL */
static void state_normaloperation_entry(void);
static void state_normaloperation_run(void);
static void state_normaloperation_exit(void);

/* SHUTDOWN */
static void state_shutdown_entry(void);
static void state_shutdown_run(void);
static void state_shutdown_exit(void);

static void StateMachine_CommonTasks(void);

static uint16_t transition_req        = 0U;
static uint16_t transition_wait_ticks = 0U;
static uint16_t transition_delay_cfg  = 1U;
static state_t  transition_target     = STATE_NULL;

static const state_handler_t g_state_table[NUMBER_OF_STATE] =
{
    [STATE_NULL]            = { state_null_entry,               state_null_run,             state_null_exit },
    [STATE_STANDBY]         = { state_standby_entry,            state_standby_run,          state_standby_exit },
    [STATE_PRECHARGE]       = { state_precharge_entry,          state_precharge_run,        state_precharge_exit },
    [STATE_SOFTSTART]       = { state_softstart_entry,          state_softstart_run,        state_softstart_exit },
    [STATE_NORMALOPERATION] = { state_normaloperation_entry,    state_normaloperation_run,  state_normaloperation_exit },
    [STATE_SHUTDOWN]        = { state_shutdown_entry,           state_shutdown_run,         state_shutdown_exit },
};


static volatile state_t g_cur_state  = STATE_NULL;
static volatile state_t g_next_state = STATE_NULL;


static void state_null_entry(void){}
static void state_null_run(void){}
static void state_null_exit(void){}

/* STANDBY */
static void state_standby_entry(void){}
static void state_standby_run(void){}
static void state_standby_exit(void){}

/* PRECHARGE */
static void state_precharge_entry(void){}
static void state_precharge_run(void){}
static void state_precharge_exit(void){}

/* SOFTSTART */
static void state_softstart_entry(void){}
static void state_softstart_run(void){}
static void state_softstart_exit(void){}

/* NORMAL */
static void state_normaloperation_entry(void){}
static void state_normaloperation_run(void){}
static void state_normaloperation_exit(void){}

/* SHUTDOWN */
static void state_shutdown_entry(void){}
static void state_shutdown_run(void){}
static void state_shutdown_exit(void){}

static void StateMachine_CommonTasks(void){}


static inline bool StateMachine_IsValidState(state_t s)
{
    return (s < (state_t)NUMBER_OF_STATE);
}

static void StateMachine_DoTransition(void)
{
    if(!StateMachine_IsValidState(g_next_state))
        g_next_state = STATE_NULL;

    if(g_next_state == g_cur_state)
        return;

    g_cur_state = g_next_state;

    if(g_state_table[g_cur_state].entry)
        g_state_table[g_cur_state].entry();
}

void StateMachine_Init(state_t init_state)
{
    if(!StateMachine_IsValidState(init_state))
        init_state = STATE_NULL;

    g_cur_state  = init_state;
    g_next_state = init_state;

    transition_req        = 0U;
    transition_wait_ticks = 0U;
    transition_target     = init_state;

    if(g_state_table[g_cur_state].entry)
        g_state_table[g_cur_state].entry();
}

void StateMachine_Step(void)
{
    if(!StateMachine_IsValidState(g_cur_state))
        g_cur_state = STATE_NULL;

    StateMachine_CommonTasks();

    if(transition_req)
    {
        if(transition_wait_ticks == 0U)
        {
            if(g_state_table[g_cur_state].exit)
                g_state_table[g_cur_state].exit();

            transition_wait_ticks = transition_delay_cfg;
            return;
        }

        transition_wait_ticks--;

        if(transition_wait_ticks == 0U)
        {
            g_next_state = transition_target;
            StateMachine_DoTransition();
            transition_req = 0U;
        }

        return;
    }

    if(g_state_table[g_cur_state].run)
        g_state_table[g_cur_state].run();
}

void StateMachine_RequestTransition(state_t next)
{
    if(StateMachine_IsValidState(next))
    {
        transition_target = next;

        if(!transition_req)
            transition_req = 1U;
    }
}

state_t StateMachine_GetCurrentState(void)
{
    return g_cur_state;
}