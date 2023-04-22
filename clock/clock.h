#ifndef IMX8MQ_CLOCK_H_
#define IMX8MQ_CLOCK_H_

#include "common_type.h"

#define CCM_PLL_NUM 39
#define CCGR_PLL_NUM 191
#define TARGET_NUM 125

#define XTAL1_REG_BASE 0x30270000
#define XTAL2_REG_BASE 0x30278000

#define SSCG_PLL_REF_DIVR2_MASK		(0x3f << 19)
#define SSCG_PLL_OUTPUT_DIV_VAL_MASK (0x3f<<1)
#define SSCG_PLL_FEEDBACK_DIV_F2_MASK (0x3f << 7) 
#define SSCG_PLL_FEEDBACK_DIV_F1_MASK	(0x3f << 13)

#define SSCG_PLL_OUTPUT_DIV_VAL(n)	(((n) << 1) & \
			SSCG_PLL_OUTPUT_DIV_VAL_MASK)
#define SSCG_PLL_FEEDBACK_DIV_F2_VAL(n)	(((n) << 7) & \
			SSCG_PLL_FEEDBACK_DIV_F2_MASK)
#define SSCG_PLL_FEEDBACK_DIV_F1_VAL(n)	(((n) << 13) & \
			SSCG_PLL_FEEDBACK_DIV_F1_MASK)
#define SSCG_PLL_REF_DIVR2_VAL(n)	(((n) << 19) & SSCG_PLL_REF_DIVR2_MASK)

#define SSCG_PLL_PD_MASK (1<<7)
#define SSCG_PLL_DRAM_PLL_CLKE_MASK	(1<<9)
#define SSCG_PLL_BYPASS1_MASK (1<<5)
#define SSCG_PLL_BYPASS2_MASK (1<<4)
#define SSCG_PLL_LOCK_MASK (1<<31)

#define CLK_ROOT_ON		(1<<28) 
#define CLK_ROOT_SOURCE_SEL(n)	(((n) & 0x7) << 24)
#define CLK_ROOT_PRE_DIV(n)	(((n) << 16) & 0x00070000)

typedef enum
{
    OSC_XTAL1=0,      /* default 25M */
    OSC_XTAL2,  /* default 27M */
} T_OSC_TYPE;

typedef enum
{
    PLL_SRC_XTAL1=0,
    PLL_SRC_XTAL2,
    PLL_SRC_HDMI,
    PLL_SRC_P_N,
} T_PLL_SRC;

typedef enum
{
    XTAL_MODE = 0, /* osc output is used as root clock */
    BYPASS_MODE, /* extal is used as root clock */
} T_OSC_MODE;

typedef enum
{
    AUDIO_PLL1 = 0,
    AUDIO_PLL2,
    VIDEO_PLL1,
    GPU_PLL,
    VPU_PLL,
    ARM_PLL,
    SYS_PLL1,
    SYS_PLL2,
    SYS_PLL3,
    VIDEO_PLL2,
    DRAM_PLL,
}T_PLL_TYPE;

typedef enum {
	CCGR_DVFS = 0,
	CCGR_ANAMIX = 1,
	CCGR_CPU = 2,
	CCGR_CSU = 4,
	CCGR_DRAM1 = 5,
	CCGR_DRAM2_OBSOLETE = 6,
	CCGR_ECSPI1 = 7,
	CCGR_ECSPI2 = 8,
	CCGR_ECSPI3 = 9,
	CCGR_ENET1 = 10,
	CCGR_GPIO1 = 11,
	CCGR_GPIO2 = 12,
	CCGR_GPIO3 = 13,
	CCGR_GPIO4 = 14,
	CCGR_GPIO5 = 15,
	CCGR_GPT1 = 16,
	CCGR_GPT2 = 17,
	CCGR_GPT3 = 18,
	CCGR_GPT4 = 19,
	CCGR_GPT5 = 20,
	CCGR_GPT6 = 21,
	CCGR_HS = 22,
	CCGR_I2C1 = 23,
	CCGR_I2C2 = 24,
	CCGR_I2C3 = 25,
	CCGR_I2C4 = 26,
	CCGR_IOMUX = 27,
	CCGR_IOMUX1 = 28,
	CCGR_IOMUX2 = 29,
	CCGR_IOMUX3 = 30,
	CCGR_IOMUX4 = 31,
	CCGR_M4 = 32,
	CCGR_MU = 33,
	CCGR_OCOTP = 34,
	CCGR_OCRAM = 35,
	CCGR_OCRAM_S = 36,
	CCGR_PCIE = 37,
	CCGR_PERFMON1 = 38,
	CCGR_PERFMON2 = 39,
	CCGR_PWM1 = 40,
	CCGR_PWM2 = 41,
	CCGR_PWM3 = 42,
	CCGR_PWM4 = 43,
	CCGR_QOS = 44,
	CCGR_DISMIX = 45,
	CCGR_MEGAMIX = 46,
	CCGR_QSPI = 47,
	CCGR_RAWNAND = 48,
	CCGR_RDC = 49,
	CCGR_ROM = 50,
	CCGR_SAI1 = 51,
	CCGR_SAI2 = 52,
	CCGR_SAI3 = 53,
	CCGR_SAI4 = 54,
	CCGR_SAI5 = 55,
	CCGR_SAI6 = 56,
	CCGR_SCTR = 57,
	CCGR_SDMA1 = 58,
	CCGR_SDMA2 = 59,
	CCGR_SEC_DEBUG = 60,
	CCGR_SEMA1 = 61,
	CCGR_SEMA2 = 62,
	CCGR_SIM_DISPLAY = 63,
	CCGR_SIM_ENET = 64,
	CCGR_SIM_M = 65,
	CCGR_SIM_MAIN = 66,
	CCGR_SIM_S = 67,
	CCGR_SIM_WAKEUP = 68,
	CCGR_SIM_USB = 69,
	CCGR_SIM_VPU = 70,
	CCGR_SNVS = 71,
	CCGR_TRACE = 72,
	CCGR_UART1 = 73,
	CCGR_UART2 = 74,
	CCGR_UART3 = 75,
	CCGR_UART4 = 76,
	CCGR_USB_CTRL1 = 77,
	CCGR_USB_CTRL2 = 78,
	CCGR_USB_PHY1 = 79,
	CCGR_USB_PHY2 = 80,
	CCGR_USDHC1 = 81,
	CCGR_USDHC2 = 82,
	CCGR_WDOG1 = 83,
	CCGR_WDOG2 = 84,
	CCGR_WDOG3 = 85,
	CCGR_VA53 = 86,
	CCGR_GPU = 87,
	CCGR_HEVC = 88,
	CCGR_AVC = 89,
	CCGR_VP9 = 90,
	CCGR_HEVC_INTER = 91,
	CCGR_GIC = 92,
	CCGR_DISPLAY = 93,
	CCGR_HDMI = 94,
	CCGR_HDMI_PHY = 95,
	CCGR_XTAL = 96,
	CCGR_PLL = 97,
	CCGR_TSENSOR = 98,
	CCGR_VPU_DEC = 99,
	CCGR_PCIE2 = 100,
	CCGR_MIPI_CSI1 = 101,
	CCGR_MIPI_CSI2 = 102,
	CCGR_MAX,
}T_CCGR_INDEX;

typedef enum
{
	ARM_PLL_CLK = 12,
	GPU_PLL_CLK = 13,
	VPU_PLL_CLK = 14,
	DRAM_PLL1 = 15,
	SYS_PLL1_CLK = 16,
	SYS_PLL1_DIV2 = 17,
	SYS_PLL1_DIV3 = 18,
	SYS_PLL1_DIV4 = 19,
	SYS_PLL1_DIV5 = 20,
	SYS_PLL1_DIV6 = 21,
	SYS_PLL1_DIV8 = 22,
	SYS_PLL1_DIV10 = 23,
	SYS_PLL1_DIV20 = 24,
	SYS_PLL2_CLK = 25,
	SYS_PLL2_DIV2 = 26,
	SYS_PLL2_DIV3 = 27,
	SYS_PLL2_DIV4 = 28,
	SYS_PLL2_DIV5 = 29,
	SYS_PLL2_DIV6 = 30,
	SYS_PLL2_DIV8 = 31,
	SYS_PLL2_DIV10 = 32,
	SYS_PLL2_DIV20 = 33,
	SYS_PLL3_CLK = 34,
	AUDIO_PLL1_CLK = 35,
	AUDIO_PLL2_CLK = 36,
	VIDEO_PLL1_CLK = 37,
	VIDEO_PLL2_CLK = 38,
}T_PLL_INDEX;

enum dram_pll_out_val {
	DRAM_PLL_OUT_100M,
	DRAM_PLL_OUT_167M,
	DRAM_PLL_OUT_266M,
	DRAM_PLL_OUT_667M,
	DRAM_PLL_OUT_400M,
	DRAM_PLL_OUT_600M,
	DRAM_PLL_OUT_700M,
	DRAM_PLL_OUT_750M,
	DRAM_PLL_OUT_800M,
};

enum dram_bypassclk_val {
	DRAM_BYPASSCLK_100M,
	DRAM_BYPASSCLK_250M,
	DRAM_BYPASSCLK_400M,
};

typedef struct
{
	UINT32 uiPllCtrl;
	UINT32 uiPllCtrlSet;
	UINT32 uiPllCtrlClr;
} T_PLL_CTRL;

typedef struct
{
    volatile UINT32 uiRootCtrl;
    volatile UINT32 uiRootSet;
    volatile UINT32 uiRootClr;
    volatile UINT32 uiRootTog;
} T_ROOT_CTRL;

typedef struct
{
    T_ROOT_CTRL tTarget;
    T_ROOT_CTRL tMisc;
    T_ROOT_CTRL tPost;
    T_ROOT_CTRL tPre;
    UINT32 aucRecv[12];
    T_ROOT_CTRL tAccess;
} T_TARGET_ROOT;

typedef struct
{
    T_OSC_TYPE tOscType; /* 需要设置哪个外部晶振 */
    UINT32 uiOscFreq; /* 外部晶振的频率，单位hz */
    T_OSC_MODE tOscMode;   
} T_OSC_TYPEDEF;

typedef struct
{
    T_PLL_TYPE tPllType;
    
} T_PLL_TYPEDEF;

typedef struct
{
    T_PLL_SRC tPllSrc;
    T_OSC_TYPEDEF tOscTypeDef;
    T_PLL_TYPEDEF tPllTypeDef;
} T_CLOCK_TYPEDEF;

typedef struct
{
    volatile UINT32 uiXtalCfg;
    volatile UINT32 uiXtalTest;
} T_OSC_REG;

typedef struct
{
	unsigned int uiSysCfg0;
	unsigned int uiSysCfg1;
	unsigned int uiSysCfg2;
} T_SYS_PLL_REG;

typedef struct
{
	UINT32 uiCcgr;
	UINT32 uiCcgrSet;
	UINT32 uiCcgrClr;
	UINT32 uiCcgrTog;
} T_CCGR_TYPEDEF;

struct anamix_pll {
	UINT32 audio_pll1_cfg0;
	UINT32 audio_pll1_cfg1;
	UINT32 audio_pll2_cfg0;
	UINT32 audio_pll2_cfg1;
	UINT32 video_pll_cfg0;
	UINT32 video_pll_cfg1;
	UINT32 gpu_pll_cfg0;
	UINT32 gpu_pll_cfg1;
	UINT32 vpu_pll_cfg0;
	UINT32 vpu_pll_cfg1;
	UINT32 arm_pll_cfg0;
	UINT32 arm_pll_cfg1;
	UINT32 sys_pll1_cfg0;
	UINT32 sys_pll1_cfg1;
	UINT32 sys_pll1_cfg2;
	UINT32 sys_pll2_cfg0;
	UINT32 sys_pll2_cfg1;
	UINT32 sys_pll2_cfg2;
	UINT32 sys_pll3_cfg0;
	UINT32 sys_pll3_cfg1;
	UINT32 sys_pll3_cfg2;
	UINT32 video_pll2_cfg0;
	UINT32 video_pll2_cfg1;
	UINT32 video_pll2_cfg2;
	UINT32 dram_pll_cfg0;
	UINT32 dram_pll_cfg1;
	UINT32 dram_pll_cfg2;
	UINT32 digprog;
	UINT32 osc_misc_cfg;
	UINT32 pllout_monitor_cfg;
	UINT32 frac_pllout_div_cfg;
	UINT32 sscg_pllout_div_cfg;
};

void uart_clk_init(E_IMX8M_UART eUart);
void ahb_ipg_clk_init();
void sys_pll_init();
void imx8mq_clk_ccgr_set(T_CCGR_INDEX eCcgrIdx, UINT8 ucIsEnable);
void gic_clk_init();
void ddr_clk_init(void);
void dram_pll_init(enum dram_pll_out_val pll_val);
void dram_disable_bypass(void);
void clk_init(void);

#endif
