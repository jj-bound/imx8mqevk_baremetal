#ifndef GIC_H_
#define GIC_H_

#include "common_type.h"

#define GICD_BASE_ADDRESS 0 /* gic distributor base address */
#define GICD_REG_SIZE 0x10000 /* gic distributor reg size */
#define GICR_BASE_ADDRESS 0x80000 /* gic cpu interface base address */
#define GICR_REG_SIZE 0xC0000 /* gic cpu interfajikzce reg size */
#define RD_BASE 0x0 /* offset by GICR*/
#define SGI_BASE 0x10000 /* offest by GICR*/

#define IMX8MQ_GIC_ADDRESS 0x38800000 /* imx8mq gic400 base address */
#define IMX8MQ_GIC400_GICD_ADDRESS (IMX8MQ_GIC_ADDRESS + GICD_BASE_ADDRESS)
#define IMX8MQ_GIC400_GICR_ADDRESS (IMX8MQ_GIC_ADDRESS + GICR_BASE_ADDRESS)

/* Distributor reg */
#define GICD_CTLR 0x0
#define GICD_TYPE 0x04
#define GICD_IIDR 0x08
#define GICD_TYPE2 0x0c
#define GICD_SETSPI_SR 0x50
#define GICD_IGROUPR 0x80
#define GICD_ISENABLER 0x100
#define GICD_ICENABLER 0x180
#define GICD_ISPENDRn 0x200
#define GICD_ICPENDRn 0x280
#define GICD_ISACTIVERn 0x300
#define GICD_ICACTIVERn 0x380
#define GICD_IPRIORITYR 0x400
#define GICD_ITARGET 0x800
#define GICD_ICFGR 0xc00
#define GICD_IROUTER 0x6000

/* Redistributor reg */
#define GICR_CTLR 0
#define GICR_IIDR 0x04
#define GICR_TYPE 0x08
#define GICR_WAKER 0x14
#define GICR_ICENABLE0 0x180
#define GICR_ICPENDR0 0X280
#define GICR_ICACTIVER0 0x380

#define ICC_IAR0_EL1  S3_0_C12_C8_0

#define GET_PE_AFF_VAL(x) \
({						  \
	__asm__ __volatile__(	\
    "mrs x10, MPIDR_EL1 \n"						\
	"lsr x9, x10, #32 \n"	\
    "bfi x10, x9, #24, #8 \n" \
	"mov %0, x10"	\
	: "=r"(x)	\
	:	\
	:"memory");			 \
 })

#define GET_PE_ACKNOWLEDGE_IRQ(x) \
({		\
	__asm__ __volatile__(	\
   "mrs x10, S3_0_C12_C8_0 \n"	\
   "mov %0, x10"	\
   :"=r"(x) \
   :	\
   :"memory"); \
})

#define END_PE_IRQ(x) \
({	\
	__asm__ __volatile__(	\
   "mov x10, %0\n" \
   "msr S3_0_C12_C8_1, x10" \
   :"=r"(x)	\
   :	\
   :"memory");	\
})

#define GET_CUR_EL(x)   \
({ \
	__asm__ __volatile__( \
	"mrs	%0, CurrentEL\n" \
	:"=r"(x)\
	:\
	:"memory"); \
})

#define GIC_SPI_BASE_INTID 32

typedef enum
{
	REG_WIDTH_32BIT = 0,
	REG_WIDTH_64BIT,
} E_REG_WIDTH;

typedef void (IRQ_CALL_FUNC)(INT32 iIrq, void *pvArg);

typedef struct
{
	UINT8 ucIntId; /* 中断id */
	UINT8 ucPriority; /* 中断优先级 */
	IRQ_CALL_FUNC * ptIrqCallBack;
} T_GIC_SPI;


typedef void (*irq_callback_func)(void);

extern irq_callback_func g_atIrqCallBack[128];

extern void gic_init(void);
extern void gic_write_reg(UINT32 uiRegAddr, UINT32 uiRegVal);
extern void gic_read_reg(UINT32 uiRegAddr, UINT32 *puiRegVal);
extern void gic_spi_init(T_GIC_SPI *ptGicSpi);


#endif
