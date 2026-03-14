/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @brief   main source file for template project
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"


#define DBG_TAG     "APP"
#define DBG_LVL     DBG_LOG
#include "dbg/tae_dbg.h"


/** @defgroup TAE32G58xx_Examples TAE32G58xx Examples
  * @brief    TAE32G58xx Examples
  * @{
  */

/** @defgroup TAE32G58xx_Template TAE32G58xx Template
  * @brief    TAE32G58xx Template
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/** @addtogroup MAIN_Private_Functions MAIN Private Functions
  * @{
  */
static void SystemClock_Config(void);
/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
void cmpss_initial_app(void);
void NVIC_initial(void);
/** @defgroup MAIN_Private_Functions MAIN Private Functions
  * @brief    MAIN Private Functions
  * @{
  */

/**
  * @brief  main entry
  * @param  None
  * @return status
  */
  

int main(void)
{
    SystemClock_Config();
    LL_Init();
	NVIC_initial();
	gpio_init_app();
	llc_factors_initial();
	VOFA_Init(VOFA_UART2);
	
	feedback_data.c[0] = *(uint32_t *)0x00020000;
	feedback_data.c[1] = *(uint32_t *)0x00020004;
	
	if(feedback_data.f[0]>=1.5f || feedback_data.f[0]<=0.5f)
	{
		feedback_data.f[0]=1.0f;
	}
	llc.OCP_adjust_num = (uint32_t)(IOUT_SC_DAC0_VALUE*feedback_data.f[0]);
	if(llc.OCP_adjust_num>4095)
	{
		llc.OCP_adjust_num  = 4095;
	}
	
	if(feedback_data.f[1]>=1.5f || feedback_data.f[1]<=0.5f)
	{
		feedback_data.f[1]=1.0f;
	}
	
	hrpwm_app_inital();
	adc_all_init(); 
	cmpss_initial_app();
	hrpwm_app_start();
	//iwdg_init();
#if	PWM_TEST_FLAG
	llc.state = State_on;
	hrpwm_llc_output();
	hrpwm_sr_output();
#endif	
	adc_converter_start();
	__LL_HRPWM_Mst_CmpA_INT_En(HRPWM);
    while (1) {
    }
}
void cmpss_initial_app(void)
{
	dac_app_init();
	dac_app_start();
	cmp_app_init();
	cmp_app_start();
}
void NVIC_initial(void)
{
	LL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_3);
	LL_NVIC_SetPriority(HRPWM_COM_IRQn,0,0);
	LL_NVIC_SetPriority(ADC1_NORM_IRQn,2,1);
	LL_NVIC_SetPriority(HRPWM_MST_IRQn,1,0);
}
/**
  * @brief  SYSCLK Config
  * @param  None
  * @return None
  */
static void SystemClock_Config(void)
{
    LL_StatusETypeDef ret;
    RCU_SysclkUserCfgTypeDef sysclk_cfg;
    //SYSCLK Clock Config
    sysclk_cfg.sysclk_src  = SYSCLK_SRC_PLL0DivClk;
    sysclk_cfg.sysclk_freq = 200000000UL;
    sysclk_cfg.pll0clk_src = PLLCLK_SRC_HSI;
    sysclk_cfg.pll0clk_src_freq = HSI_VALUE;
    sysclk_cfg.apb0_clk_div = RCU_CLK_DIV_2;
	
	
    sysclk_cfg.apb1_clk_div = RCU_CLK_DIV_2;
    sysclk_cfg.ahb_clk_div  = RCU_CLK_DIV_1;
    ret = LL_RCU_SysclkInit(RCU, &sysclk_cfg);
    if (ret == LL_OK){
        SystemCoreClockUpdate(sysclk_cfg.sysclk_freq);
		LL_RCU_ADC_ClkCfg(RCU_CLK_SRC_PLL0, RCU_CLK_DIV_4);
        LL_RCU_HRPWM_ClkCfg(RCU_CLK_SRC_PLL0, RCU_CLK_DIV_1);
    }
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    if (file != NULL) {
        LOG_E("Assert failed in %s line %" PRIu32 "", file, line);
    }

    /* Infinite loop */
    while (1) {
        __NOP();
    }
}
#endif

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

