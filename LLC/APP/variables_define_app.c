/* Includes ------------------------------------------------------------------*/
#include "variables_define_app.h"


LLC_PWM_CmpTypeDef mpwm,phase1_pwm0, phase1_sr_pwm4, phase2_pwm2, phase2_sr_pwm5;

PHY_VALUE_TYPE PhyValue;

StateFlag_t StateFlag = {0};

digitctrl_PI V_Loop = {0};
ProtectFlag_t ProtectFlag = {0};















TW_LLC_TypeDef llc;









