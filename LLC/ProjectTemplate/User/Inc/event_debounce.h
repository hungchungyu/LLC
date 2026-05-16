#ifndef _EVENT_DEBOUNCE_H_
#define _EVENT_DEBOUNCE_H_

#include "utils.h"
#include "main.h"
#include "variables_define_app.h"

typedef unsigned short          BIT;
typedef unsigned short          BYTE;
typedef unsigned short          WORD;
typedef unsigned long           DWORD;
typedef unsigned long long      QWORD;

typedef union WordType
{
    unsigned int val;

    struct
    {
        unsigned b0  : 1;
        unsigned b1  : 1;
        unsigned b2  : 1;
        unsigned b3  : 1;
        unsigned b4  : 1;
        unsigned b5  : 1;
        unsigned b6  : 1;
        unsigned b7  : 1;
        unsigned b8  : 1;
        unsigned b9  : 1;
        unsigned b10 : 1;
        unsigned b11 : 1;
        unsigned b12 : 1;
        unsigned b13 : 1;
        unsigned b14 : 1;
        unsigned b15 : 1;
    }bits;

} WORDTYPE;


extern WORDTYPE PSONOFF_InputStableCount;

void PSONOFF_MonitorEvents(uint16_t HpnCnt, uint16_t RvyCnt);


void event_EventIsMatch(unsigned int* StaAndTmr, unsigned int HpnMchPnt, unsigned int RvyMchPnt, unsigned short EvtIsHpn, unsigned short EvtIsRvy);


#endif