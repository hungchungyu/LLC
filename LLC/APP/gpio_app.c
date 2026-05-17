#include "main.h"
#include "include_app.h"

void gpio_init_app(void)
{
	GPIO_InitTypeDef    GPIO_Init = {0};

	/***************** ON/OFF input gpio ******************/
	GPIO_Init.Alternate = GPIO_AF0_INPUT;
	GPIO_Init.IntMode   = GPIO_INT_MODE_CLOSE;
	GPIO_Init.OType     = GPIO_OTYPE_PP;
	GPIO_Init.Pull      = GPIO_NOPULL;
	GPIO_Init.Speed     = GPIO_SPEED_FREQ_LOW;

	GPIO_Init.Pin       = GPIO_PIN_11;        // PB11, ON/OFF input
	LL_GPIO_Init(GPIOB, &GPIO_Init);


	/***************** TEST output gpio ******************/
	GPIO_Init.Alternate = GPIO_AF1_OUTPUT;
	GPIO_Init.IntMode   = GPIO_INT_MODE_CLOSE;
	GPIO_Init.OType     = GPIO_OTYPE_PP;
	GPIO_Init.Pull      = GPIO_NOPULL;
	GPIO_Init.Speed     = GPIO_SPEED_FREQ_LOW;

	/* PA5, PA7 : TP2, TP4 */
	/* PA10, PA11 : original test GPIO */
	GPIO_Init.Pin       = GPIO_PIN_5 | GPIO_PIN_7 |
												GPIO_PIN_10 | GPIO_PIN_11;
	LL_GPIO_Init(GPIOA, &GPIO_Init);

	/* PB14, PB15 : original test GPIO */
	GPIO_Init.Pin       = GPIO_PIN_14 | GPIO_PIN_15;
	LL_GPIO_Init(GPIOB, &GPIO_Init);


	/***************** GPIO default output level ******************/
	LL_GPIO_WritePin(GPIOA, GPIO_PIN_5,  GPIO_PIN_RESET);   // TP2
	LL_GPIO_WritePin(GPIOA, GPIO_PIN_7,  GPIO_PIN_RESET);   // TP4

	LL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
	LL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);

	LL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	LL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);


	/***************** DAC output gpio ******************/
	GPIO_Init.Alternate = GPIO_AF15_DAC0;
	GPIO_Init.IntMode   = GPIO_INT_MODE_CLOSE;
	GPIO_Init.OType     = GPIO_OTYPE_PP;
	GPIO_Init.Pull      = GPIO_NOPULL;
	GPIO_Init.Speed     = GPIO_SPEED_FREQ_LOW;

	/* PA4, PA6 : DAC output */
	GPIO_Init.Pin       = GPIO_PIN_4 | GPIO_PIN_6;
	LL_GPIO_Init(GPIOA, &GPIO_Init);
}
