#ifndef POWER_STATE_MACHINE_H_
#define POWER_STATE_MACHINE_H_

typedef void (*state_fn_t)(void);

typedef struct
{
    state_fn_t entry;
    state_fn_t run;
    state_fn_t exit;
} state_handler_t;

typedef enum
{
    STATE_NULL              = 0,
    STATE_STANDBY           = 1,
    STATE_PRECHARGE         = 2,
    STATE_SOFTSTART         = 3,
    STATE_NORMALOPERATION   = 4,
    STATE_SHUTDOWN          = 5,
    NUMBER_OF_STATE
} state_t;


#endif