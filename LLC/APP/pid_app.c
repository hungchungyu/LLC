#include "main.h"
#include "utils.h"
#include "pid_app.h"

__SECTION(RAMCODE)
void calc_PI(digitctrl_PI* pi)
{
    float err, integral, u_max, u_min;

    u_max = pi->Umax * 1000.0f;         //1000x extended
    u_min = pi->Umin * 1000.0f;

    err = pi->Ref - pi->Fb;

    integral = (pi->Ki * err) + pi->Integral_sum;
    integral = (integral > u_max) ? u_max: integral;
    integral = (integral < u_min) ? u_min : integral;

    pi->Integral_sum = integral;

    pi ->TargetOut = pi->Kp * err + integral;
    pi ->TargetOut = (pi ->TargetOut > u_max) ? u_max: pi ->TargetOut;
    pi ->TargetOut = (pi ->TargetOut < u_min) ? u_min : pi ->TargetOut;
    pi ->TargetOut = (pi ->TargetOut) * 0.001;
}


__SECTION(RAMCODE)
void iir_calculation (cIIR_TypeDef *iir,float x)
{

}
