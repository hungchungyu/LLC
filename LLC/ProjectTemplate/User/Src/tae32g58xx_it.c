 /**
  ******************************************************************************
  * @file    tae32g58xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
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
#include "tae32g58xx_it.h"


/** @addtogroup TAE32G58xx_Examples
  * @{
  */

/** @addtogroup TAE32G58xx_Template
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup TAE32G58xx_IT_Exported_Functions TAE32G58xx IT Exported Functions
  * @brief    TAE32G58xx IT Exported Functions
  * @{
  */

/** @defgroup TAE32G58xx_IT_Exported_Functions_Group1 Cortex-M4 Processor Exceptions Handlers
  * @brief    Cortex-M4 Processor Exceptions Handlers
  * @{
  */

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1) {
    }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1) {
    }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1) {
    }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1) {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}
/********************************************APP IRQHandler****************************************/
__SECTION(RAMCODE)
void ADC1_NORM_IRQHandler(void)
{
	uint32_t int_en, int_pending;
	
    //ADC Normal All Interrupt Enalbe and Pending Get
    int_en = __LL_ADC_NormAllIntEn_Get(ADC1);
    int_pending = __LL_ADC_NormAllIntPending_Get(ADC1);

	    //Injected Sequence End Interrupt Handler
    if ((int_en & ADC1_IER_EOSIE_Msk) && (int_pending & ADC1_ISR_EOS_Msk)) {
        //Clear Interrupt Pending
        __LL_ADC_REG_SeqEndIntPnd_Clr(ADC1);
		LL_ADC_Norm_REG_SeqEndCallback(ADC1);
	}
	
}

/**
  * @brief  This function handles HRPWM Common  interrupt request.
  * @param  None
  * @retval None
  */
__SECTION(RAMCODE)
void HRPWM_COMM_IRQHandler(void)
{
	IWDG->KEYR = 0xAAAA;//∂¿¡¢ø¥√≈π∑Œππ∑
	LL_HRPWM_Comm_IRQHandler(HRPWM);
}
/**
  * @}
  */
__SECTION(RAMCODE)
void HRPWM_MST_IRQHandler(void)
{
	uint32_t int_en, int_pending;
    int_en = __LL_HRPWM_Mst_AllIntEn_Get(HRPWM);
    int_pending = __LL_HRPWM_Mst_AllIntPnd_Get(HRPWM);
    //Compare A Interrupt Handler
    if ((int_en & HRPWM_MST_MDIER_MCMPAIE_Msk) && (int_pending & HRPWM_MST_MISR_MCMPA_Msk)) {
        //Clear Interrupt Pending
        __LL_HRPWM_Mst_CmpAIntPnd_Clr(HRPWM);
        //Callback
        LL_HRPWM_Mst_CmpACallback(HRPWM);
    }
}
/**
  * @brief  This function handles ADC1 Sample interrupt request.
  * @param  None
  * @retval None
  */
void ADC1_SAMP_IRQHandler(void)		// Not used?
{
#ifdef LL_ADC_MODULE_ENABLED
    LL_ADC_Samp_IRQHandler(ADC1);
#endif
}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
#ifdef LL_MODULE_ENABLED
    LL_IncTick();
#endif

#ifdef LL_CORTEX_MODULE_ENABLED
    LL_SYSTICK_IRQHandler();
#endif
}

/**
  * @}
  */


/******************************************************************************/
/*                  TAE32G58xx Peripherals Interrupt Handlers                 */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_tae32g58xx.c).                                              */
/******************************************************************************/

/** @defgroup TAE32G58xx_IT_Exported_Functions_Group2 XXX Peripherals Interrupt Handlers
  * @brief    XXX Peripherals Interrupt Handlers
  * @{
  */

/**
  * @brief  This function handles XXX interrupt request.
  * @param  None
  * @retval None
  */
/*void XXX_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

