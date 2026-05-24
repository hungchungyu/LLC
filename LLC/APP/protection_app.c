#include "Protection_App.h"

__SECTION(RAMCODE)
void switch_state_check_app(void)
{

}

/**
* @function void over_output_voltage_check_app (void)
* @brief    Description: output voltage over check
* @return   
*/
__SECTION(RAMCODE)
void over_output_voltage_check_app(void)
{

}                                                                                 
/**
* @function void over_dc_voltage_check_app (void)
* @brief    Description: app over dcbus voltage check
* @return   
*/
__SECTION(RAMCODE)
void input_dcbus_voltage_check_app (void)
{

}

__SECTION(RAMCODE)
void over_output_current_check_app (void)
{

}

__SECTION(RAMCODE)
void over_temp_check(void)
{

}



__SECTION(RAMCODE)
void openloop_check(void)
{

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

