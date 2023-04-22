#include"gic.h"
#include"clock.h"
#include"my_printf.h"

#define GIC_PRINT(fmt, ...) \
	my_printf("[GIC]"fmt"\r\n", ##__VA_ARGS__);

volatile UINT32 *puiGicDistributorBase = (volatile UINT32 *)IMX8MQ_GIC400_GICD_ADDRESS;

irq_callback_func g_atIrqCallBack[128] = {NULL};	

extern void gic_cpu_interface_init();

void gic_write_reg(UINT32 uiRegAddr, UINT32 uiRegVal)
{
	volatile UINT32 *puiRegAddr = (volatile UINT32 *)uiRegAddr;
	//GIC_PRINT("reg addr:0x%x", puiRegAddr);
	*puiRegAddr = uiRegVal;
}

void gic_read_reg(UINT32 uiRegAddr, UINT32 *puiRegVal)
{
	volatile UINT32 *puiRegAddr = (volatile UINT32 *)uiRegAddr;
	//GIC_PRINT("reg addr:0x%x", puiRegAddr);
	*puiRegVal = *puiRegAddr;
}

static void gic_set_reg_bit(UINT32 uiRegAddr, void * pvRegVal, E_REG_WIDTH eRegWidth)
{	
	switch(eRegWidth)
	{
		case REG_WIDTH_32BIT:
		{
			UINT32 *puiRegVal = (UINT32 *)pvRegVal;
			gic_write_reg(uiRegAddr, *puiRegVal);
			break;
		}
		
		case REG_WIDTH_64BIT:
		{
			UINT64 *pullRegVal = (UINT64 *)pvRegVal;
			volatile UINT64 *pullRegAddr = (volatile UINT64 *)uiRegAddr;
			*pullRegAddr = *pullRegVal;
			break;
		}
			
		default:
		{
			GIC_PRINT("error reg width");
			break;
		}
	}
}

static void gic_set_router(UINT64 ullAffVal)
{
	UINT32 uiIdx = 0;
	UINT32 uiRegVal = 0;
	UINT32 uiRegAddr = 0;
	
	for (uiIdx = 32; uiIdx < 1019; uiIdx++)
	{		
		uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS + GICD_IROUTER + uiIdx * sizeof(UINT64);
		//gic_set_reg_bit(uiRegAddr, &ullRegVal, REG_WIDTH_64BIT);
		uiRegVal = ullAffVal;/*(((ullAffVal>>16)&0xFF)<<16) | \
				   (((ullAffVal>>8)&0xFF)<<8) | \
				   (ullAffVal&0xFF);*/
		gic_write_reg(uiRegAddr, uiRegVal);
		
		//GIC_PRINT("-------------route-0x%#x----uiIdx:0x%x", uiRegAddr, uiIdx);
		//GIC_PRINT("route val1:0x%x", uiRegVal);
		uiRegVal = (ullAffVal >> 32);//(ullAffVal>>24)&0xFF;
		//GIC_PRINT("route val1:0x%x", uiRegVal);
		uiRegAddr += sizeof(UINT32);
		gic_write_reg(uiRegAddr,uiRegVal);
	}
}

static void gic_distributor_init()
{
	UINT32 uiRegVal = 0;
	UINT32 uiIdx = 0;
	UINT32 uiRegAddr = 0;
	UINT64 ullAffVal = 0;
	
	uiRegVal = 0; //(1<<2)|(1<<1)|(1<<0)|(1<<5)|(1<<4);
	uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS+GICD_CTLR;
	gic_write_reg(uiRegAddr, uiRegVal);
	
	gic_read_reg(uiRegAddr, &uiRegVal);
	while(uiRegVal & (1<<31) != 0);
	
	uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS+GICD_TYPE;
	gic_read_reg(uiRegAddr, &uiRegVal);
	GIC_PRINT("gic type:0x%x", uiRegVal);
	
	uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS+GICD_IIDR;
	gic_read_reg(uiRegAddr, &uiRegVal);
	GIC_PRINT("gic id:0x%x", uiRegVal);
	
	uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS+GICD_TYPE2;
	gic_read_reg(uiRegAddr, &uiRegVal);
	GIC_PRINT("gic type2:0x%x", uiRegVal);
		
	/* config all level triger */
	for (uiIdx = 0; uiIdx < 64; uiIdx++)
	{
		uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS + GICD_ICFGR + uiIdx * sizeof(UINT32);
		uiRegVal = 0x55555555;
		gic_write_reg(uiRegAddr, uiRegVal);		
	}
	
	for (uiIdx = 0; uiIdx < 255; uiIdx++)
	{
		uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS + GICD_IPRIORITYR + uiIdx * sizeof(UINT32);
		uiRegVal = 0xa0a0a0a0;
		gic_write_reg(uiRegAddr, uiRegVal);		
	}
		
	uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS+GICD_CTLR;
	gic_read_reg(uiRegAddr, &uiRegVal);
	while(uiRegVal & (1<<31) != 0);
	
	
	uiRegVal |= (1<<2)|(1<<1)|(1<<0)|(1<<5)|(1<<4)|(1<<6);
	uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS+GICD_CTLR;
	gic_write_reg(uiRegAddr, uiRegVal);

	for (uiIdx = 0; uiIdx < 32; uiIdx++)
	{
		uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS+GICD_IGROUPR+uiIdx*sizeof(UINT32);
		uiRegVal = 0;
		gic_write_reg(uiRegAddr, uiRegVal);
	}
	
	for (uiIdx = 0; uiIdx < 255; uiIdx++)
	{
		uiRegVal = 0xa0a0a0a0;
		uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS+GICD_IPRIORITYR + uiIdx*sizeof(UINT32);
		gic_write_reg(uiRegAddr, uiRegVal);
	}
	
	/* 获取affinty val */
	GET_PE_AFF_VAL(ullAffVal);
	UINT32 uiAffVal =ullAffVal;
	GIC_PRINT("affval:0x%x", uiAffVal);
	gic_set_router(ullAffVal);	
	
	/* disable all  inter*/
	for (uiIdx = 0; uiIdx < 32; uiIdx++)
	{
		uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS+GICD_ICENABLER+uiIdx*sizeof(UINT32);
		uiRegVal = 0xFFFFFFFF;
		gic_write_reg(uiRegAddr, uiRegVal);
	}
	
	/* clear all pending */
	for (uiIdx = 0; uiIdx < 32; uiIdx++)
	{
		uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS + GICD_ICPENDRn + uiIdx * sizeof(UINT32);
		uiRegVal = 0;
		gic_write_reg(uiRegAddr, uiRegVal);
	}
	
	/* clear all active */
	for (uiIdx = 0; uiIdx < 32; uiIdx++)
	{
		uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS + GICD_ICACTIVERn + uiIdx * sizeof(UINT32);
		uiRegVal = 0;
		gic_write_reg(uiRegAddr, uiRegVal);
	}
}

static void gic_redistributor_init(void)
{
	UINT32 uiRegVal = 0;
	UINT32 uiRegAddr = 0;

#if 0	
	uiRegAddr = IMX8MQ_GIC400_GICR_ADDRESS+RD_BASE+GICR_CTLR;
	gic_read_reg(uiRegAddr, &uiRegVal);
	uiRegVal &= ~(7<<24);
	uiRegVal |= (1<<0);
	uiRegVal |= (1<<2);//~((7<<24)|(1<<0));
	gic_write_reg(uiRegAddr, uiRegVal);
#endif
	
	uiRegAddr = IMX8MQ_GIC400_GICR_ADDRESS+RD_BASE+GICR_IIDR;
	gic_read_reg(uiRegAddr, &uiRegVal);
	GIC_PRINT("GICR_IIDR val:0x%x", uiRegVal);
	
	uiRegAddr = IMX8MQ_GIC400_GICR_ADDRESS+RD_BASE+GICR_TYPE ;
	gic_read_reg(uiRegAddr, &uiRegVal);
	GIC_PRINT("GICR_TYPE val1:0x%x", uiRegVal);
	
	uiRegAddr += 0x4;
	gic_read_reg(uiRegAddr, &uiRegVal);
	GIC_PRINT("GICR_TYPE val2:0x%x", uiRegVal);
	
	uiRegAddr = IMX8MQ_GIC400_GICR_ADDRESS+RD_BASE+GICR_WAKER;
	gic_read_reg(uiRegAddr, &uiRegVal);
	uiRegVal &= ~(1<<1);
	gic_write_reg(uiRegAddr, uiRegVal);
#if 1
	while(1)
	{
		gic_read_reg(uiRegAddr, &uiRegVal);
		GIC_PRINT("GICR_WAKER=0x%x", (uiRegVal&(1<<2)));
		if ((uiRegVal & (1<<2)) == 0)
		{
			break;
		}
	}
#endif
	
	uiRegAddr = IMX8MQ_GIC400_GICR_ADDRESS+RD_BASE+GICR_ICENABLE0;
	uiRegVal = 0xFFFFFFFF;
	gic_write_reg(uiRegAddr, uiRegVal);
	
	uiRegAddr = IMX8MQ_GIC400_GICR_ADDRESS+RD_BASE+GICR_ICPENDR0;
	uiRegVal = 0xFFFFFFFF;
	gic_write_reg(uiRegAddr, uiRegVal);
	
	uiRegAddr = IMX8MQ_GIC400_GICR_ADDRESS+RD_BASE+GICR_ICACTIVER0;
	uiRegVal = 0xFFFFFFFF;
	gic_write_reg(uiRegAddr, uiRegVal);
}

void gic_init()
{
	/* gic时钟初始化 */
	gic_clk_init();
	/* gic distrbutor 初始化 */
	gic_distributor_init();
	/* gic redistributor 初始化 */
	gic_redistributor_init();
	/* gic cpu interface 初始化 */
	gic_cpu_interface_init();
}

void gic_spi_init(T_GIC_SPI *ptGicSpi)
{
	UINT32 uiSpiId = GIC_SPI_BASE_INTID + ptGicSpi->ucIntId;
	UINT32 uiRegAddr = 0;
	UINT32 uiRegBit = 0;
	UINT32 uiRegVal = 0;

#if 1
	g_atIrqCallBack[ptGicSpi->ucIntId] = ptGicSpi->ptIrqCallBack;
	

	/* 设置优先级 */
	uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS + GICD_IPRIORITYR;
	uiRegAddr += (uiSpiId / 4) * sizeof(UINT32);
	uiRegBit = uiSpiId % 4;
	gic_read_reg(uiRegAddr, &uiRegVal);
	
	uiRegVal &= ~(0xFF<<(uiRegBit*4));
	uiRegVal |= (ptGicSpi->ucPriority)<< (uiRegBit*4);
	gic_write_reg(uiRegAddr, uiRegVal);

	GIC_PRINT("uiRegAddr:0x%x, uiRegVal:0x%x,regbit:0x%x",
			  uiRegAddr, uiRegVal, uiRegBit);
	/* 使能中断 */
	uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS + GICD_ISENABLER;
	uiRegAddr += (uiSpiId / 32) * sizeof(UINT32);
	uiRegBit = uiSpiId % 32;
	gic_read_reg(uiRegAddr, &uiRegVal);
	uiRegVal |= 1<<uiRegBit;
	gic_write_reg(uiRegAddr, uiRegVal);
#endif	
#if 0
	uiRegAddr = IMX8MQ_GIC400_GICD_ADDRESS + GICD_SETSPI_SR;
	gic_write_reg(uiRegAddr, uiSpiId);
#endif
}
