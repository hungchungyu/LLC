/**
  ******************************************************************************
  * @file    main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
  *          
  ******************************************************************************
  * @attention
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
#ifndef _INCLUDE_APP_H_
#define _INCLUDE_APP_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "adc_app.h"
#include "hrpwm_app.h"
#include "variables_define_app.h"
#include "gpio_app.h"
#include "llc_app.h"
//#include "uart_app.h"
#include "protection_app.h"
#include "dac_app.h"
#include "cmp_app.h"
//#include "i2c_app.h"
#include "user_vofa.h"
#include "pid_app.h"
#include "iwdg_app.h"
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

