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
#ifndef _ADC_APP_H_
#define _ADC_APP_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "tae32g58xx_ll.h"
/*************ADC0*****************/
#define TEMPERATURE_SAMPLE_CHN2    		ADC_CH_2	
#define CURRENTR_SHARE_SAMPLE_CHN3		ADC_CH_3
#define CURRENT_OUTPUT_SAMPLE_CHN15		ADC_CH_15

/*************ADC1*****************/
#define	PRIMARY_CURRENT1_SAMPLE_CHN1	ADC_CH_16
#define	PRIMARY_CURRENT2_SAMPLE_CHN3	ADC_CH_3
#define	VOLTAGE_OUTPUT_SAMPLE_CHN5		ADC_CH_5
#define CURRENT_REF_SAMPLE_CHN9			ADC_CH_9


void adc0_initial_app(ADC_TypeDef *Instance);
void adc1_initial_app(ADC_TypeDef *Instance);
void get_adc_data(void);
void adc_all_init(void);
void adc_converter_start(void);
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MAIN_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/


