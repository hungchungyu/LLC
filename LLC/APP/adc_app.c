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
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void dc_voltage_slope_calc(void);
/**
* @function void adc_init_app(void)
* @brief    Description: app adc init
* @return   None return.
*/
//
 void adc0_initial_app(ADC_TypeDef *Instance)
 {
	ADC_InitTypeDef       user_adc_init;
    ADC_REG_ComCfgTypeDef user_adc_reg_com_cfg;
    ADC_REG_ChCfgTypeDef  user_adc_reg_ch_cfg;
    ADC_DMA_CfgTypeDef    user_adc_dma_cfg;
    ADC_Cal_CfgTypeDef    user_adc_cal_cfg;

    memset((void *)&user_adc_init,        0x00, sizeof(user_adc_init));
    memset((void *)&user_adc_reg_com_cfg, 0x00, sizeof(user_adc_reg_com_cfg));
    memset((void *)&user_adc_reg_ch_cfg,  0x00, sizeof(user_adc_reg_ch_cfg));
    memset((void *)&user_adc_dma_cfg,     0x00, sizeof(user_adc_dma_cfg));
    memset((void *)&user_adc_cal_cfg,     0x00, sizeof(user_adc_cal_cfg));
	 
//User ADC Init
	 /*2.9V*/
	__LL_SYSCTRL_SpRegWrite_Unlock(SYSCTRL);				
		__LL_SYSCTRL_VREFBUFOutputVol_Set(SYSCTRL,0);
		__LL_SYSCTRL_VREFBUF_En(SYSCTRL);
	__LL_SYSCTRL_SpRegWrite_Lock(SYSCTRL);
	 
	 
    user_adc_init.overrun_mode   = ADC_OVERRUN_DATA_OVERWRITTEN;
    user_adc_init.dual_mode      = ADC_DUAL_MODE_INDEPEND;

    //Oversample Config
    user_adc_init.over_samp_cfg.trig_en   = false;
    user_adc_init.over_samp_cfg.ratio     = ADC_OVER_SAMP_RATIO_8;
    user_adc_init.over_samp_cfg.shift     = ADC_OVER_SAMP_SHIFT_RIGHT_3;
    user_adc_init.over_samp_cfg.norm_mode = ADC_NORM_OVER_SAMP_CONTINUE; // Not one time , continue
    user_adc_init.over_samp_cfg.reg_en    = true;
    user_adc_init.over_samp_cfg.inj_en    = false;
    //user_adc_init.over_samp_cfg.inj_mode  = ADC_OVER_SAMP_MODE_NORMAL;
    LL_ADC_Init(ADC0, &user_adc_init);
    LL_ADC_Init(ADC1, &user_adc_init);


    /*****************************************ADC0*****************************************/
    user_adc_reg_com_cfg.dis_cont_en = false;
    user_adc_reg_com_cfg.conv_mode   = ADC_REG_CONV_SINGLE;
    user_adc_reg_com_cfg.seq_len     = ADC_REG_SEQ_LEN_3;
    user_adc_reg_com_cfg.trig_pol    = ADC_SEQ_TRIG_POL_HW_RISING;
    user_adc_reg_com_cfg.trig_evt    = ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG0;
    LL_ADC_REG_ComCfg(ADC0, &user_adc_reg_com_cfg);

		//ADC0_IN2
    //User ADC Regular Channel Config
    user_adc_reg_ch_cfg.seq_num     = ADC_REG_SEQ_NUM_1;
    user_adc_reg_ch_cfg.ch          = TEMPERATURE_SAMPLE_CHN2;
    user_adc_reg_ch_cfg.done_int_en = false;
    user_adc_reg_ch_cfg.input_mode  = ADC_INPUT_MODE_SINGLE_END;
		user_adc_reg_ch_cfg.samp_time   = ADC_SAMP_TIME_14_CYCLES;
    LL_ADC_REG_ChCfg(ADC0, &user_adc_reg_ch_cfg);


    //User ADC DMA Config
    user_adc_dma_cfg.ch          = TEMPERATURE_SAMPLE_CHN2;
    user_adc_dma_cfg.circ_en     = true;
    user_adc_dma_cfg.half_int_en = false;
    user_adc_dma_cfg.cplt_int_en = false;
    user_adc_dma_cfg.addr        = (uint32_t)&temperature_samp;
    user_adc_dma_cfg.len         = sizeof(temperature_samp);
    LL_ADC_DMA_Cfg(ADC0, &user_adc_dma_cfg);


    //User ADC Calibration Config
    user_adc_cal_cfg.ch       = TEMPERATURE_SAMPLE_CHN2;
    user_adc_cal_cfg.coef_grp = ADC_CAL_COEF_GRP_0;
    user_adc_cal_cfg.sat_dis  = false;
    user_adc_cal_cfg.offset   = 0;
    user_adc_cal_cfg.gain     = 8192;
    LL_ADC_Cal_Cfg(ADC0, &user_adc_cal_cfg);
		
		
		
		
		
		
		//ADC0_IN4
  	user_adc_reg_ch_cfg.seq_num     = ADC_REG_SEQ_NUM_2;
    user_adc_reg_ch_cfg.ch          = CURRENTR_SHARE_SAMPLE_CHN3;
    user_adc_reg_ch_cfg.done_int_en = false;
    user_adc_reg_ch_cfg.input_mode  = ADC_INPUT_MODE_SINGLE_END;
    LL_ADC_REG_ChCfg(ADC0, &user_adc_reg_ch_cfg);


    //User ADC DMA Config
    user_adc_dma_cfg.ch          = CURRENTR_SHARE_SAMPLE_CHN3;
    user_adc_dma_cfg.circ_en     = true;
    user_adc_dma_cfg.half_int_en = false;
    user_adc_dma_cfg.cplt_int_en = false;
    user_adc_dma_cfg.addr        = (uint32_t)&current_share_samp;
    user_adc_dma_cfg.len         = sizeof(current_share_samp);
    LL_ADC_DMA_Cfg(ADC0, &user_adc_dma_cfg);


    //User ADC Calibration Config
    user_adc_cal_cfg.ch       = CURRENTR_SHARE_SAMPLE_CHN3;
    user_adc_cal_cfg.coef_grp = ADC_CAL_COEF_GRP_0;
    user_adc_cal_cfg.sat_dis  = false;
    user_adc_cal_cfg.offset   = 0;
    user_adc_cal_cfg.gain     = 8192;
    LL_ADC_Cal_Cfg(ADC0, &user_adc_cal_cfg);
	
	  //User ADC Regular Channel Config
    user_adc_reg_ch_cfg.seq_num     = ADC_REG_SEQ_NUM_3;
    user_adc_reg_ch_cfg.ch          = CURRENT_OUTPUT_SAMPLE_CHN15;
    user_adc_reg_ch_cfg.done_int_en = false;
    user_adc_reg_ch_cfg.input_mode  = ADC_INPUT_MODE_SINGLE_END;

    LL_ADC_REG_ChCfg(ADC0, &user_adc_reg_ch_cfg);


    //User ADC DMA Config
    user_adc_dma_cfg.ch          = CURRENT_OUTPUT_SAMPLE_CHN15;
    user_adc_dma_cfg.circ_en     = true;
    user_adc_dma_cfg.half_int_en = false;
    user_adc_dma_cfg.cplt_int_en = false;
    user_adc_dma_cfg.addr        = (uint32_t)&llc_current_samp; 
    user_adc_dma_cfg.len         = sizeof(llc_current_samp);
    LL_ADC_DMA_Cfg(ADC0, &user_adc_dma_cfg);


    //User ADC Calibration Config
    user_adc_cal_cfg.ch       = CURRENT_OUTPUT_SAMPLE_CHN15;
    user_adc_cal_cfg.coef_grp = ADC_CAL_COEF_GRP_1;
    user_adc_cal_cfg.sat_dis  = false;
    user_adc_cal_cfg.offset   = 0;
    user_adc_cal_cfg.gain     = 8192;
    LL_ADC_Cal_Cfg(ADC0, &user_adc_cal_cfg);

	
/*****************************************ADC0*****************************************/
 }
 
 void adc1_initial_app(ADC_TypeDef *Instance)
{
	ADC_InitTypeDef       user_adc_init;
    ADC_REG_ComCfgTypeDef user_adc_reg_com_cfg;
    ADC_REG_ChCfgTypeDef  user_adc_reg_ch_cfg;
    ADC_DMA_CfgTypeDef    user_adc_dma_cfg;
    ADC_Cal_CfgTypeDef    user_adc_cal_cfg;

    memset((void *)&user_adc_init,        0x00, sizeof(user_adc_init));
    memset((void *)&user_adc_reg_com_cfg, 0x00, sizeof(user_adc_reg_com_cfg));
    memset((void *)&user_adc_reg_ch_cfg,  0x00, sizeof(user_adc_reg_ch_cfg));
    memset((void *)&user_adc_dma_cfg,     0x00, sizeof(user_adc_dma_cfg));
    memset((void *)&user_adc_cal_cfg,     0x00, sizeof(user_adc_cal_cfg));
    user_adc_reg_com_cfg.dis_cont_en = false;
    user_adc_reg_com_cfg.conv_mode   = ADC_REG_CONV_SINGLE;
    user_adc_reg_com_cfg.seq_len     = ADC_REG_SEQ_LEN_4;
    user_adc_reg_com_cfg.trig_pol    = ADC_SEQ_TRIG_POL_HW_RISING;
    user_adc_reg_com_cfg.trig_evt    = ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG1;
    LL_ADC_REG_ComCfg(ADC1, &user_adc_reg_com_cfg);
	
			//ADC1_IN1
	//User ADC Regular Channel Config
    user_adc_reg_ch_cfg.seq_num     = ADC_REG_SEQ_NUM_1;
    user_adc_reg_ch_cfg.ch          = PRIMARY_CURRENT1_SAMPLE_CHN1;
    user_adc_reg_ch_cfg.done_int_en = false;
    user_adc_reg_ch_cfg.input_mode  = ADC_INPUT_MODE_SINGLE_END;
    user_adc_reg_ch_cfg.samp_time   = ADC_SAMP_TIME_14_CYCLES;

    LL_ADC_REG_ChCfg(ADC1, &user_adc_reg_ch_cfg);

    //User ADC DMA Config
    user_adc_dma_cfg.ch          = PRIMARY_CURRENT1_SAMPLE_CHN1;
    user_adc_dma_cfg.circ_en     = true;
    user_adc_dma_cfg.half_int_en = false;
    user_adc_dma_cfg.cplt_int_en = false;
    user_adc_dma_cfg.addr        = (uint32_t)&primary_current1_samp; 
    user_adc_dma_cfg.len         = sizeof(primary_current1_samp);
    LL_ADC_DMA_Cfg(ADC1, &user_adc_dma_cfg);

    //User ADC Calibration Config
    user_adc_cal_cfg.ch       = PRIMARY_CURRENT1_SAMPLE_CHN1;
    user_adc_cal_cfg.coef_grp = ADC_CAL_COEF_GRP_1;
    user_adc_cal_cfg.sat_dis  = false;
    user_adc_cal_cfg.offset   = 0;
    user_adc_cal_cfg.gain     = 8192;
    LL_ADC_Cal_Cfg(ADC1, &user_adc_cal_cfg);
	
    //User ADC Regular Channel Config
    user_adc_reg_ch_cfg.seq_num     = ADC_REG_SEQ_NUM_2;
    user_adc_reg_ch_cfg.ch          = PRIMARY_CURRENT2_SAMPLE_CHN3;
    user_adc_reg_ch_cfg.done_int_en = false;
    user_adc_reg_ch_cfg.input_mode  = ADC_INPUT_MODE_SINGLE_END;
    user_adc_reg_ch_cfg.samp_time   = ADC_SAMP_TIME_2_CYCLES;
    LL_ADC_REG_ChCfg(ADC1, &user_adc_reg_ch_cfg);

    //User ADC DMA Config
    user_adc_dma_cfg.ch          = PRIMARY_CURRENT2_SAMPLE_CHN3;
    user_adc_dma_cfg.circ_en     = true;
    user_adc_dma_cfg.half_int_en = false;
    user_adc_dma_cfg.cplt_int_en = false;
    user_adc_dma_cfg.addr        = (uint32_t)&primary_current2_samp;
    user_adc_dma_cfg.len         = sizeof(primary_current2_samp);
    LL_ADC_DMA_Cfg(ADC1, &user_adc_dma_cfg);

    //User ADC Calibration Config
    user_adc_cal_cfg.ch       = PRIMARY_CURRENT2_SAMPLE_CHN3;
    user_adc_cal_cfg.coef_grp = ADC_CAL_COEF_GRP_0;
    user_adc_cal_cfg.sat_dis  = false;
    user_adc_cal_cfg.offset   = 0;
    user_adc_cal_cfg.gain     = 8192;
    LL_ADC_Cal_Cfg(ADC1, &user_adc_cal_cfg);
		
		//ADC1_IN5
  	user_adc_reg_ch_cfg.seq_num     = ADC_REG_SEQ_NUM_3;
    user_adc_reg_ch_cfg.ch          = VOLTAGE_OUTPUT_SAMPLE_CHN5;
    user_adc_reg_ch_cfg.done_int_en = false;
    user_adc_reg_ch_cfg.input_mode  = ADC_INPUT_MODE_SINGLE_END;
    LL_ADC_REG_ChCfg(ADC1, &user_adc_reg_ch_cfg);

    //User ADC DMA Config
    user_adc_dma_cfg.ch          = VOLTAGE_OUTPUT_SAMPLE_CHN5;
    user_adc_dma_cfg.circ_en     = true;
    user_adc_dma_cfg.half_int_en = false;
    user_adc_dma_cfg.cplt_int_en = false;
    user_adc_dma_cfg.addr        = (uint32_t)&llc_voltage_samp;
    user_adc_dma_cfg.len         = sizeof(llc_voltage_samp);
    LL_ADC_DMA_Cfg(ADC1, &user_adc_dma_cfg);

    //User ADC Calibration Config
    user_adc_cal_cfg.ch       = VOLTAGE_OUTPUT_SAMPLE_CHN5;
    user_adc_cal_cfg.coef_grp = ADC_CAL_COEF_GRP_0;
    user_adc_cal_cfg.sat_dis  = false;
    user_adc_cal_cfg.offset   = 0;
    user_adc_cal_cfg.gain     = 8192;
    LL_ADC_Cal_Cfg(ADC1, &user_adc_cal_cfg);
	
		//ADC1_IN9
  	user_adc_reg_ch_cfg.seq_num     = ADC_REG_SEQ_NUM_4;
    user_adc_reg_ch_cfg.ch          = CURRENT_REF_SAMPLE_CHN9;
    user_adc_reg_ch_cfg.done_int_en = false;
    user_adc_reg_ch_cfg.input_mode  = ADC_INPUT_MODE_SINGLE_END;
    LL_ADC_REG_ChCfg(ADC1, &user_adc_reg_ch_cfg);

    //User ADC DMA Config
    user_adc_dma_cfg.ch          = CURRENT_REF_SAMPLE_CHN9;
    user_adc_dma_cfg.circ_en     = true;
    user_adc_dma_cfg.half_int_en = false;
    user_adc_dma_cfg.cplt_int_en = false;
    user_adc_dma_cfg.addr        = (uint32_t)&llc_current_ref_samp;
    user_adc_dma_cfg.len         = sizeof(llc_current_ref_samp);
    LL_ADC_DMA_Cfg(ADC1, &user_adc_dma_cfg);

    //User ADC Calibration Config
    user_adc_cal_cfg.ch       = CURRENT_REF_SAMPLE_CHN9;
    user_adc_cal_cfg.coef_grp = ADC_CAL_COEF_GRP_0;
    user_adc_cal_cfg.sat_dis  = false;
    user_adc_cal_cfg.offset   = 0;
    user_adc_cal_cfg.gain     = 8192;
    LL_ADC_Cal_Cfg(ADC1, &user_adc_cal_cfg);
 }

 void adc_all_init(void)
 {
	 adc0_initial_app(ADC0);
	 adc1_initial_app(ADC1);
 }
 void adc_converter_start(void)
 {
	__LL_ADC_REG_Conv_Start(ADC0);
	__LL_ADC_REG_Conv_Start(ADC1);
	__LL_ADC_REG_SeqEnd_INT_En(ADC1);
 }
__SECTION(RAMCODE)
void get_adc_data(void)
{                                                                                        
	llc.vout_raw	=	((float)llc_voltage_samp[0]		)/ADC_FULL_NUM*VOUT_FULL_RANGE;
	llc.vout_raw = llc.vout_raw*feedback_data.f[1];//校准更新
	llc.iout_raw 	=	((float)llc_current_samp[0]-llc_current_ref_samp[0]+55)/ADC_FULL_NUM*IOUT_FULL_RANGE;
	llc.iout_raw=llc.iout_raw*feedback_data.f[0];//校准更新
	llc.iin_phase1_temp  =	((float)primary_current1_samp[0])/ADC_FULL_NUM*I_PRIMARRY_SIDE_FULL;
	llc.iin_phase2_temp  =	((float)primary_current2_samp[0])/ADC_FULL_NUM*I_PRIMARRY_SIDE_FULL;
	llc.temperature_raw  = (temperature_samp[0]<<2);
	llc.iin_phase1_LPF = llc.iin_phase1_LPF + llc.iin_phase1_temp - llc.iin_phase1;
	llc.iin_phase1 = llc.iin_phase1_LPF /500.0f;
	llc.iin_phase2_LPF = llc.iin_phase2_LPF + llc.iin_phase2_temp - llc.iin_phase2;
	llc.iin_phase2 = llc.iin_phase2_LPF /500.0f;

}
int32_t tx_cnt;
__SECTION(RAMCODE)
 void LL_ADC_Norm_REG_SeqEndCallback(ADC_TypeDef *Instance)            //ADC常规序列转换完毕中断
{ 
 	GPIOA->BSR = GPIO_PIN_10;
	get_adc_data();
	llc_handle();
	llc_ok_s_func();    
	if(tx_cnt++==2){
		IWDG->KEYR = 0xAAAA;//独立看门狗喂狗
//		tx_vofa_data.f[0] = llc.vout_raw;
//		tx_vofa_data.f[1] = llc.vout_ref;
//		tx_vofa_data.f[2] = llc.lag_phase_balance_duty;
//		tx_vofa_data.f[3] = llc.temperature_raw;
//		tx_vofa_data.f[4] = llc.iin_phase1;
//		tx_vofa_data.f[5] = llc.fault_num;
		
		tx_vofa_data.f[0] = llc.vout_raw;
		tx_vofa_data.f[1] = llc.iout_raw;
		tx_vofa_data.f[2] = llc.peak_filter_100.result;
		tx_vofa_data.f[3] = llc.vout_err_load-llc.Vo_err;
		tx_vofa_data.f[4] = llc.vloop.output;
		tx_vofa_data.f[5] = llc.iloop.output;
		
		vofa_tx(DMA_CHANNEL_0);
		tx_cnt = 0;
	}
	GPIOA->BSR = GPIO_PIN_10<<16;
}

/**
  * @brief  Initializes the ADC MSP
  * @param  Instance Specifies ADC peripheral
  * @retval None
  */

void LL_ADC_MspInit(ADC_TypeDef *Instance)
{
    GPIO_InitTypeDef ADC_GPIO_Init;

    //Assert param
    assert_param(IS_ADC_ALL_INSTANCE(Instance));

    memset((void *)&ADC_GPIO_Init, 0x00, sizeof(ADC_GPIO_Init));

    //ADC GPIO Common Config
    ADC_GPIO_Init.IntMode   = GPIO_INT_MODE_CLOSE;
    ADC_GPIO_Init.OType     = GPIO_OTYPE_PP;
    ADC_GPIO_Init.Pull      = GPIO_NOPULL;
    ADC_GPIO_Init.Speed     = GPIO_SPEED_FREQ_LOW;
    ADC_GPIO_Init.Alternate = GPIO_AF15_ADC;
    if (Instance == ADC0) {
        //ADC0 Pinmux Config: PA1->ADC0_IN1  PA3->ADC0_IN4 PB0->ADC0_IN15 
        ADC_GPIO_Init.Pin = GPIO_PIN_1 | GPIO_PIN_2;
        LL_GPIO_Init(GPIOA, &ADC_GPIO_Init);
        ADC_GPIO_Init.Pin = GPIO_PIN_0;	
        LL_GPIO_Init(GPIOB, &ADC_GPIO_Init);

        //ADC0 Bus Clock Enable and Soft Reset Release
        LL_RCU_ADC0_ClkEnRstRelease();
 
        //NVIC ADC0 Interrupt Enable
		LL_NVIC_EnableIRQ(ADC0_NORM_IRQn);
    } else if (Instance == ADC1) {
        //ADC1 Pinmux Config: PA4->ADC1_IN16 PA6->ADC1_IN3 PC4->ADC1_IN5
        ADC_GPIO_Init.Pin = GPIO_PIN_4;
        LL_GPIO_Init(GPIOC, &ADC_GPIO_Init);
		ADC_GPIO_Init.Pin = GPIO_PIN_4| GPIO_PIN_6;
        LL_GPIO_Init(GPIOA, &ADC_GPIO_Init);

        //ADC1 Bus Clock Enable and Soft Reset Release
        LL_RCU_ADC1_ClkEnRstRelease();

        //NVIC ADC1 Interrupt Enable
       LL_NVIC_EnableIRQ(ADC1_NORM_IRQn);

    }
}

 /*===================end of adc_app.c===========================*/
