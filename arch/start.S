#include "macro.h"

.text
.global _start
_start:
	ldr x0, =8000000
	msr CNTFRQ_EL0, x0

	ldr x0, =0x187FF0
	mov sp, x0/* ����c����֮ǰ������ջ */
	//msr sp_el3,x0

    ldr w0, =0x30220004 
	ldr w1, [x0]
	orr w1, w1, #(3<<11)
	str w1, [x0]

	msr daifclr, #7
	
	mrs x0, scr_el3
	orr x0, x0, #(7<<1)
	and x0, x0, #(~(1<<0))
	msr scr_el3, x0
	
	adr x0,vector_table
	msr vbar_el3, x0

	bl clk_init
	bl uart_init
	bl ddr_init

	bl copy2ddr

	ldr x0, =0x40900000
	mov sp, x0

	bl clean_bss

	ldr x9, =0x4021F000
	adr lr, main
	add lr,lr,x9
	b fix_rel_addr

    //ldr x9, =0x4021F000 //RELOCATE_OFS
	//ldr x0, =main
	//add x0,x0,x9

	//adr x0, __rel_dyn_start
    //bl printf_ddr_main
	//mov pc, x0
	//ldr pc, =main
	//bl main

halt_loop:
	b halt_loop

