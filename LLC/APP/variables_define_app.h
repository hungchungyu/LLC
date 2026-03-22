#ifndef __VARIABLES_DEFINE_APP_H__
#define __VARIABLES_DEFINE_APP_H__

#ifdef __cplusplus
 extern "C" {
#endif
/*============================ Include =======================================*/
#include "main.h"
/*============================ Defines (Constant) ============================*/
#define PWM_TEST_FLAG						0//PWM 测试开关
#define HRPWM_LLC_OUTPUT_EN 				1//使能LLC输出
#define USE_SWITCH_ENABLE_LLC				1//使能物理开关
#define CURRENT_BALANCE_EN					1//均流功能使能开关

#define LLC_PHASE1_ENABLE	 				1//第一相的原边PWM
#if LLC_PHASE1_ENABLE
	#define HRPWM_SR1_OUTPUT_EN				1//第一相的副边SR
#endif	 
	 
#define LLC_PHASE2_ENABLE	 				1//第二相的原边PWM
#if LLC_PHASE2_ENABLE
	#define HRPWM_SR2_OUTPUT_EN				1//第二相的副边SR
#endif

#define ILOOP_LIMIT							1//0:关闭LLC限流 1：开启LLC限流

#define	LLC_PHASE1_PWM5       			(HRPWM_SLV_PWM_5)
#define	LLC_PHASE2_PWM4 	     		(HRPWM_SLV_PWM_4)
#define LLC_PHASE1_SR_PWM3       		(HRPWM_SLV_PWM_3)
#define LLC_PHASE2_SR_PWM2				(HRPWM_SLV_PWM_2)
#define USER_ADC_TRIG_PWM0				(HRPWM_SLV_PWM_0)
/*******PWM start BIT********/
#define HRPWM_MASTER_START_BIT     		BIT(16)
#define HRPWM_PWM0_START_BIT     		BIT(17)
#define HRPWM_PWM1_START_BIT        	BIT(18)
#define LLC_PHASE2_SR_PWM2_START_BIT	BIT(19)
#define LLC_PHASE1_SR_PWM3_START_BIT	BIT(20)
#define LLC_PHASE2_PWM4_START_BIT		BIT(21)
#define LLC_PHASE1_PWM5_START_BIT		BIT(22)
#define HRPWM_PWM7_START_BIT        	BIT(24)
/*******PWM OEN BIT********/
#define HRPWM_PWM1_OEN_A_BIT			BIT(2)
#define LLC_PHASE2_SR_PWM2_OEN_A_BIT	BIT(4)
#define LLC_PHASE2_SR_PWM2_OEN_B_BIT	BIT(5)
#define LLC_PHASE1_SR_PWM3_OEN_A_BIT	BIT(6)
#define LLC_PHASE1_SR_PWM3_OEN_B_BIT	BIT(7)
#define LLC_PHASE2_PWM4_OEN_A_BIT		BIT(8)
#define LLC_PHASE2_PWM4_OEN_B_BIT		BIT(9)
#define LLC_PHASE1_PWM5_OEN_A_BIT		BIT(10)
#define LLC_PHASE1_PWM5_OEN_B_BIT		BIT(11)
#define HRPWM_PWM7_OEN_B_BIT      		BIT(15)
/*******PWM ODIS BIT********/
#define HRPWM_PWM1_ODIS_A_BIT			BIT(2)
#define LLC_PHASE2_SR_PWM2_ODIS_A_BIT	BIT(4)
#define LLC_PHASE2_SR_PWM2_ODIS_B_BIT	BIT(5)
#define LLC_PHASE1_SR_PWM3_ODIS_A_BIT	BIT(6)
#define LLC_PHASE1_SR_PWM3_ODIS_B_BIT	BIT(7)
#define LLC_PHASE2_PWM4_ODIS_A_BIT		BIT(8)
#define LLC_PHASE2_PWM4_ODIS_B_BIT		BIT(9)
#define LLC_PHASE1_PWM5_ODIS_A_BIT		BIT(10)
#define LLC_PHASE1_PWM5_ODIS_B_BIT		BIT(11)
#define HRPWM_PWM7_ODIS_B_BIT     		BIT(15)
/*ADC OFFSET&GAIN*/
#define ADC_OFFSET							0
#define ADC_GAIN							8192

#define BUF_LEN0       						1
#define BUF_LEN1       						1
/*===================== ADC VREF Define ========================*/
#define VOUT_FULL_RANGE 			(float)60.9 //full range of ADC for llc out
#define VOUT_SET_POINT				(float)53.5
#define VOUT_OV_POINT				(float)57.0
#define VOUT_UNOV_POINT				(float)50.0
#define SOFT_START_VOLTAGE			(float)0.004

#define IOUT_FULL_RANGE 			(float)72.5 //full range of ADC for IOUT	
	

	
#define IOUT_OC_POINT				(float)58.8
#define IOUT_SC_POINT				(float)61.6	
#define IOUT_HOC					(float)71.6//(61.6A 硬件保护点为满载电流的110%，带0.3V的抬升)

#define I_PRIMARRY_SIDE_FULL		(float)29.743589//A
#define ADC_FULL_NUM				(float)8192.0
/*====================current set=======================*/

#define HRPWM_BASIC_FREQ    		(float)200000			//KHZ
#define HRPWM_DIV_X         		(float)16
#define HRPWM_FINAL_FREQ    		(float)HRPWM_BASIC_FREQ * HRPWM_DIV_X
#define HRPWM_ONE_STEP_TIME			((float)(1000000/(HRPWM_BASIC_FREQ*HRPWM_DIV_X)))  //ns
	
#define LLC_SW_FREQ_MAX				(200.0)//kHz
#define LLC_SW_PERIOD_MIN			((uint32_t)(HRPWM_FINAL_FREQ/LLC_SW_FREQ_MAX))//register value
#define LLC_SW_FREQ_MIN				(60.0)//kHz

#define LLC_SW_PERIOD_MAX			((uint32_t)(HRPWM_FINAL_FREQ/LLC_SW_FREQ_MIN))//register value
#define LLC_MODE_SWITCH				((float)(LLC_SW_FREQ_MIN/LLC_SW_FREQ_MAX))

#define LLC_DEADTIME				(float)(150)//ns
#define LLC_DEADTIME_COUNT			((int32_t)(LLC_DEADTIME/HRPWM_ONE_STEP_TIME))//register value
#define LLC_MINTIME_COUNT           50

#define LLC_START_UP_FREQ			(150.0)//kHz
#define LLC_START_UP_CNT			((int32_t)(HRPWM_FINAL_FREQ/LLC_START_UP_FREQ))//register value

#define LLC_SR_DT_ON                (50.0)//ns
#define LLC_SR_DT_OFF               (100.0)//ns
#define LLC_SR_MAX_TIME				(4000.0)// ns
#define LLC_SR_DEADTIME_ON          (LLC_SR_DT_ON)
#define LLC_SR_DEADTIME_COUNT_ON    ((uint32_t)(LLC_SR_DEADTIME_ON/HRPWM_ONE_STEP_TIME))//register value
#define LLC_SR_DEADTIME_OFF         (LLC_SR_DT_OFF)
#define LLC_SR_DEADTIME_COUNT_OFF   ((uint32_t)(LLC_SR_DEADTIME_OFF/HRPWM_ONE_STEP_TIME))//register value
#define LLC_SR_MAX_CNT				((int32_t)(LLC_SR_MAX_TIME/HRPWM_ONE_STEP_TIME))//register value

#define IOUT_SR_OPEN_CURRENT		15.0f//A
#define IOUT_SR_CLOSE_CURRENT		(12.0f)//A

#define LLC_OK_EN_CURRENT			(20.0f)
#define LLC_OK_DIS_CURRENT			(15.0f)

#define LLC_SAMPLE_FREQ             100	//khz
#define LLC_SAMPLE_PERIOD           ((int32_t)(HRPWM_FINAL_FREQ/LLC_SAMPLE_FREQ))-1//register value 

#define ADC_IRQ_ONE_CYCLE_TIME		(1.0/(LLC_SAMPLE_FREQ*1000))//s
#define LLC_OPP2_TIME				0.2//(s)
#define LLC_OPP2_COUNT				(int32_t)(LLC_OPP2_TIME/ADC_IRQ_ONE_CYCLE_TIME)

#define LLC_BURST_MODE_MAX_CNT      220
#define LLC_BURST_THRESHOLD			2.0
#define LLC_BURST_THRESHOLD_VALUE	(float)(LLC_BURST_THRESHOLD/53.5)
#define LLC_BURST_OUT_POINT			55.5f
#define V_KP						(float)2.0//1.4//2.0
#define V_KI						(float)0.145//0.14//0.135//0.085//0.035
#define V_KD						(float)0.01//0.01




/*恒流环参数*/
#define IOUT_CC_POINT				(float)56.0

/*kpkikd的参数尽量控制在1.2以内！！！*/
#define I_KP						(float)0.005//恒流环kp	
#define I_KI						(float)0.00011//恒流环ki
#define I_KD						(float)0.0001//恒流环kd





#define Lead_Phase_IIR_A0                   (float)1.0
#define Lead_Phase_IIR_A1                   (float)-0.4398
#define Lead_Phase_IIR_A2                   (float)0.0
#define Lead_Phase_IIR_A3                   (float)0.0
#define Lead_Phase_IIR_A4                   (float)0.0

#define Lead_Phase_IIR_B0                   (float)2.5850
#define Lead_Phase_IIR_B1                   (float)-2.3834;
#define Lead_Phase_IIR_B2                   (float)0.0
#define Lead_Phase_IIR_B3                   (float)0.0
#define Lead_Phase_IIR_B4                   (float)0.0

	
#define LLC_IIR_A0                   (float)1.0
#define LLC_IIR_A1                   (float)-0.2057
#define LLC_IIR_A2                   (float)1.021
#define LLC_IIR_A3                   (float)0.3011
#define LLC_IIR_A4                   (float)-0.1168
                                            
#define LLC_IIR_B0                   (float)397.1
#define LLC_IIR_B1                   (float)-673.9
#define LLC_IIR_B2                   (float)-110.8
#define LLC_IIR_B3                   (float)674
#define LLC_IIR_B4                   (float)-286.2

/*================================== Enums ===================================*/
extern  int32_t irq_cnt,buf_len,cnt_up;
/*============================ Structure & Unions ============================*/
typedef enum 
{
    State_idle = 0,
	State_charge,
	State_enable,
    State_rampup,
    State_on,
    State_fault,
}STATE;
typedef enum
{
    Light_load = 0,
    Half_load,
    Full_load,
}LOAD_STATE;

typedef enum
{
    VBus_over_voltage = 0,
    Vin_over_voltage,
    Vin_under_voltage,
    Current_over_range,
}FAULT_STATE;
typedef struct
{
	float p_part;
	float i_part;
	float d_part;
	float kp;
	float ki;
	float kd;
	float last_err;
	float output;
	float upper_limit;
}TW_PID_TypeDef ;

typedef struct
{
	float A[5];
	float A_part;
	float B[5];
	float B_part;
	float result;
	float upper_limit;
	float X[5];
	float Y[5];
}cIIR_TypeDef;



typedef enum
{
	key_off = 0,
	key_on = 1,
}KEY_MODE;
typedef enum
{
	voltage_mode = 0,
	current_mode = 1,
}OUTPUT_MODE;
typedef enum 
{
    sr_pwm_off = 0, 
    sr_pwm_on = 1, 
}TW_SRPWM_TypeDef;

typedef enum
{
	pwm_mode = 0,
	pfm_mode = 1,
}SWITCH_MODE;
/*Inital Factors Define*/
 typedef struct
{   
    uint16_t first_init_cnt;
    bool     first_init;
    uint16_t fault_pwm;
    uint16_t fault_num;
    bool     start_failed;
	float  vout_raw;//Q15
	float  vout_protect_raw;//Q15	
	float  iout_raw;//Q15
	float  temperature_raw;//Q15
	float  iin_phase1_temp;
	float  iin_phase2_temp;
	float  iin_phase1_LPF;
	float  iin_phase2_LPF;
	float  iin_phase1;
	float  iin_phase2;
	float  llc_result;
	float  slope;
	float  interphase_current_err;
	int32_t delay_cnt_temp;
	int32_t delay_cnt;
	bool	sr_pwm;    
    bool	is_vbus_ok;
	bool	charge_flag;
	bool	ac_ok;
	bool    hard_fault;
	int16_t de_rampup;
	int16_t  charge_cnt;
	int32_t  sr_delay_cnt;
	int32_t lead_phase_balance_duty;
	int32_t lag_phase_balance_duty;
    uint16_t is_ovp;
    uint16_t is_ocp;
    uint16_t is_uvp;
	uint16_t is_otp;
	uint16_t is_sus_ocp;
	uint16_t is_open_loop;
	int32_t dead_time;
	int32_t sr_on_dead_time ;
	int32_t sr_off_dead_time;
	int32_t sr_max_on_time	;
	int32_t burst_cnt;
	float vout_target;	
	float vout_ref;	
	float vout_err_load;	
	float iout_target;	
	float iout_ref;		
	float Vo_err;
	int16_t	switch_cnt;
	int16_t switch_off_cnt;
	bool     fault_occured;
    OUTPUT_MODE output_mode;
	KEY_MODE    key_state;
	SWITCH_MODE switch_mode;
	cIIR_TypeDef   iir_vloop;
	cIIR_TypeDef   iir_iloop;
	cIIR_TypeDef   peak_filter_100;
	cIIR_TypeDef   peak_filter_200;
	cIIR_TypeDef   peak_filter_250;
	cIIR_TypeDef   peak_filter_4k;
    TW_PID_TypeDef vloop;
    TW_PID_TypeDef iloop;
	TW_PID_TypeDef leadphase_balance_loop;
	TW_PID_TypeDef lagphase_balance_loop;
	TW_PID_TypeDef buckloop;
	uint32_t sys_tick_100us;
	STATE state;
	
	float peek_100_ratio;
	
	bool loop_block_flag;
	bool pre_loop_block_flag;
	int16_t loop_block_count;
	
	
	int16_t llc_unovp_count;
	
	int16_t sustain_iloop_count;
	int16_t sustain_vloop_count;
	
	int16_t llc_open_loop_count;
	
	bool current_sharing_flag;
	bool current1_s_en_flag;
	bool current2_s_en_flag;
	int16_t phase1_sharing_count;
	int16_t phase2_sharing_count;
	float current_row_temp;
	
	volatile bool data_update_finish_flag;
	float pwm_mode_ratio;
	
	int32_t count_delay;
	uint32_t OCP_adjust_num;
	
	float pre_V_error;
	float V_error_derta;
	int32_t delay_300us_count;
	
}TW_LLC_TypeDef;

typedef struct 
{
    int32_t period;
    int32_t compa;
    int32_t compb;
    int32_t compc;
    int32_t compd;
}TW_HRPWM_TypeDef; 


typedef union
{
	float   f[2];
	uint32_t c[2];
}ADJUST_TYPE;  
  

extern volatile ADJUST_TYPE feedback_data;
extern	int16_t current_share_samp			[BUF_LEN1] ;
extern	int16_t primary_current1_samp  		[BUF_LEN1] ;
extern	int16_t primary_current2_samp		[BUF_LEN1] ;
extern	int16_t llc_current_samp			[BUF_LEN1] ;
extern	int16_t temperature_samp			[BUF_LEN1] ;
extern	int16_t llc_voltage_samp			[BUF_LEN1] ;
extern	 int16_t llc_current_ref_samp		[BUF_LEN1] ;
 
extern TW_LLC_TypeDef llc;	
extern volatile TW_HRPWM_TypeDef mpwm,pwm0,pwm1,phase2_sr_pwm2,phase1_sr_pwm3,phase2_pwm4,phase1_pwm5;

void pfc_hrpwm_outdis_app(void);
void data_init_app(void);
void llc_factors_initial(void);
#ifdef __cplusplus
}
#endif

#endif
/*************************** (C) COPYRIGHT2021Tai-Action ***** END OF FILE *****/ 

