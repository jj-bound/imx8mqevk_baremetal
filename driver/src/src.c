#include "src.h"
#include "generic_timer.h"

void ddr_reset(void)
{
	volatile UINT32 *puiSrcDdr = (volatile UINT32 *)0x30391000;
	volatile UINT32 *puiSrcDdr2 = (volatile UINT32 *)0x30391004;
	
	*puiSrcDdr |= 0xF;
	*puiSrcDdr2 |= 0xF;
	
	udelay(500);
	
	*puiSrcDdr &= ~(0xF);
	*puiSrcDdr2 &= ~(0xF);
}
