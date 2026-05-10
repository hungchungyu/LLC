#include "main.h"
#include "include_app.h"
#include "tmr_app.h"

void TMR_ClockInit_App(TMR_TypeDef *Instance);

void tmr_init_app(TMR_TypeDef *Instance)
{
  TMR_BaseInitTypeDef tmr_base_init;

    if (!IS_TMR_ALL_INSTANCE(Instance)) 
    {
        return;
    }

    TMR_ClockInit_App(Instance);



    memset((void *)&tmr_base_init, 0x00, sizeof(tmr_base_init));


    tmr_base_init.auto_preload_en = true;
    tmr_base_init.work_mode       = TMR_WORK_MODE_CONTINUE;
    tmr_base_init.period          = 100 - 1;
    tmr_base_init.prescaler       = 1000 - 1;
    tmr_base_init.update_evt_en   = true;
    tmr_base_init.update_evt_src  = TMR_UPDATE_EVT_SRC_OV;

    LL_TMR_Base_Cfg(Instance, &tmr_base_init);


    __LL_TMR_OverflowIntPnd_Clr(Instance);
    __LL_TMR_UpdateIntPnd_Clr(Instance);

    LL_TMR_Start(Instance);
}

void TMR_ClockInit_App(TMR_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_TMR_ALL_INSTANCE(Instance));

    if (Instance == TMR0) {
        //TMR0 Bus Clock Enable and Soft Reset Release
        LL_RCU_TMR0_ClkEnRstRelease();

        //NVIC TMR0 Interrupt Enable
        LL_NVIC_EnableIRQ(TMR0_IRQn);
    } else if (Instance == TMR1) {
        //TMR1 Bus Clock Enable and Soft Reset Release
        LL_RCU_TMR1_ClkEnRstRelease();

        //NVIC TMR1 Interrupt Enable
        LL_NVIC_EnableIRQ(TMR1_IRQn);
    } else if (Instance == TMR2) {
        //TMR2 Bus Clock Enable and Soft Reset Release
        LL_RCU_TMR2_ClkEnRstRelease();

        //NVIC TMR2 Interrupt Enable
        LL_NVIC_EnableIRQ(TMR2_IRQn);
    } else if (Instance == TMR3) {
        //TMR3 Bus Clock Enable and Soft Reset Release
        LL_RCU_TMR3_ClkEnRstRelease();

        //NVIC TMR3 Interrupt Enable
        LL_NVIC_EnableIRQ(TMR3_IRQn);
    } else if (Instance == TMR4) {
        //TMR4 Bus Clock Enable and Soft Reset Release
        LL_RCU_TMR4_ClkEnRstRelease();

        //NVIC TMR4 Interrupt Enable
        LL_NVIC_EnableIRQ(TMR4_IRQn);
    } else if (Instance == TMR7) {
        //TMR7 Bus Clock Enable and Soft Reset Release
        LL_RCU_TMR7_ClkEnRstRelease();

        //NVIC TMR7 Interrupt Enable
        LL_NVIC_EnableIRQ(TMR7_IRQn);
    } else if (Instance == TMR8) {
        //TMR8 Bus Clock Enable and Soft Reset Release
        LL_RCU_TMR8_ClkEnRstRelease();

        //NVIC TMR8 Interrupt Enable
        LL_NVIC_EnableIRQ(TMR8_IRQn);
    } else if (Instance == TMR9) {
        //TMR9 Bus Clock Enable and Soft Reset Release
        LL_RCU_TMR9_ClkEnRstRelease();

        //NVIC TMR9 Interrupt Enable
        LL_NVIC_EnableIRQ(TMR9_BRK_IRQn);
        LL_NVIC_EnableIRQ(TMR9_UPD_IRQn);
        LL_NVIC_EnableIRQ(TMR9_TRG_IRQn);
        LL_NVIC_EnableIRQ(TMR9_CC_IRQn);
    } else if (Instance == TMR10) {
        //TMR10 Bus Clock Enable and Soft Reset Release
        LL_RCU_TMR10_ClkEnRstRelease();

        //NVIC TMR10 Interrupt Enable
        LL_NVIC_EnableIRQ(TMR10_BRK_IRQn);
        LL_NVIC_EnableIRQ(TMR10_UPD_IRQn);
        LL_NVIC_EnableIRQ(TMR10_TRG_IRQn);
        LL_NVIC_EnableIRQ(TMR10_CC_IRQn);
    }
}


