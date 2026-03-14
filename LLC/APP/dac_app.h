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
#ifndef _DAC_APP_H_
#define _DAC_APP_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll.h"
#include <stdio.h>
#include <main.h>
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#define VOUT_OV_VOLTAG       		58
#define VOUT_OV_DAC8_VALUE			(int32_t)(VOUT_OV_VOLTAG/VOUT_FULL_RANGE*4096)
	
#define I_PRIMARRY_OC             	28.0
#define I_PRIMARRY_OC_DAC1_VALUE	(int32_t)((float)(I_PRIMARRY_OC/I_PRIMARRY_SIDE_FULL)*4096)

#define IOUT_SC_DAC					IOUT_HOC
#define IOUT_SC_DAC0_VALUE			(int32_t)(IOUT_HOC/IOUT_FULL_RANGE*4096)

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void dac_app_init(void);
void dac_app_start(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MAIN_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

