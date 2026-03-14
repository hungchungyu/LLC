#include "main.h"

void iwdg_init(void)
{
	SYSCTRL->KEYR=0x87e4;			//系统寄存器解锁
	SYSCTRL->KEYR=0x8a3d;			//特殊寄存器解锁1
	SYSCTRL->KEYR=0x19ec;			//特殊寄存器解锁2
	SYSCTRL->SYSDCR |=0x1;			//使能IWDG调试
	SYSCTRL->KEYR |= 0x1UL<<16;		//系统寄存器加锁
	SYSCTRL->KEYR |= 0x1UL<<17;		//特殊寄存器加锁	
	
	
	IWDG->KEYR = 0x3FAC;//解锁
	//CR默认复位模式，禁能中断
	//PSCR 4分频
	IWDG->PSCR = 0x01;
	IWDG->RLR = 0xFA0;//500ms
	IWDG->KEYR = 0xAAAA;//加载RLR
	IWDG->KEYR = 0xFFFF;//加锁
	IWDG->KEYR = 0xCCCC;
}