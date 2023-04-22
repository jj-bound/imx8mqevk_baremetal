#include "exception.h"
#include "my_printf.h"
#include "gic.h"

void key_irq_handler(void)
{
	volatile UINT32 *puiKeyState = (volatile UINT32 *)0x30220018;
	
	my_printf("irq func 1\r\n");
	if (((*puiKeyState)>>13)& 0x01 == 1)
	{
		my_printf("key irq\r\n");
		/* clear irq state */
		*puiKeyState |= (1<<13);
	}
}

void do_sp0_sync(struct sys_reg *ptSysReg, unsigned int uiEsr)
{
	my_printf("sp0 sync func\r\n");
}

void do_sp0_irq(struct sys_reg *ptSysReg, unsigned int uiEsr)
{
	my_printf("sp0 irq func\r\n");
}

void do_sp0_fiq(struct sys_reg *ptSysReg, unsigned int uiEsr)
{
	my_printf("sp0 fiq func\r\n");
}

void do_sp0_error(struct sys_reg *ptSysReg, unsigned int uiEsr)
{
	my_printf("sp0 error func\r\n");
}

void do_spx_sync(struct sys_reg *ptSysReg, unsigned int uiEsr)
{
	my_printf("spx sync func:0x%x\r\n", uiEsr);
}

void do_spx_irq(struct sys_reg *ptSysReg, unsigned int uiEsr)
{
	UINT64 ullIntId = 0;
	UINT32 uiSpiId = 0;
	volatile UINT32 *puiKeyState = (volatile UINT32 *)0x30220018;
	
	//my_printf("spx irq func\r\n");
	GET_PE_ACKNOWLEDGE_IRQ(ullIntId);
	my_printf("int id:0x%x\r\n", ullIntId);
	uiSpiId = ullIntId;
	END_PE_IRQ(ullIntId);
	
	my_printf("int id2:0x%x\r\n", uiSpiId);
	
	if (uiSpiId == 0x64)
	{
		key_irq_handler();
	}
	
	
	
	my_printf("inter state:0x%x\r\n", *puiKeyState);

}

void do_spx_fiq(struct sys_reg *ptSysReg, unsigned int uiEsr)
{
	my_printf("spx fiq func\r\n");
}

void do_spx_serror(struct sys_reg *ptSysReg, unsigned int uiEsr)
{
	my_printf("spx error func\r\n");
}

void do_lower_arch64_sync(struct sys_reg *ptSysReg, unsigned int uiEsr)
{
	my_printf("arch64 sync func\r\n");
}

void do_lower_arch64_irq(struct sys_reg *ptSysReg, unsigned int uiEsr)
{
	my_printf("arch64 irq func\r\n");
}

void do_lower_arch64_fiq(struct sys_reg *ptSysReg, unsigned int uiEsr)
{
	my_printf("arch64 fiq func\r\n");
}

void do_lower_arch64_serror(struct sys_reg *ptSysReg, unsigned int uiEsr)
{
	my_printf("arch64 error func\r\n");
}
