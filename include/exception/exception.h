#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

struct sys_reg
{
	unsigned long elr;
	unsigned long regs[31];
};

void do_sp0_sync(struct sys_reg *ptSysReg, unsigned int uiEsr);
void do_sp0_irq(struct sys_reg *ptSysReg, unsigned int uiEsr);
void do_sp0_fiq(struct sys_reg *ptSysReg, unsigned int uiEsr);
void do_sp0_error(struct sys_reg *ptSysReg, unsigned int uiEsr);

void do_spx_sync(struct sys_reg *ptSysReg, unsigned int uiEsr);
void do_spx_irq(struct sys_reg *ptSysReg, unsigned int uiEsr);
void do_spx_fiq(struct sys_reg *ptSysReg, unsigned int uiEsr);
void do_spx_serror(struct sys_reg *ptSysReg, unsigned int uiEsr);

void do_lower_arch64_sync(struct sys_reg *ptSysReg, unsigned int uiEsr);
void do_lower_arch64_irq(struct sys_reg *ptSysReg, unsigned int uiEsr);
void do_lower_arch64_fiq(struct sys_reg *ptSysReg, unsigned int uiEsr);
void do_lower_arch64_serror(struct sys_reg *ptSysReg, unsigned int uiEsr);
#endif
