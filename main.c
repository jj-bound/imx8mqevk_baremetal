#include "generic_timer.h"
#include "uart.h"
#include "clock.h"
#include "./include/gic/gic.h"
#include "my_printf.h"
#include "ddr.h"

#include "code_relocate.h"

struct sctr_regs {
	unsigned int cntcr;
	unsigned int cntsr;
	unsigned int cntcv1;
	unsigned int cntcv2;
	unsigned int resv1[4];
	unsigned int cntfid0;
	unsigned int cntfid1;
	unsigned int cntfid2;
	unsigned int resv2[1001];
	unsigned int counterid[1];
};


void key_init(void)
{
	volatile UINT32 *puiKeyConf = (volatile UINT32 *)0x30220004;
	volatile UINT32 *puiKeyIcr = (volatile UINT32 *)0x3022000C;
	volatile UINT32 *puiKeyImr = (volatile UINT32 *)0x30220014;
	
	T_GIC_SPI tGicSpi;
	
	*puiKeyConf &= ~(1<<13);
	*puiKeyIcr &= ~(3<<26);
	*puiKeyIcr |= 3<<26;
	
	*puiKeyImr = 1<<13;

#if 1
	tGicSpi.ucIntId = 68;
	tGicSpi.ucPriority = 0;
	//tGicSpi.ptIrqCallBack = key_irq_handler;
	gic_spi_init(&tGicSpi);
#endif
}

void printf_ddr_main(UINT64 ulladdr)
{
	UINT32 *puiVal = ulladdr;
	my_printf("addr 0x%x:0x%x\r\n", ulladdr, *puiVal);
}

int main()
{
	int iRet = 0;
    volatile unsigned int *puiGpioCfg = (volatile unsigned int *)0x30220004;
    volatile unsigned int *puiGpioData = (volatile unsigned int *)0x30220000;
 	volatile unsigned int *puiCcgrSctrSet = (volatile unsigned int *)0x30384394;
	volatile UINT32 *puiKeyState = (volatile UINT32 *)0x30220018;
	
	UINT8 ucKeyState = 0;
	UINT32 uiRegAddr = 0;
	UINT32 uiRegVal = 0;
	UINT32 uiIdx = 0;
	UINT64 ullIntId = 0;
	UINT64 ullCurEl = 0;
	extern char _end[0]  ;
	volatile UINT32 *puiCodeAddr = (volatile UINT32 *)0x40A00000;
	
 	*puiGpioData |= (3<<11);
		
	*puiCcgrSctrSet = 0x03;	
	
	volatile UINT32 *puiDdrAddr = (volatile UINT32 *)(0x40000000);
	*puiDdrAddr = 0;

    gic_init();
	key_init();
	
	my_printf("test1\r\n");
	my_printf("_end:0x%x\r\n",_end );
	my_printf("__rel_dyn_start:0x%x,__rel_dyn_end:0x%x\r\n",__rel_dyn_start, __rel_dyn_end);

	my_printf("cur sp addr:0x%x\r\n", &ucKeyState);

	*puiKeyState = 0xFFFFFFFF;
	

	
#if 1
    while(1)
    {
#if 1		
		*puiGpioData &= ~(3<<11);  
		udelay(1*1000*1000);
		*puiGpioData |= (3<<11);
		mdelay(1000);   
    	//my_printf("test val\r\n");
		//my_printf("%x\r\n", *puiKeyState);
		//my_printf("main func key state:0x%x\r\n", *puiKeyState);
		
		*puiDdrAddr = (*puiDdrAddr)+1;
		my_printf("ddr val:%x\r\n", *puiDdrAddr);
#endif
	}
#endif
    return 0;
}
