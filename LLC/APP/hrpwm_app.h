/**
  ******************************************************************************
  * @file    tmf5xxx_ll_adc_app.h
  * @author  Degital Power Application Team
  * @brief   Header file of ADC_APP config.h.
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _HRPWM_APP_H_
#define _HRPWM_APP_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll.h"
#include <stdio.h>

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void hrpwm_app_inital(void);
void LL_HRPWM_MspInit(HRPWM_TypeDef *Instance);
void hrpwm_updata_app(void);
void hrpwm_app_start(void);
void hrpwm_app_outdis(void);
void hrpwm_llc_output(void);
void hrpwm_llc_output_dis(void);
void hrpwm_sr_output(void);
void hrpwm_sr_output_dis(void);
void hrpwm_upmos_charge(void);
void hrpwm_upmos_charge_dis(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MAIN_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/


