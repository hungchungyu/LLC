#ifndef _UTILS_H_
#define _UTILS_H_

#include "variables_define_app.h"

#define LLC_MAX_PWM_SWITCHING_FREQUENCY_HZ   	((float)(LLC_SW_FREQ_MAX * 1000.0f))   // 200kHz
#define LLC_MIN_PWM_SWITCHING_FREQUENCY_HZ   	((float)(LLC_SW_FREQ_MIN * 1000.0f))   // 100kHz

#define LLC_PRIM_PWM_DEADBAND_NS							((float)(LLC_DEADTIME * 1e-9f))     // 150ns
#define LLC_PWMSYSCLOCK_FREQ_HZ   						((float)(3.2f * 1000.0f * 1000.0f * 1000.0f))   // 3.2GHz

#define LLC_PWM_DEADBAND_COUNT               ((uint32_t)((LLC_PWMSYSCLOCK_FREQ_HZ * LLC_PRIM_PWM_DEADBAND_NS) + 0.5f))

#define LLC_MAX_FREQ_PERIOD_COUNT            ((uint32_t)((LLC_PWMSYSCLOCK_FREQ_HZ / LLC_MAX_PWM_SWITCHING_FREQUENCY_HZ) + 0.5f))
#define LLC_MIN_FREQ_PERIOD_COUNT            ((uint32_t)((LLC_PWMSYSCLOCK_FREQ_HZ / LLC_MIN_PWM_SWITCHING_FREQUENCY_HZ) + 0.5f))


static inline float ClampFloat(float x, float min, float max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

static inline float LLC_SlewValue(float* current, float* target)
{
    float rise_step = 0.00001f;
    float fall_step = 0.00001f;

    *target  = ClampFloat(*target,  -0.5f, 1.0f);
    *current = ClampFloat(*current, -0.5f, 1.0f);

    if(*target > *current)
    {
        *current += rise_step;

        if(*current > *target)
        {
            *current = *target;
        }
    }
    else if(*target < *current)
    {
        *current -= fall_step;

        if(*current < *target)
        {
            *current = *target;
        }
    }

    *current = ClampFloat(*current, -0.5f, 1.0f);

    return *current;
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
void digitctrl_PI_ClearAllKeepKpKi(digitctrl_PI* pi);
#endif