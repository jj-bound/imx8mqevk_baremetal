
#include "linkage.h"
#include "macro.h"
//#include "exception.h"

/*
 * Vector entry
 */
.align	11
ENTRY(vector_table)
	ventry curr_el_sp0_sync
	ventry curr_el_sp0_irq
	ventry curr_el_sp0_fiq
	ventry curr_el_sp0_serror

	ventry curr_el_spx_sync
	ventry curr_el_spx_irq
	ventry curr_el_spx_fiq
	ventry curr_el_spx_serror

	ventry lower_el_aarch64_sync
	ventry lower_el_aarch64_irq
	ventry lower_el_aarch64_fiq
	ventry lower_el_aarch64_serror

	ventry lower_el_aarch32_sync
	ventry lower_el_aarch32_irq
	ventry lower_el_aarch32_fiq
	ventry lower_el_aarch32_serror
ENDPROC(vector_table)


ENTRY(curr_el_sp0_sync)
	bl _push_stack
	bl do_sp0_sync
	b _pop_stack
ENDPROC(curr_el_sp0_sync)

ENTRY(curr_el_sp0_irq)
	bl _push_stack
	bl do_sp0_irq
	bl _pop_stack
ENDPROC(curr_el_sp0_irq)

ENTRY(curr_el_sp0_fiq)
	bl _push_stack
	bl do_sp0_fiq
	b _pop_stack
ENDPROC(curr_el_sp0_fiq)

ENTRY(curr_el_sp0_serror)
	bl _push_stack
	bl do_sp0_error
	b _pop_stack
ENDPROC(curr_el_sp0_serror)
	
ENTRY(curr_el_spx_sync)
	bl _push_stack
	bl do_spx_sync
	b _pop_stack
ENDPROC(curr_el_spx_sync)

ENTRY(curr_el_spx_irq)
	//bl _push_stack
	stp x28,x29,[sp, #-16]!
	stp x26,x27,[sp, #-16]!
	stp x24,x25,[sp, #-16]!
	stp x22,x23,[sp, #-16]!
	stp x20,x21,[sp, #-16]!
	stp x18,x19,[sp, #-16]!
	stp x16,x17,[sp, #-16]!
	stp x14,x15,[sp, #-16]!
	stp x12,x13,[sp, #-16]!
	stp x10,x11,[sp, #-16]!
	stp x8,x9,[sp, #-16]!
	stp x6,x7,[sp, #-16]!
	stp x4,x5,[sp, #-16]!
	stp x2,x3,[sp, #-16]!
	stp x0,x1,[sp, #-16]!

	mov x21,sp
	mrs x22,elr_el3
	mrs x23,spsr_el3
	stp lr,x21, [sp, #-16]!
	stp x22,x23,[sp, #-16]!
	
	bl do_spx_irq
	//b _pop_stack
	ldp x21,x22,[sp],#16
	msr elr_el3,x21
	msr spsr_el3,x22
	
	ldp lr,x21,[sp],#16
	mov sp,x21
	
	ldp x0,x1, [sp],#16
	ldp x2,x3, [sp],#16
	ldp x4,x5, [sp],#16
	ldp x6,x7, [sp],#16
	ldp x8,x9, [sp],#16
	ldp x10,x11, [sp],#16
	ldp x12,x13, [sp],#16
	ldp x14,x15, [sp],#16
	ldp x16,x17, [sp],#16
	ldp x18,x19, [sp],#16
	ldp x20,x21, [sp],#16
	ldp x22,x23, [sp],#16
	ldp x24,x25, [sp],#16
	ldp x26,x27, [sp],#16
	ldp x28,x29, [sp],#16
	
	eret
ENDPROC(curr_el_spx_irq)

ENTRY(curr_el_spx_fiq)
	bl _push_stack
	bl do_spx_fiq
	b _pop_stack
ENDPROC(curr_el_spx_fiq)

ENTRY(curr_el_spx_serror)
	bl _push_stack
	bl do_spx_serror
	b _pop_stack
ENDPROC(curr_el_spx_serror)

ENTRY(lower_el_aarch64_sync)
	bl _push_stack
	bl do_lower_arch64_sync
	b _pop_stack
ENDPROC(lower_el_aarch64_sync)

ENTRY(lower_el_aarch64_irq)
	bl _push_stack
	bl do_lower_arch64_irq
	b _pop_stack
ENDPROC(lower_el_aarch64_irq)

ENTRY(lower_el_aarch64_fiq)
	bl _push_stack
	bl do_lower_arch64_fiq
	bl _pop_stack
ENDPROC(lower_el_aarch64_fiq)

ENTRY(lower_el_aarch64_serror)
	bl _push_stack
	bl do_lower_arch64_serror
	b _pop_stack
ENDPROC(lower_el_aarch64_serror)

ENTRY(lower_el_aarch32_sync)
	b .
ENDPROC(lower_el_aarch32_sync)

ENTRY(lower_el_aarch32_irq)
	b .
ENDPROC(lower_el_aarch32_irq)

ENTRY(lower_el_aarch32_fiq)
	b .
ENDPROC(lower_el_aarch32_fiq)

ENTRY(lower_el_aarch32_serror)
	b .
ENDPROC(lower_el_aarch32_serror)


ENTRY(_push_stack)
	stp x28,x29,[sp, #-16]!
	stp x26,x27,[sp, #-16]!
	stp x24,x25,[sp, #-16]!
	stp x22,x23,[sp, #-16]!
	stp x20,x21,[sp, #-16]!
	stp x18,x19,[sp, #-16]!
	stp x16,x17,[sp, #-16]!
	stp x14,x15,[sp, #-16]!
	stp x12,x13,[sp, #-16]!
	stp x10,x11,[sp, #-16]!
	stp x8,x9,[sp, #-16]!
	stp x6,x7,[sp, #-16]!
	stp x4,x5,[sp, #-16]!
	stp x2,x3,[sp, #-16]!
	stp x0,x1,[sp, #-16]!

	mov x21,sp
	mrs x22,elr_el3
	mrs x23,spsr_el3
	stp lr,x21, [sp, #-16]!
	stp x22,x23,[sp, #-16]!

	ret
ENDPROC(_push_stack)

ENTRY(_pop_stack)

	ldp x21,x22,[sp],#16
	msr elr_el3,x21
	msr spsr_el3,x22
	
	ldp lr,x21,[sp],#16
	mov sp,x21
	
	ldp x0,x1, [sp],#16
	ldp x2,x3, [sp],#16
	ldp x4,x5, [sp],#16
	ldp x6,x7, [sp],#16
	ldp x8,x9, [sp],#16
	ldp x10,x11, [sp],#16
	ldp x12,x13, [sp],#16
	ldp x14,x15, [sp],#16
	ldp x16,x17, [sp],#16
	ldp x18,x19, [sp],#16
	ldp x20,x21, [sp],#16
	ldp x22,x23, [sp],#16
	ldp x24,x25, [sp],#16
	ldp x26,x27, [sp],#16
	ldp x28,x29, [sp],#16
	msr elr_el3,lr
	eret
ENDPROC(_pop_stack)
