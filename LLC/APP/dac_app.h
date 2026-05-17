#ifndef _DAC_APP_H_
#define _DAC_APP_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll.h"
#include <stdio.h>
#include <main.h>


#define DAC0_INIT_VALUE                 (2048U)
#define DAC2_INIT_VALUE                 (4095U)

void dac_app_init(void);
void dac_app_start(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MAIN_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

