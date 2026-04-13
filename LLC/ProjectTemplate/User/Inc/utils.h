#ifndef _UTILS_H_
#define _UTILS_H_

typedef volatile struct digitctrl_PI{
    float Ref;                // Input reference
    float Fb;                 // Feedback

    float Kp;                 // Proportional gain
    float Ki;                 // Integral gain
    float Integral_sum;       // Integral storage
    float Umax;               // Upper control saturation limit
    float Umin;               // Lower control saturation limit
    float Out;

} digitctrl_PI;

extern digitctrl_PI P1_I_Loop;


void open_loop(void);
void updata_hrpwm();

#endif