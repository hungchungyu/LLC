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
	
	/*****************input gpio******************/
	GPIO_Init.Alternate = GPIO_AF0_INPUT;
	GPIO_Init.IntMode   = GPIO_INT_MODE_CLOSE;
	GPIO_Init.Pin       = GPIO_PIN_1|GPIO_PIN_2;
	LL_GPIO_Init(GPIOC,&GPIO_Init);

	GPIO_Init.Pin       = GPIO_PIN_2;
	LL_GPIO_Init(GPIOD,&GPIO_Init);
	
	GPIO_Init.Pin       = GPIO_PIN_7|GPIO_PIN_9;
	LL_GPIO_Init(GPIOB,&GPIO_Init);
	
	/*****************output gpio******************/
	GPIO_Init.Alternate = GPIO_AF1_OUTPUT;
	GPIO_Init.OType     = GPIO_OTYPE_PP;
	GPIO_Init.Pull      = GPIO_NOPULL;
	GPIO_Init.Speed     = GPIO_SPEED_FREQ_LOW;
	
	GPIO_Init.Pull      = GPIO_NOPULL;
	GPIO_Init.Pin       = GPIO_PIN_0|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;

	LL_GPIO_Init(GPIOA,&GPIO_Init);
	GPIO_Init.Pull      = GPIO_NOPULL;
	GPIO_Init.Pin       = GPIO_PIN_12;
	LL_GPIO_Init(GPIOC,&GPIO_Init);	
}
