/**
  ******************************************************************************
  * @file    APP/gpio_app.c
  * @author 004 
  * @version V1.0.0
  * @date    12-03-2021
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
* @function void gpio_init_app(void)
* @brief    Description: app gpio init
* @return   None return.
*/
void gpio_init_app(void)
{
    GPIO_InitTypeDef    GPIO_Init = {0};       
	
		/***************** TEST output gpio******************/
		GPIO_Init.Alternate = GPIO_AF1_OUTPUT;
		GPIO_Init.IntMode   = GPIO_INT_MODE_CLOSE;
		GPIO_Init.OType     = GPIO_OTYPE_PP;						// Push-Pull
		GPIO_Init.Pull      = GPIO_NOPULL;							// No pull up/down
		GPIO_Init.Speed     = GPIO_SPEED_FREQ_LOW;
		
		GPIO_Init.Pin       = GPIO_PIN_10|GPIO_PIN_11;	// PA10, PA11
		LL_GPIO_Init(GPIOA,&GPIO_Init);
		GPIO_Init.Pin       = GPIO_PIN_14|GPIO_PIN_15;	// PB14, PB15
		LL_GPIO_Init(GPIOB,&GPIO_Init);
		
		LL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
		LL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
		
		LL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		LL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
}
