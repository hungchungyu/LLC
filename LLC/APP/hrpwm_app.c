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
//TYPE_ADC_CTL_INIT  adc_ctl_cfg;
//TYPE_ADC_IRQ_CFG   adc_irq_cfg;
//TYPE_ADC_CFG       adc_cfg;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
* @function void adc_init_app(void)
* @brief    Description: app adc init
* @return   None return.
*/


void hrpwm_init(void)
{
    /*mpwm init*/
    mpwm.period  = LLC_SW_PERIOD_MIN-1;    // 320000k/200k = 16000          
    mpwm.compa   = 20;
    mpwm.compb   = mpwm.period/4;
    mpwm.compc   = 40;
    mpwm.compd   = 3199;

    /*phase2_pwm4 init*/
    phase2_pwm4.period  = LLC_SW_PERIOD_MIN-1;                    
    phase2_pwm4.compa   = LLC_SW_PERIOD_MIN/2-1;
    phase2_pwm4.compb   = 900;
    phase2_pwm4.compc   = 800;
	/*phase1_pwm5 init*/
    phase1_pwm5.period  = LLC_SW_PERIOD_MIN-1;                    
    phase1_pwm5.compa   = LLC_SW_PERIOD_MIN/2-1-LLC_DEADTIME_COUNT;
    phase1_pwm5.compb   = phase1_pwm5.compa +LLC_DEADTIME_COUNT;
    phase1_pwm5.compc   = phase1_pwm5.period -LLC_DEADTIME_COUNT;
	
		phase1_sr_pwm3.period  = phase1_pwm5.period;                    
    phase1_sr_pwm3.compa   = LLC_SR_DEADTIME_COUNT_ON;
    phase1_sr_pwm3.compb   = phase1_pwm5.compa-LLC_SR_DEADTIME_COUNT_OFF;
    phase1_sr_pwm3.compc   = phase1_pwm5.compb+LLC_SR_DEADTIME_COUNT_ON;
		phase1_sr_pwm3.compd   = phase1_pwm5.compc -LLC_SR_DEADTIME_COUNT_OFF;
}

void hrpwm_app_config(HRPWM_TypeDef *Instance)
{
		HRPWM_TmrBaseCfgTypeDef    user_hrpwm_tmr_base_cfg;
    HRPWM_TmrCmpCfgTypeDef     user_hrpwm_tmr_cmp_cfg;
    HRPWM_Slv_OutputCfgTypeDef user_hrpwm_slv_output_cfg;
		HRPWM_Comm_ADCTrigCfgTypeDef user_hrpwm_comm_adctrig_cfg;
		HRPWM_Comm_FltCfgTypeDef   user_hrpwm_comm_flt_cfg;

    memset((void *)&user_hrpwm_tmr_base_cfg,   0x00, sizeof(user_hrpwm_tmr_base_cfg));
    memset((void *)&user_hrpwm_tmr_cmp_cfg,    0x00, sizeof(user_hrpwm_tmr_cmp_cfg));
    memset((void *)&user_hrpwm_slv_output_cfg, 0x00, sizeof(user_hrpwm_slv_output_cfg));
		memset((void *)&user_hrpwm_comm_adctrig_cfg, 0x00, sizeof(user_hrpwm_comm_adctrig_cfg));
		memset((void *)&user_hrpwm_comm_flt_cfg,   0x00, sizeof(user_hrpwm_comm_flt_cfg));
	
    //HRPWM LL Init
    LL_HRPWM_Init(Instance);
	
	
    //User HRPWM Timer Base Config
    user_hrpwm_tmr_base_cfg.rep_prd    				= 0;												// Master.MREP Repetition no work mode like continue/single mode
    user_hrpwm_tmr_base_cfg.cntr_prd   				= phase1_pwm5.period ;
    user_hrpwm_tmr_base_cfg.int_en_msk 				= HRPWM_SLV_INT_NONE;
    user_hrpwm_tmr_base_cfg.clk_prescl 				= HRPWM_CLK_PRESCL_MUL_16;
    user_hrpwm_tmr_base_cfg.work_mode  				= HRPWM_WORK_MODE_CONTINUE;

    user_hrpwm_tmr_base_cfg.sync_rst_en      		= false;
    user_hrpwm_tmr_base_cfg.sync_start_en    		= false;
    user_hrpwm_tmr_base_cfg.single_retrig_en 		= false;
    user_hrpwm_tmr_base_cfg.cntr_rst_evt     		= HRPWM_SLV0_CNTR_RST_EVT_NONE;
    user_hrpwm_tmr_base_cfg.resync_mode      		= HRPWM_SLV_RESYNC_NEXT_RST_ROLLOVER;

    user_hrpwm_tmr_base_cfg.half_mode_en        	= false;
    user_hrpwm_tmr_base_cfg.intlvd_mode         	= HRPWM_INTLVD_MODE_CLOSE;
    user_hrpwm_tmr_base_cfg.push_pull_en        	= false;
    user_hrpwm_tmr_base_cfg.trig_half_en        	= false;
    user_hrpwm_tmr_base_cfg.cmpA_greatr_than_en 	= false;
    user_hrpwm_tmr_base_cfg.cmpC_greatr_than_en 	= false;
    user_hrpwm_tmr_base_cfg.upd_gate            	= HRPWM_SLV_UPD_GATE_BST_DMA_INDEPEND;
    user_hrpwm_tmr_base_cfg.cmpB_auto_dly_mode  	= HRPWM_SLV_CMPB_AUTO_DLY_ALWAYS;
    user_hrpwm_tmr_base_cfg.cmpD_auto_dly_mode  	= HRPWM_SLV_CMPD_AUTO_DLY_ALWAYS;

    //Master PWM Timer Base Config
    LL_HRPWM_TmrBaseCfg(Instance, HRPWM_MST_PWM, &user_hrpwm_tmr_base_cfg);
		
		
		
		
    //Slave PWMx Timer Base Config
		user_hrpwm_tmr_base_cfg.work_mode  				= HRPWM_WORK_MODE_SINGLE;
		
		
		user_hrpwm_tmr_base_cfg.upd_gate            	= HRPWM_SLV_UPD_GATE_BST_DMA_INDEPEND;
		user_hrpwm_tmr_base_cfg.single_retrig_en 			= true;			// ReTrigger
		user_hrpwm_tmr_base_cfg.cntr_rst_evt     			= HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_PRD;
    LL_HRPWM_TmrBaseCfg(Instance, LLC_PHASE1_PWM5, &user_hrpwm_tmr_base_cfg);
	
		user_hrpwm_tmr_base_cfg.resync_mode					= HRPWM_SLV_RESYNC_IMDT;
		user_hrpwm_tmr_base_cfg.cntr_rst_evt     		= HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPB;
		LL_HRPWM_TmrBaseCfg(Instance, LLC_PHASE2_PWM4, &user_hrpwm_tmr_base_cfg);
	
	
		// SR
		user_hrpwm_tmr_base_cfg.resync_mode				= HRPWM_SLV_RESYNC_NEXT_RST_ROLLOVER;
		user_hrpwm_tmr_base_cfg.upd_gate            	= HRPWM_SLV_UPD_GATE_BST_DMA_INDEPEND;
		user_hrpwm_tmr_base_cfg.cntr_rst_evt     		= HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_PRD;
		LL_HRPWM_TmrBaseCfg(Instance, LLC_PHASE1_SR_PWM3, &user_hrpwm_tmr_base_cfg);
	
	
		user_hrpwm_tmr_base_cfg.resync_mode				=HRPWM_SLV_RESYNC_IMDT;
		user_hrpwm_tmr_base_cfg.cntr_rst_evt     		= HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPB;
		LL_HRPWM_TmrBaseCfg(Instance, LLC_PHASE2_SR_PWM2, &user_hrpwm_tmr_base_cfg);
	
	
	
	
	
	
	
    //User HRPWM Timer Compare Config
    user_hrpwm_tmr_cmp_cfg.pre_load_en    			= true;
    user_hrpwm_tmr_cmp_cfg.cmp_a_val      			= 100;
		user_hrpwm_tmr_cmp_cfg.cmp_b_val      			= phase1_pwm5.compb;
    user_hrpwm_tmr_cmp_cfg.cmp_c_val      			= phase1_pwm5.compc;
		user_hrpwm_tmr_cmp_cfg.rst_ro_upd_en				= true;
		
		
    //Master PWM Timer Compare Config
    LL_HRPWM_TmrCmpCfg(Instance, HRPWM_MST_PWM, &user_hrpwm_tmr_cmp_cfg);
		
		
		
		user_hrpwm_tmr_cmp_cfg.pre_load_en    			= true;
		user_hrpwm_tmr_cmp_cfg.rst_ro_upd_en				= true;
		user_hrpwm_tmr_cmp_cfg.mst_pwm_upd_en           =false;// true;
    //Slave PWMx Timer Compare Config
    LL_HRPWM_TmrCmpCfg(Instance, LLC_PHASE1_PWM5, &user_hrpwm_tmr_cmp_cfg);
		LL_HRPWM_TmrCmpCfg(Instance, LLC_PHASE2_PWM4, &user_hrpwm_tmr_cmp_cfg);
	
		user_hrpwm_tmr_cmp_cfg.pre_load_en    			= true;
    user_hrpwm_tmr_cmp_cfg.cmp_a_val      			= phase1_sr_pwm3.compa;
		user_hrpwm_tmr_cmp_cfg.cmp_b_val      			= phase1_sr_pwm3.compb;
    user_hrpwm_tmr_cmp_cfg.cmp_c_val      			= phase1_sr_pwm3.compc;
		user_hrpwm_tmr_cmp_cfg.cmp_d_val      			= phase1_sr_pwm3.compd;
		user_hrpwm_tmr_cmp_cfg.rst_ro_upd_en			= true;
		user_hrpwm_tmr_cmp_cfg.mst_pwm_upd_en           = true;
    //Master PWM Timer Compare Config
    LL_HRPWM_TmrCmpCfg(Instance, LLC_PHASE1_SR_PWM3, &user_hrpwm_tmr_cmp_cfg);
		LL_HRPWM_TmrCmpCfg(Instance, LLC_PHASE2_SR_PWM2, &user_hrpwm_tmr_cmp_cfg);



    //User HRPWM Slave PWMx Output Config
		user_hrpwm_slv_output_cfg.swap_en               = false;
    user_hrpwm_slv_output_cfg.dly_prot_en           = false;
    user_hrpwm_slv_output_cfg.bal_idle_auto_rcvr_en = false;
    user_hrpwm_slv_output_cfg.dly_prot_mode         = HRPWM_SLV_DLY_PROT_MECH_OUTA_EVTy_IDLE;
		
    user_hrpwm_slv_output_cfg.Aout_set_evt_msk 		= HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPC;
    user_hrpwm_slv_output_cfg.Aout_clr_evt_msk 		= HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPD;
    user_hrpwm_slv_output_cfg.Aout_pol         		= HRPWM_SLV_OUT_POL_ACT_HITH;
    user_hrpwm_slv_output_cfg.Aout_idle_lvl    		= HRPWM_SLV_OUT_IDLE_LVL_INVLD; 	
    user_hrpwm_slv_output_cfg.Aout_flt_lvl     		= HRPWM_SLV_OUT_FAULT_LVL_INVLD;	// Actions following FLT0, 3, and 6

    user_hrpwm_slv_output_cfg.Bout_set_evt_msk 		= HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPA;
    user_hrpwm_slv_output_cfg.Bout_clr_evt_msk 		= HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPB;
    user_hrpwm_slv_output_cfg.Bout_pol         		= HRPWM_SLV_OUT_POL_ACT_HITH;
    user_hrpwm_slv_output_cfg.Bout_idle_lvl    		= HRPWM_SLV_OUT_IDLE_LVL_INVLD;
    user_hrpwm_slv_output_cfg.Bout_flt_lvl     		= HRPWM_SLV_OUT_FAULT_LVL_INVLD;	// Actions following FLT0, 3, and 6
#if PWM_TEST_FLAG
	user_hrpwm_slv_output_cfg.flt_en[0]             = true;
	user_hrpwm_slv_output_cfg.flt_en[3]             = true;
	user_hrpwm_slv_output_cfg.flt_en[6]             = true;
	
	user_hrpwm_slv_output_cfg.flt_en[7]             = false;
#else
	user_hrpwm_slv_output_cfg.flt_en[0]             = true;		// __LL_HRPWM_Slv_Flt0_En()
	user_hrpwm_slv_output_cfg.flt_en[3]             = true;
	user_hrpwm_slv_output_cfg.flt_en[6]             = true;
	user_hrpwm_slv_output_cfg.flt_en[7]             = false;
#endif
    LL_HRPWM_Slv_OutputCfg(Instance, LLC_PHASE1_PWM5, &user_hrpwm_slv_output_cfg);	// PWM5 will be affected by FLT0,3,6
	
	user_hrpwm_slv_output_cfg.Aout_clr_evt_msk 		= HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPD|HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPB;
	LL_HRPWM_Slv_OutputCfg(Instance, LLC_PHASE2_PWM4, &user_hrpwm_slv_output_cfg);		// PWM4 will be affected by FLT0,3,6
	
	
	user_hrpwm_slv_output_cfg.Aout_set_evt_msk 		= HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPA;
	user_hrpwm_slv_output_cfg.Aout_clr_evt_msk 		= HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPB;
	
	user_hrpwm_slv_output_cfg.Bout_set_evt_msk 		= HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPC;
	user_hrpwm_slv_output_cfg.Bout_clr_evt_msk 		= HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPD|HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPB;
	
	LL_HRPWM_Slv_OutputCfg(Instance, LLC_PHASE1_SR_PWM3, &user_hrpwm_slv_output_cfg);
	LL_HRPWM_Slv_OutputCfg(Instance, LLC_PHASE2_SR_PWM2, &user_hrpwm_slv_output_cfg);

	//User HRPWM Common Fault Config
    user_hrpwm_comm_flt_cfg.sys_flt_int_en = false;
    user_hrpwm_comm_flt_cfg.samp_clk_div   = HRPWM_COMM_FLT_SAMP_CLK_DIV_1;

    user_hrpwm_comm_flt_cfg.input_en = true;
    user_hrpwm_comm_flt_cfg.int_en   = true;
    user_hrpwm_comm_flt_cfg.fil_len  = 5;//5
    user_hrpwm_comm_flt_cfg.thres    = 3;//3
    user_hrpwm_comm_flt_cfg.pol      = HRPWM_COMM_FLT_INPUT_POL_ACT_HIGH;
		
		
		
    user_hrpwm_comm_flt_cfg.src      = HRPWM_COMM_FLT0_INPUT_SRC_CMP1_OUT;
    user_hrpwm_comm_flt_cfg.rst_mode = HRPWM_COMM_FLT_CNTR_RST_RSTRO_ALWAYS;

    user_hrpwm_comm_flt_cfg.blk_en   = false;
    user_hrpwm_comm_flt_cfg.blk_src  = HRPWM_COMM_FLT_BLK_SRC_FIXED_WIN;
    LL_HRPWM_Comm_FltCfg(Instance, HRPWM_FLT_NUM_0, &user_hrpwm_comm_flt_cfg); 

    user_hrpwm_comm_flt_cfg.fil_len  = 10;//5
    user_hrpwm_comm_flt_cfg.thres    = 0;//3
		user_hrpwm_comm_flt_cfg.src      = HRPWM_COMM_FLT3_INPUT_SRC_CMP0_OUT;
		LL_HRPWM_Comm_FltCfg(Instance, HRPWM_FLT_NUM_3, &user_hrpwm_comm_flt_cfg);

    user_hrpwm_comm_flt_cfg.fil_len  = 5;//5
    user_hrpwm_comm_flt_cfg.thres    = 3;//3
		user_hrpwm_comm_flt_cfg.src      = HRPWM_COMM_FLT6_INPUT_SRC_CMP7_OUT;
		LL_HRPWM_Comm_FltCfg(Instance, HRPWM_FLT_NUM_6, &user_hrpwm_comm_flt_cfg);

		user_hrpwm_comm_flt_cfg.src      = HRPWM_COMM_FLT7_INPUT_SRC_CMP8_OUT;
		LL_HRPWM_Comm_FltCfg(Instance, HRPWM_FLT_NUM_7, &user_hrpwm_comm_flt_cfg);
	
	
	
    //Preload Enable, software need to generate a update event to update the shadow register to the working register
    //If Preload Disable or has other update source, don't need this action.
  	LL_HRPWM_Comm_DLL_Start(Instance);
    LL_HRPWM_RegUpd_Frc(Instance, HRPWM_MST_PWM);			// SW force one time update
    LL_HRPWM_RegUpd_Frc(Instance,LLC_PHASE1_PWM5);
		LL_HRPWM_RegUpd_Frc(Instance,LLC_PHASE2_PWM4);
		LL_HRPWM_RegUpd_Frc(Instance,LLC_PHASE1_SR_PWM3);
		LL_HRPWM_RegUpd_Frc(Instance,LLC_PHASE2_SR_PWM2);
}
void adc_triger_pwm0_config(HRPWM_TypeDef *Instance)
{
	HRPWM_TmrBaseCfgTypeDef    		user_hrpwm_tmr_base_cfg;
    HRPWM_TmrCmpCfgTypeDef     		user_hrpwm_tmr_cmp_cfg;
	HRPWM_Comm_ADCTrigCfgTypeDef	user_hrpwm_comm_adctrig_cfg;
	
    memset((void *)&user_hrpwm_tmr_base_cfg,   0x00, sizeof(user_hrpwm_tmr_base_cfg));
    memset((void *)&user_hrpwm_tmr_cmp_cfg,    0x00, sizeof(user_hrpwm_tmr_cmp_cfg));
	memset((void *)&user_hrpwm_comm_adctrig_cfg, 0x00, sizeof(user_hrpwm_comm_adctrig_cfg));
	
	//User HRPWM Timer Base Config
    user_hrpwm_tmr_base_cfg.rep_prd    				= 0;
    user_hrpwm_tmr_base_cfg.int_en_msk 				= HRPWM_SLV_INT_NONE;
    user_hrpwm_tmr_base_cfg.clk_prescl 				= HRPWM_CLK_PRESCL_MUL_16;
    user_hrpwm_tmr_base_cfg.work_mode  				= HRPWM_WORK_MODE_CONTINUE;
    user_hrpwm_tmr_base_cfg.resync_mode      		= HRPWM_SLV_RESYNC_NEXT_RST_ROLLOVER;
		user_hrpwm_tmr_base_cfg.cntr_prd   						= LLC_SAMPLE_PERIOD;
		user_hrpwm_tmr_base_cfg.cntr_rst_evt     		= HRPWM_SLV0_CNTR_RST_EVT_NONE;
		LL_HRPWM_TmrBaseCfg(Instance, USER_ADC_TRIG_PWM0, &user_hrpwm_tmr_base_cfg);
	
	//User HRPWM Common ADC Trigger Config
    user_hrpwm_comm_adctrig_cfg.trig_evt    = HRPWM_COMM_ADC02_TRIG_EVT_PWM0_CMPD;
    user_hrpwm_comm_adctrig_cfg.trig_len    = HRPWM_COMM_ADC_TRIG_EVT_LEN_15CLK;
    user_hrpwm_comm_adctrig_cfg.upd_src     = HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM0;
    user_hrpwm_comm_adctrig_cfg.post_scaler = 0;
    LL_HRPWM_Comm_ADCTrigCfg(Instance, HRPWM_ADC_TRIG_NUM_0, &user_hrpwm_comm_adctrig_cfg);
		
		
		user_hrpwm_tmr_cmp_cfg.cmp_d_val		= 500;
		LL_HRPWM_TmrCmpCfg(Instance, USER_ADC_TRIG_PWM0, &user_hrpwm_tmr_cmp_cfg);
		
		
         //User HRPWM Common ADC Trigger Config
    user_hrpwm_comm_adctrig_cfg.trig_evt    = HRPWM_COMM_ADC13_TRIG_EVT_PWM0_PRD;
    user_hrpwm_comm_adctrig_cfg.trig_len    = HRPWM_COMM_ADC_TRIG_EVT_LEN_15CLK;
    user_hrpwm_comm_adctrig_cfg.upd_src     = HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM0;
    user_hrpwm_comm_adctrig_cfg.post_scaler = 0;
    LL_HRPWM_Comm_ADCTrigCfg(Instance, HRPWM_ADC_TRIG_NUM_1, &user_hrpwm_comm_adctrig_cfg);
		
		LL_HRPWM_RegUpd_Frc(Instance,USER_ADC_TRIG_PWM0);
	
}
void hrpwm_app_start(void)
{
	HRPWM->Master.MCR1  |=
						   HRPWM_MASTER_START_BIT|
						   HRPWM_PWM0_START_BIT|
						   LLC_PHASE2_SR_PWM2_START_BIT|
						   LLC_PHASE1_SR_PWM3_START_BIT|
						   LLC_PHASE1_PWM5_START_BIT |
						   HRPWM_PWM1_START_BIT|
						   LLC_PHASE2_PWM4_START_BIT|
						   HRPWM_PWM7_START_BIT|
						   0;
}
void hrpwm_app_inital(void)
{
    hrpwm_init();
    hrpwm_app_config(HRPWM);
		adc_triger_pwm0_config(HRPWM);
}

void hrpwm_llc_output(void)
{
	HRPWM->Common.OENR |=
#if	 HRPWM_LLC_OUTPUT_EN
#if	LLC_PHASE1_ENABLE
						LLC_PHASE1_PWM5_OEN_A_BIT|
	                    LLC_PHASE1_PWM5_OEN_B_BIT|
#endif
#if	LLC_PHASE2_ENABLE
						LLC_PHASE2_PWM4_OEN_A_BIT|
						LLC_PHASE2_PWM4_OEN_B_BIT|
#endif
#endif	
						0;
}
void hrpwm_sr_output(void)
{
	HRPWM->Common.OENR |=
#if	 HRPWM_SR1_OUTPUT_EN
						LLC_PHASE1_SR_PWM3_OEN_A_BIT|
	                    LLC_PHASE1_SR_PWM3_OEN_B_BIT|
#endif	
#if	 HRPWM_SR2_OUTPUT_EN
						LLC_PHASE2_SR_PWM2_OEN_A_BIT|
	                    LLC_PHASE2_SR_PWM2_OEN_B_BIT|
#endif	
						0;
}


void hrpwm_sr_output_dis(void)
{
	HRPWM->Common.ODISR |=
#if HRPWM_SR1_OUTPUT_EN
						LLC_PHASE1_SR_PWM3_ODIS_A_BIT |
						LLC_PHASE1_SR_PWM3_ODIS_B_BIT |
#endif
#if HRPWM_SR2_OUTPUT_EN
						LLC_PHASE2_SR_PWM2_ODIS_A_BIT |
						LLC_PHASE2_SR_PWM2_ODIS_B_BIT |
#endif
							0;
}
void hrpwm_llc_output_dis(void)
{
	HRPWM->Common.ODISR |=
#if HRPWM_LLC_OUTPUT_EN
#if LLC_PHASE1_ENABLE	
						LLC_PHASE1_PWM5_ODIS_A_BIT|  
						LLC_PHASE1_PWM5_ODIS_B_BIT|
#endif
#if LLC_PHASE2_ENABLE
						LLC_PHASE2_PWM4_ODIS_A_BIT |
						LLC_PHASE2_PWM4_ODIS_B_BIT |
#endif
#endif
							0;
}

void hrpwm_app_outdis(void)
{
	HRPWM->Common.ODISR |=
#if HRPWM_LLC_OUTPUT_EN
#if LLC_PHASE1_ENABLE	
						LLC_PHASE1_PWM5_ODIS_A_BIT|  
						LLC_PHASE1_PWM5_ODIS_B_BIT|
#endif
#if LLC_PHASE2_ENABLE
						LLC_PHASE2_PWM4_ODIS_A_BIT|
						LLC_PHASE2_PWM4_ODIS_A_BIT|
#endif
#endif

#if	HRPWM_SR1_OUTPUT_EN
						LLC_PHASE1_SR_PWM3_ODIS_A_BIT|
						LLC_PHASE1_SR_PWM3_ODIS_B_BIT|
#endif
#if	HRPWM_SR2_OUTPUT_EN
						LLC_PHASE2_SR_PWM2_ODIS_A_BIT|
						LLC_PHASE2_SR_PWM2_ODIS_B_BIT|
#endif
						0;
}

__SECTION(RAMCODE)
void hrpwm_upmos_charge(void)
{
	HRPWM->Common.OENR |=
#if HRPWM_LLC_OUTPUT_EN
#if	LLC_PHASE1_ENABLE
						LLC_PHASE1_PWM5_OEN_A_BIT|
#endif
#if	LLC_PHASE2_ENABLE
						LLC_PHASE2_PWM4_OEN_A_BIT|
#endif
#endif
						0;
}
__SECTION(RAMCODE)
void hrpwm_upmos_charge_dis(void)
{
	HRPWM->Common.ODISR |=
#if HRPWM_LLC_OUTPUT_EN
#if LLC_PHASE1_ENABLE
						LLC_PHASE1_PWM5_ODIS_A_BIT|
#endif
	
#if	LLC_PHASE2_ENABLE
						LLC_PHASE2_PWM4_ODIS_A_BIT|
#endif
#endif
						0;
}
__SECTION(RAMCODE)
void LL_HRPWM_Mst_CmpACallback(HRPWM_TypeDef *Instance)
{
	IWDG->KEYR = 0xAAAA;//reload watch dog
	GPIOA->BSR = GPIO_PIN_11;
#if CURRENT_BALANCE_EN
	if(llc.iout_raw>20.0f&&llc.state == State_on && llc.current_sharing_flag == false){
		if(llc.iin_phase1>llc.iin_phase2)
		{
			llc.phase1_sharing_count++;
			llc.phase2_sharing_count=0;
		}else if(llc.iin_phase1<=llc.iin_phase2)
		{
			llc.phase1_sharing_count=0;
			llc.phase2_sharing_count++;
		}
		if(llc.phase2_sharing_count>=10000)
		{
			llc.phase2_sharing_count = 0;
			llc.current2_s_en_flag = true;
			llc.current1_s_en_flag = false;
			llc.current_sharing_flag = true;
		}
		if(llc.phase1_sharing_count>=10000)
		{
			llc.phase1_sharing_count = 0;
			llc.current1_s_en_flag = true;
			llc.current2_s_en_flag = false;
			llc.current_sharing_flag = true;
		}
	}
	
	if(llc.current_sharing_flag == true && llc.iout_raw>20.0f)
	{
		phase2phase_current_balance_func();
	}
	else{
		llc.leadphase_balance_loop.output =0;
		llc.leadphase_balance_loop.i_part =0;
		llc.lag_phase_balance_duty = 0;
		
		llc.lead_phase_balance_duty = 0;
		llc.lagphase_balance_loop.output =0;
		llc.lagphase_balance_loop.i_part =0;
	}
#endif
	pwm_data_calc();
	if(llc.state==State_on||llc.state == State_rampup){
		hrpwm_updata_app();
	}
//	__LL_HRPWM_Mst_CmpA_INT_Dis(HRPWM);
	GPIOA->BSR = GPIO_PIN_11<<16;
}
__SECTION(RAMCODE)
void hrpwm_updata_app()
{
	int32_t master_cmpa,master_cmpb;
    //¼ÓËø(½ûÖ¹¸üÐÂ)
	HRPWM->Common.CR0 |= 0x81FF;		//PWM2~5 & Burst mode
	__NOP();__NOP();__NOP();__NOP();__NOP();
	if(llc.state == State_charge){
		HRPWM->PWM[LLC_PHASE1_PWM5].REG.CMPCR = LLC_DEADTIME_COUNT-1;
		HRPWM->PWM[LLC_PHASE1_PWM5].REG.CMPDR = LLC_SW_PERIOD_MIN>>1;
		HRPWM->PWM[LLC_PHASE1_PWM5].REG.PERR  = LLC_SW_PERIOD_MIN-1;
	}else{
		HRPWM->PWM[LLC_PHASE1_PWM5].REG.CMPAR = phase1_pwm5.compa;
		HRPWM->PWM[LLC_PHASE1_PWM5].REG.CMPBR = phase1_pwm5.compb;
		HRPWM->PWM[LLC_PHASE1_PWM5].REG.CMPCR = phase1_pwm5.compc;
		HRPWM->PWM[LLC_PHASE1_PWM5].REG.CMPDR = phase1_pwm5.compd;
		HRPWM->PWM[LLC_PHASE1_PWM5].REG.PERR  = phase1_pwm5.period;
		
		HRPWM->PWM[LLC_PHASE1_SR_PWM3].REG.CMPAR = phase1_sr_pwm3.compa;
		HRPWM->PWM[LLC_PHASE1_SR_PWM3].REG.CMPBR = phase1_sr_pwm3.compb;
		HRPWM->PWM[LLC_PHASE1_SR_PWM3].REG.CMPCR = phase1_sr_pwm3.compc;
		HRPWM->PWM[LLC_PHASE1_SR_PWM3].REG.CMPDR = phase1_sr_pwm3.compd;
		HRPWM->PWM[LLC_PHASE1_SR_PWM3].REG.PERR  = phase1_sr_pwm3.period;
#if		LLC_PHASE2_ENABLE 
		HRPWM->PWM[LLC_PHASE2_PWM4].REG.CMPAR = phase2_pwm4.compa;
		HRPWM->PWM[LLC_PHASE2_PWM4].REG.CMPBR = phase2_pwm4.compb;
		HRPWM->PWM[LLC_PHASE2_PWM4].REG.CMPCR = phase2_pwm4.compc;
		HRPWM->PWM[LLC_PHASE2_PWM4].REG.CMPDR = phase2_pwm4.compd;
		HRPWM->PWM[LLC_PHASE2_PWM4].REG.PERR  = phase2_pwm4.period;
		
		HRPWM->PWM[LLC_PHASE2_SR_PWM2].REG.CMPAR = phase2_sr_pwm2.compa;
		HRPWM->PWM[LLC_PHASE2_SR_PWM2].REG.CMPBR = phase2_sr_pwm2.compb;
		HRPWM->PWM[LLC_PHASE2_SR_PWM2].REG.CMPCR = phase2_sr_pwm2.compc;
		HRPWM->PWM[LLC_PHASE2_SR_PWM2].REG.CMPDR = phase2_sr_pwm2.compd; 
		HRPWM->PWM[LLC_PHASE2_SR_PWM2].REG.PERR  = phase2_sr_pwm2.period;
#endif		
	}
	HRPWM->Master.MPER       = phase1_pwm5.period;
	master_cmpb 			 = phase1_pwm5.period/4;
	HRPWM->Master.MCMPBR     = master_cmpb;//
	HRPWM->Master.MCMPAR     = (phase1_pwm5.period>>2)-1000;//
	__NOP();__NOP();__NOP();__NOP();__NOP();
	HRPWM->Common.CR0 &= ~(0x81FF);	//PWM2~5 & Burst mdoe
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    

/**
  * @brief  HRPWM Common Fault 3 Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__SECTION(RAMCODE)
void LL_HRPWM_Comm_Flt0Callback(HRPWM_TypeDef *Instance) //LLC I_primarry oc
{ 
	llc.fault_num |=BIT(0);
	llc.state = State_fault; 
	llc.hard_fault = true;	
}
/**
  * @brief  HRPWM Common Fault 3 Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__SECTION(RAMCODE)
void LL_HRPWM_Comm_Flt3Callback(HRPWM_TypeDef *Instance) //LLC I_primarry oc
{
	llc.fault_num |=BIT(1);
	llc.state = State_fault;  
	llc.hard_fault = true;
}
/**
  * @brief  HRPWM Common Fault 3 Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__SECTION(RAMCODE)
void LL_HRPWM_Comm_Flt7Callback(HRPWM_TypeDef *Instance) //LLC I_primarry oc
{
	llc.fault_num |=BIT(2);
	llc.state = State_fault;
	llc.hard_fault = true;	
}
/**
  * @brief  HRPWM Common Fault 3 Interrupt Callback
  * @param  Instance Specifies HRPWM peripheral
  * @return None
  */
__SECTION(RAMCODE)
void LL_HRPWM_Comm_Flt6Callback(HRPWM_TypeDef *Instance) //LLC I_primarry oc
{
	llc.fault_num |=BIT(3);
	llc.state = State_fault; 
	llc.hard_fault = true;
}
/**
  * @brief  Initializes the HRPWM MSP
  * @param  Instance Specifies HRPWM peripheral
  * @retval None
  */
void LL_HRPWM_MspInit(HRPWM_TypeDef *Instance)
{ 
	GPIO_InitTypeDef HRPWM_GPIO_Init;
	//Assert param
	//HRPWM Bus Clock Disable and Soft Reset Assert
	//HRPWM Slave 2 Output Pinmux Config: PB12->OUT2A, PB13->OUT2B
	HRPWM_GPIO_Init.OType = GPIO_OTYPE_PP;
	HRPWM_GPIO_Init.Pull  = GPIO_NOPULL; 
	HRPWM_GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
	
	HRPWM_GPIO_Init.Pin 	= GPIO_PIN_12 | GPIO_PIN_13;
	HRPWM_GPIO_Init.Alternate = GPIO_AF14_HRPWM;
	LL_GPIO_Init(GPIOB, &HRPWM_GPIO_Init);

	//HRPWM Slave 3 Output Pinmux Config: PB14->OUT3A, PB15->OUT3B
    HRPWM_GPIO_Init.Pin = GPIO_PIN_14 | GPIO_PIN_15;
    HRPWM_GPIO_Init.Alternate = GPIO_AF14_HRPWM;
    LL_GPIO_Init(GPIOB, &HRPWM_GPIO_Init);

    //HRPWM Slave 5 Output Pinmux Config: PC6->OUT5A, PC7->OUT5B
    HRPWM_GPIO_Init.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    HRPWM_GPIO_Init.Alternate = GPIO_AF14_HRPWM;
    LL_GPIO_Init(GPIOC, &HRPWM_GPIO_Init);

   	//HRPWM Slave 4 Output Pinmux Config: PC8->OUT4A
		HRPWM_GPIO_Init.Pin = GPIO_PIN_8|GPIO_PIN_9;
    HRPWM_GPIO_Init.Alternate = GPIO_AF14_HRPWM;
    LL_GPIO_Init(GPIOC, &HRPWM_GPIO_Init);
		
		
    LL_RCU_HRPWM_ClkEnRstRelease();
		
	LL_NVIC_EnableIRQ(HRPWM_MST_IRQn);
	LL_NVIC_EnableIRQ(HRPWM_COM_IRQn);

}


///*============end of hrpwm_app.c===============*/