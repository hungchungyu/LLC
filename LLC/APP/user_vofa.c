/**
  ******************************************************************************
  * @file    App/VOFA_app.c
  * @author  004 
  * @version V1.0.0
  * @date    13-06-2023
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2023 Tai-Action</center></h2>
  *
  *
  *
  ******************************************************************************
  */ 
  
  /* Includes ------------------------------------------------------------------*/
#include "user_vofa.h"
/** @addtogroup Template_Project
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* 宏定义请查看user_vofa.h ----------------------------------------------------*/



/*数据的帧尾（格式固定）*/
uint8_t tail[4] = {0x00, 0x00, 0x80, 0x7f};
DMA_UserCfgTypeDef  dma_user_cfg;

/*串口接收缓冲器：用于接收VOFA发送给下位机的数据*/
char rx_buf[REC_BYTE_LEN];
uint16_t rx_index = 0;

/*发送,接收数据缓冲器，可以在其它c文件中调用*/
float rx_vofa_data[REC_DATA_NUM];   //串口接收到的字符串数据经过处理后得到的浮点数据

TX_VOFA_DATA tx_vofa_data;

uint8_t vofa_flog = 0;

DMA_ChannelETypeDef vofa_dma_ch;

/*将串口接收到的字符串数据解析成float数据*/
void rec_buf(char* rxbuf, float* fc_buf)
{
    uint8_t i, j;
    char buf[REC_DATA_LEN];
    for(i = 0; i < REC_DATA_NUM; i++)
    {
        for(j = 0; j < REC_DATA_LEN; j++)
        {
            buf[j] = rxbuf[i * REC_DATA_LEN + j];
        }
        fc_buf[i] = atof(buf);
    }
}
__SECTION(RAMCODE)
void vofa_tx(DMA_ChannelETypeDef ch)
{
	if((__LL_DMA_IsTransCpltIntPnd(DMA, ch))){
		__LL_DMA_TransCpltIntPnd_Clr(DMA,ch);
		__LL_DMA_Ch_En(DMA, ch);	
	}
}


/*中断回调函数*/
void LL_UART_RxAvailableCallback(UART_TypeDef* Instance)
{
    uint32_t rxsize = __LL_UART_RxFIFOLvl_Get(Instance);
    uint16_t rxdata;


    for(uint32_t icnt = 0; icnt < rxsize; icnt ++)
    {
        rxdata = (Instance->RDR & 0xff);

        if(__LL_UART_IsRxFIFOErr(Instance) != 1)
        {
            rx_buf[rx_index++] = (rxdata & 0xFF);
        }
    }
    if(rx_index >= REC_BYTE_LEN)
    {
        rx_index = 0;
        rec_buf(rx_buf, rx_vofa_data);
    }
}

/* vofa串口初始化 */
DMA_ChannelETypeDef VOFA_Init(UART_TypeDef *Instance)  
{
    UART_InitTypeDef		uart_init;
	UART_HandleTypeDef		*uart_hdl;
    DMA_UserCfgTypeDef		dma_user_cfg;
	DMA_LLCfgTypeDef		pllc_cfg;
	DMA_ChannelETypeDef		ch;
    memset((void*)&uart_init, 0, sizeof(uart_init));
	memset((void *)&dma_user_cfg, 0, sizeof(dma_user_cfg));

    //User UART Init
    uart_init.baudrate = USER_UART_BAUDRATE;
    uart_init.dat_len  = UART_DAT_LEN_8b;
    uart_init.parity   = UART_PARITY_NO;
    uart_init.stop_len = UART_STOP_LEN_1b;
	
	ch = DMA_CHANNEL_0;
	LL_UART_Init(Instance, &uart_init);
	if (Instance == UART0) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_UART0_TX;
    } else if (Instance == UART1) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_UART1_TX;
    } else if (Instance == UART2) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_UART2_TX;
    } else if (Instance == UART3) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_UART3_TX;
    } else if (Instance == UART4) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_UART4_TX;
    }
	//DMA Transmit Default Config
    dma_user_cfg.trans_type 	= DMA_TRANS_TYPE_M2P;
	dma_user_cfg.trans_mode 	= DMA_TRANS_MODE_SINGLE; 
	dma_user_cfg.dst_addr_mode 	= DMA_ADDR_MODE_FIX;
    dma_user_cfg.src_addr_mode 	= DMA_ADDR_MODE_INC;
	dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_8b;
	dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_8b;
    dma_user_cfg.src_hs_ifc 	= DMA_HANDSHAKE_IFC_MEMORY;
    dma_user_cfg.end_arg 		= NULL;
	pllc_cfg.src_burst			= DMA_BURST_LEN_8;
	pllc_cfg.dst_burst			= DMA_BURST_LEN_8;
	pllc_cfg.src_periph_bus		= DMA_PERIPH_BUS_AHB_MST1;
	pllc_cfg.dst_periph_bus		= DMA_PERIPH_BUS_AHB_MST2;
	dma_user_cfg.ll_cfg			= &pllc_cfg;
	LL_DMA_Init(DMA, ch, &dma_user_cfg);
	__LL_DMA_SrcAddr_Set(DMA, ch, (uint32_t)tx_vofa_data.c);
    __LL_DMA_DstAddr_Set(DMA, ch, (uint32_t)&Instance->TDR);
	__LL_DMA_BlockTransCnt_Set(DMA, ch, sizeof(tx_vofa_data.c)/sizeof(tx_vofa_data.c[0]));
	__LL_UART_TxDMA_En(Instance);
    memset(tx_vofa_data.f, 0, sizeof(tx_vofa_data.f));
    tx_vofa_data.c[(4 * TX_DATA_NUM)] 	  = 0x00;
    tx_vofa_data.c[(4 * TX_DATA_NUM) + 1] = 0x00;
    tx_vofa_data.c[(4 * TX_DATA_NUM) + 2] = 0x80;
    tx_vofa_data.c[(4 * TX_DATA_NUM) + 3] = 0x7f;
	__LL_DMA_Ch_En(DMA, ch);
	return ch;
}

/**
* @function void xxx_init_app(void)
* @brief    Description: app xxx init
* @return   None return.
*/




/**
  * @}
  */

/*************************** (C) COPYRIGHT2020Tai-Micro ***** END OF FILE *****/

