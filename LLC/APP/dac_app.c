#include "main.h"
#include "include_app.h"

void dac_app_init(void)
{
	DAC_InitTypeDef user_dac_init;

	memset((void *)&user_dac_init, 0x00, sizeof(user_dac_init));

	user_dac_init.trig_en = false;
	user_dac_init.buf_out_en = true;
	user_dac_init.bypass_buf_out_en = false;

	LL_DAC_Init(DAC0, &user_dac_init);
	LL_DAC_Init(DAC2, &user_dac_init);


	LL_DAC_ValueSet(DAC0, DAC0_INIT_VALUE);
	LL_DAC_ValueSet(DAC2, DAC2_INIT_VALUE);

}

void dac_app_start(void)
{
	LL_DAC_Start(DAC0);
	LL_DAC_Start(DAC2);
}	

void LL_DAC_MspInit(DAC_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_DAC_ALL_INSTANCE(Instance));
	    //DAC GPIO Common Config
	LL_RCU_DAC_ClkEnRstRelease();
}
