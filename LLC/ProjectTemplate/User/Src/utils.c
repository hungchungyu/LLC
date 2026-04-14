#include "utils.h"
#include "main.h"
#include "variables_define_app.h"

digitctrl_PI P1_I_Loop;
float open_loop_value = -500.0f;

static inline void Sweep_Comp_UpDown(volatile TW_HRPWM_TypeDef* pwm)
{
    static float compb_f = (float)LLC_DEADTIME_COUNT;
    static int8_t dir = 1;

    float period      = (float)(HRPWM_FINAL_FREQ / LLC_SW_FREQ_MAX);
    float half_period = period * 0.5f;

    if(dir > 0)
    {
        compb_f += 0.01f;
        if(compb_f >= half_period)
        {
            compb_f = half_period;
            dir = -1;
        }
    }
    else
    {
        compb_f -= 0.01f;
        if(compb_f <= (float)LLC_DEADTIME_COUNT)
        {
            compb_f = (float)LLC_DEADTIME_COUNT;
            dir = 1;
        }
    }

    pwm->compb = (int32_t)(compb_f + 0.5f);  
		pwm->compd = pwm->compb + ((int32_t)(half_period + 0.5f));
}

static inline float SlewRateLimit(float cmd, float target)
{	
    float delta = target - cmd;
    float rise_step = 100.0f;
    float drop_step = 100.0f;

    if(delta > rise_step)
    {
        cmd += rise_step;
    }
    else if(delta < -drop_step)
    {
        cmd -= drop_step;
    }
    else
    {
        cmd = target;
    }

    return cmd;
}

static inline void Value_To_Period(digitctrl_PI* p, volatile TW_HRPWM_TypeDef* pwm)
{
    float value = p->Out;

    if(value <= 0.0)
    {
			int32_t period = (int32_t)(HRPWM_FINAL_FREQ/LLC_SW_FREQ_MAX);
			int32_t half_period = period >> 1;
			float k = (value + 500.0f) / 500.0f;   // -500~0 -> 0%~100%(1/2PRD)
			
			if(value < -500.0f) value = -500.0f;
			if(value > 0.0f)    value = 0.0f;
			
			pwm->period	= period - 1;
			pwm->compa	= LLC_DEADTIME_COUNT - 1;
			pwm->compc  = half_period + LLC_DEADTIME_COUNT - 1;
						
			pwm->compb = pwm->compa + (int32_t)(k * (half_period - pwm->compa));
			pwm->compd = pwm->compb + half_period;
			
		}
    else if(value >= 0.0)
    {

    }

}

int32_t debug_sw_freq = 0;
int32_t debug_period  = 0;
int32_t debug_duty  = 0;
static inline void Sweep_Freq_UpDown_50Duty(volatile TW_HRPWM_TypeDef* pwm)
{
    static float sw_freq = LLC_SW_FREQ_MAX;
    static int8_t dir = -1;   // -1: high -> low, +1: low -> high

    float period_f;
    int32_t period;
    int32_t half_period;

    if(dir < 0)
    {
        sw_freq -= 0.001f;
        if(sw_freq <= LLC_SW_FREQ_MIN)
        {
            sw_freq = LLC_SW_FREQ_MIN;
            dir = 1;
        }
    }
    else
    {
        sw_freq += 0.001f;
        if(sw_freq >= LLC_SW_FREQ_MAX)
        {
            sw_freq = LLC_SW_FREQ_MAX;
            dir = -1;
        }
    }

    period_f = (float)HRPWM_FINAL_FREQ / sw_freq;
    period   = (int32_t)(period_f + 0.5f);
    half_period = period >> 1;

    if(half_period <= LLC_DEADTIME_COUNT)
    {
        half_period = LLC_DEADTIME_COUNT + 1;
        period = half_period << 1;
    }

    pwm->period = period - 1;

    pwm->compa  = LLC_DEADTIME_COUNT - 1;
    pwm->compb  = half_period - 1;

    pwm->compc  = half_period + LLC_DEADTIME_COUNT - 1;
    pwm->compd  = period - 1;
		
		debug_sw_freq = sw_freq;
		debug_period  = period;
}

static inline void Sweep_DutyMax_Then_FreqDown(volatile TW_HRPWM_TypeDef* pwm)
{
    typedef enum
    {
        SWEEP_DUTY_UP = 0,
        SWEEP_FREQ_DOWN
    } sweep_stage_t;

    static sweep_stage_t stage = SWEEP_DUTY_UP;

    static float compb_f = (float)LLC_DEADTIME_COUNT;
    static float sw_freq = LLC_SW_FREQ_MAX;
    static float duty_ratio = 0.0f;

    float period_f;
    float half_period_f;
    int32_t period;
    int32_t half_period;
    int32_t compb_int;
    int32_t compd_int;

    period_f      = (float)HRPWM_FINAL_FREQ / sw_freq;
    half_period_f = period_f * 0.5f;

    if(stage == SWEEP_DUTY_UP)
    {
        compb_f += 0.01f;

        if(compb_f >= (half_period_f - 1.0f))
        {
            compb_f = half_period_f - 1.0f;
            stage = SWEEP_FREQ_DOWN;
        }

        compb_int = (int32_t)(compb_f + 0.5f);
        compd_int = compb_int + (int32_t)(half_period_f + 0.5f);

        pwm->compb = compb_int;
        pwm->compd = compd_int;

        duty_ratio = (compb_f - (float)LLC_DEADTIME_COUNT) /
                     (half_period_f - (float)LLC_DEADTIME_COUNT);

        if(duty_ratio < 0.0f)
            duty_ratio = 0.0f;
        else if(duty_ratio > 1.0f)
            duty_ratio = 1.0f;
    }
    else
    {
        sw_freq -= 0.0001f;
        if(sw_freq <= LLC_SW_FREQ_MIN)
        {
            sw_freq = LLC_SW_FREQ_MIN;
        }

        period_f    = (float)HRPWM_FINAL_FREQ / sw_freq;
        period      = (int32_t)(period_f + 0.5f);
        half_period = period >> 1;

        if(half_period <= LLC_DEADTIME_COUNT)
        {
            half_period = LLC_DEADTIME_COUNT + 1;
            period = half_period << 1;
        }

        compb_f = (float)LLC_DEADTIME_COUNT +
                  duty_ratio * ((float)half_period - (float)LLC_DEADTIME_COUNT);

        if(compb_f < (float)LLC_DEADTIME_COUNT)
            compb_f = (float)LLC_DEADTIME_COUNT;
        else if(compb_f > ((float)half_period - 1.0f))
            compb_f = (float)half_period - 1.0f;

        compb_int = (int32_t)(compb_f + 0.5f);
        compd_int = compb_int + half_period;

        pwm->period = period - 1;
        pwm->compa  = LLC_DEADTIME_COUNT - 1;
        pwm->compb  = compb_int;
        pwm->compc  = half_period + LLC_DEADTIME_COUNT - 1;
        pwm->compd  = compd_int;

        if(pwm->compb >= half_period)
            pwm->compb = half_period - 1;

        if(pwm->compd >= period)
            pwm->compd = period - 1;
    }

    debug_sw_freq = sw_freq;
    debug_period  = (int32_t)(period_f + 0.5f);
    debug_duty    = duty_ratio;
}

void open_loop(void)
{
	static int32_t i = 0;
	
	//SlewRateLimit(open_loop_value, 1000.0f);
	//Value_To_Period(&P1_I_Loop, &phase1_pwm0);
	

	//Sweep_Comp_UpDown(&phase1_pwm0);
	//Sweep_Freq_UpDown_50Duty(&phase1_pwm0);
	Sweep_DutyMax_Then_FreqDown(&phase1_pwm0);
	updata_hrpwm();
}

static inline void Digital_PIcontroller(digitctrl_PI* pi)
{
    float err, integral, u_max, u_min;

    u_max = pi->Umax * 1000.0f;         //1000x extended
    u_min = pi->Umin * 1000.0f;

    err = pi->Ref - pi->Fb;

    integral = (pi->Ki * err) + pi->Integral_sum;
    integral = (integral > u_max) ? u_max: integral;
    integral = (integral < u_min) ? u_min : integral;

    pi->Integral_sum = integral;

    pi ->Out = pi->Kp * err + integral;
    pi ->Out = (pi ->Out > u_max) ? u_max: pi ->Out;
    pi ->Out = (pi ->Out < u_min) ? u_min : pi ->Out;
    pi ->Out = (pi ->Out) * 0.001;
}
/*
static inline void V_Loop_PI(void)
{
    if(cnt10 >= 10)
    {
#ifndef OPEN_LOOP_TEST
        V_Loop.Fb = PhyValue.vout.actual_LPF;

        Digital_PIcontroller(&V_Loop);
        P1.I_Loop.Ref = V_Loop.Out;
        P2.I_Loop.Ref = V_Loop.Out;
#endif

    }
}
*/


void updata_hrpwm()
{
	HRPWM->Common.CR0 |= 0x81FF;							//PWM0~7 & Burst mode
	__NOP();__NOP();__NOP();__NOP();__NOP();
	
	
		HRPWM->PWM[LLC_PHASE1_PWM0].REG.CMPAR = phase1_pwm0.compa;
		HRPWM->PWM[LLC_PHASE1_PWM0].REG.CMPBR = phase1_pwm0.compb;
		HRPWM->PWM[LLC_PHASE1_PWM0].REG.CMPCR = phase1_pwm0.compc;
		HRPWM->PWM[LLC_PHASE1_PWM0].REG.CMPDR = phase1_pwm0.compd;
		HRPWM->PWM[LLC_PHASE1_PWM0].REG.PERR  = phase1_pwm0.period;
	
		HRPWM->PWM[LLC_PHASE2_PWM2].REG.CMPAR = phase1_pwm0.compa;
		HRPWM->PWM[LLC_PHASE2_PWM2].REG.CMPBR = phase1_pwm0.compb;
		HRPWM->PWM[LLC_PHASE2_PWM2].REG.CMPCR = phase1_pwm0.compc;
		HRPWM->PWM[LLC_PHASE2_PWM2].REG.CMPDR = phase1_pwm0.compd;
		HRPWM->PWM[LLC_PHASE2_PWM2].REG.PERR  = phase1_pwm0.period;
		//HRPWM->Master.MPER       = phase1_pwm0.period;
	
	__NOP();__NOP();__NOP();__NOP();__NOP();
	HRPWM->Common.CR0 &= ~(0x81FF);
}