#ifndef _VOFA_APP_H
#define _VOFA_APP_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "tae32g58xx_ll.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define USER_UART_BAUDRATE         3000000   					//波特率
#define USER_UART_TIMEOUT          10       					//发送最大等待时间
#define VOFA_UART2                  UART2 						//VOFA串口使用UART2

/*要接收的数据：即需要调整的参数,如PID的系数，可以通过VOFA发送想要更改的数据给下位机，
通过下位机程序将接收值赋值给相应变量即可。*/
#define REC_DATA_NUM       4           							//要接收的数据的个数
#define REC_DATA_LEN       REC_DATA_NUM+1           			//要接收的数据的字节数（每个数据要求一样的长度，且为字符串形式）
#define REC_BYTE_LEN       REC_DATA_LEN*REC_DATA_NUM          	//要接收的字节数

/*发送的数据：即想要在VOFA上观察的数据，可以是ADC采集的电压或电流的值*/
#define TX_DATA_NUM        6         							//发送数据的个数 
#define TX_DATA_LEN        (TX_DATA_NUM+1)*4

typedef union
{
	float   f[TX_DATA_LEN];
	uint8_t c[TX_DATA_LEN];
}TX_VOFA_DATA;
extern DMA_ChannelETypeDef vofa_dma_ch;
extern float rx_vofa_data[REC_DATA_NUM];   						//串口接收到的字符串数据经过处理后得到的浮点数据
extern TX_VOFA_DATA tx_vofa_data;
extern uint8_t vofa_flog;
void rec_buf(char* rxbuf,float* fc_buf);
void vofa_tx(DMA_ChannelETypeDef ch);
DMA_ChannelETypeDef VOFA_Init(UART_TypeDef *Instance);

#ifdef __cplusplus
}
#endif

#endif 
/******************************** END OF FILE ********************/

