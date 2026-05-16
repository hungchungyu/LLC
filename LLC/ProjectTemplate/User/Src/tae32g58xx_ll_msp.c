/**
  ******************************************************************************
  * @file    tae32g58xx_ll_msp.c
  * @author  MCD Application Team
  * @brief   LL MSP module.
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


#define DBG_TAG             "MSP LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


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
/* Private Functions ---------------------------------------------------------*/
/** @defgroup MSP_LL_Private_Functions MSP LL Private Functions
  * @brief    MSP LL Private Functions
  * @{
  */

/**
  * @brief  Initializes the Global MSP
  * @param  None
  * @retval None
  */
void LL_MspInit(void)
{
#ifdef LL_GPIO_MODULE_ENABLED
    //GPIO Msp Init
    LL_RCU_GPIOA_ClkEnRstRelease();
    LL_RCU_GPIOB_ClkEnRstRelease();
    LL_RCU_GPIOC_ClkEnRstRelease();
    LL_RCU_GPIOD_ClkEnRstRelease();
    LL_RCU_GPIOE_ClkEnRstRelease();
    LL_RCU_GPIOF_ClkEnRstRelease();
#endif

#ifdef LL_DMA_MODULE_ENABLED
    //DMA Msp Init
    LL_RCU_DMA_ClkEnRstRelease();

    //DMA Channel Interrupt Enable
#endif

#ifdef LL_EFLASH_MODULE_ENABLED
    //EFLASH Msp Init
    LL_RCU_EFLASH_ClkEnRstRelease();
#endif
}

/**
  * @brief  DeInitializes the Global MSP
  * @param  None
  * @retval None
  */
void LL_MspDeInit(void)
{
#ifdef LL_GPIO_MODULE_ENABLED
    //GPIO Msp DeInit
    LL_RCU_GPIOA_ClkDisRstAssert();
    LL_RCU_GPIOB_ClkDisRstAssert();
    LL_RCU_GPIOC_ClkDisRstAssert();
    LL_RCU_GPIOD_ClkDisRstAssert();
    LL_RCU_GPIOE_ClkDisRstAssert();
    LL_RCU_GPIOF_ClkDisRstAssert();
#endif

#ifdef LL_DMA_MODULE_ENABLED
    //DMA Msp DeInit
    LL_RCU_DMA_ClkDisRstAssert();

    //DMA Channel Interrupt Disable
    LL_NVIC_DisableIRQ(DMA_CH0_IRQn);
    LL_NVIC_DisableIRQ(DMA_CH1_IRQn);
    LL_NVIC_DisableIRQ(DMA_CH2_IRQn);
    LL_NVIC_DisableIRQ(DMA_CH3_IRQn);
    LL_NVIC_DisableIRQ(DMA_CH4_IRQn);
    LL_NVIC_DisableIRQ(DMA_CH5_IRQn);
#endif

#ifdef LL_EFLASH_MODULE_ENABLED
    //EFLASH Msp DeInit
    LL_RCU_EFLASH_ClkDisRstAssert();
#endif
}

/**
  * @brief  Initializes the UART MSP
  * @param  Instance Specifies UART peripheral
  * @retval None
  */
void LL_UART_MspInit(UART_TypeDef *Instance)
{

}

/**
  * @brief  DeInitializes the UART MSP
  * @param  Instance Specifies UART peripheral
  * @retval None
  */
void LL_UART_MspDeInit(UART_TypeDef *Instance)
{

}


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

