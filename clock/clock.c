#include "clock.h"
#include "generic_timer.h"
#include "my_printf.h"

/* ccm相关寄存器定义 */
#if 0
T_ROOT_CTRL *s_ptCcmGpr = (T_ROOT_CTRL *)0x30380000;   /* 0x3038_0000 */
T_ROOT_CTRL *s_aptPllCtrl[CCM_PLL_NUM] = (T_ROOT_CTRL *)0x30380800;
T_ROOT_CTRL *s_aptCcgrCtrl[CCGR_PLL_NUM] = (T_ROOT_CTRL *)0x30384000;
T_TARGET_ROOT *s_aptTarget[TARGET_NUM] = (T_TARGET_ROOT *)0x30388000;
#endif

static void imx8mq_osc_init(T_PLL_SRC tPllSrc, T_OSC_TYPEDEF *ptOsc);

INT32 imx8mq_clk_init(T_CLOCK_TYPEDEF *ptClk)
{
    if (NULL == ptClk)
    {
        return -1;
    }

    if (ptClk->tPllSrc == PLL_SRC_XTAL1 || PLL_SRC_XTAL2 == ptClk->tPllSrc)
    {
        imx8mq_osc_init(ptClk->tPllSrc, &ptClk->tOscTypeDef);
    }

    //sys_pll_init();

    return 0;
}

static void imx8mq_osc_init(T_PLL_SRC tPllSrc, T_OSC_TYPEDEF *ptOsc)
{
    T_OSC_REG *ptOscReg = NULL;
    UINT32 uiRegVal = 0;

    if (tPllSrc == PLL_SRC_XTAL1)
    {
        ptOscReg = (T_OSC_REG *)XTAL1_REG_BASE;
    }
    else
    {
        ptOscReg = (T_OSC_REG *)XTAL2_REG_BASE;
    }

    uiRegVal = ((ptOsc->tOscMode)<<31);

    ptOscReg->uiXtalCfg = uiRegVal;
}

void imx8mq_clk_ccgr_set(T_CCGR_INDEX eCcgrIdx, UINT8 ucIsEnable)
{
	volatile T_CCGR_TYPEDEF *ptCcgrReg = NULL;

	switch(eCcgrIdx)
	{
		case CCGR_UART1:
		{
			ptCcgrReg = (volatile T_CCGR_TYPEDEF * )0x30384490;
			break;
		}

		case CCGR_UART2:
		{
			ptCcgrReg = (volatile T_CCGR_TYPEDEF * )0x303844A0;
			break;
		}

		case CCGR_UART3:
		{
			ptCcgrReg = (volatile T_CCGR_TYPEDEF * )0x303844B0;
			break;
		}

		case CCGR_UART4:
		{
			ptCcgrReg = (volatile T_CCGR_TYPEDEF * )0x303844C0;
			break;
		}

		case CCGR_GIC:
		{
			ptCcgrReg = (volatile T_CCGR_TYPEDEF * )0x303845C0;
			break;
		}
			
		case CCGR_DRAM1:
		{
			ptCcgrReg = (volatile T_CCGR_TYPEDEF *)0x30384050;
			break;
		}
			
		default:
		{
			return;
		}
	}

	if (ucIsEnable == 0)
	{
		ptCcgrReg->uiCcgrClr = 0x03;
	}
	else
	{
		ptCcgrReg->uiCcgrSet = 0x03;
	}
}

static void imx8mq_clk_pll_set(T_PLL_INDEX ePllIdx, UINT8 ucIsEnable)
{
	volatile T_PLL_CTRL *ptPllCtrl = NULL;

	switch(ePllIdx)
	{
		case ARM_PLL_CLK:
		{
			ptPllCtrl = (volatile T_PLL_CTRL * )0x303808C0;
			break;
		}

		case SYS_PLL1_CLK:
		{
			ptPllCtrl = (volatile T_PLL_CTRL * )0x30380900;
			break;
		}

		case SYS_PLL1_DIV2:
		{
			ptPllCtrl = (volatile T_PLL_CTRL * )0x30380910;
			break;
		}

		case SYS_PLL1_DIV3:
		{
			ptPllCtrl = (volatile T_PLL_CTRL * )0x30380920;
			break;
		}

		case SYS_PLL1_DIV4:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380930;
			break;
	    }

		case SYS_PLL1_DIV5:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380940;
			break;
	    }

		case SYS_PLL1_DIV6:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380950;
			break;
	    }

		case SYS_PLL1_DIV8:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380960;
			break;
	    }

		case SYS_PLL1_DIV10:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380970;
			break;
	    }

		case SYS_PLL1_DIV20:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380980;
			break;
	    }

		case SYS_PLL2_CLK:
		{
			ptPllCtrl = (volatile T_PLL_CTRL * )0x30380990;
			break;
		}

		case SYS_PLL2_DIV2:
		{
			ptPllCtrl = (volatile T_PLL_CTRL * )0x303809a0;
			break;
		}

		case SYS_PLL2_DIV3:
		{
			ptPllCtrl = (volatile T_PLL_CTRL * )0x303809b0;
			break;
		}

		case SYS_PLL2_DIV4:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x303809c0;
			break;
	    }

		case SYS_PLL2_DIV5:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x303809d0;
			break;
	    }

		case SYS_PLL2_DIV6:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x303809e0;
			break;
	    }

		case SYS_PLL2_DIV8:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x303809F0;
			break;
	    }

		case SYS_PLL2_DIV10:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380A00;
			break;
	    }

		case SYS_PLL2_DIV20:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380A10;
			break;
	    }

		default:
		{
			return;
		}
	}

	if (ucIsEnable == 0)
	{
		ptPllCtrl->uiPllCtrlClr = 0x03;
	}
	else
	{
		ptPllCtrl->uiPllCtrlSet = 0x03;
	}
}

void _delay(UINT32 uiDelay)
{
	while(uiDelay--);
}

void sys_pll_init()
{
	volatile T_SYS_PLL_REG *ptPll1Reg = (volatile T_SYS_PLL_REG *)0x30360030;
    volatile T_SYS_PLL_REG *ptPll2Reg  = (volatile T_SYS_PLL_REG *)0x3036003C;
    volatile unsigned int *puiGpioData = (volatile unsigned int *)0x30220000;
	UINT32 uiValCfg0 = 0;
	int ret = 0;

    ptPll1Reg->uiSysCfg0 |= (1<<23)|(1<<21)|(1<<19)|(1<<17)|\
							 (1<<15)|(1<<13)|(1<<11)|(1<<9);
	 
	ptPll1Reg->uiSysCfg0 |= 0x20 | 0x10;
	ptPll1Reg->uiSysCfg2 = (3<<13)|(3<<7);
	ptPll1Reg->uiSysCfg1 =0;
	 
	uiValCfg0 =  (1<<25)|(1<<23)|(1<<21)|(1<<19)|(1<<17)|\
				  (1<<15)|(1<<13)|(1<<11)|(1<<9)| (1<<3);
	
	ptPll1Reg->uiSysCfg0 = uiValCfg0 | 0x10;

	udelay(70);
	ptPll1Reg->uiSysCfg0 = uiValCfg0;
	 
	while(1)
	{
		ret = ((ptPll1Reg->uiSysCfg0)>>31) & 0x01;
        if (ret)
        {
            break;
        }
	}	
	
//	my_printf("pll1 cfg0:0x%x\r\n",ptPll1Reg->uiSysCfg0);
	ptPll2Reg->uiSysCfg0 |= (1<<23)|(1<<21)|(1<<19)|(1<<17)|\
							(1<<15)|(1<<13)|(1<<11)|(1<<9);
	
	ptPll2Reg->uiSysCfg0 |= 0x20 | 0x10;
	ptPll2Reg->uiSysCfg2 = (3<<13)|(4<<7);
	ptPll2Reg->uiSysCfg1 =0;
	
	uiValCfg0 =  (1<<25)|(1<<23)|(1<<21)|(1<<19)|(1<<17)|\
				 (1<<15)|(1<<13)|(1<<11)|(1<<9)| (1<<3);
	
	ptPll2Reg->uiSysCfg0 = uiValCfg0 | 0x10;

	udelay(70);
	ptPll2Reg->uiSysCfg0 = uiValCfg0;
	
  
	
	while(1)
	{
		ret = ((ptPll2Reg->uiSysCfg0)>>31) & 0x01;
        if (ret)
        {
            break;
        }
	}	
//	my_printf("pll2 cfg0:0x%x\r\n",ptPll2Reg->uiSysCfg0);	
}

void ahb_ipg_clk_init()
{
	volatile UINT32 *puiAhbClkTarget = (volatile UINT32 *) 0x30389000;

	//imx8mq_clk_ccgr_set(tCcgrIdx, 0);
	*puiAhbClkTarget = (1<<28)|(4<<24); //0<<24
	//imx8mq_clk_ccgr_set(tCcgrIdx, 0);
}

void uart_clk_init(E_IMX8M_UART eUart)
{
	volatile UINT32 *puiUartClkTarget = NULL;
	T_CCGR_INDEX tCcgrIdx;

	switch(eUart)
	{
		case UART1:
		{
			puiUartClkTarget = (volatile UINT32 *)0x3038AF00;
			tCcgrIdx = CCGR_UART1;
			break;
		}

		case UART2:
		{
			puiUartClkTarget = (volatile UINT32 *)0x3038AF80;
			tCcgrIdx = CCGR_UART2;
			break;
		}

		case UART3:
		{
			puiUartClkTarget = (volatile UINT32 *)0x3038B000;
			tCcgrIdx = CCGR_UART3;
			break;
		}

		case UART4:
		{
			puiUartClkTarget = (volatile UINT32 *)0x3038B080;
			tCcgrIdx = CCGR_UART4;
			break;
		}

		default:
		{
			return;
		}
	}

	imx8mq_clk_ccgr_set(tCcgrIdx, 0);
	*puiUartClkTarget = (1<<28)|(1<<24); //(0<<24);//
	imx8mq_clk_ccgr_set(tCcgrIdx, 1);
}

void gic_clk_init()
{
	volatile UINT32 *puiGicClkTarget = (volatile UINT32 *)0x3038B200;
	/* targer 100,selcect 1:pll2_div5 200M */
	imx8mq_clk_ccgr_set(CCGR_GIC, 0);
	*puiGicClkTarget = (1<<28)|(1<<24);
	imx8mq_clk_ccgr_set(CCGR_GIC, 1);
}

void ddr_clk_init()
{
	volatile UINT32 *puiDdrAltTartget = (volatile UINT32 *)0x3038A000;
	volatile UINT32 *puiDdrApbTartget = (volatile UINT32 *)0x3038A080;

	imx8mq_clk_ccgr_set(CCGR_DRAM1, 0);
	/* target 64,select 1:pll1 800M */
	//*puiDdrAltTartget = (1<<28)| (1<<24);
	/* target 65,select 1:pll2_div5 200M */
	*puiDdrApbTartget =  (1<<28)|(1<<24);//(1<<28)|CLK_ROOT_SOURCE_SEL(4) | CLK_ROOT_PRE_DIV(3);//;
	imx8mq_clk_ccgr_set(CCGR_DRAM1, 1);
}

static struct anamix_pll *ana_pll = (struct anamix_pll *)0x30360000;

void dram_pll_init(enum dram_pll_out_val pll_val)
{
	UINT32 *pll_control_reg = &ana_pll->dram_pll_cfg0;
	UINT32 *pll_cfg_reg2 = &ana_pll->dram_pll_cfg2;

	/* Bypass */
	*pll_control_reg |= (1<<5);
	*pll_control_reg |= (1<<4);

	switch (pll_val) {
		case DRAM_PLL_OUT_800M:
	        *pll_cfg_reg2  &= ~(SSCG_PLL_OUTPUT_DIV_VAL_MASK | SSCG_PLL_FEEDBACK_DIV_F2_MASK |
					 SSCG_PLL_FEEDBACK_DIV_F1_MASK | SSCG_PLL_REF_DIVR2_MASK);
			*pll_cfg_reg2 |= SSCG_PLL_OUTPUT_DIV_VAL(0);
			*pll_cfg_reg2 |= SSCG_PLL_FEEDBACK_DIV_F2_VAL(11);
			*pll_cfg_reg2 |= SSCG_PLL_FEEDBACK_DIV_F1_VAL(39);
			*pll_cfg_reg2 |= SSCG_PLL_REF_DIVR2_VAL(29);
			break;
		case DRAM_PLL_OUT_600M:
			*pll_cfg_reg2 &= ~(SSCG_PLL_OUTPUT_DIV_VAL_MASK | SSCG_PLL_FEEDBACK_DIV_F2_MASK |
					 SSCG_PLL_FEEDBACK_DIV_F1_MASK | SSCG_PLL_REF_DIVR2_MASK);
			*pll_cfg_reg2 |= SSCG_PLL_OUTPUT_DIV_VAL(1);
			*pll_cfg_reg2 |= SSCG_PLL_FEEDBACK_DIV_F2_VAL(17);
			*pll_cfg_reg2 |= SSCG_PLL_FEEDBACK_DIV_F1_VAL(39);
			*pll_cfg_reg2 |= SSCG_PLL_REF_DIVR2_VAL(29);
			
			break;
		case DRAM_PLL_OUT_400M:
			*pll_cfg_reg2 &= ~(SSCG_PLL_OUTPUT_DIV_VAL_MASK | SSCG_PLL_FEEDBACK_DIV_F2_MASK |
					 SSCG_PLL_FEEDBACK_DIV_F1_MASK | SSCG_PLL_REF_DIVR2_MASK);
			*pll_cfg_reg2 |= SSCG_PLL_OUTPUT_DIV_VAL(1);
			*pll_cfg_reg2 |= SSCG_PLL_FEEDBACK_DIV_F2_VAL(11);
			*pll_cfg_reg2 |= SSCG_PLL_FEEDBACK_DIV_F1_VAL(39);
			*pll_cfg_reg2 |= SSCG_PLL_REF_DIVR2_VAL(29);
			
			break;
		case DRAM_PLL_OUT_167M:
			*pll_cfg_reg2 &= ~(SSCG_PLL_OUTPUT_DIV_VAL_MASK | SSCG_PLL_FEEDBACK_DIV_F2_MASK |
					 SSCG_PLL_FEEDBACK_DIV_F1_MASK | SSCG_PLL_REF_DIVR2_MASK);
			*pll_cfg_reg2 |= SSCG_PLL_OUTPUT_DIV_VAL(3);
			*pll_cfg_reg2 |= SSCG_PLL_FEEDBACK_DIV_F2_VAL(8);
			*pll_cfg_reg2 |= SSCG_PLL_FEEDBACK_DIV_F1_VAL(45);
			*pll_cfg_reg2 |= SSCG_PLL_REF_DIVR2_VAL(30);
			
			break;
		default:
			break;
	}

	/* Clear power down bit */
	*pll_control_reg &= ~SSCG_PLL_PD_MASK;
	
	/* Eanble ARM_PLL/SYS_PLL  */
	*pll_control_reg |= SSCG_PLL_DRAM_PLL_CLKE_MASK;
	
	/* Clear bypass */
	*pll_control_reg &= ~SSCG_PLL_BYPASS1_MASK;
	udelay(100);
	*pll_control_reg &= ~SSCG_PLL_BYPASS2_MASK;
	
	/* Wait lock */
	while (!((*pll_control_reg) & SSCG_PLL_LOCK_MASK));
}

void dram_disable_bypass(void)
{//48 65
	volatile UINT32 *puiDdrAltTartget = (volatile UINT32 *)0x30389800;//0x3038A000;
	volatile UINT32 *puiDdrApbTartget = (volatile UINT32 *)0x3038A080;
		
	*puiDdrAltTartget = CLK_ROOT_ON | CLK_ROOT_SOURCE_SEL(3);
	*puiDdrApbTartget = (1<<28)|(1<<24);//CLK_ROOT_ON | CLK_ROOT_SOURCE_SEL(4) | CLK_ROOT_PRE_DIV(3);
}


static void osc_init(void)
{
    volatile unsigned int *ptXtal1Cfg = (volatile unsigned int *)0x30270000;
    *ptXtal1Cfg &= (~(0<<31));
    *ptXtal1Cfg |= (0xff<<16);
}

static void arm_clock_init(unsigned int src_freq)
{
    /* pllout=1000MHZ 
       pllout = src_freq/DIVR_VAL * 8 * (1+DIVFI+(DIVFF/2^24))/DIVQ_VAL
       src_freq=24MHZ
       DIVR_VAL=12
       DIVFI=124
    */
    int ret = 0;
    
    volatile unsigned int *ptPllCfg0 = (volatile unsigned int *)0x30360028;
    volatile unsigned int *ptPllCfg1 = (volatile unsigned int *)0x3036002c;
    volatile unsigned int *puiArmTarget = (volatile unsigned int *)0x30388000;

    imx8mq_clk_ccgr_set(CCGR_SCTR, 1);

    *ptPllCfg1 = 0x7c;
    *ptPllCfg0 = (1<<21)|(0<<16)|(1<<15)|(1<<12)|(12<<5)|(0<<0);
#if 1
    while(1)
    {
        ret = ((*ptPllCfg0)>>31) & 0x01;
        if (ret)
        {
            break;
        }
    }
#endif

    *ptPllCfg0 &= ~(1<<12);

    *puiArmTarget = (1<<28)|(1<<24);
    
}



void Delay(unsigned int delay)
{
	while(delay--);
}

void clk_init(void)
{
volatile unsigned int *puiCcgrSctrSet = (volatile unsigned int *)0x30384394;
	/* 配置晶振 */
	osc_init();
	/* 配置arm芯片时钟 */
    arm_clock_init(25000000);
  
	arm_generic_timer_init();
	/* sys pll时钟初始化 */
	sys_pll_init();
	/* 配置ipg_clk */
	ahb_ipg_clk_init();
	/* 配置uart1 clk */
	uart_clk_init(UART1);

	puiCcgrSctrSet = 0x03;	
}