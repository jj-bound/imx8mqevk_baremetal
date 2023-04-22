#ifndef DDR_H_
#define DDR_H_

#include "common_type.h"

#define IMEM_LEN 32768 /* byte */
#define DMEM_LEN 16384 /* byte */
#define IMEM_2D_OFFSET 	49152

#define IMEM_OFFSET_ADDR 0x00050000
#define DMEM_OFFSET_ADDR 0x00054000
#define DDR_TRAIN_CODE_BASE_ADDR 0x3c000000

#define DDRC_DDR_SS_GPR0	0x3d000000
#define SRC_DDRC_RCR_ADDR	0x30391000

#define LPDDR4_HDT_CTL_2D	0xC8  /* stage completion */
#define LPDDR4_HDT_CTL_3200_1D	0xC8  /* stage completion */
#define LPDDR4_HDT_CTL_400_1D	0xC8  /* stage completion */
#define LPDDR4_HDT_CTL_100_1D	0xC8  /* stage completion */

/* 2D share & weight */
#define LPDDR4_2D_WEIGHT	0x1f7f
#define LPDDR4_2D_SHARE		1
#define LPDDR4_CATRAIN_3200_1d	0
#define LPDDR4_CATRAIN_400	0
#define LPDDR4_CATRAIN_100	0
#define LPDDR4_CATRAIN_3200_2d	0

#define WR_POST_EXT_3200  /* recommened to define */

/* lpddr4 phy training config */
/* for LPDDR4 Rtt */
#define LPDDR4_RTT40	6
#define LPDDR4_RTT48	5
#define LPDDR4_RTT60	4
#define LPDDR4_RTT80	3
#define LPDDR4_RTT120	2
#define LPDDR4_RTT240	1
#define LPDDR4_RTT_DIS	0

/* for LPDDR4 Ron */
#define LPDDR4_RON34	7
#define LPDDR4_RON40	6
#define LPDDR4_RON48	5
#define LPDDR4_RON60	4
#define LPDDR4_RON80	3

#define LPDDR4_PHY_ADDR_RON60	0x1
#define LPDDR4_PHY_ADDR_RON40   0x3
#define LPDDR4_PHY_ADDR_RON30   0x7
#define LPDDR4_PHY_ADDR_RON24   0xf
#define LPDDR4_PHY_ADDR_RON20   0x1f

/* for read channel */
#define LPDDR4_RON		LPDDR4_RON40 /* MR3[5:3] */
#define LPDDR4_PHY_RTT		30
#define LPDDR4_PHY_VREF_VALUE 	17

/* for write channel */
#define LPDDR4_PHY_RON		30
#define LPDDR4_PHY_ADDR_RON	LPDDR4_PHY_ADDR_RON40
#define LPDDR4_RTT_DQ		LPDDR4_RTT40 /* MR11[2:0] */
#define LPDDR4_RTT_CA		LPDDR4_RTT40 /* MR11[6:4] */
#define LPDDR4_RTT_CA_BANK0	LPDDR4_RTT40 /* MR11[6:4] */
#define LPDDR4_RTT_CA_BANK1	LPDDR4_RTT40 /* LPDDR4_RTT_DIS//MR11[6:4] */
#define LPDDR4_VREF_VALUE_CA		((1<<6)|(0xd)) /*((0<<6)|(0xe)) MR12 */
#define LPDDR4_VREF_VALUE_DQ_RANK0	((1<<6)|(0xd)) /* MR14 */
#define LPDDR4_VREF_VALUE_DQ_RANK1	((1<<6)|(0xd)) /* MR14 */
#define LPDDR4_MR22_RANK0           	((0<<5)|(1<<4)|(0<<3)|(LPDDR4_RTT40)) /* MR22: OP[5:3]ODTD-CA,CS,CK */
#define LPDDR4_MR22_RANK1		((0<<5)|(1<<4)|(0<<3)|(LPDDR4_RTT40)) /* MR22: OP[5:3]ODTD-CA,CS,CK */
#define LPDDR4_MR3_PU_CAL		1 /* MR3[0] */

#define DDRC_IPS_BASE_ADDR(X)	(0x3d400000 + ((X) * 0x2000000))

#define DDRC_MSTR(X)             (DDRC_IPS_BASE_ADDR(X) + 0x00)
#define DDRC_STAT(X)             (DDRC_IPS_BASE_ADDR(X) + 0x04)
#define DDRC_MSTR1(X)            (DDRC_IPS_BASE_ADDR(X) + 0x08)
#define DDRC_MRCTRL0(X)          (DDRC_IPS_BASE_ADDR(X) + 0x10)
#define DDRC_MRCTRL1(X)          (DDRC_IPS_BASE_ADDR(X) + 0x14)
#define DDRC_MRSTAT(X)           (DDRC_IPS_BASE_ADDR(X) + 0x18)
#define DDRC_MRCTRL2(X)          (DDRC_IPS_BASE_ADDR(X) + 0x1c)
#define DDRC_DERATEEN(X)         (DDRC_IPS_BASE_ADDR(X) + 0x20)
#define DDRC_DERATEINT(X)        (DDRC_IPS_BASE_ADDR(X) + 0x24)
#define DDRC_MSTR2(X)            (DDRC_IPS_BASE_ADDR(X) + 0x28)
#define DDRC_PWRCTL(X)           (DDRC_IPS_BASE_ADDR(X) + 0x30)
#define DDRC_PWRTMG(X)           (DDRC_IPS_BASE_ADDR(X) + 0x34)
#define DDRC_HWLPCTL(X)          (DDRC_IPS_BASE_ADDR(X) + 0x38)
#define DDRC_HWFFCCTL(X)         (DDRC_IPS_BASE_ADDR(X) + 0x3c)
#define DDRC_HWFFCSTAT(X)        (DDRC_IPS_BASE_ADDR(X) + 0x40)
#define DDRC_RFSHCTL0(X)         (DDRC_IPS_BASE_ADDR(X) + 0x50)
#define DDRC_RFSHCTL1(X)         (DDRC_IPS_BASE_ADDR(X) + 0x54)
#define DDRC_RFSHCTL2(X)         (DDRC_IPS_BASE_ADDR(X) + 0x58)
#define DDRC_RFSHCTL3(X)         (DDRC_IPS_BASE_ADDR(X) + 0x60)
#define DDRC_RFSHTMG(X)          (DDRC_IPS_BASE_ADDR(X) + 0x64)
#define DDRC_ECCCFG0(X)          (DDRC_IPS_BASE_ADDR(X) + 0x70)
#define DDRC_ECCCFG1(X)          (DDRC_IPS_BASE_ADDR(X) + 0x74)
#define DDRC_ECCSTAT(X)          (DDRC_IPS_BASE_ADDR(X) + 0x78)
#define DDRC_ECCCLR(X)           (DDRC_IPS_BASE_ADDR(X) + 0x7c)
#define DDRC_ECCERRCNT(X)        (DDRC_IPS_BASE_ADDR(X) + 0x80)
#define DDRC_ECCCADDR0(X)        (DDRC_IPS_BASE_ADDR(X) + 0x84)
#define DDRC_ECCCADDR1(X)        (DDRC_IPS_BASE_ADDR(X) + 0x88)
#define DDRC_ECCCSYN0(X)         (DDRC_IPS_BASE_ADDR(X) + 0x8c)
#define DDRC_ECCCSYN1(X)         (DDRC_IPS_BASE_ADDR(X) + 0x90)
#define DDRC_ECCCSYN2(X)         (DDRC_IPS_BASE_ADDR(X) + 0x94)
#define DDRC_ECCBITMASK0(X)      (DDRC_IPS_BASE_ADDR(X) + 0x98)
#define DDRC_ECCBITMASK1(X)      (DDRC_IPS_BASE_ADDR(X) + 0x9c)
#define DDRC_ECCBITMASK2(X)      (DDRC_IPS_BASE_ADDR(X) + 0xa0)
#define DDRC_ECCUADDR0(X)        (DDRC_IPS_BASE_ADDR(X) + 0xa4)
#define DDRC_ECCUADDR1(X)        (DDRC_IPS_BASE_ADDR(X) + 0xa8)
#define DDRC_ECCUSYN0(X)         (DDRC_IPS_BASE_ADDR(X) + 0xac)
#define DDRC_ECCUSYN1(X)         (DDRC_IPS_BASE_ADDR(X) + 0xb0)
#define DDRC_ECCUSYN2(X)         (DDRC_IPS_BASE_ADDR(X) + 0xb4)
#define DDRC_ECCPOISONADDR0(X)   (DDRC_IPS_BASE_ADDR(X) + 0xb8)
#define DDRC_ECCPOISONADDR1(X)   (DDRC_IPS_BASE_ADDR(X) + 0xbc)
#define DDRC_CRCPARCTL0(X)       (DDRC_IPS_BASE_ADDR(X) + 0xc0)
#define DDRC_CRCPARCTL1(X)       (DDRC_IPS_BASE_ADDR(X) + 0xc4)
#define DDRC_CRCPARCTL2(X)       (DDRC_IPS_BASE_ADDR(X) + 0xc8)
#define DDRC_CRCPARSTAT(X)       (DDRC_IPS_BASE_ADDR(X) + 0xcc)
#define DDRC_INIT0(X)            (DDRC_IPS_BASE_ADDR(X) + 0xd0)
#define DDRC_INIT1(X)            (DDRC_IPS_BASE_ADDR(X) + 0xd4)
#define DDRC_INIT2(X)            (DDRC_IPS_BASE_ADDR(X) + 0xd8)
#define DDRC_INIT3(X)            (DDRC_IPS_BASE_ADDR(X) + 0xdc)
#define DDRC_INIT4(X)            (DDRC_IPS_BASE_ADDR(X) + 0xe0)
#define DDRC_INIT5(X)            (DDRC_IPS_BASE_ADDR(X) + 0xe4)
#define DDRC_INIT6(X)            (DDRC_IPS_BASE_ADDR(X) + 0xe8)
#define DDRC_INIT7(X)            (DDRC_IPS_BASE_ADDR(X) + 0xec)
#define DDRC_DIMMCTL(X)          (DDRC_IPS_BASE_ADDR(X) + 0xf0)
#define DDRC_RANKCTL(X)          (DDRC_IPS_BASE_ADDR(X) + 0xf4)
#define DDRC_DRAMTMG0(X)         (DDRC_IPS_BASE_ADDR(X) + 0x100)
#define DDRC_DRAMTMG1(X)         (DDRC_IPS_BASE_ADDR(X) + 0x104)
#define DDRC_DRAMTMG2(X)         (DDRC_IPS_BASE_ADDR(X) + 0x108)
#define DDRC_DRAMTMG3(X)         (DDRC_IPS_BASE_ADDR(X) + 0x10c)
#define DDRC_DRAMTMG4(X)         (DDRC_IPS_BASE_ADDR(X) + 0x110)
#define DDRC_DRAMTMG5(X)         (DDRC_IPS_BASE_ADDR(X) + 0x114)
#define DDRC_DRAMTMG6(X)         (DDRC_IPS_BASE_ADDR(X) + 0x118)
#define DDRC_DRAMTMG7(X)         (DDRC_IPS_BASE_ADDR(X) + 0x11c)
#define DDRC_DRAMTMG8(X)         (DDRC_IPS_BASE_ADDR(X) + 0x120)
#define DDRC_DRAMTMG9(X)         (DDRC_IPS_BASE_ADDR(X) + 0x124)
#define DDRC_DRAMTMG10(X)        (DDRC_IPS_BASE_ADDR(X) + 0x128)
#define DDRC_DRAMTMG11(X)        (DDRC_IPS_BASE_ADDR(X) + 0x12c)
#define DDRC_DRAMTMG12(X)        (DDRC_IPS_BASE_ADDR(X) + 0x130)
#define DDRC_DRAMTMG13(X)        (DDRC_IPS_BASE_ADDR(X) + 0x134)
#define DDRC_DRAMTMG14(X)        (DDRC_IPS_BASE_ADDR(X) + 0x138)
#define DDRC_DRAMTMG15(X)        (DDRC_IPS_BASE_ADDR(X) + 0x13C)
#define DDRC_DRAMTMG16(X)        (DDRC_IPS_BASE_ADDR(X) + 0x140)
#define DDRC_DRAMTMG17(X)        (DDRC_IPS_BASE_ADDR(X) + 0x144)
#define DDRC_ZQCTL0(X)           (DDRC_IPS_BASE_ADDR(X) + 0x180)
#define DDRC_ZQCTL1(X)           (DDRC_IPS_BASE_ADDR(X) + 0x184)
#define DDRC_ZQCTL2(X)           (DDRC_IPS_BASE_ADDR(X) + 0x188)
#define DDRC_ZQSTAT(X)           (DDRC_IPS_BASE_ADDR(X) + 0x18c)
#define DDRC_DFITMG0(X)          (DDRC_IPS_BASE_ADDR(X) + 0x190)
#define DDRC_DFITMG1(X)          (DDRC_IPS_BASE_ADDR(X) + 0x194)
#define DDRC_DFILPCFG0(X)        (DDRC_IPS_BASE_ADDR(X) + 0x198)
#define DDRC_DFILPCFG1(X)        (DDRC_IPS_BASE_ADDR(X) + 0x19c)
#define DDRC_DFIUPD0(X)          (DDRC_IPS_BASE_ADDR(X) + 0x1a0)
#define DDRC_DFIUPD1(X)          (DDRC_IPS_BASE_ADDR(X) + 0x1a4)
#define DDRC_DFIUPD2(X)          (DDRC_IPS_BASE_ADDR(X) + 0x1a8)
#define DDRC_DFIMISC(X)          (DDRC_IPS_BASE_ADDR(X) + 0x1b0)
#define DDRC_DFITMG2(X)          (DDRC_IPS_BASE_ADDR(X) + 0x1b4)
#define DDRC_DFITMG3(X)          (DDRC_IPS_BASE_ADDR(X) + 0x1b8)
#define DDRC_DFISTAT(X)          (DDRC_IPS_BASE_ADDR(X) + 0x1bc)
#define DDRC_DBICTL(X)           (DDRC_IPS_BASE_ADDR(X) + 0x1c0)
#define DDRC_DFIPHYMSTR(X)       (DDRC_IPS_BASE_ADDR(X) + 0x1c4)
#define DDRC_TRAINCTL0(X)        (DDRC_IPS_BASE_ADDR(X) + 0x1d0)
#define DDRC_TRAINCTL1(X)        (DDRC_IPS_BASE_ADDR(X) + 0x1d4)
#define DDRC_TRAINCTL2(X)        (DDRC_IPS_BASE_ADDR(X) + 0x1d8)
#define DDRC_TRAINSTAT(X)        (DDRC_IPS_BASE_ADDR(X) + 0x1dc)
#define DDRC_ADDRMAP0(X)         (DDRC_IPS_BASE_ADDR(X) + 0x200)
#define DDRC_ADDRMAP1(X)         (DDRC_IPS_BASE_ADDR(X) + 0x204)
#define DDRC_ADDRMAP2(X)         (DDRC_IPS_BASE_ADDR(X) + 0x208)
#define DDRC_ADDRMAP3(X)         (DDRC_IPS_BASE_ADDR(X) + 0x20c)
#define DDRC_ADDRMAP4(X)         (DDRC_IPS_BASE_ADDR(X) + 0x210)
#define DDRC_ADDRMAP5(X)         (DDRC_IPS_BASE_ADDR(X) + 0x214)
#define DDRC_ADDRMAP6(X)         (DDRC_IPS_BASE_ADDR(X) + 0x218)
#define DDRC_ADDRMAP7(X)         (DDRC_IPS_BASE_ADDR(X) + 0x21c)
#define DDRC_ADDRMAP8(X)         (DDRC_IPS_BASE_ADDR(X) + 0x220)
#define DDRC_ADDRMAP9(X)         (DDRC_IPS_BASE_ADDR(X) + 0x224)
#define DDRC_ADDRMAP10(X)        (DDRC_IPS_BASE_ADDR(X) + 0x228)
#define DDRC_ADDRMAP11(X)        (DDRC_IPS_BASE_ADDR(X) + 0x22c)
#define DDRC_ODTCFG(X)           (DDRC_IPS_BASE_ADDR(X) + 0x240)
#define DDRC_ODTMAP(X)           (DDRC_IPS_BASE_ADDR(X) + 0x244)
#define DDRC_SCHED(X)            (DDRC_IPS_BASE_ADDR(X) + 0x250)
#define DDRC_SCHED1(X)           (DDRC_IPS_BASE_ADDR(X) + 0x254)
#define DDRC_PERFHPR1(X)         (DDRC_IPS_BASE_ADDR(X) + 0x25c)
#define DDRC_PERFLPR1(X)         (DDRC_IPS_BASE_ADDR(X) + 0x264)
#define DDRC_PERFWR1(X)          (DDRC_IPS_BASE_ADDR(X) + 0x26c)
#define DDRC_PERFVPR1(X)         (DDRC_IPS_BASE_ADDR(X) + 0x274)
#define DDRC_PERFVPW1(X)         (DDRC_IPS_BASE_ADDR(X) + 0x278)
#define DDRC_DQMAP0(X)           (DDRC_IPS_BASE_ADDR(X) + 0x280)
#define DDRC_DQMAP1(X)           (DDRC_IPS_BASE_ADDR(X) + 0x284)
#define DDRC_DQMAP2(X)           (DDRC_IPS_BASE_ADDR(X) + 0x288)
#define DDRC_DQMAP3(X)           (DDRC_IPS_BASE_ADDR(X) + 0x28c)
#define DDRC_DQMAP4(X)           (DDRC_IPS_BASE_ADDR(X) + 0x290)
#define DDRC_DQMAP5(X)           (DDRC_IPS_BASE_ADDR(X) + 0x294)
#define DDRC_DBG0(X)             (DDRC_IPS_BASE_ADDR(X) + 0x300)
#define DDRC_DBG1(X)             (DDRC_IPS_BASE_ADDR(X) + 0x304)
#define DDRC_DBGCAM(X)           (DDRC_IPS_BASE_ADDR(X) + 0x308)
#define DDRC_DBGCMD(X)           (DDRC_IPS_BASE_ADDR(X) + 0x30c)
#define DDRC_DBGSTAT(X)          (DDRC_IPS_BASE_ADDR(X) + 0x310)
#define DDRC_SWCTL(X)            (DDRC_IPS_BASE_ADDR(X) + 0x320)
#define DDRC_SWSTAT(X)           (DDRC_IPS_BASE_ADDR(X) + 0x324)
#define DDRC_OCPARCFG0(X)        (DDRC_IPS_BASE_ADDR(X) + 0x330)
#define DDRC_OCPARCFG1(X)        (DDRC_IPS_BASE_ADDR(X) + 0x334)
#define DDRC_OCPARCFG2(X)        (DDRC_IPS_BASE_ADDR(X) + 0x338)
#define DDRC_OCPARCFG3(X)        (DDRC_IPS_BASE_ADDR(X) + 0x33c)
#define DDRC_OCPARSTAT0(X)       (DDRC_IPS_BASE_ADDR(X) + 0x340)
#define DDRC_OCPARSTAT1(X)       (DDRC_IPS_BASE_ADDR(X) + 0x344)
#define DDRC_OCPARWLOG0(X)       (DDRC_IPS_BASE_ADDR(X) + 0x348)
#define DDRC_OCPARWLOG1(X)       (DDRC_IPS_BASE_ADDR(X) + 0x34c)
#define DDRC_OCPARWLOG2(X)       (DDRC_IPS_BASE_ADDR(X) + 0x350)
#define DDRC_OCPARAWLOG0(X)      (DDRC_IPS_BASE_ADDR(X) + 0x354)
#define DDRC_OCPARAWLOG1(X)      (DDRC_IPS_BASE_ADDR(X) + 0x358)
#define DDRC_OCPARRLOG0(X)       (DDRC_IPS_BASE_ADDR(X) + 0x35c)
#define DDRC_OCPARRLOG1(X)       (DDRC_IPS_BASE_ADDR(X) + 0x360)
#define DDRC_OCPARARLOG0(X)      (DDRC_IPS_BASE_ADDR(X) + 0x364)
#define DDRC_OCPARARLOG1(X)      (DDRC_IPS_BASE_ADDR(X) + 0x368)
#define DDRC_POISONCFG(X)        (DDRC_IPS_BASE_ADDR(X) + 0x36C)
#define DDRC_POISONSTAT(X)       (DDRC_IPS_BASE_ADDR(X) + 0x370)
#define DDRC_ADVECCINDEX(X)      (DDRC_IPS_BASE_ADDR(X) + 0x3)
#define DDRC_ADVECCSTAT(X)       (DDRC_IPS_BASE_ADDR(X) + 0x3)
#define DDRC_ECCPOISONPAT0(X)    (DDRC_IPS_BASE_ADDR(X) + 0x3)
#define DDRC_ECCPOISONPAT1(X)    (DDRC_IPS_BASE_ADDR(X) + 0x3)
#define DDRC_ECCPOISONPAT2(X)    (DDRC_IPS_BASE_ADDR(X) + 0x3)
#define DDRC_HIFCTL(X)           (DDRC_IPS_BASE_ADDR(X) + 0x3)

#define DDRC_PSTAT(X)            (DDRC_IPS_BASE_ADDR(X) + 0x3fc)
#define DDRC_PCCFG(X)            (DDRC_IPS_BASE_ADDR(X) + 0x400)
#define DDRC_PCFGR_0(X)          (DDRC_IPS_BASE_ADDR(X) + 0x404)
#define DDRC_PCFGR_1(X)          (DDRC_IPS_BASE_ADDR(X) + 1*0xb0+0x404)
#define DDRC_PCFGR_2(X)          (DDRC_IPS_BASE_ADDR(X) + 2*0xb0+0x404)
#define DDRC_PCFGR_3(X)          (DDRC_IPS_BASE_ADDR(X) + 3*0xb0+0x404)
#define DDRC_PCFGW_0(X)          (DDRC_IPS_BASE_ADDR(X) + 0x408)
#define DDRC_PCFGW_1(X)          (DDRC_IPS_BASE_ADDR(X) + 1*0xb0+0x408)
#define DDRC_PCFGW_2(X)          (DDRC_IPS_BASE_ADDR(X) + 2*0xb0+0x408)
#define DDRC_PCFGW_3(X)          (DDRC_IPS_BASE_ADDR(X) + 3*0xb0+0x408)
#define DDRC_PCFGC_0(X)          (DDRC_IPS_BASE_ADDR(X) + 0x40c)
#define DDRC_PCFGIDMASKCH(X)     (DDRC_IPS_BASE_ADDR(X) + 0x410)
#define DDRC_PCFGIDVALUECH(X)    (DDRC_IPS_BASE_ADDR(X) + 0x414)
#define DDRC_PCTRL_0(X)          (DDRC_IPS_BASE_ADDR(X) + 0x490)
#define DDRC_PCTRL_1(X)          (DDRC_IPS_BASE_ADDR(X) + 0x490 + 1*0xb0)
#define DDRC_PCTRL_2(X)          (DDRC_IPS_BASE_ADDR(X) + 0x490 + 2*0xb0)
#define DDRC_PCTRL_3(X)          (DDRC_IPS_BASE_ADDR(X) + 0x490 + 3*0xb0)
#define DDRC_PCFGQOS0_0(X)       (DDRC_IPS_BASE_ADDR(X) + 0x494)
#define DDRC_PCFGQOS1_0(X)       (DDRC_IPS_BASE_ADDR(X) + 0x498)
#define DDRC_PCFGWQOS0_0(X)      (DDRC_IPS_BASE_ADDR(X) + 0x49c)
#define DDRC_PCFGWQOS1_0(X)      (DDRC_IPS_BASE_ADDR(X) + 0x4a0)
#define DDRC_SARBASE0(X)         (DDRC_IPS_BASE_ADDR(X) + 0xf04)
#define DDRC_SARSIZE0(X)         (DDRC_IPS_BASE_ADDR(X) + 0xf08)
#define DDRC_SBRCTL(X)           (DDRC_IPS_BASE_ADDR(X) + 0xf24)
#define DDRC_SBRSTAT(X)          (DDRC_IPS_BASE_ADDR(X) + 0xf28)
#define DDRC_SBRWDATA0(X)        (DDRC_IPS_BASE_ADDR(X) + 0xf2c)
#define DDRC_SBRWDATA1(X)        (DDRC_IPS_BASE_ADDR(X) + 0xf30)
#define DDRC_PDCH(X)             (DDRC_IPS_BASE_ADDR(X) + 0xf34)

#define DDRC_FREQ1_DERATEEN(X)         (DDRC_IPS_BASE_ADDR(X) + 0x2020)
#define DDRC_FREQ1_DERATEINT(X)        (DDRC_IPS_BASE_ADDR(X) + 0x2024)
#define DDRC_FREQ1_RFSHCTL0(X)         (DDRC_IPS_BASE_ADDR(X) + 0x2050)
#define DDRC_FREQ1_RFSHTMG(X)          (DDRC_IPS_BASE_ADDR(X) + 0x2064)
#define DDRC_FREQ1_INIT3(X)            (DDRC_IPS_BASE_ADDR(X) + 0x20dc)
#define DDRC_FREQ1_INIT4(X)            (DDRC_IPS_BASE_ADDR(X) + 0x20e0)
#define DDRC_FREQ1_INIT6(X)            (DDRC_IPS_BASE_ADDR(X) + 0x20e8)
#define DDRC_FREQ1_INIT7(X)            (DDRC_IPS_BASE_ADDR(X) + 0x20ec)
#define DDRC_FREQ1_DRAMTMG0(X)         (DDRC_IPS_BASE_ADDR(X) + 0x2100)
#define DDRC_FREQ1_DRAMTMG1(X)         (DDRC_IPS_BASE_ADDR(X) + 0x2104)
#define DDRC_FREQ1_DRAMTMG2(X)         (DDRC_IPS_BASE_ADDR(X) + 0x2108)
#define DDRC_FREQ1_DRAMTMG3(X)         (DDRC_IPS_BASE_ADDR(X) + 0x210c)
#define DDRC_FREQ1_DRAMTMG4(X)         (DDRC_IPS_BASE_ADDR(X) + 0x2110)
#define DDRC_FREQ1_DRAMTMG5(X)         (DDRC_IPS_BASE_ADDR(X) + 0x2114)
#define DDRC_FREQ1_DRAMTMG6(X)         (DDRC_IPS_BASE_ADDR(X) + 0x2118)
#define DDRC_FREQ1_DRAMTMG7(X)         (DDRC_IPS_BASE_ADDR(X) + 0x211c)
#define DDRC_FREQ1_DRAMTMG8(X)         (DDRC_IPS_BASE_ADDR(X) + 0x2120)
#define DDRC_FREQ1_DRAMTMG9(X)         (DDRC_IPS_BASE_ADDR(X) + 0x2124)
#define DDRC_FREQ1_DRAMTMG10(X)        (DDRC_IPS_BASE_ADDR(X) + 0x2128)
#define DDRC_FREQ1_DRAMTMG11(X)        (DDRC_IPS_BASE_ADDR(X) + 0x212c)
#define DDRC_FREQ1_DRAMTMG12(X)        (DDRC_IPS_BASE_ADDR(X) + 0x2130)
#define DDRC_FREQ1_DRAMTMG13(X)        (DDRC_IPS_BASE_ADDR(X) + 0x2134)
#define DDRC_FREQ1_DRAMTMG14(X)        (DDRC_IPS_BASE_ADDR(X) + 0x2138)
#define DDRC_FREQ1_DRAMTMG15(X)        (DDRC_IPS_BASE_ADDR(X) + 0x213C)
#define DDRC_FREQ1_DRAMTMG16(X)        (DDRC_IPS_BASE_ADDR(X) + 0x2140)
#define DDRC_FREQ1_DRAMTMG17(X)        (DDRC_IPS_BASE_ADDR(X) + 0x2144)
#define DDRC_FREQ1_ZQCTL0(X)           (DDRC_IPS_BASE_ADDR(X) + 0x2180)
#define DDRC_FREQ1_DFITMG0(X)          (DDRC_IPS_BASE_ADDR(X) + 0x2190)
#define DDRC_FREQ1_DFITMG1(X)          (DDRC_IPS_BASE_ADDR(X) + 0x2194)
#define DDRC_FREQ1_DFITMG2(X)          (DDRC_IPS_BASE_ADDR(X) + 0x21b4)
#define DDRC_FREQ1_DFITMG3(X)          (DDRC_IPS_BASE_ADDR(X) + 0x21b8)
#define DDRC_FREQ1_ODTCFG(X)           (DDRC_IPS_BASE_ADDR(X) + 0x2240)

#define DDRC_FREQ2_DERATEEN(X)         (DDRC_IPS_BASE_ADDR(X) + 0x3020)
#define DDRC_FREQ2_DERATEINT(X)        (DDRC_IPS_BASE_ADDR(X) + 0x3024)
#define DDRC_FREQ2_RFSHCTL0(X)         (DDRC_IPS_BASE_ADDR(X) + 0x3050)
#define DDRC_FREQ2_RFSHTMG(X)          (DDRC_IPS_BASE_ADDR(X) + 0x3064)
#define DDRC_FREQ2_INIT3(X)            (DDRC_IPS_BASE_ADDR(X) + 0x30dc)
#define DDRC_FREQ2_INIT4(X)            (DDRC_IPS_BASE_ADDR(X) + 0x30e0)
#define DDRC_FREQ2_INIT6(X)            (DDRC_IPS_BASE_ADDR(X) + 0x30e8)
#define DDRC_FREQ2_INIT7(X)            (DDRC_IPS_BASE_ADDR(X) + 0x30ec)
#define DDRC_FREQ2_DRAMTMG0(X)         (DDRC_IPS_BASE_ADDR(X) + 0x3100)
#define DDRC_FREQ2_DRAMTMG1(X)         (DDRC_IPS_BASE_ADDR(X) + 0x3104)
#define DDRC_FREQ2_DRAMTMG2(X)         (DDRC_IPS_BASE_ADDR(X) + 0x3108)
#define DDRC_FREQ2_DRAMTMG3(X)         (DDRC_IPS_BASE_ADDR(X) + 0x310c)
#define DDRC_FREQ2_DRAMTMG4(X)         (DDRC_IPS_BASE_ADDR(X) + 0x3110)
#define DDRC_FREQ2_DRAMTMG5(X)         (DDRC_IPS_BASE_ADDR(X) + 0x3114)
#define DDRC_FREQ2_DRAMTMG6(X)         (DDRC_IPS_BASE_ADDR(X) + 0x3118)
#define DDRC_FREQ2_DRAMTMG7(X)         (DDRC_IPS_BASE_ADDR(X) + 0x311c)
#define DDRC_FREQ2_DRAMTMG8(X)         (DDRC_IPS_BASE_ADDR(X) + 0x3120)
#define DDRC_FREQ2_DRAMTMG9(X)         (DDRC_IPS_BASE_ADDR(X) + 0x3124)
#define DDRC_FREQ2_DRAMTMG10(X)        (DDRC_IPS_BASE_ADDR(X) + 0x3128)
#define DDRC_FREQ2_DRAMTMG11(X)        (DDRC_IPS_BASE_ADDR(X) + 0x312c)
#define DDRC_FREQ2_DRAMTMG12(X)        (DDRC_IPS_BASE_ADDR(X) + 0x3130)
#define DDRC_FREQ2_DRAMTMG13(X)        (DDRC_IPS_BASE_ADDR(X) + 0x3134)
#define DDRC_FREQ2_DRAMTMG14(X)        (DDRC_IPS_BASE_ADDR(X) + 0x3138)
#define DDRC_FREQ2_DRAMTMG15(X)        (DDRC_IPS_BASE_ADDR(X) + 0x313C)
#define DDRC_FREQ2_DRAMTMG16(X)        (DDRC_IPS_BASE_ADDR(X) + 0x3140)
#define DDRC_FREQ2_DRAMTMG17(X)        (DDRC_IPS_BASE_ADDR(X) + 0x3144)
#define DDRC_FREQ2_ZQCTL0(X)           (DDRC_IPS_BASE_ADDR(X) + 0x3180)
#define DDRC_FREQ2_DFITMG0(X)          (DDRC_IPS_BASE_ADDR(X) + 0x3190)
#define DDRC_FREQ2_DFITMG1(X)          (DDRC_IPS_BASE_ADDR(X) + 0x3194)
#define DDRC_FREQ2_DFITMG2(X)          (DDRC_IPS_BASE_ADDR(X) + 0x31b4)
#define DDRC_FREQ2_DFITMG3(X)          (DDRC_IPS_BASE_ADDR(X) + 0x31b8)
#define DDRC_FREQ2_ODTCFG(X)           (DDRC_IPS_BASE_ADDR(X) + 0x3240)

#define DDRC_FREQ3_DERATEEN(X)         (DDRC_IPS_BASE_ADDR(X) + 0x4020)
#define DDRC_FREQ3_DERATEINT(X)        (DDRC_IPS_BASE_ADDR(X) + 0x4024)
#define DDRC_FREQ3_RFSHCTL0(X)         (DDRC_IPS_BASE_ADDR(X) + 0x4050)
#define DDRC_FREQ3_RFSHTMG(X)          (DDRC_IPS_BASE_ADDR(X) + 0x4064)
#define DDRC_FREQ3_INIT3(X)            (DDRC_IPS_BASE_ADDR(X) + 0x40dc)
#define DDRC_FREQ3_INIT4(X)            (DDRC_IPS_BASE_ADDR(X) + 0x40e0)
#define DDRC_FREQ3_INIT6(X)            (DDRC_IPS_BASE_ADDR(X) + 0x40e8)
#define DDRC_FREQ3_INIT7(X)            (DDRC_IPS_BASE_ADDR(X) + 0x40ec)
#define DDRC_FREQ3_DRAMTMG0(X)         (DDRC_IPS_BASE_ADDR(X) + 0x4100)
#define DDRC_FREQ3_DRAMTMG1(X)         (DDRC_IPS_BASE_ADDR(X) + 0x4104)
#define DDRC_FREQ3_DRAMTMG2(X)         (DDRC_IPS_BASE_ADDR(X) + 0x4108)
#define DDRC_FREQ3_DRAMTMG3(X)         (DDRC_IPS_BASE_ADDR(X) + 0x410c)
#define DDRC_FREQ3_DRAMTMG4(X)         (DDRC_IPS_BASE_ADDR(X) + 0x4110)
#define DDRC_FREQ3_DRAMTMG5(X)         (DDRC_IPS_BASE_ADDR(X) + 0x4114)
#define DDRC_FREQ3_DRAMTMG6(X)         (DDRC_IPS_BASE_ADDR(X) + 0x4118)
#define DDRC_FREQ3_DRAMTMG7(X)         (DDRC_IPS_BASE_ADDR(X) + 0x411c)
#define DDRC_FREQ3_DRAMTMG8(X)         (DDRC_IPS_BASE_ADDR(X) + 0x4120)
#define DDRC_FREQ3_DRAMTMG9(X)         (DDRC_IPS_BASE_ADDR(X) + 0x4124)
#define DDRC_FREQ3_DRAMTMG10(X)        (DDRC_IPS_BASE_ADDR(X) + 0x4128)
#define DDRC_FREQ3_DRAMTMG11(X)        (DDRC_IPS_BASE_ADDR(X) + 0x412c)
#define DDRC_FREQ3_DRAMTMG12(X)        (DDRC_IPS_BASE_ADDR(X) + 0x4130)
#define DDRC_FREQ3_DRAMTMG13(X)        (DDRC_IPS_BASE_ADDR(X) + 0x4134)
#define DDRC_FREQ3_DRAMTMG14(X)        (DDRC_IPS_BASE_ADDR(X) + 0x4138)
#define DDRC_FREQ3_DRAMTMG15(X)        (DDRC_IPS_BASE_ADDR(X) + 0x413C)
#define DDRC_FREQ3_DRAMTMG16(X)        (DDRC_IPS_BASE_ADDR(X) + 0x4140)

#define DDRC_FREQ3_ZQCTL0(X)           (DDRC_IPS_BASE_ADDR(X) + 0x4180)
#define DDRC_FREQ3_DFITMG0(X)          (DDRC_IPS_BASE_ADDR(X) + 0x4190)
#define DDRC_FREQ3_DFITMG1(X)          (DDRC_IPS_BASE_ADDR(X) + 0x4194)
#define DDRC_FREQ3_DFITMG2(X)          (DDRC_IPS_BASE_ADDR(X) + 0x41b4)
#define DDRC_FREQ3_DFITMG3(X)          (DDRC_IPS_BASE_ADDR(X) + 0x41b8)
#define DDRC_FREQ3_ODTCFG(X)           (DDRC_IPS_BASE_ADDR(X) + 0x4240)
#define DDRC_DFITMG0_SHADOW(X)         (DDRC_IPS_BASE_ADDR(X) + 0x2190)
#define DDRC_DFITMG1_SHADOW(X)         (DDRC_IPS_BASE_ADDR(X) + 0x2194)
#define DDRC_DFITMG2_SHADOW(X)         (DDRC_IPS_BASE_ADDR(X) + 0x21b4)
#define DDRC_DFITMG3_SHADOW(X)         (DDRC_IPS_BASE_ADDR(X) + 0x21b8)
#define DDRC_ODTCFG_SHADOW(X)          (DDRC_IPS_BASE_ADDR(X) + 0x2240)

typedef enum{
	E_DDR_TYPE_LPDDR4 = 0, 
} E_DDR_TYPE;

enum fw_type {
	FW_1D_IMAGE,
	FW_2D_IMAGE,
};

typedef struct{
	unsigned int uiMstr;  /* offset 0 */
    unsigned int uiOpStat;  //0x4
    unsigned int auiRecv1[2]; //0x8
    unsigned int uiMrctrl0; //0x10
    unsigned int uiMrctrl1;  //0x14
    unsigned int uiMrStat; //0x18
    unsigned int uiMrctrl2; //0x1C
    unsigned int uiDeratEn; //0x20
    unsigned int uiDeratEint; //0x24
    unsigned int auiRecv2[2];  //0x28
    unsigned int uiPwrCtrl;  //0x30
    unsigned int uiPwrTmg;   //0x34
    unsigned int uiHwlpCtl;  //0x38
    unsigned int auiRecv3[5]; //0x3C
    unsigned int uiRfshCtrl0; //0x50
    unsigned int uiRfshCtrl1; //0x54
    unsigned int auiRecv4[2]; //0x58
    unsigned int uiRfshCtrl3; //0x60
    unsigned int uiRfshTmg; //0x64
    unsigned int auiRecv5[22]; // 0x68
    unsigned int uiCrcParCtl0; //0xc0
    unsigned int uiCrcParCtl1; //0xc4
    unsigned int auiRecv6[1]; //0xc8
    unsigned int uiCrcParStat; //0xcc
    unsigned int uiSdramInit0; //0xd0
    unsigned int uiSdramInit1; //0xd4
    unsigned int uiSdramInit2; //0xd8
    unsigned int uiSdramInit3; //0xdc
    unsigned int uiSdramInit4; //0xe0
    unsigned int uiSdramInit5; //0xe4
    unsigned int uiSdramInit6; //0xe8
    unsigned int uiSdramInit7; //0xec
    unsigned int uiDimmCtl; //0xf0
    unsigned int uiRankCtl; //0xf4
    unsigned int auiRecv7[2]; //0xf8
    unsigned int uiSdramTmg0; //0x100
    unsigned int uiSdramTmg1; //0x104
    unsigned int uiSdramTmg2; //0x108
    unsigned int uiSdramTmg3; //0x10C
    unsigned int uiSdramTmg4; //0x110
    unsigned int uiSdramTmg5; //0x114
    unsigned int uiSdramTmg6; //0x118
    unsigned int uiSdramTmg7; //0x11C
    unsigned int uiSdramTmg8; //0x120
    unsigned int uiSdramTmg9; //0x124
    unsigned int uiSdramTmg10; //0x128
    unsigned int uiSdramTmg11; //0x12c
    unsigned int uiSdramTmg12; //0x130
    unsigned int uiSdramTmg13; //0x134
    unsigned int uiSdramTmg14; //0x138
    unsigned int uiSdramTmg15; //0x13c
    unsigned int auiRecv8[16]; //0x140
    unsigned int uiZqCtl0; //0x180
    unsigned int uiZqCtl1; //0x184
    unsigned int uiZqCtl2; //0x188
    unsigned int uiZqStat; //0x18c
    unsigned int uiDfiTmg0; //0x190
    unsigned int uiDfiTmg1; //0x194
    unsigned int uiDfiLpCfg0; //0x198
    unsigned int uiDfiLpCfg1; //0x19C
    unsigned int uiDfiUpd0; //0x1A0
    unsigned int uiDfiUpd1; //0x1A4
    unsigned int uiDfiUpd2; //0x1A8
    unsigned int auiRecv9[1];//0x1Ac
    unsigned int uiDfiMisc; //0x1B0
    unsigned int uiDfiTmg2; //0x1B4
    unsigned int uiDfiTmg3; //0x1B8
    unsigned int uiDfiStat; //0x1BC
    unsigned int uiDdiCtl; //0x1C0
    unsigned int auiRecv10[15]; //0x1C4
    unsigned int uiAddrMap0;//0x200
    unsigned int uiAddrMap1;//0x204
    unsigned int uiAddrMap2;//0x208
    unsigned int uiAddrMap3;//0x20c
    unsigned int uiAddrMap4;//0x210
    unsigned int uiAddrMap5;//0x214
    unsigned int uiAddrMap6;//0x218
    unsigned int uiAddrMap7;//0x21C
    unsigned int uiAddrMap8;//0x220
    unsigned int uiAddrMap9;//0x224
    unsigned int uiAddrMap10;//0x228
    unsigned int uiAddrMap11;//0x22C
    unsigned int auiRecv11[4]; //0x230
    unsigned int uiOdtCfg; //0x240
    unsigned int uiOdtMap; //0x244
    unsigned int auiRecv12[2];//0x248
    unsigned int uiSched; //0x250
    unsigned int uiSched1; //0x254
    unsigned int auiRecv13[1];//0x258
    unsigned int uiPerHPr1;//0x25C
    unsigned int auiRecv14[1];//0x260
    unsigned int uiPerLPr1;//0x264
    unsigned int auiRecv15[1]; //0x268
    unsigned int uiPerWr1;//0x26C
    unsigned int auiRecv16[36];//0x270
    unsigned int uiDbg0;//0x300
    unsigned int uiDbg1;//0x304
    unsigned int uiDbgCam;//0x308
    unsigned int uiDbgCmd;//0x30C
    unsigned int uiDbgStat;//0x310
    unsigned int auiRecv17[3];//0x314
    unsigned int uiSwCtl;//0x320
    unsigned int uiSwStat;//0x324
    unsigned int auiRecv18[17]; //0x328
    unsigned int uiPoisonCfg;//0x36c
    unsigned int uiPoisonStat;//0x370
    unsigned int auiRecv19[34];//0x374
    unsigned int uiPStat;//0x3Fc
    unsigned int uiPcCfg;//0x400
    unsigned int uiPcFgR0;//0x404
    unsigned int uiPcFgW0;//0x408
    unsigned int auiRecv20[33];//0x40C
    unsigned int uiPctrl0;//0x490
    unsigned int uiPcfQos0;//0x494
    unsigned int uiPcfQos1;//0x498
    unsigned int uiPcfWqs0;//0x49c
    unsigned int uiPcfWqs1;//0x4A0
} T_DDRC_TYPEDEF;

typedef struct
{
	UINT32 uiRegAddr;
	UINT32 uiVal;
} T_DDR_CFG_PARAM;

typedef struct{
	unsigned int drate;
	enum fw_type fw_type;
	T_DDR_CFG_PARAM *fsp_cfg;
	unsigned int fsp_cfg_num;
} T_DRAM_FSP_MSG;

void ddr_init(E_DDR_TYPE eDdrType);
#endif
