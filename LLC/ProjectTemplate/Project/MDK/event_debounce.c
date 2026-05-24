#include "event_debounce.h"
#include "variables_define_app.h"

#define EvtSta(Reg)         ((Reg) & (1L << (15)))
#define SetEvtSta(Reg)      (Reg) = 0x8000
#define ClrEvtSta(Reg)      (Reg) = 0x0000


WORDTYPE PSONOFF_InputStableCount;
WORDTYPE VOUT_OVP_Count;
WORDTYPE RSENSE1_OCP_Count;

void PSONOFF_MonitorEvents(uint16_t HpnCnt, uint16_t RvyCnt)
{
    uint16_t EvtIsHpn;
    uint16_t EvtIsRvy;

#ifndef SCENARIO_DISABLE_PSONOFF_MONITOR
    EvtIsHpn = ONOFF_VALUE();
#else
    EvtIsHpn = 1U;
#endif

    EvtIsRvy = !EvtIsHpn;

    PSONOFF_InputStableCount.val++;

    event_EventIsMatch(&PSONOFF_InputStableCount.val,
                       HpnCnt,
                       RvyCnt,
                       EvtIsHpn,
                       EvtIsRvy);	
	
	if(PSONOFF_InputStableCount.bits.b15)
	{
			StateFlag.bits.ps_on = 1;
	}
	else
	{
			StateFlag.bits.ps_on = 0;
	}
}



void VOUT_OVP_MonitorEvents(uint16_t HpnCnt, uint16_t RvyCnt)
{
    uint16_t EvtIsHpn;
    uint16_t EvtIsRvy;

#ifndef SCENARIO_DISABLE_VOUT_OVP_MONITOR
    EvtIsHpn = (PhyValue.vout.actual_LPF > VOUT_OVP_LEVEL);
#else
    EvtIsHpn = 0U;
#endif

    EvtIsRvy = !EvtIsHpn;

    VOUT_OVP_Count.val++;

    event_EventIsMatch(&VOUT_OVP_Count.val,
                       HpnCnt,
                       RvyCnt,
                       EvtIsHpn,
                       EvtIsRvy);

		if(VOUT_OVP_Count.bits.b15)
		{
			ProtectFlag.bits.vout_ovp = 1;
		}
		else
		{
			ProtectFlag.bits.vout_ovp = 0;
		}

}

void RSENSE1_OCP_MonitorEvents(uint16_t HpnCnt, uint16_t RvyCnt)
{
    uint16_t EvtIsHpn;
    uint16_t EvtIsRvy;

#ifndef SCENARIO_DISABLE_RSENSE1_OCP_MONITOR
    EvtIsHpn = (PhyValue.rsense1.actual_LPF > RSENSE1_OCP_LEVEL);
#else
    EvtIsHpn = 0U;
#endif

    EvtIsRvy = !EvtIsHpn;

    RSENSE1_OCP_Count.val++;

    event_EventIsMatch(&RSENSE1_OCP_Count.val,
                       HpnCnt,
                       RvyCnt,
                       EvtIsHpn,
                       EvtIsRvy);

		if(RSENSE1_OCP_Count.bits.b15)
		{
			ProtectFlag.bits.rsense1_ocp = 1;
		}
		else
		{
			ProtectFlag.bits.rsense1_ocp = 0;
		}

}

void event_EventIsMatch(unsigned int* StaAndTmr, unsigned int HpnMchPnt, unsigned int RvyMchPnt, unsigned short EvtIsHpn, unsigned short EvtIsRvy)
{
    if(EvtSta(*StaAndTmr))
    {
        /* Event Recovery */
        if(EvtIsRvy)
        {
            if((*StaAndTmr & 0x7FFF) >= RvyMchPnt) // Event recovers longer than the defining time.
            {
                ClrEvtSta(*StaAndTmr);  // Clear event status.
            }
        }
        else
        {
            SetEvtSta(*StaAndTmr);      // Set event status.
        }
    }
    else
    {
        /* Event Happen */
        if(EvtIsHpn)
        {
            if((*StaAndTmr & 0x7FFF) >= HpnMchPnt) // Event happens longer than the defining time.
            {
                SetEvtSta(*StaAndTmr);  // Set event status.
            }
        }
        else
        {
            ClrEvtSta(*StaAndTmr);      // Clear event status.
        }
    }
}