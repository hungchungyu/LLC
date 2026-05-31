#include "Protection_App.h"
#include "event_debounce.h"
#include "state_machine.h"

#define LLC_PROTECT_ISR_PERIOD_US        (20U)

#define TIME_US_TO_COUNT(us)             ((uint16_t)((us) / LLC_PROTECT_ISR_PERIOD_US))


__SECTION(RAMCODE)
void fault_check_app (void)
{
	state_t cur_state;

	cur_state = StateMachine_GetCurrentState();

	if((cur_state > STATE_STANDBY) && (cur_state < STATE_SHUTDOWN))
	{
		VOUT_OVP_MonitorEvents(TIME_US_TO_COUNT(100U), TIME_US_TO_COUNT(20U));
		RSENSE1_OCP_MonitorEvents(TIME_US_TO_COUNT(100U), TIME_US_TO_COUNT(20U));

			if((ProtectFlag.bits.vout_ovp != 0U) ||
			   (ProtectFlag.bits.rsense1_ocp != 0U) ||
			   (ProtectFlag.bits.cmpss_fault != 0U))
			{
				StateMachine_RequestShutdownReset();
			}
	}


}
/**@*/

