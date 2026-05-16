#ifndef __LLC_APP_H__
#define __LLC_APP_H__
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include <string.h>
#include <stdio.h>

void llc_state_idle(void);
void llc_state_rampup(void);
void llc_state_on(void);
void llc_state_fault(void);

void voltage_loop_caculation_app(void);
void current_loop_caculation_app(void);    
void upper_mos_charge (void);
void llc_state_enable(void);

int32_t abs_user (int32_t data_in);


#ifdef __cplusplus
}
#endif

#endif //__XXXXX_H__

/************************ (C) COPYRIGHT TX Microelectronics *****END OF FILE****/
