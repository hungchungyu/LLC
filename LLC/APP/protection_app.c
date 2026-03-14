/**
  ******************************************************************************
  * @file    APP/protection_app.c
  * @author 004 
  * @version V1.0.0
  * @date    17-04-2020
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2020 Tai-Action</center></h2>
  *
  *
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "Protection_App.h"

__SECTION(RAMCODE)
void switch_state_check_app(void)
{
	if(llc.key_state == key_off){
		if(LL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)==GPIO_PIN_RESET)
		{
			llc.switch_cnt++;
			if(llc.switch_cnt>500){    //
				llc.key_state = key_on;
				llc.fault_num  &= ~BIT(7);
				llc.switch_off_cnt =0;
			}
		}
	}
	if(llc.key_state == key_on&&LL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)==GPIO_PIN_SET)
	{
		llc.switch_off_cnt++;
		if(llc.switch_off_cnt>10){
			llc.key_state = key_off;
			llc.switch_cnt=0; 
			llc.fault_num |= BIT(7);
			llc.switch_off_cnt =0;
		}
	}
}

/**
* @function void over_output_voltage_check_app (void)
* @brief    Description: output voltage over check
* @return   
*/
__SECTION(RAMCODE)
void over_output_voltage_check_app(void)
{
	if(llc.vout_raw > (int16_t)VOUT_OV_POINT)
    {
        llc.is_ovp = 1;
        llc.fault_num |=BIT(5);
		llc.llc_unovp_count = 0;
    }
    else if(llc.vout_raw <=(int16_t)VOUT_UNOV_POINT)
	{
		if(llc.llc_unovp_count++>=1000)
		{
			llc.llc_unovp_count = 0;
			llc.is_ovp = 0;
			llc.fault_num &= ~BIT(5);
		}

    }
}                                                                                 
/**
* @function void over_dc_voltage_check_app (void)
* @brief    Description: app over dcbus voltage check
* @return   
*/
__SECTION(RAMCODE)
void input_dcbus_voltage_check_app (void)
{
	static uint16_t count = 0;
    if(llc.is_vbus_ok)
    {
        if(LL_GPIO_ReadPin(GPIOD,GPIO_PIN_2) == GPIO_PIN_SET)
        {
            count++;
            if(count > 5)//about 
            {
                llc.is_vbus_ok = 0;
                count = 0;
				llc.fault_num |= BIT(11);
            }
        }
        else
        {
            count = 0;
        }  
    }
    else
    {
        if(LL_GPIO_ReadPin(GPIOD,BIT(2))  == GPIO_PIN_RESET)
        {
            count++;
            if(count > 2500)//about 25ms
            {
                llc.is_vbus_ok = 1;
                count = 0;
				llc.fault_num &= ~BIT(11);
            }
        }
        else
        {
            count = 0;
        }
    }
}
/**
* @function void over_input_current_check_app (void)
* @brief    Description: app over input current check
* @return   
*/
__SECTION(RAMCODE)
void over_output_current_check_app (void)
{
	static uint32_t oc_count = 0;
	if(llc.iout_raw > IOUT_SC_POINT)
	{
		llc.is_ocp = 1;
		llc.fault_num |=BIT(6);
	}
	else if(llc.iout_raw > IOUT_OC_POINT)
	{
		if(oc_count++ > LLC_OPP2_COUNT)
		{
			oc_count = 0;
			llc.is_ocp = 1;
			llc.fault_num |=BIT(7);
		}
	}
	else
	{
		oc_count = 0;
//		llc.is_ocp = 0;
//		llc.fault_num &= ~BIT(7);
//		llc.fault_num &= ~BIT(6);
	}
}

__SECTION(RAMCODE)
void over_temp_check(void)
{
	if(llc.temperature_raw<4739) //大于75℃
	{
		llc.fault_num |= BIT(8);
		llc.is_otp = 1;
	}else if(llc.temperature_raw>9850)//小于50℃恢复
	{
		llc.fault_num &= ~BIT(8);
		llc.is_otp = 0;
	}
}



__SECTION(RAMCODE)
void openloop_check(void)
{
	if(llc.state == State_rampup && llc.vout_raw<=VOUT_SET_POINT)
	{
		llc.llc_open_loop_count++;
	}else
	{
		llc.llc_open_loop_count = 0;
	}
	if(llc.llc_open_loop_count >= 500)
	{
		llc.fault_num |=BIT(10);
		
	}
}


__SECTION(RAMCODE)
void fault_check_app (void)
{
	over_output_voltage_check_app();  //LLC output voltage 
	input_dcbus_voltage_check_app();
	over_output_current_check_app();
	switch_state_check_app();
	over_temp_check();
}
/**@*/

