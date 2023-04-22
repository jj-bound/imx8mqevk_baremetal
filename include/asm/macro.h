#define CPTR_EL2_RES1		(3 << 12 | 0x3ff)           /* Reserved, RES1 */
/*
 * SCTLR_EL2 bits definitions
 */
#define SCTLR_EL2_RES1		(3 << 28 | 3 << 22 | 1 << 18 | 1 << 16 |\
				 1 << 11 | 3 << 4)	    /* Reserved, RES1 */
#define SCTLR_EL2_EE_LE		(0 << 25) //Exception Little-endian          */
#define SCTLR_EL2_WXN_DIS	(0 << 19) // Write permission is not XN       */
#define SCTLR_EL2_ICACHE_DIS	(0 << 12) // Instruction cache disabled       */
#define SCTLR_EL2_SA_DIS	(0 << 3)  //Stack Alignment Check disabled   */
#define SCTLR_EL2_DCACHE_DIS	(0 << 2)  // Data cache disabled              */
#define SCTLR_EL2_ALIGN_DIS	(0 << 1)  //Alignment check disabled         */
#define SCTLR_EL2_MMU_DIS	(0)       // MMU disabled    

/*
 * SCR_EL3 bits definitions
 */
#define SCR_EL3_RW_AARCH64	(1 << 10) /* Next lower level is AArch64     */
#define SCR_EL3_RW_AARCH32	(0 << 10) /* Lower lowers level are AArch32  */
#define SCR_EL3_HCE_EN		(1 << 8)  /* Hypervisor Call enable          */
#define SCR_EL3_SMD_DIS		(1 << 7)  /* Secure Monitor Call disable     */
#define SCR_EL3_RES1		(3 << 4)  /* Reserved, RES1                  */
#define SCR_EL3_NS_EN		(1 << 0)  /* EL0 and EL1 in Non-scure state  */

/*
 * SPSR_EL3/SPSR_EL2 bits definitions
 */
#define SPSR_EL_END_LE		(0 << 9)  /* Exception Little-endian          */
#define SPSR_EL_DEBUG_MASK	(1 << 9)  /* Debug exception masked           */
#define SPSR_EL_ASYN_MASK	(1 << 8)  /* Asynchronous data abort masked   */
#define SPSR_EL_SERR_MASK	(1 << 8)  /* System Error exception masked    */
#define SPSR_EL_IRQ_MASK	(1 << 7)  /* IRQ exception masked             */
#define SPSR_EL_FIQ_MASK	(1 << 6)  /* FIQ exception masked             */
#define SPSR_EL_T_A32		(0 << 5)  /* AArch32 instruction set A32      */
#define SPSR_EL_M_AARCH64	(0 << 4)  /* Exception taken from AArch64     */
#define SPSR_EL_M_AARCH32	(1 << 4)  /* Exception taken from AArch32     */
#define SPSR_EL_M_SVC		(0x3)     /* Exception taken from SVC mode    */
#define SPSR_EL_M_HYP		(0xa)     /* Exception taken from HYP mode    */
#define SPSR_EL_M_EL1H		(5)       /* Exception taken from EL1h mode   */
#define SPSR_EL_M_EL2H		(9)       /* Exception taken from EL2h mode   */


.macro	switch_el, xreg, el3_label, el2_label, el1_label
	mrs	\xreg, CurrentEL
	cmp	\xreg, 0xc
	b.eq	\el3_label
	cmp	\xreg, 0x8
	b.eq	\el2_label
	cmp	\xreg, 0x4
	b.eq	\el1_label
.endm

.macro ventry, label
.align 7
	b \label
.endm

.macro armv8_switch_to_el2_m, ep, tmp
msr cptr_el3, xzr		/* Disable coprocessor traps to EL3 */
mov \tmp, #CPTR_EL2_RES1
msr cptr_el2, \tmp		/* Disable coprocessor traps to EL2 */

/* Initialize Generic Timers */
msr cntvoff_el2, xzr

ldr	\tmp, =(SCTLR_EL2_RES1 | SCTLR_EL2_EE_LE |\
			SCTLR_EL2_WXN_DIS | SCTLR_EL2_ICACHE_DIS |\
			SCTLR_EL2_SA_DIS | SCTLR_EL2_DCACHE_DIS |\
			SCTLR_EL2_ALIGN_DIS | SCTLR_EL2_MMU_DIS)
msr	sctlr_el2, \tmp

mov \tmp, sp
msr sp_el2, \tmp		/* Migrate SP */
mrs \tmp, vbar_el3
msr vbar_el2, \tmp		/* Migrate VBAR */

ldr \tmp, =(SCR_EL3_RW_AARCH64 | SCR_EL3_HCE_EN |\
		SCR_EL3_SMD_DIS | SCR_EL3_RES1 |\
		SCR_EL3_NS_EN)
msr scr_el3, \tmp
	
		/* Return to the EL2_SP2 mode from EL3 */
ldr \tmp, =(SPSR_EL_DEBUG_MASK | SPSR_EL_SERR_MASK |\
		SPSR_EL_IRQ_MASK | SPSR_EL_FIQ_MASK |\
		SPSR_EL_M_AARCH64 | SPSR_EL_M_EL2H)
msr spsr_el3, \tmp
msr elr_el3, \ep
eret
.endm

