#ifndef _GPIO_APP_H_
#define _GPIO_APP_H_

#include "tae32g58xx_ll.h"
#include <stdio.h>



/***************** ON/OFF Input Define ******************/
#define ONOFF_PORT          GPIOB
#define ONOFF_PIN           GPIO_PIN_11

#define ONOFF_VALUE()       LL_GPIO_ReadPin(ONOFF_PORT, ONOFF_PIN)

/***************** TEST GPIO Define ******************/

/* PA4~PA7 : TP1~TP4 */
#define TP1_PORT        GPIOA
#define TP1_PIN         GPIO_PIN_4

#define TP2_PORT        GPIOA
#define TP2_PIN         GPIO_PIN_5

#define TP3_PORT        GPIOA
#define TP3_PIN         GPIO_PIN_6

#define TP4_PORT        GPIOA
#define TP4_PIN         GPIO_PIN_7

#define TP1_HIGH()    LL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)
#define TP1_LOW()     LL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define TP1_TOGGLE()  LL_GPIO_TogglePin(GPIOA, GPIO_PIN_4)

#define TP2_HIGH()    LL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET)
#define TP2_LOW()     LL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET)
#define TP2_TOGGLE()  LL_GPIO_TogglePin(GPIOA, GPIO_PIN_5)

#define TP3_HIGH()    LL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET)
#define TP3_LOW()     LL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET)
#define TP3_TOGGLE()  LL_GPIO_TogglePin(GPIOA, GPIO_PIN_6)

#define TP4_HIGH()    LL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET)
#define TP4_LOW()     LL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET)
#define TP4_TOGGLE()  LL_GPIO_TogglePin(GPIOA, GPIO_PIN_7)

/* PA10, PA11 : original test GPIO */
#define TEST1_PORT      GPIOA
#define TEST1_PIN       GPIO_PIN_10

#define TEST2_PORT      GPIOA
#define TEST2_PIN       GPIO_PIN_11

#define TEST1_HIGH()    LL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET)
#define TEST1_LOW()     LL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET)
#define TEST1_TOGGLE()  LL_GPIO_TogglePin(GPIOA, GPIO_PIN_10)

#define TEST2_HIGH()    LL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET)
#define TEST2_LOW()     LL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET)
#define TEST2_TOGGLE()  LL_GPIO_TogglePin(GPIOA, GPIO_PIN_11)


void gpio_init_app(void);
 
#endif



