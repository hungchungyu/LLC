/* Includes ------------------------------------------------------------------*/
#include "variables_define_app.h"


LLC_PWM_CmpTypeDef mpwm,phase1_pwm0, phase1_sr_pwm4, phase2_pwm2, phase2_sr_pwm5;

PHY_VALUE_TYPE PhyValue;

volatile StateFlag_t StateFlag = {0};

digitctrl_PI V_Loop =
{
    VOUT_TARGET_LEVEL,
    0.0f,
    V_LOOP_KP,
    V_LOOP_KI,
    0.0f,
    V_LOOP_START_CMD,
    V_LOOP_START_CMD,
    V_LOOP_OUTPUT_MAX,
    V_LOOP_OUTPUT_MIN,
};
volatile ProtectFlag_t ProtectFlag = {0};















TW_LLC_TypeDef llc;









