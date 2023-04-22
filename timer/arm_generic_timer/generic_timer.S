/*
	armv8 通用定时器

*/
#include "linkage.h"

#define GENERIC_TIMER_MAX_FREQENCY (0xFFFFFFFF)
#define GENERIC_TIMER_MAX_CNT (0xFFFFFFFF)

#define TIME_S_TO_US (1000*1000)
#define TIME_S_TO_MS (1000)
/* 错误码定义 */
#define ERROR_FREQENCY (0xFFFFFFFF)
#define ERROR_CNT (-2)

#define CNT_H_CTL ((1<<2)|(1<<1)|(1<<0))

/* 
	arm v8 generic timer init function
	x0:generic timer freqency(0~0xFFFFFFFF)
	x1:generic timer cnt
*/
ENTRY(arm_generic_timer_init) 

ldr x0, =0x30384394
ldr w1, =0x3
str w1, [x0] 

ldr x0, =0x306C0000
ldr w1, [x0]
and w1, w1, #(~((1<<8)|(1<<9)))
orr w1, w1, #(1<<8)
orr w1, w1, #(1<<1)
orr w1, w1, #(1<<0)
str w1, [x0]

mov x0, #3 << 20
msr cpacr_el1, x0


ldr x0,=CNT_H_CTL
msr CNTHCTL_EL2,x0

ldr x0, =((1<<9)|(1<<8)|(1<<2)|(1<<1)|(1<<0))
msr CNTKCTL_EL1,x0


ldr x4, =0x01
msr cntp_ctl_el0, x4

ret
ENDPROC(arm_generic_timer_init)

/* 
	udelay function
	input:
		x0 delay time unit:us
*/

ENTRY(udelay)
/* get arm generic timer freq */
	mrs x1, cntfrq_el0
/* covert to timer cnt per us */
	ldr x2, =TIME_S_TO_US
	udiv x1, x1, x2
/* get timer cnt */
	mul x0, x0, x1

	msr CNTP_TVAL_EL0, x0

1:
	mrs x0, CNTP_CTL_EL0
	and x0,x0, #4
	cmp x0, #4
	b.ne 1b
	
	ret
ENDPROC(udelay)

/* 
	mdelay function
	input:
		x0 delay time unit:ms
*/

ENTRY(mdelay)
/* get arm generic timer freq */
	mrs x1, cntfrq_el0
/* covert to timer cnt per ms */
	ldr x2, =TIME_S_TO_MS
	udiv x1, x1, x2
/* get timer cnt */
	mul x0, x0, x1

	msr CNTP_TVAL_EL0, x0
	
1:
	mrs x0, CNTP_CTL_EL0
	and x0,x0, #4
	cmp x0, #4
	b.ne 1b
	
	ret
ENDPROC(mdelay)

/* 
	delay function
	input:
		x0 delay time unit:s
*/

ENTRY(delay)
	mrs x1, CNTFRQ_EL0
	mul x0,x0,x1

	msr CNTP_TVAL_EL0, x0
2:
	mrs x0, cntp_ctl_el0
	and x0,x0, 0x4
	cmp x0, 0x4
	bne 2b
	
	ret
ENDPROC(delay)

