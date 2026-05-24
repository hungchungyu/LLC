#include "utils.h"
#include "main.h"







void digitctrl_PI_ClearAllKeepKpKi(digitctrl_PI* pi)
{
    float kp;
    float ki;

    kp = pi->Kp;
    ki = pi->Ki;

    pi->Ref          = 0.0f;
    pi->Fb           = 0.0f;
    pi->Integral_sum = 0.0f;
    pi->TargetOut    = 0.0f;
    pi->ActualOut    = 0.0f;
    pi->Umax         = 0.0f;
    pi->Umin         = 0.0f;

    pi->Kp = kp;
    pi->Ki = ki;
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

