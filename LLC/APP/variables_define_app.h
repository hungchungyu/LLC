#ifndef __VARIABLES_DEFINE_APP_H__
#define __VARIABLES_DEFINE_APP_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "pid_app.h"

#define OPEN_LOOP_TEST                  1U

//#define SCENARIO_DISABLE_PSONOFF_MONITOR
//#define SCENARIO_DISABLE_VOUT_OVP_MONITOR
//#define SCENARIO_DISABLE_RSENSE1_OCP_MONITOR

#define HRPWM_LLC_OUTPUT_EN             1U      /* Enable LLC output */

#define LLC_PHASE1_ENABLE               1U      /* Enable phase 1 primary-side PWM */
#define LLC_PHASE2_ENABLE               1U      /* Enable phase 2 primary-side PWM */

#if LLC_PHASE1_ENABLE
#define HRPWM_SR1_OUTPUT_EN             0U      /* Enable phase 1 secondary-side SR output */
#endif

#if LLC_PHASE2_ENABLE
#define HRPWM_SR2_OUTPUT_EN             0U      /* Enable phase 2 secondary-side SR output */
#endif


#define VOUT_TARGET_LEVEL        				48.0f

#define VOUT_OVP_LEVEL                  60.0f
#define RSENSE1_OCP_LEVEL               10.0f


#define LLC_PHASE1_PWM0                 (HRPWM_SLV_PWM_0)    /* PA8, PA9 */
#define LLC_PHASE1_SR_PWM4              (HRPWM_SLV_PWM_4)    /* PC8, PC9 */

#define LLC_PHASE2_PWM2                 (HRPWM_SLV_PWM_2)    /* PB12, PB13 */
#define LLC_PHASE2_SR_PWM5              (HRPWM_SLV_PWM_5)    /* PC6, PC7 */


#define HRPWM_BASIC_FREQ                ((float)200000.0f)   /* 200000kHz = 200MHz */
#define HRPWM_DIV_X                     ((float)16.0f)
#define HRPWM_FINAL_FREQ                (HRPWM_BASIC_FREQ * HRPWM_DIV_X)
#define HRPWM_ONE_STEP_TIME             ((float)(1000000.0f / (HRPWM_BASIC_FREQ * HRPWM_DIV_X)))   /* 0.3125ns */

#define LLC_SW_FREQ_MAX                 (200.0f)             /* kHz */
#define LLC_SW_FREQ_MIN                 (100.0f)             /* kHz */

#define LLC_SW_PERIOD_MIN               ((uint32_t)(HRPWM_FINAL_FREQ / LLC_SW_FREQ_MAX))           /* register value */

#define LLC_DEADTIME                    ((float)150.0f)      /* ns */
#define LLC_DEADTIME_COUNT              ((int32_t)(LLC_DEADTIME / HRPWM_ONE_STEP_TIME))             /* register value: 480 */

#define LLC_SAMPLE_FREQ                 (50.0f)              /* kHz */
#define LLC_SAMPLE_PERIOD               (((int32_t)(HRPWM_FINAL_FREQ / LLC_SAMPLE_FREQ)) - 1)       /* register value */

#define USER_ADC_TRIG_PWM1              (HRPWM_SLV_PWM_1)


#define VOUT_SAMPLE_FACTOR              (1.0f)
#define RSENSE1_SAMPLE_FACTOR           (1.0f)
#define VP_SAMPLE_FACTOR                (1.0f)
#define VN_SAMPLE_FACTOR                (1.0f)


typedef struct
{
    uint32_t period;
    uint32_t compa;
    uint32_t compb;
    uint32_t compc;
    uint32_t compd;

} LLC_PWM_CmpTypeDef;


typedef struct
{
    uint16_t raw;                       /* ADC raw data */
    uint16_t raw_avg;                   /* ADC averaged raw data */

    float actual;                       /* Converted physical value */
    float actual_avg;                   /* Averaged physical value */
    float actual_LPF;                   /* Low-pass filtered physical value */

} ADC_PHY_TYPE;


typedef struct
{
    ADC_PHY_TYPE vout;
    ADC_PHY_TYPE rsense1;
    ADC_PHY_TYPE vp;
    ADC_PHY_TYPE vn;

} PHY_VALUE_TYPE;


typedef union
{
    uint64_t QWord;

    struct
    {
        unsigned int ps_on              : 1;
        unsigned int controller_enable  : 1;

    } bits;

} StateFlag_t;





typedef union
{
    uint64_t QWord;

    struct
    {
        unsigned int vout_ovp           : 1;
        unsigned int rsense1_ocp        : 1;

    } bits;

} ProtectFlag_t;


extern ProtectFlag_t ProtectFlag;
extern StateFlag_t StateFlag;
extern digitctrl_PI V_Loop;
extern PHY_VALUE_TYPE PhyValue;

extern LLC_PWM_CmpTypeDef mpwm;
extern LLC_PWM_CmpTypeDef phase1_pwm0;
extern LLC_PWM_CmpTypeDef phase1_sr_pwm4;
extern LLC_PWM_CmpTypeDef phase2_pwm2;
extern LLC_PWM_CmpTypeDef phase2_sr_pwm5;








/*******PWM start BIT********/
#define HRPWM_MASTER_START_BIT     		BIT(16)
#define HRPWM_PWM0_START_BIT     			BIT(17)
#define HRPWM_PWM1_START_BIT        	BIT(18)
#define HRPWM_PWM2_START_BIT     			BIT(19)
#define HRPWM_PWM3_START_BIT        	BIT(20)
#define HRPWM_PWM4_START_BIT        	BIT(21)
#define HRPWM_PWM5_START_BIT        	BIT(22)
#define HRPWM_PWM6_START_BIT        	BIT(23)
#define HRPWM_PWM7_START_BIT        	BIT(24)


/*******PWM OEN BIT********/
#define HRPWM_PWM0_OEN_A_BIT					BIT(0)
#define HRPWM_PWM0_OEN_B_BIT      		BIT(1)
#define HRPWM_PWM1_OEN_A_BIT					BIT(2)
#define HRPWM_PWM1_OEN_B_BIT      		BIT(3)
#define HRPWM_PWM2_OEN_A_BIT					BIT(4)
#define HRPWM_PWM2_OEN_B_BIT      		BIT(5)
#define HRPWM_PWM3_OEN_A_BIT					BIT(6)
#define HRPWM_PWM3_OEN_B_BIT      		BIT(7)
#define HRPWM_PWM4_OEN_A_BIT					BIT(8)
#define HRPWM_PWM4_OEN_B_BIT      		BIT(9)
#define HRPWM_PWM5_OEN_A_BIT					BIT(10)
#define HRPWM_PWM5_OEN_B_BIT      		BIT(11)
#define HRPWM_PWM6_OEN_A_BIT					BIT(12)
#define HRPWM_PWM6_OEN_B_BIT      		BIT(13)
#define HRPWM_PWM7_OEN_A_BIT					BIT(14)
#define HRPWM_PWM7_OEN_B_BIT      		BIT(15)



#define BUF_LEN0       						1
#define BUF_LEN1       						1

typedef enum 
{
    State_idle = 0,
	State_charge,
	State_enable,
    State_rampup,
    State_on,
    State_fault,
}STATE;


typedef struct
{

}TW_PID_TypeDef ;

typedef struct
{

}cIIR_TypeDef;

 typedef struct
{   

}TW_LLC_TypeDef;


  



 
extern TW_LLC_TypeDef llc;	


#ifdef __cplusplus
}
#endif

#endif

