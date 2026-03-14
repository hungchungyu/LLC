/**
  ******************************************************************************
  * @file    APP/dac_app.c
  * @author 004 
  * @version V1.0.0
  * @date    17-04-2020
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2020 Tai-Micro</center></h2>
  *
  *
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "include_app.h"
/** @addtogroup Template_Project
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
* @function void adc_init_app(void)
* @brief    Description: app adc init
* @return   None return.
*/
/**
  * @brief  User DAC Init
  * @param  Instance Specifies DAC peripheral
  * @return None
  */

void dac_app_init(void)
{
    DAC_InitTypeDef user_dac_init;
    memset((void *)&user_dac_init, 0x00, sizeof(user_dac_init));
    //User DAC Init
    user_dac_init.trig_en = false;
	//DAC Init
    LL_DAC_Init(DAC0, &user_dac_init);
	LL_DAC_Init(DAC1, &user_dac_init);
	LL_DAC_Init(DAC7, &user_dac_init);
	LL_DAC_Init(DAC8, &user_dac_init);
	
	LL_DAC_ValueSet(DAC0, llc.OCP_adjust_num);//LLC  Isec
	LL_DAC_ValueSet(DAC1,I_PRIMARRY_OC_DAC1_VALUE);//LLC Ip1    I_PRIMARRY_OC_DAC1_VALUE
	LL_DAC_ValueSet(DAC7,I_PRIMARRY_OC_DAC1_VALUE);//LLC Ip2    I_PRIMARRY_OC_DAC1_VALUE
	LL_DAC_ValueSet(DAC8, VOUT_OV_DAC8_VALUE);//LLC  Vo
}

void dac_app_start(void)
{
	LL_DAC_Start(DAC0);//LLC  Isec
	LL_DAC_Start(DAC1);//LLC Ip1
	LL_DAC_Start(DAC7);//LLC Ip2
	LL_DAC_Start(DAC8);//LLC  Vo
}	
/**
  * @brief  Initializes the DAC MSP
  * @param  Instance Specifies DAC peripheral
  * @return None
  */
void LL_DAC_MspInit(DAC_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_DAC_ALL_INSTANCE(Instance));
	    //DAC GPIO Common Config
	LL_RCU_DAC_ClkEnRstRelease();
}
