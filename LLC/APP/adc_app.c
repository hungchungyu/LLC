#include "main.h"
#include "include_app.h"
#include "tae32g58xx_ll_gpio.h"

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

    /* VREF buffer output voltage = 2.9 V */
    __LL_SYSCTRL_SpRegWrite_Unlock(SYSCTRL);
    __LL_SYSCTRL_VREFBUFOutputVol_Set(SYSCTRL, 0);
    __LL_SYSCTRL_VREFBUF_En(SYSCTRL);
    __LL_SYSCTRL_SpRegWrite_Lock(SYSCTRL);

    user_adc_init.overrun_mode = ADC_OVERRUN_DATA_OVERWRITTEN;
    user_adc_init.dual_mode    = ADC_DUAL_MODE_INDEPEND;

    /* Oversample config */
    user_adc_init.over_samp_cfg.trig_en   = false;
    user_adc_init.over_samp_cfg.ratio     = ADC_OVER_SAMP_RATIO_8;
    user_adc_init.over_samp_cfg.shift     = ADC_OVER_SAMP_SHIFT_RIGHT_3;
    user_adc_init.over_samp_cfg.norm_mode = ADC_NORM_OVER_SAMP_CONTINUE;
    user_adc_init.over_samp_cfg.reg_en    = true;
    user_adc_init.over_samp_cfg.inj_en    = false;

    LL_ADC_Init(Instance, &user_adc_init);

    /************************ ADC0 Regular Common Config ************************/

    user_adc_reg_com_cfg.dis_cont_en = false;
    user_adc_reg_com_cfg.conv_mode   = ADC_REG_CONV_SINGLE;

    /* 4 regular channels: SEQ1 ~ SEQ4 */
    user_adc_reg_com_cfg.seq_len     = ADC_REG_SEQ_LEN_4;

    /* Hardware trigger from HRPWM ADCTRG0 */
    user_adc_reg_com_cfg.trig_pol    = ADC_SEQ_TRIG_POL_HW_RISING;
    user_adc_reg_com_cfg.trig_evt    = ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG0;

    LL_ADC_REG_ComCfg(Instance, &user_adc_reg_com_cfg);

    /************************ ADC0_IN7 : VOUT ************************/

    user_adc_reg_ch_cfg.seq_num     = ADC_REG_SEQ_NUM_1;
    user_adc_reg_ch_cfg.ch          = VOUT_SAMPLE_CHN7;
    user_adc_reg_ch_cfg.done_int_en = false;
    user_adc_reg_ch_cfg.input_mode  = ADC_INPUT_MODE_SINGLE_END;
    user_adc_reg_ch_cfg.samp_time   = ADC_SAMP_TIME_14_CYCLES;

    LL_ADC_REG_ChCfg(Instance, &user_adc_reg_ch_cfg);

    /************************ ADC0_IN8 : RSENSE1 ************************/

    user_adc_reg_ch_cfg.seq_num     = ADC_REG_SEQ_NUM_2;
    user_adc_reg_ch_cfg.ch          = RSENSE1_SAMPLE_CHN3;
    user_adc_reg_ch_cfg.done_int_en = false;
    user_adc_reg_ch_cfg.input_mode  = ADC_INPUT_MODE_SINGLE_END;
    user_adc_reg_ch_cfg.samp_time   = ADC_SAMP_TIME_14_CYCLES;

    LL_ADC_REG_ChCfg(Instance, &user_adc_reg_ch_cfg);

    /************************ ADC0_IN1 : VP ************************/

    user_adc_reg_ch_cfg.seq_num     = ADC_REG_SEQ_NUM_3;
    user_adc_reg_ch_cfg.ch          = VP_SAMPLE_CHN1;
    user_adc_reg_ch_cfg.done_int_en = false;
    user_adc_reg_ch_cfg.input_mode  = ADC_INPUT_MODE_SINGLE_END;
    user_adc_reg_ch_cfg.samp_time   = ADC_SAMP_TIME_14_CYCLES;

    LL_ADC_REG_ChCfg(Instance, &user_adc_reg_ch_cfg);

    /************************ ADC0_IN2 : VN ************************/

    user_adc_reg_ch_cfg.seq_num     = ADC_REG_SEQ_NUM_4;
    user_adc_reg_ch_cfg.ch          = VN_SAMPLE_CHN2;
    user_adc_reg_ch_cfg.done_int_en = false;
    user_adc_reg_ch_cfg.input_mode  = ADC_INPUT_MODE_SINGLE_END;
    user_adc_reg_ch_cfg.samp_time   = ADC_SAMP_TIME_14_CYCLES;

    LL_ADC_REG_ChCfg(Instance, &user_adc_reg_ch_cfg);

	
/*****************************************ADC0*****************************************/
 }
 
 void adc1_initial_app(ADC_TypeDef *Instance)
{
	
 }

 void adc_all_init(void)
 {
	 adc0_initial_app(ADC0);
 }
 void adc_converter_start(void)
 {
	__LL_ADC_REG_Conv_Start(ADC0);
	__LL_ADC_REG_SeqEnd_INT_En(ADC0);
 }
 
 /*
 * First-order LPF coefficient:
 *
 * K = 1 - exp(-2 * PI * Fc / Fs)
 *
 * Fs = 50 kHz
 * Fc = 5 kHz
 * K  = 1 - exp(-2 * PI * 5000 / 50000)
 * K  ~= 0.466
 */
#define LLC_ADC_LPF_K                   (0.466f)
__SECTION(RAMCODE)
void get_adc_data(void)
{                                                                                        
/**************************** ADC Physical Value Update ****************************/

    uint16_t raw;

    raw = ADC_VOUT_RAW_VALUE();
    PhyValue.vout.raw = raw;
    PhyValue.vout.actual = (float)raw * VOUT_SAMPLE_FACTOR;
    PhyValue.vout.actual_LPF += (PhyValue.vout.actual - PhyValue.vout.actual_LPF) * LLC_ADC_LPF_K;

    raw = ADC_RSENSE1_RAW_VALUE();
    PhyValue.rsense1.raw = raw;
    PhyValue.rsense1.actual = (float)raw * RSENSE1_SAMPLE_FACTOR;
    PhyValue.rsense1.actual_LPF += (PhyValue.rsense1.actual - PhyValue.rsense1.actual_LPF) * LLC_ADC_LPF_K;

    raw = ADC_VP_RAW_VALUE();
    PhyValue.vp.raw = raw;
    PhyValue.vp.actual = (float)raw * VP_SAMPLE_FACTOR;
    PhyValue.vp.actual_LPF += (PhyValue.vp.actual - PhyValue.vp.actual_LPF) * LLC_ADC_LPF_K;

    raw = ADC_VN_RAW_VALUE();
    PhyValue.vn.raw = raw;
    PhyValue.vn.actual = (float)raw * VN_SAMPLE_FACTOR;
    PhyValue.vn.actual_LPF += (PhyValue.vn.actual - PhyValue.vn.actual_LPF) * LLC_ADC_LPF_K;

}

__SECTION(RAMCODE)
 void LL_ADC_Norm_REG_SeqEndCallback(ADC_TypeDef *Instance)            
{ 
	get_adc_data();
}

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
	
		if (Instance == ADC0) 
		{
        //ADC0 Pinmux Config: 
        ADC_GPIO_Init.Pin = GPIO_PIN_0 | GPIO_PIN_1;
        LL_GPIO_Init(GPIOA, &ADC_GPIO_Init);
			
        ADC_GPIO_Init.Pin = GPIO_PIN_1 | GPIO_PIN_2;	
        LL_GPIO_Init(GPIOC, &ADC_GPIO_Init);

        //ADC0 Bus Clock Enable and Soft Reset Release
        LL_RCU_ADC0_ClkEnRstRelease();
 
        //NVIC ADC0 Interrupt Enable
				LL_NVIC_EnableIRQ(ADC0_NORM_IRQn);
    } 
		else if (Instance == ADC1) 
		{

        //ADC1 Bus Clock Enable and Soft Reset Release
        LL_RCU_ADC1_ClkEnRstRelease();

        //NVIC ADC1 Interrupt Enable
       LL_NVIC_EnableIRQ(ADC1_NORM_IRQn);

    }

}

 /*===================end of adc_app.c===========================*/
