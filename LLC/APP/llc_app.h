/**
  ******************************************************************************
  * @file    ????
  * @author  TW
  * @version V1.1.0
  * @date    xx-xx-20xx(??)
  * @brief   ????
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 TXMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LLC_APP_H__
#define __LLC_APP_H__
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#include "main.h"
#include <string.h>
#include <stdio.h>
/** @addtogroup ???
  * @{
  */
void llc_state_idle(void);
void llc_state_rampup(void);
void llc_state_on(void);
void llc_state_fault(void);
void llc_handle(void);
void voltage_loop_caculation_app(void);
void current_loop_caculation_app(void);    
void upper_mos_charge (void);
void llc_state_enable(void);
void pwm_data_calc(void);
void dc_voltage_slope_calc(void) ;
int32_t abs_user (int32_t data_in);
void phase2phase_current_balance_func(void);
void llc_ok_s_func(void);
#ifdef __cplusplus
}
#endif

#endif //__XXXXX_H__

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT TX Microelectronics *****END OF FILE****/
