#ifndef _PID_APP_H_
#define _PID_APP_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll.h"
#include <stdio.h>
#include "variables_define_app.h"

typedef struct
{
    float Ref;
    float Fb;
    float Kp;
    float Ki;
    float Integral_sum;

    float TargetOut;
    float ActualOut;

    float Umax;
    float Umin;

} digitctrl_PI;

void calc_PI(digitctrl_PI* pi);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MAIN_H_ */








































