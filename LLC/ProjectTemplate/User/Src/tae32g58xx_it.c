#include "main.h"
#include "tae32g58xx_it.h"
#include "utils.h"
#include "variables_define_app.h"

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1) {
    }
}


void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1) {
    }
}


void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1) {
    }
}


void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1) {
    }
}


void SVC_Handler(void)
{
}


void DebugMon_Handler(void)
{
}


void PendSV_Handler(void)
{
}
/********************************************APP IRQHandler****************************************/
__SECTION(RAMCODE)
void ADC0_NORM_IRQHandler(void)
{
    uint32_t int_en;
    uint32_t int_pending;
    float pwm_value;

    TEST2_HIGH();

    /* ADC normal all interrupt enable and pending get */
    int_en      = __LL_ADC_NormAllIntEn_Get(ADC0);
    int_pending = __LL_ADC_NormAllIntPending_Get(ADC0);

    /* Normal sequence end interrupt handler */
    if((int_en & ADC0_IER_EOSIE_Msk) && (int_pending & ADC0_ISR_EOS_Msk))
    {
        /* Clear interrupt pending */
        __LL_ADC_REG_SeqEndIntPnd_Clr(ADC0);

        LL_ADC_Norm_REG_SeqEndCallback(ADC0);
			
			if(StateFlag.bits.controller_enable == 1)
			{
					#ifndef OPEN_LOOP_TEST
					V_Loop.Ref = VOUT_TARGET_LEVEL;				
					V_Loop.Fb = PhyValue.vout.actual_LPF;
					calc_PI(&V_Loop);
					#endif
					pwm_value = LLC_SlewValue(&V_Loop.ActualOut, &V_Loop.TargetOut);

					CtrlToPwm(pwm_value, &phase1_pwm0);
					CtrlToPwm(pwm_value, &phase2_pwm2);
					hrpwm_updata_app();
			}

    }

    TEST2_LOW();
}


__SECTION(RAMCODE)
void HRPWM_COMM_IRQHandler(void)
{
    LL_HRPWM_Comm_IRQHandler(HRPWM);
}

__SECTION(RAMCODE)
void HRPWM_MST_IRQHandler(void)
{

}

void ADC1_SAMP_IRQHandler(void)		// Not used?
{

}

void SysTick_Handler(void)
{
#ifdef LL_MODULE_ENABLED
    LL_IncTick();
#endif

#ifdef LL_CORTEX_MODULE_ENABLED
    LL_SYSTICK_IRQHandler();
#endif
}



/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

