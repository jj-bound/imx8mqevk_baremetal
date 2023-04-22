#include "linkage.h"
#include "macro.h"


/* cpu interface systerm register */
#define ICC_SRE_EL1		S3_0_C12_C12_5
#define ICC_SRE_EL2		S3_4_C12_C9_5
#define ICC_SRE_EL3		S3_6_C12_C12_5

#define ICC_AP0R0_EL1 S3_0_C12_C8_4
#define ICC_AP0R1_EL1 S3_0_C12_C8_5
#define ICC_AP0R2_EL1 S3_0_C12_C8_6
#define ICC_AP0R3_EL1 S3_0_C12_C8_7

#define ICC_AP1R0_EL1 S3_0_C12_C9_0
#define ICC_AP1R1_EL1 S3_0_C12_C9_1
#define ICC_AP1R2_EL1 S3_0_C12_C9_2
#define ICC_AP1R3_EL1 S3_0_C12_C9_3

#define ICC_BPR0_EL1 S3_0_C12_C8_3
#define ICC_BPR1_EL1 S3_0_C12_C12_3

#define ICC_CTLR_EL1 S3_0_C12_C12_4
#define ICC_CTLR_EL3 S3_6_C12_C12_4

#define ICC_DIR_EL1 S3_0_C12_C11_1

#define ICC_EOIR0_EL1 S3_0_C12_C8_1
#define ICC_EOIR1_EL1 S3_0_C12_C12_1

#define ICC_HPPIR0_EL1 S3_0_C12_C8_2
#define ICC_HPPIR1_EL1 S3_0_C12_C12_2

#define ICC_IAR0_EL1  S3_0_C12_C8_0
#define ICC_IAR1_EL1  S3_0_C12_C12_0

#define ICC_IGRPEN0_EL1 S3_0_C12_C12_6
#define ICC_IGRPEN1_EL1 S3_0_C12_C12_7
#define ICC_IGRPEN1_EL3 S3_6_C12_C12_7

#define ICC_PMR_EL1 S3_0_C4_C6_0

#define ICC_RPR_EL1 S3_0_C12_C11_3


ENTRY(gic_cpu_interface_init)
#if 1
	mrs x0, ICC_SRE_EL3
	orr x0, x0,  #0xf//#(1<<0)
	msr ICC_SRE_EL3, x0
	isb
	
	msr ICC_CTLR_EL3, xzr
	isb

	msr ICC_CTLR_EL1, xzr
	isb

	ldr x0, =0xF0
	msr ICC_PMR_EL1, x0

	ldr x0, =0x3
	msr ICC_BPR0_EL1, x0
	msr ICC_BPR1_EL1, x0
	
	mov x10, #0x1
	msr ICC_IGRPEN0_EL1, x10
	ret
#endif
ENDPROC(gic_cpu_interface_init)
