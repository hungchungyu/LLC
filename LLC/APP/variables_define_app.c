/**
  ******************************************************************************
  * @file    APP/variables_define.c
  * @author  004 
  * @version V1.0.0
  * @date    15-01-2021
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2021 Tai-Action</center></h2>
  *
  *
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "variables_define_app.h"


volatile TW_HRPWM_TypeDef phase1_pwm0, phase1_sr_pwm4, phase2_pwm2, phase2_sr_pwm5;








/*============================ Defines (Constant) ============================*/

TW_LLC_TypeDef llc;

/*============================ Defines (Alias) ===============================*/
int16_t current_share_samp			[BUF_LEN1] ;
int16_t primary_current1_samp  		[BUF_LEN1] ;
int16_t primary_current2_samp		[BUF_LEN1] ;
int16_t llc_current_samp			[BUF_LEN1] ;
int16_t temperature_samp			[BUF_LEN1] ;
int16_t llc_voltage_samp			[BUF_LEN1] ;
int16_t llc_current_ref_samp		[BUF_LEN1] ;
                                                                              


volatile ADJUST_TYPE feedback_data;
volatile TW_HRPWM_TypeDef mpwm,pwm0,pwm1,phase2_sr_pwm2,phase1_sr_pwm3,phase2_pwm4,phase1_pwm5;
volatile uint16_t pwm_test_value;
void llc_factors_initial(void)
{
	llc.dead_time = LLC_DEADTIME_COUNT;
	llc.sr_on_dead_time 	= LLC_SR_DEADTIME_COUNT_ON;
	llc.sr_off_dead_time 	= LLC_SR_DEADTIME_COUNT_OFF; 
	llc.sr_max_on_time		= LLC_SR_MAX_CNT;
	llc.vloop.kp = V_KP;
	llc.vloop.ki = V_KI;
	llc.vloop.kd = V_KD;
	
	llc.iloop.kp = I_KP;
	llc.iloop.ki = I_KI;
	llc.iloop.kd = I_KD;
	
	
	llc.vloop.upper_limit = 1.0f;
	llc.iloop.upper_limit = 1.0f;
	
	llc.leadphase_balance_loop.kp = 0.0001f;
	llc.leadphase_balance_loop.ki = 0.00001f;
	llc.leadphase_balance_loop.kd = 0.0000f;
	llc.leadphase_balance_loop.upper_limit = 1.0f;
	
	llc.lagphase_balance_loop.kp = 0.0001f;
	llc.lagphase_balance_loop.ki = 0.00001f;
	llc.lagphase_balance_loop.kd = 0.0000f;
	llc.lagphase_balance_loop.upper_limit = 1.0f;
	llc.vout_target   = VOUT_SET_POINT;
	
	/*************************controller parameter initial*************************/
	llc.iir_vloop.A[0]  = LLC_IIR_A0 ;
	llc.iir_vloop.A[1]  = LLC_IIR_A1 ;
	llc.iir_vloop.A[2]  = LLC_IIR_A2 ;
	llc.iir_vloop.A[3]  = LLC_IIR_A3 ;
	llc.iir_vloop.A[4]  = LLC_IIR_A4 ;
									
	llc.iir_vloop.B[0]	= LLC_IIR_B0 ;
	llc.iir_vloop.B[1]  = LLC_IIR_B1 ;
	llc.iir_vloop.B[2]  = LLC_IIR_B2 ;
	llc.iir_vloop.B[3]  = LLC_IIR_B3 ;
	llc.iir_vloop.B[4]  = LLC_IIR_B4 ;
	/********************phase lead controller inital**********************/
	llc.peak_filter_100.A[0]  = 1.0;
	llc.peak_filter_100.A[1]  = 1.99872651954061675f;
	llc.peak_filter_100.A[2]  = -0.998765973469715407f;
	llc.peak_filter_100.A[3]  = 0.0f;
	llc.peak_filter_100.A[4]  = 0.0f;
				                 
	llc.peak_filter_100.B[0]  = 0.000617013265142296596f;
	llc.peak_filter_100.B[1]  = 0.0f;
	llc.peak_filter_100.B[2]  = -0.000617013265142296596f;
	llc.peak_filter_100.B[3]  = 0.0f;
	llc.peak_filter_100.B[4]  = 0.0f;
	
	llc.peak_filter_200.A[0]  = 1.0;
	llc.peak_filter_200.A[1]  = 1.99860815931089486f;
	llc.peak_filter_200.A[2]  = -0.998765973469715407f;
	llc.peak_filter_200.A[3]  = 0.0f;
	llc.peak_filter_200.A[4]  = 0.0f;
				               
	llc.peak_filter_200.B[0]  = 0.000617013265142296596f;
	llc.peak_filter_200.B[1]  = 0.0f;
	llc.peak_filter_200.B[2]  = -0.000617013265142296596;
	llc.peak_filter_200.B[3]  = 0.0f;
	llc.peak_filter_200.B[4]  = 0.0f;
	
	
	llc.peak_filter_250.A[0]  = 1.0;
	llc.peak_filter_250.A[1]  = 1.99967112203814823f;
	llc.peak_filter_250.A[2]  = -0.999917846939807786f;
	llc.peak_filter_250.A[3]  = 0.0f;
	llc.peak_filter_250.A[4]  = 0.0f;
				               
	llc.peak_filter_250.B[0]  = 0.0000410765300961069002f;
	llc.peak_filter_250.B[1]  = 0.0f;
	llc.peak_filter_250.B[2]  = -0.0000410765300961069002f;
	llc.peak_filter_250.B[3]  = 0.0f;
	llc.peak_filter_250.B[4]  = 0.0f;	
	
	llc.peak_filter_4k.A[0]  = 1.0;
	llc.peak_filter_4k.A[1]  = 1.96433194803253697;
	llc.peak_filter_4k.A[2]  = -0.999753072815858568;
	llc.peak_filter_4k.A[3]  = 0.0f;
	llc.peak_filter_4k.A[4]  = 0.0f;
				          
	llc.peak_filter_4k.B[0]  = 0.000123463592070716111;
	llc.peak_filter_4k.B[1]  = 0.0f;
	llc.peak_filter_4k.B[2]  = -0.000123463592070716111;
	llc.peak_filter_4k.B[3]  = 0.0f;
	llc.peak_filter_4k.B[4]  = 0.0f;
	
	llc.current_sharing_flag = false;
	llc.current1_s_en_flag = false;
	llc.current2_s_en_flag = false;
	
	
}
/*************************** (C) COPYRIGHT2021Tai-Action ***** END OF FILE *****/
 







