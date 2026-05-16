
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dbg/tae_dbg.h"
#include "state_machine.h"
#include "event_debounce.h"

static void SystemClock_Config(void);

void AppTimer_1msTask(void);
void cmpss_initial_app(void);
void NVIC_initial(void);

uint32_t gpio_test = 0;
int main(void)
{
	SystemClock_Config();
	
	LL_Init();
	NVIC_initial();				// Nested vectored interrupt controller
	gpio_init_app();
	
	hrpwm_app_inital();
	
	adc_all_init(); 
	hrpwm_app_start();
	
	tmr_init_app(TMR7);
	
	//cmpss_initial_app();
	//iwdg_init();
	
	
#if	PWM_TEST_FLAG
	llc.state = State_on;
	//hrpwm_sr_output();
#endif	
	
	
	adc_converter_start();
	//__LL_HRPWM_Mst_CmpA_INT_En(HRPWM);
	
	StateMachine_Init(STATE_STANDBY);
	while (1) 
	{
		if (__LL_TMR_AllIntPnd_Get(TMR7) & TMR9_SR_OVIF_Msk)
		{
			__LL_TMR_OverflowIntPnd_Clr(TMR7);

    /* 1ms task */
			AppTimer_1msTask();
		}	
	}
}

#define DEBOUNCE_CNT_1MS     (1U)
#define DEBOUNCE_CNT_10MS    (10U)

void AppTimer_1msTask(void)
{
		TEST1_HIGH();
		
		PSONOFF_MonitorEvents(DEBOUNCE_CNT_10MS, DEBOUNCE_CNT_1MS);
	
		if(PSONOFF_InputStableCount.bits.b15 == 0)
			StateMachine_RequestTransition(STATE_STANDBY);
		
		StateMachine_Step();
		TEST1_LOW();
}

void cmpss_initial_app(void)
{
	dac_app_init();
	dac_app_start();
	cmp_app_init();
	cmp_app_start();
}
void NVIC_initial(void)
{
	LL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_3);
	
	//LL_NVIC_SetPriority(HRPWM_COM_IRQn,0,0);
	LL_NVIC_SetPriority(ADC1_NORM_IRQn,2,1);
	//LL_NVIC_SetPriority(HRPWM_MST_IRQn,1,0);
}

static void SystemClock_Config(void)
{
    LL_StatusETypeDef ret;
    RCU_SysclkUserCfgTypeDef sysclk_cfg;
	
	
    //SYSCLK Clock Config
    sysclk_cfg.sysclk_src  = SYSCLK_SRC_PLL0DivClk;
    sysclk_cfg.sysclk_freq = 200000000UL;				// 200M Hz
    sysclk_cfg.pll0clk_src = PLLCLK_SRC_HSI;
    sysclk_cfg.pll0clk_src_freq = HSI_VALUE;		// Internal 8M Hz 
	
    sysclk_cfg.apb0_clk_div = RCU_CLK_DIV_2;
    sysclk_cfg.apb1_clk_div = RCU_CLK_DIV_2;
    sysclk_cfg.ahb_clk_div  = RCU_CLK_DIV_1;

    ret = LL_RCU_SysclkInit(RCU, &sysclk_cfg);
    if (ret == LL_OK)
			{
        SystemCoreClockUpdate(sysclk_cfg.sysclk_freq);
				LL_RCU_ADC_ClkCfg(RCU_CLK_SRC_PLL0, RCU_CLK_DIV_4);		// ADC CLK 50M Hz (Max:60M Hz)
        LL_RCU_HRPWM_ClkCfg(RCU_CLK_SRC_PLL0, RCU_CLK_DIV_1);	// HRPWM CLK 200M Hz
			}
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    if (file != NULL) {
        LOG_E("Assert failed in %s line %" PRIu32 "", file, line);
    }

    /* Infinite loop */
    while (1) {
        __NOP();
    }
}
#endif
