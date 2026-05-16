#include "event_debounce.h"


#define EvtSta(Reg)         ((Reg) & (1L << (15)))
#define SetEvtSta(Reg)      (Reg) = 0x8000
#define ClrEvtSta(Reg)      (Reg) = 0x0000


WORDTYPE PSONOFF_InputStableCount;

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