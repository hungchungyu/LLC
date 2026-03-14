/**
  ******************************************************************************
  * @file    APP/Adc_app.c
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
//int16_t adc_test1[512]       __SECTION(SECTION_RAMB);
//int16_t adc_test2[512]       __SECTION(SECTION_RAMB);
//TYPE_ADC_CTL_INIT  adc_ctl_cfg;
//TYPE_ADC_IRQ_CFG   adc_irq_cfg;
//TYPE_ADC_CFG       adc_cfg;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void cmp_app_init(void)
{
    CMP_InitTypeDef user_cmp_init;

    memset((void *)&user_cmp_init, 0x00, sizeof(user_cmp_init));

	
		//CMP2_INP0 CMP1_INP1 CMP7_INP0 CMP8_INP0 CMP3_INP0 CMP0_INP1
    //User CMP Init
    user_cmp_init.rising_int_en  			= false;
    user_cmp_init.falling_int_en 			= false;
    user_cmp_init.output_invert_en 			= false;
	user_cmp_init.hyst						= CMP_HYST_30mv; 
    user_cmp_init.blk_evt					= CMP_BLK_EVT_NONE;
    user_cmp_init.input_src					= CMP_INPUT_SRC_ANOLOG;
    user_cmp_init.neg_in_src				= CMP_NEG_IN_SRC_DACz_OUT;
	user_cmp_init.posi_in_src				= CMP_POSI_IN_SRC_CMP_INP1;
	user_cmp_init.output_dbc				= 200;
    //CMP0
	LL_CMP_Init(CMP0, &user_cmp_init);
	user_cmp_init.output_dbc				= 25;
	LL_CMP_Init(CMP1, &user_cmp_init);
	LL_CMP_Init(CMP7, &user_cmp_init);
		//CMP8
	user_cmp_init.posi_in_src				= CMP_POSI_IN_SRC_CMP_INP0;
	user_cmp_init.output_dbc				= 25;
	user_cmp_init.neg_in_src				= CMP_NEG_IN_SRC_DACy_OUT;
	LL_CMP_Init(CMP8, &user_cmp_init);
	
}

void cmp_app_start(void)
{
	LL_CMP_Start(CMP0);
	LL_CMP_Start(CMP1);
	LL_CMP_Start(CMP7);
	LL_CMP_Start(CMP8);
}
/**
  * @brief  Initializes the CMP MSP
  * @param  Instance Specifies CMP peripheral
  * @return None
  */
void LL_CMP_MspInit(CMP_TypeDef *Instance)
{
    GPIO_InitTypeDef CMP_GPIO_Init;
    //Assert param
    assert_param(IS_CMP_ALL_INSTANCE(Instance));
    memset((void *)&CMP_GPIO_Init, 0x00, sizeof(CMP_GPIO_Init));
    //CMP GPIO Common Config
    CMP_GPIO_Init.IntMode = GPIO_INT_MODE_CLOSE;
    CMP_GPIO_Init.OType   = GPIO_OTYPE_PP;
    CMP_GPIO_Init.Pull    = GPIO_NOPULL;
    CMP_GPIO_Init.Speed   = GPIO_SPEED_FREQ_LOW;
    if (Instance == CMP0) {
        CMP_GPIO_Init.Pin = GPIO_PIN_1;
        CMP_GPIO_Init.Alternate = GPIO_AF15_CMP;
        LL_GPIO_Init(GPIOB, &CMP_GPIO_Init);
        //NVIC CMP0 Interrupt Enable
    }else if (Instance == CMP1) {
        CMP_GPIO_Init.Pin = GPIO_PIN_3;
        CMP_GPIO_Init.Alternate = GPIO_AF15_CMP;
        LL_GPIO_Init(GPIOA, &CMP_GPIO_Init);
	}else if (Instance == CMP7) {
		CMP_GPIO_Init.Pin = GPIO_PIN_8; 
        CMP_GPIO_Init.Alternate =GPIO_AF15_CMP ;
        LL_GPIO_Init(GPIOA, &CMP_GPIO_Init); 
    }else if (Instance == CMP8) {
        //CMP8 Pinmux Config: PC5->CMP8_INP0
        CMP_GPIO_Init.Pin = GPIO_PIN_5;
        CMP_GPIO_Init.Alternate = GPIO_AF15_CMP;
        LL_GPIO_Init(GPIOC, &CMP_GPIO_Init);
    }
	LL_RCU_CMP_ClkEnRstRelease();
	
}
/**
  * @brief  CMP Rising Edge Interrupt Callback
  * @param  Instance Specifies CMP peripheral
  * @return None
  */
