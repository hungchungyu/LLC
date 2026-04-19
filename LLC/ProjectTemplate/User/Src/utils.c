#include "utils.h"
#include "main.h"
#include "variables_define_app.h"


#define LLC_MAX_PWM_SWITCHING_FREQUENCY_HZ   	((float)(200.0f * 1000.0f))   // 200kHz
#define LLC_MIN_PWM_SWITCHING_FREQUENCY_HZ   	((float)(100.0f * 1000.0f))   // 100kHz

#define LLC_PRIM_PWM_DEADBAND_NS							((float)(150.0f * 1e-9f))     // 150ns
#define LLC_PWMSYSCLOCK_FREQ_HZ   						((float)(3.2f * 1000.0f * 1000.0f * 1000.0f))   // 3.2GHz

#define LLC_PWM_DEADBAND_COUNT               ((uint32_t)((LLC_PWMSYSCLOCK_FREQ_HZ * LLC_PRIM_PWM_DEADBAND_NS) + 0.5f))

#define LLC_MAX_FREQ_PERIOD_COUNT            ((uint32_t)((LLC_PWMSYSCLOCK_FREQ_HZ / LLC_MAX_PWM_SWITCHING_FREQUENCY_HZ) + 0.5f))
#define LLC_MIN_FREQ_PERIOD_COUNT            ((uint32_t)((LLC_PWMSYSCLOCK_FREQ_HZ / LLC_MIN_PWM_SWITCHING_FREQUENCY_HZ) + 0.5f))


digitctrl_PI P1_I_Loop;
float open_loop_value = -500.0f;

typedef struct
{
    uint32_t period;
    uint32_t compa;
    uint32_t compb;
    uint32_t compc;
    uint32_t compd;
} LLC_PWM_CmpTypeDef;

LLC_PWM_CmpTypeDef phase1_pwm, phase2_pwm;

/* Clamp value within range */
static inline float ClampFloat(float x, float min, float max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

static inline void CtrlToPwm(float value, LLC_PWM_CmpTypeDef *pwm_cmp)
{
    float freq_hz;
    float period_f;
    float duty_f;
    float ratio;

    uint32_t period;
    uint32_t half_period;
    uint32_t duty_cnt;
    uint32_t min_duty_cnt;
    uint32_t max_duty_cnt;

    if (pwm_cmp == 0u)
    {
        return;
    }

    /* Clamp input command to valid range */
    value = ClampFloat(value, -0.5f, 1.0f);

    if (value <= 0.0f)
    {
        /* ---------------------------------------------
         * Soft-start region
         * value: -0.5 ~ 0
         * freq : fixed at max frequency
         * duty : LLC_PWM_DEADBAND_COUNT ~ max safe 50%
         * --------------------------------------------- */
        freq_hz = LLC_MAX_PWM_SWITCHING_FREQUENCY_HZ;

        period_f = LLC_PWMSYSCLOCK_FREQ_HZ / freq_hz;
        period   = (uint32_t)(period_f + 0.5f);

        half_period  = period >> 1;
        min_duty_cnt = LLC_PWM_DEADBAND_COUNT;
        max_duty_cnt = half_period - 1u;

        if (max_duty_cnt < min_duty_cnt)
        {
            max_duty_cnt = min_duty_cnt;
        }

        /* Map:
         * value = -0.5 -> duty = LLC_PWM_DEADBAND_COUNT
         * value =  0.0 -> duty = max_duty_cnt
         */
        ratio  = (value + 0.5f) / 0.5f;
        duty_f = (float)min_duty_cnt +
                 ((float)(max_duty_cnt - min_duty_cnt) * ratio);

        duty_cnt = (uint32_t)(duty_f + 0.5f);

        if (duty_cnt < min_duty_cnt)
        {
            duty_cnt = min_duty_cnt;
        }
        if (duty_cnt > max_duty_cnt)
        {
            duty_cnt = max_duty_cnt;
        }
    }
    else
    {
        /* ---------------------------------------------
         * Normal control region
         * value: 0 ~ 1
         * freq : max frequency -> min frequency
         * duty : fixed at max safe 50%
         * --------------------------------------------- */
        freq_hz = LLC_MAX_PWM_SWITCHING_FREQUENCY_HZ -
                  ((LLC_MAX_PWM_SWITCHING_FREQUENCY_HZ - LLC_MIN_PWM_SWITCHING_FREQUENCY_HZ) * value);

        period_f = LLC_PWMSYSCLOCK_FREQ_HZ / freq_hz;
        period   = (uint32_t)(period_f + 0.5f);

        half_period  = period >> 1;
        min_duty_cnt = LLC_PWM_DEADBAND_COUNT;
        max_duty_cnt = half_period - 1u;

        if (max_duty_cnt < min_duty_cnt)
        {
            max_duty_cnt = min_duty_cnt;
        }

        duty_cnt = max_duty_cnt;
    }

    pwm_cmp->period = period - 1u;
    pwm_cmp->compa  = LLC_PWM_DEADBAND_COUNT;
    pwm_cmp->compb  = duty_cnt;
    pwm_cmp->compc  = half_period + LLC_PWM_DEADBAND_COUNT;
    pwm_cmp->compd  = half_period + duty_cnt;
}
static inline float LLC_SlewValue(float target)
{
    static float current = -0.5f;

    float rise_step = 0.00001f;
    float fall_step = 0.00001f;

    target = ClampFloat(target, -0.5f, 1.0f);

    if (target > current)
    {
        current += rise_step;
        if (current > target)
        {
            current = target;
        }
    }
    else if (target < current)
    {
        current -= fall_step;
        if (current < target)
        {
            current = target;
        }
    }

    current = ClampFloat(current, -0.5f, 1.0f);

    return current;
}
void open_loop(void)
{
	static float ctrl_value = 1.0;
	float pwm_value = LLC_SlewValue(ctrl_value);

	CtrlToPwm(pwm_value, &phase1_pwm);
	CtrlToPwm(pwm_value, &phase2_pwm);
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
	
	
		HRPWM->PWM[LLC_PHASE1_PWM0].REG.CMPAR = phase1_pwm.compa;
		HRPWM->PWM[LLC_PHASE1_PWM0].REG.CMPBR = phase1_pwm.compb;
		HRPWM->PWM[LLC_PHASE1_PWM0].REG.CMPCR = phase1_pwm.compc;
		HRPWM->PWM[LLC_PHASE1_PWM0].REG.CMPDR = phase1_pwm.compd;
		HRPWM->PWM[LLC_PHASE1_PWM0].REG.PERR  = phase1_pwm.period;
	
		HRPWM->PWM[LLC_PHASE2_PWM2].REG.CMPAR = phase2_pwm.compa;
		HRPWM->PWM[LLC_PHASE2_PWM2].REG.CMPBR = phase2_pwm.compb;
		HRPWM->PWM[LLC_PHASE2_PWM2].REG.CMPCR = phase2_pwm.compc;
		HRPWM->PWM[LLC_PHASE2_PWM2].REG.CMPDR = phase2_pwm.compd;
		HRPWM->PWM[LLC_PHASE2_PWM2].REG.PERR  = phase2_pwm.period;

	__NOP();__NOP();__NOP();__NOP();__NOP();
	HRPWM->Common.CR0 &= ~(0x81FF);
}