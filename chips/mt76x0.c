/*
 *************************************************************************
 * Ralink Tech Inc.
 * 5F., No.36, Taiyuan St., Jhubei City,
 * Hsinchu County 302,
 * Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2010, Ralink Technology, Inc.
 *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program; if not, write to the                         *
 * Free Software Foundation, Inc.,                                       *
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                       *
 *************************************************************************/


#include "rt_config.h"

#if defined(MT7650) || defined(MT7630)
#include "mcu/mt7650_firmware.h"
#endif

#ifdef MT7610
#include "mcu/mt7610_firmware.h"
#endif

#ifdef SINGLE_SKU_V2
#define MT76x0_RF_2G_PA_MODE0_DECODE	0
#define MT76x0_RF_2G_PA_MODE1_DECODE	29491 /* 3.6 * 8192 */
#define MT76x0_RF_2G_PA_MODE3_DECODE	4096 /* 0.5 * 8192 */

#define MT76x0_RF_5G_PA_MODE0_DECODE	0
#define MT76x0_RF_5G_PA_MODE1_DECODE	0
#endif /* SINGLE_SKU_V2 */

UCHAR MT76x0_EeBuffer[EEPROM_SIZE] = {
	0x83, 0x38, 0x01, 0x00, 0x00, 0x0c, 0x43, 0x28, 0x83, 0x00, 0x83, 0x28, 0x14, 0x18, 0xff, 0xff,
	0xff, 0xff, 0x83, 0x28, 0x14, 0x18, 0x00, 0x00, 0x01, 0x00, 0x6a, 0xff, 0x00, 0x02, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x0c, 0x43, 0x28, 0x83, 0x01, 0x00, 0x0c,
	0x43, 0x28, 0x83, 0x02, 0x33, 0x0a, 0xec, 0x00, 0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0x20, 0x01, 0x55, 0x77, 0xa8, 0xaa, 0x8c, 0x88, 0xff, 0xff, 0x0a, 0x08, 0x08, 0x06,
	0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x05, 0x05,
	0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x06, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x66, 0x66, 0xcc, 0xaa, 0x88, 0x66, 0xcc, 0xaa, 0x88, 0x66, 0xcc, 0xaa, 0x88, 0x66, 0xcc, 0xaa,
	0x88, 0x66, 0xcc, 0xaa, 0x88, 0x66, 0xcc, 0xaa, 0x88, 0x66, 0xaa, 0xaa, 0x88, 0x66, 0xaa, 0xaa,
	0x88, 0x66, 0xaa, 0xaa, 0x88, 0x66, 0xcc, 0xaa, 0x88, 0x66, 0xcc, 0xaa, 0x88, 0x66, 0xcc, 0xaa,
	0x88, 0x66, 0xcc, 0xaa, 0x88, 0x66, 0xaa, 0xaa, 0x88, 0x66, 0xaa, 0xaa, 0x88, 0x66, 0xaa, 0xaa,
	0x88, 0x66, 0xaa, 0xaa, 0x88, 0x66, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	} ;

#define BIT0		(1 << 0)
#define BIT1		(1 << 1)
#define BIT2		(1 << 2)
#define BIT3		(1 << 3)
#define BIT4		(1 << 4)
#define BIT5		(1 << 5)
#define BIT6		(1 << 6)
#define BIT7		(1 << 7)
#define BIT8		(1 << 8)
#define BIT9		(1 << 9)
#define BIT10	(1 << 10)
#define BIT11	(1 << 11)
#define BIT12	(1 << 12)
#define BIT13	(1 << 13)
#define BIT14	(1 << 14)
#define BIT15	(1 << 15)
#define BIT16	(1 << 16)
#define BIT17	(1 << 17)
#define BIT18	(1 << 18)
#define BIT19	(1 << 19)
#define BIT20	(1 << 20)
#define BIT21	(1 << 21)
#define BIT22	(1 << 22)
#define BIT23	(1 << 23)
#define BIT24	(1 << 24)
#define BIT25	(1 << 25)
#define BIT26	(1 << 26)
#define BIT27	(1 << 27)
#define BIT28	(1 << 28)
#define BIT29	(1 << 29)
#define BIT30	(1 << 30)
#define BIT31	(1 << 31)

#define MT7650_EFUSE_CTRL	0x0024
#define LDO_CTRL1			0x0070

#ifdef CONFIG_WIFI_TEST
struct RF_BANK_OFFSET MT76x0_RFBankOffset[] = {
	{RF_BANK0, 0x0000, 0x0080},
	{RF_BANK5, 0x0000, 0x0080},
	{RF_BANK6, 0x0000, 0x0080},
	{RF_BANK7, 0x0000, 0x0080},
};
#endif /* CONFIG_WIFI_TEST */

static RTMP_REG_PAIR	MT76x0_MACRegTable[] = {
	{PBF_SYS_CTRL,		0x80c00},
	{PBF_CFG,			0x77723c1f},
	{FCE_PSE_CTRL,			0x1},

	{AMPDU_MAX_LEN_20M1S,	0xBAA99887}, /* Recommended by JerryCK @20120905 */

	{TX_SW_CFG0,		0x601}, /* Delay bb_tx_pe for proper tx_mcs_pwr update */
	{TX_SW_CFG1,		0x00040000}, /* Set rf_tx_pe deassert time to 1us by Chee's comment @MT7650_CR_setting_1018.xlsx */
	{TX_SW_CFG2,		0x0},

// TODO: shiang-6590, check what tx report will send to us when following default value set as 2
	{0xa44,					0x0}, /* disable Tx info report */


#ifdef HDR_TRANS_SUPPORT
	{HEADER_TRANS_CTRL_REG, 0x2}, /* 0x1: TX, 0x2: RX */
	{TSO_CTRL, 			0x7050},
#else
	{HEADER_TRANS_CTRL_REG, 0x0},
	{TSO_CTRL, 			0x0},
#endif /* HDR_TRANS_SUPPORT */


	/* BB_PA_MODE_CFG0(0x1214) Keep default value @20120903 */
	{BB_PA_MODE_CFG1, 0x00500055},

	/* RF_PA_MODE_CFG0(0x121C) Keep default value @20120903 */
	{RF_PA_MODE_CFG1, 0x00500055},

	{TX_ALC_CFG_0, 0x2F2F000C},
	{TX0_BB_GAIN_ATTEN, 0x00000000}, /* set BBP atten gain = 0 */

	{TX_PWR_CFG_0, 0x3A3A3A3A},
	{TX_PWR_CFG_1, 0x3A3A3A3A},
	{TX_PWR_CFG_2, 0x3A3A3A3A},
	{TX_PWR_CFG_3, 0x3A3A3A3A},
	{TX_PWR_CFG_4, 0x3A3A3A3A},
	{TX_PWR_CFG_7, 0x3A3A3A3A},
	{TX_PWR_CFG_8, 0x3A},
	{TX_PWR_CFG_9, 0x3A},
	{0x150C, 0x00000002}, /*Enable Tx length > 4095 byte */
	{0x1238, 0x001700C8}, /* Disable bt_abort_tx_en(0x1238[21] = 0) which is not used at MT7650 @MT7650_E3_CR_setting_1115.xlsx */
	{LDO_CTRL1, 0x6B006464}, /* Default LDO_DIG supply 1.26V, change to 1.2V */
};

static UCHAR MT76x0_NUM_MAC_REG_PARMS = (sizeof(MT76x0_MACRegTable) / sizeof(RTMP_REG_PAIR));

static RTMP_REG_PAIR MT76x0_DCOC_Tab[] = {
	{CAL_R47, 0x000010F0},
	{CAL_R48, 0x00008080},
	{CAL_R49, 0x00000F07},
	{CAL_R50, 0x00000040},
	{CAL_R51, 0x00000404},
	{CAL_R52, 0x00080803},
	{CAL_R53, 0x00000704},
	{CAL_R54, 0x00002828},
	{CAL_R55, 0x00005050},
};
static UCHAR MT76x0_DCOC_Tab_Size = (sizeof(MT76x0_DCOC_Tab) / sizeof(RTMP_REG_PAIR));

static RTMP_REG_PAIR MT76x0_BBP_Init_Tab[] = {
	{CORE_R1, 0x00000002},
	{CORE_R4, 0x00000000},
	{CORE_R24, 0x00000000},
	{CORE_R32, 0x4003000a},
	{CORE_R42, 0x00000000},
	{CORE_R44, 0x00000000},

	{IBI_R11, 0x00000080},

	/*
		0x2300[5] Default Antenna:
		0 for WIFI main antenna
		1  for WIFI aux  antenna

	*/
	{AGC1_R0, 0x00021400},
	{AGC1_R1, 0x00000003},
	{AGC1_R2, 0x003A6464},
	{AGC1_R15, 0x88A28CB8},
	{AGC1_R22, 0x00001E21},
	{AGC1_R23, 0x0000272C},
	{AGC1_R24, 0x00002F3A},
	{AGC1_R25, 0x8000005A},
	{AGC1_R26, 0x007C2005},
	{AGC1_R34, 0x000A0C0C},
	{AGC1_R37, 0x2121262C},
	{AGC1_R41, 0x38383E45},
	{AGC1_R57, 0x00001010},
	{AGC1_R59, 0xBAA20E96},
	{AGC1_R63, 0x00000001},

	{TXC_R0, 0x00280403},
	{TXC_R1, 0x00000000},

	{RXC_R1, 0x00000012},
	{RXC_R2, 0x00000011},
	{RXC_R3, 0x00000005},
	{RXC_R4, 0x00000000},
	{RXC_R5, 0xF977C4EC},
	{RXC_R7, 0x00000090},

	{TXO_R8, 0x00000000},

	{TXBE_R0, 0x00000000},
	{TXBE_R4, 0x00000004},
	{TXBE_R6, 0x00000000},
	{TXBE_R8, 0x00000014},
	{TXBE_R9, 0x20000000},
	{TXBE_R10, 0x00000000},
	{TXBE_R12, 0x00000000},
	{TXBE_R13, 0x00000000},
	{TXBE_R14, 0x00000000},
	{TXBE_R15, 0x00000000},
	{TXBE_R16, 0x00000000},
	{TXBE_R17, 0x00000000},

	{RXFE_R1, 0x00008800}, /* Add for E3 */
	{RXFE_R3, 0x00000000},
	{RXFE_R4, 0x00000000},

	{RXO_R13, 0x00000092},
	{RXO_R14, 0x00060612},
	{RXO_R15, 0xC8321B18},
	{RXO_R16, 0x0000001E},
	{RXO_R17, 0x00000000},
	{RXO_R18, 0xCC00A993},
	{RXO_R19, 0xB9CB9CB9},
	{RXO_R20, 0x26c00057}, /* IOT issue with Broadcom AP */
	{RXO_R21, 0x00000001},
	{RXO_R24, 0x00000006},
};
static UCHAR MT76x0_BBP_Init_Tab_Size = (sizeof(MT76x0_BBP_Init_Tab) / sizeof(RTMP_REG_PAIR));


MT76x0_BBP_Table MT76x0_BPP_SWITCH_Tab[] = {
	{RF_G_BAND | RF_BW_20 | RF_BW_40,				{AGC1_R8, 0x0E344EF0}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R8, 0x122C54F2}},

	{RF_G_BAND | RF_BW_20 | RF_BW_40,				{AGC1_R14, 0x310F2E39}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R14, 0x310F2A3F}},

	{RF_G_BAND | RF_BW_20 | RF_BW_40,				{AGC1_R32, 0x00003230}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R32, 0x0000181C}},

	{RF_G_BAND | RF_BW_20 | RF_BW_40,				{AGC1_R33, 0x00003240}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R33, 0x00003218}},

	{RF_G_BAND | RF_BW_20 | RF_BW_40,				{AGC1_R35, 0x11112016}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R35, 0x11112016}},

	{RF_G_BAND | RF_BW_20 | RF_BW_40,				{RXO_R28, 0x0000008A}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{RXO_R28, 0x0000008A}},	
	
	{RF_G_BAND | RF_BW_20 | RF_BW_40,				{AGC1_R4, 0x1FEDA049}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R4, 0x1FECA054}},

	{RF_G_BAND | RF_BW_20 | RF_BW_40,				{AGC1_R6, 0x00000045}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R6, 0x0000000A}},

	{RF_G_BAND | RF_BW_20,							{AGC1_R12, 0x05052879}},
	{RF_G_BAND | RF_BW_40,							{AGC1_R12, 0x050528F9}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R12, 0x050528F9}},

	{RF_G_BAND | RF_BW_20 | RF_BW_40,				{AGC1_R13, 0x35050004}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R13, 0x2C3A0406}},

	{RF_G_BAND | RF_BW_20 | RF_BW_40,				{AGC1_R27, 0x000000E1}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R27, 0x000000EC}},

	{RF_G_BAND | RF_BW_20,							{AGC1_R28, 0x00060806}},
	{RF_G_BAND | RF_BW_40,							{AGC1_R28, 0x00050806}},
	{RF_A_BAND | RF_BW_40,							{AGC1_R28, 0x00060801}},
	{RF_A_BAND | RF_BW_20 | RF_BW_80,				{AGC1_R28, 0x00060806}},

	{RF_G_BAND | RF_BW_20 | RF_BW_40,				{AGC1_R31, 0x00000F23}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R31, 0x00000F13}},

	{RF_G_BAND | RF_BW_20,							{AGC1_R39, 0x2A2A3036}},
	{RF_G_BAND | RF_BW_40,							{AGC1_R39, 0x2A2A2C36}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40,				{AGC1_R39, 0x2A2A3036}},
	{RF_A_BAND | RF_BW_80,							{AGC1_R39, 0x2A2A2A36}},
	
	{RF_G_BAND | RF_BW_20,							{AGC1_R43, 0x27273438}},
	{RF_G_BAND | RF_BW_40,							{AGC1_R43, 0x27272D38}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R43, 0x27272B30}},

	{RF_G_BAND | RF_BW_20 | RF_BW_40,				{AGC1_R51, 0x17171C1C}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R51, 0xFFFFFFFF}},

	{RF_G_BAND | RF_BW_20,							{AGC1_R53, 0x26262A2F}},
	{RF_G_BAND | RF_BW_40,							{AGC1_R53, 0x2626322F}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R53, 0xFFFFFFFF}},

	{RF_G_BAND | RF_BW_20,							{AGC1_R55, 0x40404E58}},
	{RF_G_BAND | RF_BW_40,							{AGC1_R55, 0x40405858}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R55, 0xFFFFFFFF}},

	{RF_G_BAND | RF_BW_20 | RF_BW_40,				{AGC1_R58, 0x00001010}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{AGC1_R58, 0x00000000}},

	{RF_G_BAND | RF_BW_20 | RF_BW_40,				{RXFE_R0, 0x3D5000E0}},
	{RF_A_BAND | RF_BW_20 | RF_BW_40 | RF_BW_80,	{RXFE_R0, 0x895000E0}},
};

UCHAR MT76x0_BPP_SWITCH_Tab_Size = (sizeof(MT76x0_BPP_SWITCH_Tab) / sizeof(MT76x0_BBP_Table));

/* Bank	Register Value(Hex) */
static BANK_RF_REG_PAIR MT76x0_RF_Central_RegTb[] = {
/*
	Bank 0 - For central blocks: BG, PLL, XTAL, LO, ADC/DAC
*/
	{RF_BANK0,	RF_R01, 0x01},
	{RF_BANK0,	RF_R02, 0x11},

	/*
		R3 ~ R7: VCO Cal.
	*/	
	{RF_BANK0,	RF_R03, 0x73}, /* VCO Freq Cal - No Bypass, VCO Amp Cal - No Bypass */
	{RF_BANK0,	RF_R04, 0x30}, /* R4 b<7>=1, VCO cal */
	{RF_BANK0,	RF_R05, 0x00},
	{RF_BANK0,	RF_R06, 0x41}, /* Set the open loop amplitude to middle since bypassing amplitude calibration */
	{RF_BANK0,	RF_R07, 0x00},

	/*
		XO
	*/
	{RF_BANK0,	RF_R08, 0x00}, 
	{RF_BANK0,	RF_R09, 0x00},
	{RF_BANK0,	RF_R10, 0x0C},
	{RF_BANK0,	RF_R11, 0x00},
	{RF_BANK0,	RF_R12, 0x00},

	/*
		BG
	*/
	{RF_BANK0,	RF_R13, 0x00},
	{RF_BANK0,	RF_R14, 0x00},
	{RF_BANK0,	RF_R15, 0x00},

	/*
		LDO
	*/
	{RF_BANK0,	RF_R19, 0x20}, 
	/*
		XO
	*/
	{RF_BANK0,	RF_R20, 0x22},
	{RF_BANK0,	RF_R21, 0x12},
	{RF_BANK0,	RF_R23, 0x00},
	{RF_BANK0,	RF_R24, 0x33}, /* See band selection for R24<1:0> */
	{RF_BANK0,	RF_R25, 0x00},

	/*
		PLL, See Freq Selection
	*/
	{RF_BANK0,	RF_R26, 0x00},
	{RF_BANK0,	RF_R27, 0x00},
	{RF_BANK0,	RF_R28, 0x00},
	{RF_BANK0,	RF_R29, 0x00},
	{RF_BANK0,	RF_R30, 0x00},
	{RF_BANK0,	RF_R31, 0x00},
	{RF_BANK0,	RF_R32, 0x00},
	{RF_BANK0,	RF_R33, 0x00},
	{RF_BANK0,	RF_R34, 0x00},
	{RF_BANK0,	RF_R35, 0x00},
	{RF_BANK0,	RF_R36, 0x00},
	{RF_BANK0,	RF_R37, 0x00},

	/*
		LO Buffer
	*/
	{RF_BANK0,	RF_R38, 0x2F},
	
	/*
		Test Ports
	*/
	{RF_BANK0,	RF_R64, 0x00},
	{RF_BANK0,	RF_R65, 0x80},
	{RF_BANK0,	RF_R66, 0x01},
	{RF_BANK0,	RF_R67, 0x04},

	/*
		ADC/DAC
	*/
	{RF_BANK0,	RF_R68, 0x00},
	{RF_BANK0,	RF_R69, 0x08},
	{RF_BANK0,	RF_R70, 0x08},
	{RF_BANK0,	RF_R71, 0x40},
	{RF_BANK0,	RF_R72, 0xD0},
	{RF_BANK0,	RF_R73, 0x93},
};
static UINT32 MT76x0_RF_Central_RegTb_Size = (sizeof(MT76x0_RF_Central_RegTb) / sizeof(BANK_RF_REG_PAIR));

static BANK_RF_REG_PAIR MT76x0_RF_2G_Channel_0_RegTb[] = {
/*
	Bank 5 - Channel 0 2G RF registers	
*/
	/*
		RX logic operation
	*/
	/* RF_R00 Change in SelectBand6590 */

	{RF_BANK5,	RF_R02, 0x0C}, /* 5G+2G (MT7610U) */
	{RF_BANK5,	RF_R03, 0x00},

	/*
		TX logic operation
	*/
	{RF_BANK5,	RF_R04, 0x00},
	{RF_BANK5,	RF_R05, 0x84},
	{RF_BANK5,	RF_R06, 0x02},

	/*
		LDO
	*/
	{RF_BANK5,	RF_R07, 0x00},
	{RF_BANK5,	RF_R08, 0x00},
	{RF_BANK5,	RF_R09, 0x00},

	/*
		RX
	*/
	{RF_BANK5,	RF_R10, 0x51},
	{RF_BANK5,	RF_R11, 0x22},
	{RF_BANK5,	RF_R12, 0x22},
	{RF_BANK5,	RF_R13, 0x0F},
	{RF_BANK5,	RF_R14, 0x47}, /* Increase mixer current for more gain */
	{RF_BANK5,	RF_R15, 0x25},
	{RF_BANK5,	RF_R16, 0xC7}, /* Tune LNA2 tank */
	{RF_BANK5,	RF_R17, 0x00},
	{RF_BANK5,	RF_R18, 0x00},
	{RF_BANK5,	RF_R19, 0x30}, /* Improve max Pin */
	{RF_BANK5,	RF_R20, 0x33},
	{RF_BANK5,	RF_R21, 0x02},
	{RF_BANK5,	RF_R22, 0x32}, /* Tune LNA1 tank */
	{RF_BANK5,	RF_R23, 0x00},
	{RF_BANK5,	RF_R24, 0x25},
	{RF_BANK5,	RF_R26, 0x00},
	{RF_BANK5,	RF_R27, 0x12},
	{RF_BANK5,	RF_R28, 0x0F},
	{RF_BANK5,	RF_R29, 0x00},

	/*
		LOGEN
	*/
	{RF_BANK5,	RF_R30, 0x51}, /* Tune LOGEN tank */
	{RF_BANK5,	RF_R31, 0x35},
	{RF_BANK5,	RF_R32, 0x31},
	{RF_BANK5,	RF_R33, 0x31},
	{RF_BANK5,	RF_R34, 0x34},
	{RF_BANK5,	RF_R35, 0x03},
	{RF_BANK5,	RF_R36, 0x00},

	/*
		TX
	*/
	{RF_BANK5,	RF_R37, 0xDD}, /* Improve 3.2GHz spur */
	{RF_BANK5,	RF_R38, 0xB3},
	{RF_BANK5,	RF_R39, 0x33},
	{RF_BANK5,	RF_R40, 0xB1},
	{RF_BANK5,	RF_R41, 0x71},
	{RF_BANK5,	RF_R42, 0xF2},
	{RF_BANK5,	RF_R43, 0x47},
	{RF_BANK5,	RF_R44, 0x77},
	{RF_BANK5,	RF_R45, 0x0E},
	{RF_BANK5,	RF_R46, 0x10},
	{RF_BANK5,	RF_R47, 0x00},
	{RF_BANK5,	RF_R48, 0x53},
	{RF_BANK5,	RF_R49, 0x03},
	{RF_BANK5,	RF_R50, 0xEF},
	{RF_BANK5,	RF_R51, 0xC7},
	{RF_BANK5,	RF_R52, 0x62},
	{RF_BANK5,	RF_R53, 0x62},
	{RF_BANK5,	RF_R54, 0x00},
	{RF_BANK5,	RF_R55, 0x00},
	{RF_BANK5,	RF_R56, 0x0F},
	{RF_BANK5,	RF_R57, 0x0F},
	{RF_BANK5,	RF_R58, 0x16},
	{RF_BANK5,	RF_R59, 0x16},
	{RF_BANK5,	RF_R60, 0x10},
	{RF_BANK5,	RF_R61, 0x10},
	{RF_BANK5,	RF_R62, 0xD0},
	{RF_BANK5,	RF_R63, 0x6C},
	{RF_BANK5,	RF_R64, 0x58},
	{RF_BANK5, 	RF_R65, 0x58},
	{RF_BANK5,	RF_R66, 0xF2},
	{RF_BANK5,	RF_R67, 0xE8},
	{RF_BANK5,	RF_R68, 0xF0},
	{RF_BANK5,	RF_R69, 0xF0},
	{RF_BANK5,	RF_R127, 0x04},
};
static UINT32 MT76x0_RF_2G_Channel_0_RegTb_Size = (sizeof(MT76x0_RF_2G_Channel_0_RegTb) / sizeof(BANK_RF_REG_PAIR));

static BANK_RF_REG_PAIR MT76x0_RF_5G_Channel_0_RegTb[] = {
/*
	Bank 6 - Channel 0 5G RF registers	
*/
	/*
		RX logic operation
	*/
	/* RF_R00 Change in SelectBandMT76x0 */

	{RF_BANK6,	RF_R02, 0x0C},
	{RF_BANK6,	RF_R03, 0x00},

	/*
		TX logic operation
	*/
	{RF_BANK6,	RF_R04, 0x00},
	{RF_BANK6,	RF_R05, 0x84},
	{RF_BANK6,	RF_R06, 0x02},

	/*
		LDO
	*/
	{RF_BANK6,	RF_R07, 0x00},
	{RF_BANK6,	RF_R08, 0x00},
	{RF_BANK6,	RF_R09, 0x00},

	/*
		RX
	*/
	{RF_BANK6,	RF_R10, 0x00},
	{RF_BANK6,	RF_R11, 0x01},
	
	{RF_BANK6,	RF_R13, 0x23},
	{RF_BANK6,	RF_R14, 0x00},
	{RF_BANK6,	RF_R15, 0x04},
	{RF_BANK6,	RF_R16, 0x22},

	{RF_BANK6,	RF_R18, 0x08},
	{RF_BANK6,	RF_R19, 0x00},
	{RF_BANK6,	RF_R20, 0x00},
	{RF_BANK6,	RF_R21, 0x00},
	{RF_BANK6,	RF_R22, 0xFB},

	/*
		LOGEN5G
	*/
	{RF_BANK6,	RF_R25, 0x76},
	{RF_BANK6,	RF_R26, 0x24},
	{RF_BANK6,	RF_R27, 0x04},
	{RF_BANK6,	RF_R28, 0x00},
	{RF_BANK6,	RF_R29, 0x00},

	/*
		TX
	*/
	{RF_BANK6,	RF_R37, 0xBB},
	{RF_BANK6,	RF_R38, 0xB3},

	{RF_BANK6,	RF_R40, 0x33},
	{RF_BANK6,	RF_R41, 0x33},

	{RF_BANK6,	RF_R43, 0x03},
	{RF_BANK6,	RF_R44, 0xB3},
	
	{RF_BANK6,	RF_R46, 0x17},
	{RF_BANK6,	RF_R47, 0x0E},
	{RF_BANK6,	RF_R48, 0x10},
	{RF_BANK6,	RF_R49, 0x07},
	
	{RF_BANK6,	RF_R62, 0x00},
	{RF_BANK6,	RF_R63, 0x00},
	{RF_BANK6,	RF_R64, 0xF1},
	{RF_BANK6,	RF_R65, 0x0F},
};
static UINT32 MT76x0_RF_5G_Channel_0_RegTb_Size = (sizeof(MT76x0_RF_5G_Channel_0_RegTb) / sizeof(BANK_RF_REG_PAIR));

static BANK_RF_REG_PAIR MT76x0_RF_VGA_Channel_0_RegTb[] = {
/*
	Bank 7 - Channel 0 VGA RF registers	
*/
	/* E3 CR */
	{RF_BANK7,	RF_R00, 0x47}, /* Allow BBP/MAC to do calibration */
	{RF_BANK7,	RF_R01, 0x00},
	{RF_BANK7,	RF_R02, 0x00},
	{RF_BANK7,	RF_R03, 0x00},
	{RF_BANK7,	RF_R04, 0x00},

	{RF_BANK7,	RF_R10, 0x13},
	{RF_BANK7,	RF_R11, 0x0F},
	{RF_BANK7,	RF_R12, 0x13}, /* For DCOC */
	{RF_BANK7,	RF_R13, 0x13}, /* For DCOC */
	{RF_BANK7,	RF_R14, 0x13}, /* For DCOC */
	{RF_BANK7,	RF_R15, 0x20}, /* For DCOC */
	{RF_BANK7,	RF_R16, 0x22}, /* For DCOC */

	{RF_BANK7,	RF_R17, 0x7C},

	{RF_BANK7,	RF_R18, 0x00},
	{RF_BANK7,	RF_R19, 0x00},
	{RF_BANK7,	RF_R20, 0x00},
	{RF_BANK7,	RF_R21, 0xF1},
	{RF_BANK7,	RF_R22, 0x11},
	{RF_BANK7,	RF_R23, 0xC2},
	{RF_BANK7,	RF_R24, 0x41},
	{RF_BANK7,	RF_R25, 0x20},
	{RF_BANK7,	RF_R26, 0x40},
	{RF_BANK7,	RF_R27, 0xD7},
	{RF_BANK7,	RF_R28, 0xA2},
	{RF_BANK7,	RF_R29, 0x60},
	{RF_BANK7,	RF_R30, 0x49},
	{RF_BANK7,	RF_R31, 0x20},
	{RF_BANK7,	RF_R32, 0x44},
	{RF_BANK7,	RF_R33, 0xC1},
	{RF_BANK7,	RF_R34, 0x60},
	{RF_BANK7,	RF_R35, 0xC0},

	{RF_BANK7,	RF_R61, 0x01},

	{RF_BANK7,	RF_R72, 0x3C},
	{RF_BANK7,	RF_R73, 0x34},
	{RF_BANK7,	RF_R74, 0x00},
};
static UINT32 MT76x0_RF_VGA_Channel_0_RegTb_Size = (sizeof(MT76x0_RF_VGA_Channel_0_RegTb) / sizeof(BANK_RF_REG_PAIR));

static const MT76x0_FREQ_ITEM MT76x0_Frequency_Plan[] =
{
	{1,		RF_G_BAND,	0x02, 0x3F, 0x28, 0xDD, 0xE2, 0x40, 0x02, 0x40, 0x02, 0, 0, 1, 0x28, 0, 0x30, 0, 0, 0x3}, /* Freq 2412 */
	{2, 	RF_G_BAND,	0x02, 0x3F, 0x3C, 0xDD, 0xE4, 0x40, 0x07, 0x40, 0x02, 0, 0, 1, 0xA1, 0, 0x30, 0, 0, 0x1}, /* Freq 2417 */
	{3, 	RF_G_BAND,	0x02, 0x3F, 0x3C, 0xDD, 0xE2, 0x40, 0x07, 0x40, 0x0B, 0, 0, 1, 0x50, 0, 0x30, 0, 0, 0x0}, /* Freq 2422 */
	{4, 	RF_G_BAND,	0x02, 0x3F, 0x28, 0xDD, 0xD4, 0x40, 0x02, 0x40, 0x09, 0, 0, 1, 0x50, 0, 0x30, 0, 0, 0x0}, /* Freq 2427 */
	{5, 	RF_G_BAND,	0x02, 0x3F, 0x3C, 0xDD, 0xD4, 0x40, 0x07, 0x40, 0x02, 0, 0, 1, 0xA2, 0, 0x30, 0, 0, 0x1}, /* Freq 2432 */
	{6, 	RF_G_BAND,	0x02, 0x3F, 0x3C, 0xDD, 0xD4, 0x40, 0x07, 0x40, 0x07, 0, 0, 1, 0xA2, 0, 0x30, 0, 0, 0x1}, /* Freq 2437 */
	{7, 	RF_G_BAND,	0x02, 0x3F, 0x28, 0xDD, 0xE2, 0x40, 0x02, 0x40, 0x07, 0, 0, 1, 0x28, 0, 0x30, 0, 0, 0x3}, /* Freq 2442 */
	{8, 	RF_G_BAND,	0x02, 0x3F, 0x3C, 0xDD, 0xD4, 0x40, 0x07, 0x40, 0x02, 0, 0, 1, 0xA3, 0, 0x30, 0, 0, 0x1}, /* Freq 2447 */
	{9, 	RF_G_BAND,	0x02, 0x3F, 0x3C, 0xDD, 0xF2, 0x40, 0x07, 0x40, 0x0D, 0, 0, 1, 0x28, 0, 0x30, 0, 0, 0x3}, /* Freq 2452 */
	{10, 	RF_G_BAND,	0x02, 0x3F, 0x28, 0xDD, 0xD4, 0x40, 0x02, 0x40, 0x09, 0, 0, 1, 0x51, 0, 0x30, 0, 0, 0x0}, /* Freq 2457 */
	{11, 	RF_G_BAND,	0x02, 0x3F, 0x3C, 0xDD, 0xD4, 0x40, 0x07, 0x40, 0x02, 0, 0, 1, 0xA4, 0, 0x30, 0, 0, 0x1}, /* Freq 2462 */
	{12, 	RF_G_BAND,	0x02, 0x3F, 0x3C, 0xDD, 0xD4, 0x40, 0x07, 0x40, 0x07, 0, 0, 1, 0xA4, 0, 0x30, 0, 0, 0x1}, /* Freq 2467 */
	{13, 	RF_G_BAND,	0x02, 0x3F, 0x28, 0xDD, 0xF2, 0x40, 0x02, 0x40, 0x02, 0, 0, 1, 0x29, 0, 0x30, 0, 0, 0x3}, /* Freq 2472 */
	{14, 	RF_G_BAND,	0x02, 0x3F, 0x28, 0xDD, 0xF2, 0x40, 0x02, 0x40, 0x04, 0, 0, 1, 0x29, 0, 0x30, 0, 0, 0x3}, /* Freq 2484 */

	{183, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x70, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x17, 0, 0, 1, 0x28, 0, 0x30, 0, 0, 0x3}, /* Freq 4915 */
	{184, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x00, 0, 0, 1, 0x29, 0, 0x30, 0, 0, 0x3}, /* Freq 4920 */
	{185, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x01, 0, 0, 1, 0x29, 0, 0x30, 0, 0, 0x3}, /* Freq 4925 */
	{187, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x03, 0, 0, 1, 0x29, 0, 0x30, 0, 0, 0x3}, /* Freq 4935 */
	{188, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x02, 0, 0, 1, 0x29, 0, 0x30, 0, 0, 0x3}, /* Freq 4940 */
	{189, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x05, 0, 0, 1, 0x29, 0, 0x30, 0, 0, 0x3}, /* Freq 4945 */
	{192, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x04, 0, 0, 1, 0x29, 0, 0x30, 0, 0, 0x3}, /* Freq 4960 */
	{196, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x06, 0, 0, 1, 0x29, 0, 0x30, 0, 0, 0x3}, /* Freq 4980 */
	
	{36, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x02, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5180 */
	{37, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x05, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5185 */
	{38, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x03, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5190 */
	{39, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x07, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5195 */
	{40, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x04, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5200 */
	{41, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x09, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5205 */
	{42, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x05, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5210 */
	{43, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x0B, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5215 */
	{44, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x06, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5220 */
	{45, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x0D, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5225 */
	{46, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x07, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5230 */
	{47, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x0F, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5235 */
	{48, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x08, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5240 */
	{49, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x11, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5245 */
	{50, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x09, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5250 */
	{51, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x13, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5255 */
	{52, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x0A, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5260 */
	{53, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x15, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5265 */
	{54, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x0B, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5270 */
	{55, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x70, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x17, 0, 0, 1, 0x2B, 0, 0x30, 0, 0, 0x3}, /* Freq 5275 */
	{56, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x00, 0, 0, 1, 0x2C, 0, 0x30, 0, 0, 0x3}, /* Freq 5280 */
	{57, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x01, 0, 0, 1, 0x2C, 0, 0x30, 0, 0, 0x3}, /* Freq 5285 */
	{58, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x01, 0, 0, 1, 0x2C, 0, 0x30, 0, 0, 0x3}, /* Freq 5290 */
	{59, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x03, 0, 0, 1, 0x2C, 0, 0x30, 0, 0, 0x3}, /* Freq 5295 */
	{60, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x02, 0, 0, 1, 0x2C, 0, 0x30, 0, 0, 0x3}, /* Freq 5300 */
	{61, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x05, 0, 0, 1, 0x2C, 0, 0x30, 0, 0, 0x3}, /* Freq 5305 */
	{62, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x03, 0, 0, 1, 0x2C, 0, 0x30, 0, 0, 0x3}, /* Freq 5310 */
	{63, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x07, 0, 0, 1, 0x2C, 0, 0x30, 0, 0, 0x3}, /* Freq 5315 */
	{64, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x04, 0, 0, 1, 0x2C, 0, 0x30, 0, 0, 0x3}, /* Freq 5320 */

	{100, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x0A, 0, 0, 1, 0x2D, 0, 0x30, 0, 0, 0x3}, /* Freq 5500 */
	{101, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x15, 0, 0, 1, 0x2D, 0, 0x30, 0, 0, 0x3}, /* Freq 5505 */
	{102, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x0B, 0, 0, 1, 0x2D, 0, 0x30, 0, 0, 0x3}, /* Freq 5510 */
	{103, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x70, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x17, 0, 0, 1, 0x2D, 0, 0x30, 0, 0, 0x3}, /* Freq 5515 */
	{104, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x00, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5520 */
	{105, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x01, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5525 */
	{106, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x01, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5530 */
	{107, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x03, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5535 */
	{108, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x02, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5540 */
	{109, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x05, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5545 */
	{110, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x03, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5550 */
	{111, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x07, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5555 */
	{112, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x04, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5560 */
	{113, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x09, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5565 */
	{114, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x05, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5570 */
	{115, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x0B, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5575 */
	{116, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x06, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5580 */
	{117, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x0D, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5585 */
	{118, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x07, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5590 */
	{119, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x0F, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5595 */
	{120, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x08, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5600 */
	{121, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x11, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5605 */
	{122, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x09, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5610 */
	{123, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x13, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5615 */
	{124, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x0A, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5620 */
	{125, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x15, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5625 */
	{126, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x0B, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5630 */
	{127, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x70, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x17, 0, 0, 1, 0x2E, 0, 0x30, 0, 0, 0x3}, /* Freq 5635 */
	{128, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x00, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5640 */
	{129, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x01, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5645 */
	{130, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x01, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5650 */
	{131, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x03, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5655 */
	{132, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x02, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5660 */
	{133, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x05, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5665 */
	{134, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x03, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5670 */
	{135, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x07, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5675 */
	{136, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x04, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5680 */

	{137, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x09, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5685 */
	{138, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x05, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5690 */
	{139, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x0B, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5695 */
	{140, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x06, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5700 */
	{141, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x0D, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5705 */
	{142, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x07, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5710 */	
	{143, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x0F, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5715 */
	{144, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x08, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5720 */
	{145, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x11, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5725 */
	{146, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x09, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5730 */
	{147, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x13, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5735 */
	{148, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x0A, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5740 */
	{149, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x15, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5745 */
	{150, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x0B, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5750 */	
	{151, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x70, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x17, 0, 0, 1, 0x2F, 0, 0x30, 0, 0, 0x3}, /* Freq 5755 */
	{152, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x00, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5760 */
	{153, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x01, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5765 */
	{154, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x01, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5770 */
	{155, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x03, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5775 */
	{156, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x02, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5780 */
	{157, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x05, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5785 */
	{158, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x03, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5790 */
	{159, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x07, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5795 */
	{160, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x04, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5800 */
	{161, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x09, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5805 */
	{162, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x05, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5810 */
	{163, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x0B, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5815 */
	{164, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x06, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5820 */
	{165, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x0D, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5825 */
	{166, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0xDD, 0xD2, 0x40, 0x04, 0x40, 0x07, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5830 */
	{167, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x0F, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5835 */
	{168, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x08, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5840 */
	{169, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x11, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5845 */
	{170, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x09, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5850 */
	{171, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x13, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5855 */
	{172, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x30, 0x97, 0xD2, 0x40, 0x04, 0x40, 0x0A, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5860 */
	{173, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x68, 0xDD, 0xD2, 0x40, 0x10, 0x40, 0x15, 0, 0, 1, 0x30, 0, 0x30, 0, 0, 0x3}, /* Freq 5865 */
};
UCHAR NUM_OF_MT76x0_CHNL = (sizeof(MT76x0_Frequency_Plan) / sizeof(MT76x0_FREQ_ITEM));


static const MT76x0_FREQ_ITEM MT76x0_SDM_Frequency_Plan[] =
{
	{1,		RF_G_BAND,	0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x28, 0, 0x0, 0x8, 0xCCCC,  0x3}, /* Freq 2412 */
	{2, 	RF_G_BAND,	0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x28, 0, 0x0, 0x8, 0x12222, 0x3}, /* Freq 2417 */
	{3, 	RF_G_BAND,	0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x28, 0, 0x0, 0x8, 0x17777, 0x3}, /* Freq 2422 */
	{4, 	RF_G_BAND,	0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x28, 0, 0x0, 0x8, 0x1CCCC, 0x3}, /* Freq 2427 */
	{5, 	RF_G_BAND,	0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x28, 0, 0x0, 0x8, 0x22222, 0x3}, /* Freq 2432 */
	{6, 	RF_G_BAND,	0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x28, 0, 0x0, 0x8, 0x27777, 0x3}, /* Freq 2437 */
	{7, 	RF_G_BAND,	0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x28, 0, 0x0, 0x8, 0x2CCCC, 0x3}, /* Freq 2442 */
	{8, 	RF_G_BAND,	0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x28, 0, 0x0, 0x8, 0x32222, 0x3}, /* Freq 2447 */
	{9, 	RF_G_BAND,	0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x28, 0, 0x0, 0x8, 0x37777, 0x3}, /* Freq 2452 */
	{10, 	RF_G_BAND,	0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x28, 0, 0x0, 0x8, 0x3CCCC, 0x3}, /* Freq 2457 */
	{11, 	RF_G_BAND,	0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x29, 0, 0x0, 0x8, 0x2222, 0x3}, /* Freq 2462 */
	{12, 	RF_G_BAND,	0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x29, 0, 0x0, 0x8, 0x7777, 0x3}, /* Freq 2467 */
	{13, 	RF_G_BAND,	0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x29, 0, 0x0, 0x8, 0xCCCC, 0x3}, /* Freq 2472 */
	{14, 	RF_G_BAND,	0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x29, 0, 0x0, 0x8, 0x19999, 0x3}, /* Freq 2484 */

	{183, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x28, 0, 0x0, 0x8, 0x3D555, 0x3}, /* Freq 4915 */
	{184, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x29, 0, 0x0, 0x8, 0x0,     0x3}, /* Freq 4920 */
	{185, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x29, 0, 0x0, 0x8, 0x2AAA,  0x3}, /* Freq 4925 */
	{187, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x29, 0, 0x0, 0x8, 0x8000,  0x3}, /* Freq 4935 */
	{188, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x29, 0, 0x0, 0x8, 0xAAAA,  0x3}, /* Freq 4940 */
	{189, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x29, 0, 0x0, 0x8, 0xD555,  0x3}, /* Freq 4945 */
	{192, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x29, 0, 0x0, 0x8, 0x15555, 0x3}, /* Freq 4960 */
	{196, 	(RF_A_BAND | RF_A_BAND_11J), 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x29, 0, 0x0, 0x8, 0x20000, 0x3}, /* Freq 4980 */
	
	{36, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0xAAAA,  0x3}, /* Freq 5180 */
	{37, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0xD555,  0x3}, /* Freq 5185 */
	{38, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x10000, 0x3}, /* Freq 5190 */
	{39, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x12AAA, 0x3}, /* Freq 5195 */
	{40, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x15555, 0x3}, /* Freq 5200 */
	{41, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x18000, 0x3}, /* Freq 5205 */
	{42, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x1AAAA, 0x3}, /* Freq 5210 */
	{43, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x1D555, 0x3}, /* Freq 5215 */
	{44, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x20000, 0x3}, /* Freq 5220 */
	{45, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x22AAA, 0x3}, /* Freq 5225 */
	{46, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x25555, 0x3}, /* Freq 5230 */
	{47, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x28000, 0x3}, /* Freq 5235 */
	{48, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x2AAAA, 0x3}, /* Freq 5240 */
	{49, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x2D555, 0x3}, /* Freq 5245 */
	{50, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x30000, 0x3}, /* Freq 5250 */
	{51, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x32AAA, 0x3}, /* Freq 5255 */
	{52, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x35555, 0x3}, /* Freq 5260 */
	{53, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x38000, 0x3}, /* Freq 5265 */
	{54, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x3AAAA, 0x3}, /* Freq 5270 */
	{55, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2B, 0, 0x0, 0x8, 0x3D555, 0x3}, /* Freq 5275 */
	{56, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2C, 0, 0x0, 0x8, 0x00000, 0x3}, /* Freq 5280 */
	{57, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2C, 0, 0x0, 0x8, 0x02AAA, 0x3}, /* Freq 5285 */
	{58, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2C, 0, 0x0, 0x8, 0x05555, 0x3}, /* Freq 5290 */
	{59, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2C, 0, 0x0, 0x8, 0x08000, 0x3}, /* Freq 5295 */
	{60, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2C, 0, 0x0, 0x8, 0x0AAAA, 0x3}, /* Freq 5300 */
	{61, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2C, 0, 0x0, 0x8, 0x0D555, 0x3}, /* Freq 5305 */
	{62, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2C, 0, 0x0, 0x8, 0x10000, 0x3}, /* Freq 5310 */
	{63, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2C, 0, 0x0, 0x8, 0x12AAA, 0x3}, /* Freq 5315 */
	{64, 	(RF_A_BAND | RF_A_BAND_LB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2C, 0, 0x0, 0x8, 0x15555, 0x3}, /* Freq 5320 */

	{100, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2D, 0, 0x0, 0x8, 0x35555, 0x3}, /* Freq 5500 */
	{101, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2D, 0, 0x0, 0x8, 0x38000, 0x3}, /* Freq 5505 */
	{102, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2D, 0, 0x0, 0x8, 0x3AAAA, 0x3}, /* Freq 5510 */
	{103, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2D, 0, 0x0, 0x8, 0x3D555, 0x3}, /* Freq 5515 */
	{104, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x00000, 0x3}, /* Freq 5520 */
	{105, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x02AAA, 0x3}, /* Freq 5525 */
	{106, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x05555, 0x3}, /* Freq 5530 */
	{107, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x08000, 0x3}, /* Freq 5535 */
	{108, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x0AAAA, 0x3}, /* Freq 5540 */
	{109, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x0D555, 0x3}, /* Freq 5545 */
	{110, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x10000, 0x3}, /* Freq 5550 */
	{111, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x12AAA, 0x3}, /* Freq 5555 */
	{112, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x15555, 0x3}, /* Freq 5560 */
	{113, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x18000, 0x3}, /* Freq 5565 */
	{114, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x1AAAA, 0x3}, /* Freq 5570 */
	{115, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x1D555, 0x3}, /* Freq 5575 */
	{116, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x20000, 0x3}, /* Freq 5580 */
	{117, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x22AAA, 0x3}, /* Freq 5585 */
	{118, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x25555, 0x3}, /* Freq 5590 */
	{119, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x28000, 0x3}, /* Freq 5595 */
	{120, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x2AAAA, 0x3}, /* Freq 5600 */
	{121, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x2D555, 0x3}, /* Freq 5605 */
	{122, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x30000, 0x3}, /* Freq 5610 */
	{123, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x32AAA, 0x3}, /* Freq 5615 */
	{124, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x35555, 0x3}, /* Freq 5620 */
	{125, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x38000, 0x3}, /* Freq 5625 */
	{126, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x3AAAA, 0x3}, /* Freq 5630 */
	{127, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2E, 0, 0x0, 0x8, 0x3D555, 0x3}, /* Freq 5635 */
	{128, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x00000, 0x3}, /* Freq 5640 */
	{129, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x02AAA, 0x3}, /* Freq 5645 */
	{130, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x05555, 0x3}, /* Freq 5650 */
	{131, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x08000, 0x3}, /* Freq 5655 */
	{132, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x0AAAA, 0x3}, /* Freq 5660 */
	{133, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x0D555, 0x3}, /* Freq 5665 */
	{134, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x10000, 0x3}, /* Freq 5670 */
	{135, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x12AAA, 0x3}, /* Freq 5675 */
	{136, 	(RF_A_BAND | RF_A_BAND_MB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x15555, 0x3}, /* Freq 5680 */

	{137, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x18000, 0x3}, /* Freq 5685 */
	{138, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x1AAAA, 0x3}, /* Freq 5690 */
	{139, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x1D555, 0x3}, /* Freq 5695 */
	{140, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x20000, 0x3}, /* Freq 5700 */
	{141, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x22AAA, 0x3}, /* Freq 5705 */
	{142, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x25555, 0x3}, /* Freq 5710 */	
	{143, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x28000, 0x3}, /* Freq 5715 */
	{144, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x2AAAA, 0x3}, /* Freq 5720 */
	{145, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x2D555, 0x3}, /* Freq 5725 */
	{146, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x30000, 0x3}, /* Freq 5730 */
	{147, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x32AAA, 0x3}, /* Freq 5735 */
	{148, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x35555, 0x3}, /* Freq 5740 */
	{149, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x38000, 0x3}, /* Freq 5745 */
	{150, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x3AAAA, 0x3}, /* Freq 5750 */	
	{151, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x2F, 0, 0x0, 0x8, 0x3D555, 0x3}, /* Freq 5755 */
	{152, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x00000, 0x3}, /* Freq 5760 */
	{153, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x02AAA, 0x3}, /* Freq 5765 */
	{154, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x05555, 0x3}, /* Freq 5770 */
	{155, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x08000, 0x3}, /* Freq 5775 */
	{156, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x0AAAA, 0x3}, /* Freq 5780 */
	{157, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x0D555, 0x3}, /* Freq 5785 */
	{158, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x10000, 0x3}, /* Freq 5790 */
	{159, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x12AAA, 0x3}, /* Freq 5795 */
	{160, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x15555, 0x3}, /* Freq 5800 */
	{161, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x18000, 0x3}, /* Freq 5805 */
	{162, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x1AAAA, 0x3}, /* Freq 5810 */
	{163, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x1D555, 0x3}, /* Freq 5815 */
	{164, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x20000, 0x3}, /* Freq 5820 */
	{165, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x22AAA, 0x3}, /* Freq 5825 */
	{166, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x25555, 0x3}, /* Freq 5830 */
	{167, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x28000, 0x3}, /* Freq 5835 */
	{168, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x2AAAA, 0x3}, /* Freq 5840 */
	{169, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x2D555, 0x3}, /* Freq 5845 */
	{170, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x30000, 0x3}, /* Freq 5850 */
	{171, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x32AAA, 0x3}, /* Freq 5855 */
	{172, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x35555, 0x3}, /* Freq 5860 */
	{173, 	(RF_A_BAND | RF_A_BAND_HB),	 0x02, 0x3F, 0x7F, 0xDD, 0xC3, 0x40, 0x0, 0x80, 0x0, 0/*0 -> 1*/, 0, 0, 0x30, 0, 0x0, 0x8, 0x38000, 0x3}, /* Freq 5865 */
};
UCHAR NUM_OF_MT76x0_SDM_CHNL = (sizeof(MT76x0_SDM_Frequency_Plan) / sizeof(MT76x0_FREQ_ITEM));

static UINT8 MT76x0_SDM_Channel[] = {
	183, 185, 43, 45, 54, 55, 57, 58, 102, 103, 105, 106, 115, 117, 126, 127, 129, 130, 139, 141, 150, 151, 153, 154, 163, 165
};
static UCHAR MT76x0_SDM_Channel_Size = (sizeof(MT76x0_SDM_Channel) / sizeof(UINT8));

static const MT76x0_RF_SWITCH_ITEM MT76x0_RF_BW_Switch[] =
{
	/*   Bank, 		Register,	Bw/Band, 	Value */
		{RF_BANK0,	RF_R17,		RF_G_BAND | BW_20,	0x00},
		{RF_BANK0,	RF_R17,		RF_G_BAND | BW_40,	0x00},
		{RF_BANK0,	RF_R17,		RF_A_BAND | BW_20,	0x00},
		{RF_BANK0,	RF_R17,		RF_A_BAND | BW_40,	0x00},
		{RF_BANK0,	RF_R17,		RF_A_BAND | BW_80,	0x00},

                // TODO: need to check B7.R6 & B7.R7 setting for 2.4G again @20121112
		{RF_BANK7,	RF_R06,		RF_G_BAND | BW_20,	0x40},
		{RF_BANK7,	RF_R06,		RF_G_BAND | BW_40,	0x1C},
		{RF_BANK7,	RF_R06,		RF_A_BAND | BW_20,	0x40},
		{RF_BANK7,	RF_R06,		RF_A_BAND | BW_40,	0x20},
		{RF_BANK7,	RF_R06,		RF_A_BAND | BW_80,	0x10},

		{RF_BANK7,	RF_R07,		RF_G_BAND | BW_20,	0x40},
		{RF_BANK7,	RF_R07,		RF_G_BAND | BW_40,	0x20},
		{RF_BANK7,	RF_R07,		RF_A_BAND | BW_20,	0x40},
		{RF_BANK7,	RF_R07,		RF_A_BAND | BW_40,	0x20},
		{RF_BANK7,	RF_R07,		RF_A_BAND | BW_80,	0x10},

		{RF_BANK7,	RF_R08,		RF_G_BAND | BW_20,	0x03},
		{RF_BANK7,	RF_R08,		RF_G_BAND | BW_40,	0x01},
		{RF_BANK7,	RF_R08,		RF_A_BAND | BW_20,	0x03},
		{RF_BANK7,	RF_R08,		RF_A_BAND | BW_40,	0x01},
		{RF_BANK7,	RF_R08,		RF_A_BAND | BW_80,	0x00},

		// TODO: need to check B7.R58 & B7.R59 setting for 2.4G again @20121112
		{RF_BANK7,	RF_R58,		RF_G_BAND | BW_20,	0x40},
		{RF_BANK7,	RF_R58,		RF_G_BAND | BW_40,	0x40},		
		{RF_BANK7,	RF_R58,		RF_A_BAND | BW_20,	0x40},
		{RF_BANK7,	RF_R58,		RF_A_BAND | BW_40,	0x40},
		{RF_BANK7,	RF_R58,		RF_A_BAND | BW_80,	0x10},

		{RF_BANK7,	RF_R59,		RF_G_BAND | BW_20,	0x40},
		{RF_BANK7,	RF_R59,		RF_G_BAND | BW_40,	0x40},
		{RF_BANK7,	RF_R59,		RF_A_BAND | BW_20,	0x40},
		{RF_BANK7,	RF_R59,		RF_A_BAND | BW_40,	0x40},
		{RF_BANK7,	RF_R59,		RF_A_BAND | BW_80,	0x10},

		{RF_BANK7,	RF_R60,		RF_G_BAND | BW_20,	0xAA},
		{RF_BANK7,	RF_R60,		RF_G_BAND | BW_40,	0xAA},
		{RF_BANK7,	RF_R60,		RF_A_BAND | BW_20,	0xAA},
		{RF_BANK7,	RF_R60,		RF_A_BAND | BW_40,	0xAA},
		{RF_BANK7,	RF_R60,		RF_A_BAND | BW_80,	0xAA},

		{RF_BANK7,	RF_R76,		BW_20,	0x40},
		{RF_BANK7,	RF_R76,		BW_40,	0x40},
		{RF_BANK7,	RF_R76,		BW_80,	0x10},

		{RF_BANK7,	RF_R77,		BW_20,	0x40},
		{RF_BANK7,	RF_R77,		BW_40,	0x40},
		{RF_BANK7,	RF_R77,		BW_80,	0x10},
};
UCHAR MT76x0_RF_BW_Switch_Size = (sizeof(MT76x0_RF_BW_Switch) / sizeof(MT76x0_RF_SWITCH_ITEM));

static const MT76x0_RF_SWITCH_ITEM MT76x0_RF_Band_Switch[] =
{
	/*   Bank, 		Register,	Bw/Band, 		Value */
		{RF_BANK0,	RF_R16,		RF_G_BAND,		0x20},
		{RF_BANK0,	RF_R16,		RF_A_BAND,		0x20},
		
		{RF_BANK0,	RF_R18,		RF_G_BAND,		0x00},
		{RF_BANK0,	RF_R18,		RF_A_BAND,		0x00},

		{RF_BANK0,	RF_R39,		RF_G_BAND,		0x36},
		{RF_BANK0,	RF_R39,		RF_A_BAND_LB,	0x34},
		{RF_BANK0,	RF_R39,		RF_A_BAND_MB,	0x33},
		{RF_BANK0,	RF_R39,		RF_A_BAND_HB,	0x31},
		{RF_BANK0,	RF_R39,		RF_A_BAND_11J,	0x36},

		{RF_BANK6,	RF_R12,		RF_A_BAND_LB,	0x44},
		{RF_BANK6,	RF_R12,		RF_A_BAND_MB,	0x44},
		{RF_BANK6,	RF_R12,		RF_A_BAND_HB,	0x55},
		{RF_BANK6,	RF_R12,		RF_A_BAND_11J,	0x44},

		{RF_BANK6,	RF_R17,		RF_A_BAND_LB,	0x02},
		{RF_BANK6,	RF_R17,		RF_A_BAND_MB,	0x00},
		{RF_BANK6,	RF_R17,		RF_A_BAND_HB,	0x00},
		{RF_BANK6,	RF_R17,		RF_A_BAND_11J,	0x05},

		{RF_BANK6,	RF_R24,		RF_A_BAND_LB,	0xA1},
		{RF_BANK6,	RF_R24,		RF_A_BAND_MB,	0x41},
		{RF_BANK6,	RF_R24,		RF_A_BAND_HB,	0x21},
		{RF_BANK6,	RF_R24,		RF_A_BAND_11J,	0xE1},

		{RF_BANK6,	RF_R39,		RF_A_BAND_LB,	0x36},
		{RF_BANK6,	RF_R39,		RF_A_BAND_MB,	0x34},
		{RF_BANK6,	RF_R39,		RF_A_BAND_HB,	0x32},
		{RF_BANK6,	RF_R39,		RF_A_BAND_11J,	0x37},

		{RF_BANK6,	RF_R42,		RF_A_BAND_LB,	0xFB},
		{RF_BANK6,	RF_R42,		RF_A_BAND_MB,	0xF3},
		{RF_BANK6,	RF_R42,		RF_A_BAND_HB,	0xEB},
		{RF_BANK6,	RF_R42,		RF_A_BAND_11J,	0xEB},

		/* Move R6-R45, R50~R59 to MT76x0_RF_INT_PA_5G_Channel_0_RegTb/MT76x0_RF_EXT_PA_5G_Channel_0_RegTb */
	
		{RF_BANK6,	RF_R127,	RF_G_BAND,		0x84},
		{RF_BANK6,	RF_R127,	RF_A_BAND,		0x04},

		{RF_BANK7,	RF_R05,		RF_G_BAND,		0x40},
		{RF_BANK7,	RF_R05,		RF_A_BAND,		0x00},

		{RF_BANK7,	RF_R09,		RF_G_BAND,		0x00},
		{RF_BANK7,	RF_R09,		RF_A_BAND,		0x00},
		
		{RF_BANK7,	RF_R70,		RF_G_BAND,		0x00},
		{RF_BANK7,	RF_R70,		RF_A_BAND,		0x6D},

		{RF_BANK7,	RF_R71,		RF_G_BAND,		0x00},
		{RF_BANK7,	RF_R71,		RF_A_BAND,		0xB0},

		{RF_BANK7,	RF_R78,		RF_G_BAND,		0x00},
		{RF_BANK7,	RF_R78,		RF_A_BAND,		0x55},

		{RF_BANK7,	RF_R79,		RF_G_BAND,		0x00},
		{RF_BANK7,	RF_R79,		RF_A_BAND,		0x55},
};
UCHAR MT76x0_RF_Band_Switch_Size = (sizeof(MT76x0_RF_Band_Switch) / sizeof(MT76x0_RF_SWITCH_ITEM));

/*
	External PA
*/
static MT76x0_RF_SWITCH_ITEM MT76x0_RF_EXT_PA_RegTb[] = {
	{RF_BANK6,	RF_R45,		RF_A_BAND_LB,	0x63},
	{RF_BANK6,	RF_R45,		RF_A_BAND_MB,	0x43},
	{RF_BANK6,	RF_R45,		RF_A_BAND_HB,	0x33},
	{RF_BANK6,	RF_R45,		RF_A_BAND_11J,	0x73},

	{RF_BANK6,	RF_R50,		RF_A_BAND_LB,	0x02},
	{RF_BANK6,	RF_R50,		RF_A_BAND_MB,	0x02},
	{RF_BANK6,	RF_R50,		RF_A_BAND_HB,	0x02},
	{RF_BANK6,	RF_R50,		RF_A_BAND_11J,	0x02},

	{RF_BANK6,	RF_R51,		RF_A_BAND_LB,	0x02},
	{RF_BANK6,	RF_R51,		RF_A_BAND_MB,	0x02},
	{RF_BANK6,	RF_R51,		RF_A_BAND_HB,	0x02},
	{RF_BANK6,	RF_R51,		RF_A_BAND_11J,	0x02},

	{RF_BANK6,	RF_R52,		RF_A_BAND_LB,	0x08},
	{RF_BANK6,	RF_R52,		RF_A_BAND_MB,	0x08},
	{RF_BANK6,	RF_R52,		RF_A_BAND_HB,	0x08},
	{RF_BANK6,	RF_R52,		RF_A_BAND_11J,	0x08},

	{RF_BANK6,	RF_R53,		RF_A_BAND_LB,	0x08},
	{RF_BANK6,	RF_R53,		RF_A_BAND_MB,	0x08},
	{RF_BANK6,	RF_R53,		RF_A_BAND_HB,	0x08},
	{RF_BANK6,	RF_R53,		RF_A_BAND_11J,	0x08},

	{RF_BANK6,	RF_R54,		RF_A_BAND_LB,	0x0A},
	{RF_BANK6,	RF_R54,		RF_A_BAND_MB,	0x0A},
	{RF_BANK6,	RF_R54,		RF_A_BAND_HB,	0x0A},
	{RF_BANK6,	RF_R54,		RF_A_BAND_11J,	0x0A},

	{RF_BANK6,	RF_R55,		RF_A_BAND_LB,	0x0A},
	{RF_BANK6,	RF_R55,		RF_A_BAND_MB,	0x0A},
	{RF_BANK6,	RF_R55,		RF_A_BAND_HB,	0x0A},
	{RF_BANK6,	RF_R55,		RF_A_BAND_11J,	0x0A},

	{RF_BANK6,	RF_R56,		RF_A_BAND_LB,	0x05},
	{RF_BANK6,	RF_R56,		RF_A_BAND_MB,	0x05},
	{RF_BANK6,	RF_R56,		RF_A_BAND_HB,	0x05},
	{RF_BANK6,	RF_R56,		RF_A_BAND_11J,	0x05},

	{RF_BANK6,	RF_R57,		RF_A_BAND_LB,	0x05},
	{RF_BANK6,	RF_R57,		RF_A_BAND_MB,	0x05},
	{RF_BANK6,	RF_R57,		RF_A_BAND_HB,	0x05},
	{RF_BANK6,	RF_R57,		RF_A_BAND_11J,	0x05},

	{RF_BANK6,	RF_R58,		RF_A_BAND_LB,	0x05},
	{RF_BANK6,	RF_R58,		RF_A_BAND_MB,	0x03},
	{RF_BANK6,	RF_R58,		RF_A_BAND_HB,	0x02},
	{RF_BANK6,	RF_R58,		RF_A_BAND_11J,	0x07},

	{RF_BANK6,	RF_R59,		RF_A_BAND_LB,	0x05},
	{RF_BANK6,	RF_R59,		RF_A_BAND_MB,	0x03},
	{RF_BANK6,	RF_R59,		RF_A_BAND_HB,	0x02},
	{RF_BANK6,	RF_R59,		RF_A_BAND_11J,	0x07},
};
static UINT32 MT76x0_RF_EXT_PA_RegTb_Size = (sizeof(MT76x0_RF_EXT_PA_RegTb) / sizeof(MT76x0_RF_SWITCH_ITEM));

/*
	Internal PA
*/
static MT76x0_RF_SWITCH_ITEM MT76x0_RF_INT_PA_RegTb[] = {
};
static UINT32 MT76x0_RF_INT_PA_RegTb_Size = (sizeof(MT76x0_RF_INT_PA_RegTb) / sizeof(MT76x0_RF_SWITCH_ITEM));
		
//
// Initialize FCE
//
VOID InitFce(
	PRTMP_ADAPTER pAd)
{
	L2_STUFFING_STRUC L2Stuffing;

	L2Stuffing.word = 0;

	DBGPRINT(RT_DEBUG_TRACE, ("%s: -->\n", __FUNCTION__));
	
	RTUSBReadMACRegister(pAd, FCE_L2_STUFF, &L2Stuffing.word);
	L2Stuffing.field.FS_WR_MPDU_LEN_EN = 0;
	RTUSBWriteMACRegister(pAd, FCE_L2_STUFF, L2Stuffing.word, FALSE);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: <--\n", __FUNCTION__));
}


/*
	Select 2.4/5GHz band
*/
VOID SelectBandMT76x0(
	IN PRTMP_ADAPTER pAd, 
	IN UCHAR Channel)
{
	if (!IS_MT76x0(pAd))
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s: Incorrect NIC\n", __FUNCTION__));
		
		return;
	}
	
	DBGPRINT(RT_DEBUG_INFO, ("%s: -->\n", __FUNCTION__));

	if (Channel <= 14) 
	{

		/*
			Select 2.4GHz 
		*/
		RF_RANDOM_WRITE(pAd, MT76x0_RF_2G_Channel_0_RegTb, MT76x0_RF_2G_Channel_0_RegTb_Size);

		rlt_rf_write(pAd, RF_BANK5, RF_R00, 0x45);
		rlt_rf_write(pAd, RF_BANK6, RF_R00, 0x44);

		rtmp_mac_set_band(pAd, BAND_24G);

		RTMP_IO_WRITE32(pAd, TX_ALC_VGA3, 0x00050007);
		RTMP_IO_WRITE32(pAd, TX0_RF_GAIN_CORR, 0x003E0002);
	}
	else
	{
		/*
			Select 5GHz 
		*/
		RF_RANDOM_WRITE(pAd, MT76x0_RF_5G_Channel_0_RegTb, MT76x0_RF_5G_Channel_0_RegTb_Size);

		rlt_rf_write(pAd, RF_BANK5, RF_R00, 0x44);
		rlt_rf_write(pAd, RF_BANK6, RF_R00, 0x45);
				
		rtmp_mac_set_band(pAd, BAND_5G);

		RTMP_IO_WRITE32(pAd, TX_ALC_VGA3, 0x00000005);
		RTMP_IO_WRITE32(pAd, TX0_RF_GAIN_CORR, 0x01010102);
	}

	DBGPRINT(RT_DEBUG_INFO, ("%s: <--\n", __FUNCTION__));
}

/*
	Set RF channel frequency parameters:	
	Rdiv: R24[1:0]
	N: R29[7:0], R30[0]
	Nominator: R31[4:0]
	Non-Sigma: !SDM R31[7:5]
	Den: (Denomina - 8) R32[4:0]
	Loop Filter Config: R33, R34
	Pll_idiv: frac comp R35[6:0]
*/
VOID SetRfChFreqParametersMT76x0(
	IN PRTMP_ADAPTER pAd, 
	IN UCHAR Channel)
{
	UINT32 i = 0, RfBand = 0, MacReg = 0;
	UCHAR RFValue = 0;
	BOOLEAN bSDM = FALSE;
	MT76x0_FREQ_ITEM *pMT76x0_freq_item = NULL;

	if (!IS_MT76x0(pAd))
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s: Incorrect NIC\n", __FUNCTION__));		
		return;
	}
	
	DBGPRINT(RT_DEBUG_INFO, ("%s: -->\n", __FUNCTION__));

	for (i = 0; i < MT76x0_SDM_Channel_Size; i++)
	{
		if (Channel == MT76x0_SDM_Channel[i])
		{
			bSDM = TRUE;
			break;
		}
	}
	
	for (i = 0; i < NUM_OF_MT76x0_CHNL; i++)
	{
		if (Channel == MT76x0_Frequency_Plan[i].Channel)
		{
			RfBand = MT76x0_Frequency_Plan[i].Band;			

			if (bSDM)
				pMT76x0_freq_item = &(MT76x0_SDM_Frequency_Plan[i]);
			else
				pMT76x0_freq_item = &(MT76x0_Frequency_Plan[i]);

			/* 
				R37
			*/
			rlt_rf_write(pAd, RF_BANK0, RF_R37, pMT76x0_freq_item->pllR37);
			
				/*
				R36
				*/
			rlt_rf_write(pAd, RF_BANK0, RF_R36, pMT76x0_freq_item->pllR36);

			/*
				R35
			*/
			rlt_rf_write(pAd, RF_BANK0, RF_R35, pMT76x0_freq_item->pllR35);

			/*
				R34
			*/
			rlt_rf_write(pAd, RF_BANK0, RF_R34, pMT76x0_freq_item->pllR34);

			/*
				R33
			*/
			rlt_rf_write(pAd, RF_BANK0, RF_R33, pMT76x0_freq_item->pllR33);

			/*
				R32<7:5>
			*/
			rlt_rf_read(pAd, RF_BANK0, RF_R32, &RFValue);
			RFValue &= ~(0xE0);
			RFValue |= pMT76x0_freq_item->pllR32_b7b5;
			rlt_rf_write(pAd, RF_BANK0, RF_R32, RFValue);
			
			/*
				R32<4:0> pll_den: (Denomina - 8)
			*/
			rlt_rf_read(pAd, RF_BANK0, RF_R32, &RFValue);
			RFValue &= ~(0x1F);
			RFValue |= pMT76x0_freq_item->pllR32_b4b0;
			rlt_rf_write(pAd, RF_BANK0, RF_R32, RFValue);

			/*
				R31<7:5>
			*/
			rlt_rf_read(pAd, RF_BANK0, RF_R31, &RFValue);
			RFValue &= ~(0xE0);
			RFValue |= pMT76x0_freq_item->pllR31_b7b5;
			rlt_rf_write(pAd, RF_BANK0, RF_R31, RFValue);

			/*
				R31<4:0> pll_k(Nominator)
			*/
			rlt_rf_read(pAd, RF_BANK0, RF_R31, &RFValue);
			RFValue &= ~(0x1F);
			RFValue |= pMT76x0_freq_item->pllR31_b4b0;
			rlt_rf_write(pAd, RF_BANK0, RF_R31, RFValue);
			
			/*
				R30<7> sdm_reset_n
			*/
			rlt_rf_read(pAd, RF_BANK0, RF_R30, &RFValue);
			RFValue &= ~(0x80);
			if (bSDM)
			{
				rlt_rf_write(pAd, RF_BANK0, RF_R30, RFValue);
				RFValue |= (0x80);
				rlt_rf_write(pAd, RF_BANK0, RF_R30, RFValue);
			}
			else
			{
				RFValue |= pMT76x0_freq_item->pllR30_b7;
				rlt_rf_write(pAd, RF_BANK0, RF_R30, RFValue);
			}
			
			/*
				R30<6:2> sdmmash_prbs,sin
			*/
			rlt_rf_read(pAd, RF_BANK0, RF_R30, &RFValue);
			RFValue &= ~(0x7C);
			RFValue |= pMT76x0_freq_item->pllR30_b6b2;
			rlt_rf_write(pAd, RF_BANK0, RF_R30, RFValue);
			
			/*
				R30<1> sdm_bp
			*/
			rlt_rf_read(pAd, RF_BANK0, RF_R30, &RFValue);
			RFValue &= ~(0x02);
			RFValue |= (pMT76x0_freq_item->pllR30_b1 << 1);
			rlt_rf_write(pAd, RF_BANK0, RF_R30, RFValue);
			
			/*
				R30<0> R29<7:0> (hex) pll_n
			*/
			RFValue = pMT76x0_freq_item->pll_n & 0x00FF;
			rlt_rf_write(pAd, RF_BANK0, RF_R29, RFValue);

			rlt_rf_read(pAd, RF_BANK0, RF_R30, &RFValue);
			RFValue &= ~(0x1);
			RFValue |= ((pMT76x0_freq_item->pll_n >> 8) & 0x0001);
			rlt_rf_write(pAd, RF_BANK0, RF_R30, RFValue);
			
			/*
				R28<7:6> isi_iso
			*/
			rlt_rf_read(pAd, RF_BANK0, RF_R28, &RFValue);
			RFValue &= ~(0xC0);
			RFValue |= pMT76x0_freq_item->pllR28_b7b6;
			rlt_rf_write(pAd, RF_BANK0, RF_R28, RFValue);
			
			/*
				R28<5:4> pfd_dly
			*/
			rlt_rf_read(pAd, RF_BANK0, RF_R28, &RFValue);
			RFValue &= ~(0x30);
			RFValue |= pMT76x0_freq_item->pllR28_b5b4;
			rlt_rf_write(pAd, RF_BANK0, RF_R28, RFValue);
			
			/*
				R28<3:2> clksel option
			*/
			rlt_rf_read(pAd, RF_BANK0, RF_R28, &RFValue);
			RFValue &= ~(0x0C);
			RFValue |= pMT76x0_freq_item->pllR28_b3b2;
			rlt_rf_write(pAd, RF_BANK0, RF_R28, RFValue);

			/*
				R28<1:0> R27<7:0> R26<7:0> (hex) sdm_k
			*/
			RFValue = pMT76x0_freq_item->Pll_sdm_k & 0x000000FF;
			rlt_rf_write(pAd, RF_BANK0, RF_R26, RFValue);

			RFValue = ((pMT76x0_freq_item->Pll_sdm_k >> 8) & 0x000000FF);
			rlt_rf_write(pAd, RF_BANK0, RF_R27, RFValue);
			
			rlt_rf_read(pAd, RF_BANK0, RF_R28, &RFValue);
			RFValue &= ~(0x3);
			RFValue |= ((pMT76x0_freq_item->Pll_sdm_k >> 16) & 0x0003);
			rlt_rf_write(pAd, RF_BANK0, RF_R28, RFValue);
			
			/*
				R24<1:0> xo_div
			*/
			rlt_rf_read(pAd, RF_BANK0, RF_R24, &RFValue);
			RFValue &= ~(0x3);
			RFValue |= pMT76x0_freq_item->pllR24_b1b0;
			rlt_rf_write(pAd, RF_BANK0, RF_R24, RFValue);

			
			pAd->LatchRfRegs.Channel = Channel; /* Channel latch */

			DBGPRINT(RT_DEBUG_TRACE,
				("%s: SwitchChannel#%d(Band = 0x%02X, RF=%d, %dT), "
				"0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, %u, 0x%02X, %u, 0x%02X, 0x%02X, 0x%02X, 0x%04X, 0x%02X, 0x%02X, 0x%02X, 0x%08X, 0x%02X\n",
				__FUNCTION__,
				Channel,
				RfBand,
				pAd->RfIcType,
				pAd->Antenna.field.TxPath,
				pMT76x0_freq_item->pllR37,
				pMT76x0_freq_item->pllR36,
				pMT76x0_freq_item->pllR35,
				pMT76x0_freq_item->pllR34,
				pMT76x0_freq_item->pllR33,
				pMT76x0_freq_item->pllR32_b7b5,
				pMT76x0_freq_item->pllR32_b4b0,
				pMT76x0_freq_item->pllR31_b7b5,
				pMT76x0_freq_item->pllR31_b4b0,
				pMT76x0_freq_item->pllR30_b7,
				pMT76x0_freq_item->pllR30_b6b2,
				pMT76x0_freq_item->pllR30_b1,
				pMT76x0_freq_item->pll_n,
				pMT76x0_freq_item->pllR28_b7b6,
				pMT76x0_freq_item->pllR28_b5b4,
				pMT76x0_freq_item->pllR28_b3b2,
				pMT76x0_freq_item->Pll_sdm_k,
				pMT76x0_freq_item->pllR24_b1b0));
			break;
		}
	}	


	for(i = 0; i < MT76x0_RF_BW_Switch_Size; i++)
	{
		if (pAd->CommonCfg.BBPCurrentBW == MT76x0_RF_BW_Switch[i].BwBand)
		{
			rlt_rf_write(pAd, 
						MT76x0_RF_BW_Switch[i].Bank,
						MT76x0_RF_BW_Switch[i].Register,
						MT76x0_RF_BW_Switch[i].Value);
		}
		else if ((pAd->CommonCfg.BBPCurrentBW == (MT76x0_RF_BW_Switch[i].BwBand & 0xFF)) &&
				 (RfBand & MT76x0_RF_BW_Switch[i].BwBand))
		{
			rlt_rf_write(pAd, 
						MT76x0_RF_BW_Switch[i].Bank,
						MT76x0_RF_BW_Switch[i].Register,
						MT76x0_RF_BW_Switch[i].Value);
		}
	}

	for(i = 0; i < MT76x0_RF_Band_Switch_Size; i++)
	{
		if (MT76x0_RF_Band_Switch[i].BwBand & RfBand)
		{
			rlt_rf_write(pAd, 
						MT76x0_RF_Band_Switch[i].Bank,
						MT76x0_RF_Band_Switch[i].Register,
						MT76x0_RF_Band_Switch[i].Value);
		}
	}
	
	RTMP_IO_READ32(pAd, RF_MISC, &MacReg);
	MacReg &= ~(0xC); /* Clear 0x518[3:2] */
	RTMP_IO_WRITE32(pAd, RF_MISC, MacReg);

	DBGPRINT(RT_DEBUG_INFO, ("\n\n*********** PAType = %d ***********\n\n", pAd->chipCap.PAType));
	if ((pAd->chipCap.PAType == INT_PA_2G_5G) ||
		((pAd->chipCap.PAType == EXT_PA_5G_ONLY) && (RfBand & RF_G_BAND)) ||
		((pAd->chipCap.PAType == EXT_PA_2G_ONLY) && (RfBand & RF_A_BAND)))
	{
		/* Internal PA */
		for(i = 0; i < MT76x0_RF_INT_PA_RegTb_Size; i++)
	{
			if (MT76x0_RF_INT_PA_RegTb[i].BwBand & RfBand)
			{
				rlt_rf_write(pAd, 
							MT76x0_RF_INT_PA_RegTb[i].Bank,
							MT76x0_RF_INT_PA_RegTb[i].Register,
							MT76x0_RF_INT_PA_RegTb[i].Value);

				DBGPRINT(RT_DEBUG_INFO, ("%s: INT_PA_RegTb - B%d.R%02d = 0x%02x\n", 
							__FUNCTION__, 
							MT76x0_RF_INT_PA_RegTb[i].Bank,
							MT76x0_RF_INT_PA_RegTb[i].Register,
							MT76x0_RF_INT_PA_RegTb[i].Value));
			}
		}
	}
	else
	{
		/*
			RF_MISC (offset: 0x0518)
			[2]1'b1: enable external A band PA, 1'b0: disable external A band PA
			[3]1'b1: enable external G band PA, 1'b0: disable external G band PA
		*/
		if (RfBand & RF_A_BAND)
		{
			RTMP_IO_READ32(pAd, RF_MISC, &MacReg);
			MacReg |= (0x4);
			RTMP_IO_WRITE32(pAd, RF_MISC, MacReg);
		}
		else
		{
			RTMP_IO_READ32(pAd, RF_MISC, &MacReg);
			MacReg |= (0x8);
			RTMP_IO_WRITE32(pAd, RF_MISC, MacReg);
		}
		
		/* External PA */
		for(i = 0; i < MT76x0_RF_EXT_PA_RegTb_Size; i++)
		{
			if (MT76x0_RF_EXT_PA_RegTb[i].BwBand & RfBand)
			{
				rlt_rf_write(pAd, 
							MT76x0_RF_EXT_PA_RegTb[i].Bank,
							MT76x0_RF_EXT_PA_RegTb[i].Register,
							MT76x0_RF_EXT_PA_RegTb[i].Value);

				DBGPRINT(RT_DEBUG_INFO, ("%s: EXT_PA_RegTb - B%d.R%02d = 0x%02x\n", 
							__FUNCTION__, 
							MT76x0_RF_EXT_PA_RegTb[i].Bank,
							MT76x0_RF_EXT_PA_RegTb[i].Register,
							MT76x0_RF_EXT_PA_RegTb[i].Value));
			}
		}
	}

	if (RfBand & RF_G_BAND)
	{
		RTMP_IO_WRITE32(pAd, TX0_RF_GAIN_ATTEN, 0x63707400);
		/* Set Atten mode = 2 for G band and disable Tx Inc DCOC Cal by Chee's comment */
		RTMP_IO_READ32(pAd, TX_ALC_CFG_1, &MacReg);
		MacReg &= 0x896400FF;
		RTMP_IO_WRITE32(pAd, TX_ALC_CFG_1, MacReg); 		
	}
	else
	{
		RTMP_IO_WRITE32(pAd, TX0_RF_GAIN_ATTEN, 0x686A7800);
		/* Set Atten mode = 0 For Ext A band and disable Tx Inc DCOC Cal by Chee's comment */
		RTMP_IO_READ32(pAd, TX_ALC_CFG_1, &MacReg);
		MacReg &= 0x890400FF;
		RTMP_IO_WRITE32(pAd, TX_ALC_CFG_1, MacReg); 		
	}
	
	DBGPRINT(RT_DEBUG_INFO, ("%s: <--\n", __FUNCTION__));
}

static VOID NICInitMT76x0RFRegisters(RTMP_ADAPTER *pAd)
{

	UINT32 IdReg;
	UCHAR RFValue;


	RF_RANDOM_WRITE(pAd, MT76x0_RF_Central_RegTb, MT76x0_RF_Central_RegTb_Size);

	RF_RANDOM_WRITE(pAd, MT76x0_RF_2G_Channel_0_RegTb, MT76x0_RF_2G_Channel_0_RegTb_Size);

	RF_RANDOM_WRITE(pAd, MT76x0_RF_5G_Channel_0_RegTb, MT76x0_RF_5G_Channel_0_RegTb_Size);

	RF_RANDOM_WRITE(pAd, MT76x0_RF_VGA_Channel_0_RegTb, MT76x0_RF_VGA_Channel_0_RegTb_Size);

	for(IdReg = 0; IdReg < MT76x0_RF_BW_Switch_Size; IdReg++)
	{
		if (pAd->CommonCfg.BBPCurrentBW == MT76x0_RF_BW_Switch[IdReg].BwBand)
		{
			rlt_rf_write(pAd, 
						MT76x0_RF_BW_Switch[IdReg].Bank,
						MT76x0_RF_BW_Switch[IdReg].Register,
						MT76x0_RF_BW_Switch[IdReg].Value);
		}
		else if ((BW_20 == (MT76x0_RF_BW_Switch[IdReg].BwBand & 0xFF)) &&
				 (RF_G_BAND & MT76x0_RF_BW_Switch[IdReg].BwBand))
		{
			rlt_rf_write(pAd, 
						MT76x0_RF_BW_Switch[IdReg].Bank,
						MT76x0_RF_BW_Switch[IdReg].Register,
						MT76x0_RF_BW_Switch[IdReg].Value);
		}
	}

	for(IdReg = 0; IdReg < MT76x0_RF_Band_Switch_Size; IdReg++)
	{
		if (MT76x0_RF_Band_Switch[IdReg].BwBand & RF_G_BAND)
		{
			rlt_rf_write(pAd, 
						MT76x0_RF_Band_Switch[IdReg].Bank,
						MT76x0_RF_Band_Switch[IdReg].Register,
						MT76x0_RF_Band_Switch[IdReg].Value);
		}
	}

	/*
		Frequency calibration
		E1: B0.R22<6:0>: xo_cxo<6:0>
		E2: B0.R21<0>: xo_cxo<0>, B0.R22<7:0>: xo_cxo<8:1> 
	*/
	RFValue = (UCHAR)(pAd->RfFreqOffset & 0xFF);
	RFValue = min(RFValue, (UCHAR)0xBF); /* Max of 9-bit built-in crystal oscillator C1 code */
	rlt_rf_write(pAd, RF_BANK0, RF_R22, RFValue);
	
	rlt_rf_read(pAd, RF_BANK0, RF_R22, &RFValue);
	DBGPRINT(RT_DEBUG_TRACE, ("%s: B0.R22 = 0x%02x\n", __FUNCTION__, RFValue));

	/* 
		Reset the DAC (Set B0.R73<7>=1, then set B0.R73<7>=0, and then set B0.R73<7>) during power up.
	*/
	rlt_rf_read(pAd, RF_BANK0, RF_R73, &RFValue);
	RFValue |= 0x80;
	rlt_rf_write(pAd, RF_BANK0, RF_R73, RFValue);	
	RFValue &= (~0x80);
	rlt_rf_write(pAd, RF_BANK0, RF_R73, RFValue);	
	RFValue |= 0x80;
	rlt_rf_write(pAd, RF_BANK0, RF_R73, RFValue);	

	/* 
		vcocal_en (initiate VCO calibration (reset after completion)) - It should be at the end of RF configuration. 
	*/
	rlt_rf_read(pAd, RF_BANK0, RF_R04, &RFValue);
	RFValue = ((RFValue & ~0x80) | 0x80); 
	rlt_rf_write(pAd, RF_BANK0, RF_R04, RFValue);
	return;
}


/*
========================================================================
Routine Description:
	Initialize specific MAC registers.

Arguments:
	pAd					- WLAN control block pointer

Return Value:
	None

Note:
========================================================================
*/
static VOID NICInitMT76x0MacRegisters(RTMP_ADAPTER *pAd)
{
	UINT32 MacReg = 0;
	USHORT trsw_mode = 0;

	/*
		Enable PBF and MAC clock
		SYS_CTRL[11:10] = 0x3
	*/
	RANDOM_WRITE(pAd, MT76x0_MACRegTable, MT76x0_NUM_MAC_REG_PARMS);

	RT28xx_EEPROM_READ16(pAd, 0x24, trsw_mode);
	if (((trsw_mode & ~(0xFFCF)) >> 4) == 0x3) {
		RTMP_IO_WRITE32(pAd, TX_SW_CFG1, 0x00040200); /* Adjust TR_SW off delay for TRSW mode */
		DBGPRINT(RT_DEBUG_TRACE, ("%s: TRSW = 0x%x\n", __FUNCTION__, ((trsw_mode & ~(0xFFCF)) >> 4)));
	}

#ifdef HDR_TRANS_TX_SUPPORT
	/*
		Enable Header Translation TX 
	*/
	RTMP_IO_READ32(pAd, HEADER_TRANS_CTRL_REG, &MacReg);
	MacReg |= 0x1; /* 0x1: TX, 0x2: RX */
	RTMP_IO_WRITE32(pAd, HEADER_TRANS_CTRL_REG, MacReg);
#endif /* HDR_TRANS_TX_SUPPORT */

	/*
		Release BBP and MAC reset
		MAC_SYS_CTRL[1:0] = 0x0
	*/
	RTMP_IO_READ32(pAd, MAC_SYS_CTRL, &MacReg);
	MacReg &= ~(0x3);
	RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, MacReg);


	/*
		Set 0x141C[15:12]=0xF
	*/
	RTMP_IO_READ32(pAd, EXT_CCA_CFG, &MacReg);
	MacReg |= (0x0000F000);
	RTMP_IO_WRITE32(pAd, EXT_CCA_CFG, MacReg);

	InitFce(pAd);

	/*
		TxRing 9 is for Mgmt frame.
		TxRing 8 is for In-band command frame.
		WMM_RG0_TXQMA: This register setting is for FCE to define the rule of TxRing 9.
		WMM_RG1_TXQMA: This register setting is for FCE to define the rule of TxRing 8.
	*/
	RTMP_IO_READ32(pAd, WMM_CTRL, &MacReg);
	MacReg &= ~(0x000003FF);
	MacReg |= (0x00000201);
	RTMP_IO_WRITE32(pAd, WMM_CTRL, MacReg);

#ifdef MCS_LUT_SUPPORT
	RTMP_IO_READ32(pAd, TX_FBK_LIMIT, &MacReg);
	if (RTMP_TEST_MORE_FLAG(pAd, fASIC_CAP_MCS_LUT))
		MacReg |= 0x40000;
	else
		MacReg &= (~0x40000);
	RTMP_IO_WRITE32(pAd, TX_FBK_LIMIT, MacReg);
#endif /* MCS_LUT_SUPPORT */

	return;
}


/*
========================================================================
Routine Description:
	Initialize specific BBP registers.

Arguments:
	pAd					- WLAN control block pointer

Return Value:
	None

Note:
========================================================================
*/
static VOID NICInitMT76x0BbpRegisters(
	IN	PRTMP_ADAPTER pAd)
{

	INT IdReg;

	RANDOM_WRITE(pAd, MT76x0_BBP_Init_Tab, MT76x0_BBP_Init_Tab_Size);
	
	for (IdReg = 0; IdReg < MT76x0_BPP_SWITCH_Tab_Size; IdReg++)
	{
		if (((RF_G_BAND | RF_BW_20) & MT76x0_BPP_SWITCH_Tab[IdReg].BwBand) == (RF_G_BAND | RF_BW_20))
		{
			RTMP_BBP_IO_WRITE32(pAd, MT76x0_BPP_SWITCH_Tab[IdReg].RegDate.Register,
					MT76x0_BPP_SWITCH_Tab[IdReg].RegDate.Value);
		}
	}

	RANDOM_WRITE(pAd, MT76x0_DCOC_Tab, MT76x0_DCOC_Tab_Size);


	return;
}


static VOID MT76x0_AsicAntennaDefaultReset(
	IN struct _RTMP_ADAPTER	*pAd,
	IN EEPROM_ANTENNA_STRUC *pAntenna)
{
	pAntenna->word = 0;
	pAntenna->field.RfIcType = RFIC_7650;
	pAntenna->field.TxPath = 1;
	pAntenna->field.RxPath = 1;
}


static VOID MT76x0_ChipBBPAdjust(RTMP_ADAPTER *pAd)
{
	static char *ext_str[]={"extNone", "extAbove", "", "extBelow"};
	UCHAR rf_bw, ext_ch;


#ifdef DOT11_N_SUPPORT
	if (get_ht_cent_ch(pAd, &rf_bw, &ext_ch) == FALSE)
#endif /* DOT11_N_SUPPORT */
	{
		rf_bw = BW_20;
		ext_ch = EXTCHA_NONE;
		pAd->CommonCfg.CentralChannel = pAd->CommonCfg.Channel;
	}

#ifdef DOT11_VHT_AC
	if (WMODE_CAP(pAd->CommonCfg.PhyMode, WMODE_AC) &&
		(pAd->CommonCfg.Channel > 14) &&
		(rf_bw == BW_40) &&
		(pAd->CommonCfg.vht_bw == VHT_BW_80) &&
		(pAd->CommonCfg.vht_cent_ch != pAd->CommonCfg.CentralChannel))
	{
		rf_bw = BW_80;
		pAd->CommonCfg.vht_cent_ch = vht_cent_ch_freq(pAd, pAd->CommonCfg.Channel);
	}

	DBGPRINT(RT_DEBUG_OFF, ("%s():rf_bw=%d, ext_ch=%d, PrimCh=%d, HT-CentCh=%d, VHT-CentCh=%d\n",
				__FUNCTION__, rf_bw, ext_ch, pAd->CommonCfg.Channel,
				pAd->CommonCfg.CentralChannel, pAd->CommonCfg.vht_cent_ch));
#endif /* DOT11_VHT_AC */

	rtmp_bbp_set_bw(pAd, rf_bw);

	/* TX/Rx : control channel setting */
	rtmp_mac_set_ctrlch(pAd, ext_ch);
	rtmp_bbp_set_ctrlch(pAd, ext_ch);
		
#ifdef DOT11_N_SUPPORT
	DBGPRINT(RT_DEBUG_TRACE, ("%s() : %s, ChannelWidth=%d, Channel=%d, ExtChanOffset=%d(%d) \n",
					__FUNCTION__, ext_str[ext_ch],
					pAd->CommonCfg.HtCapability.HtCapInfo.ChannelWidth,
					pAd->CommonCfg.Channel,
					pAd->CommonCfg.RegTransmitSetting.field.EXTCHA,
					pAd->CommonCfg.AddHTInfo.AddHtInfo.ExtChanOffset));
#endif /* DOT11_N_SUPPORT */
}

static VOID MT76x0_ChipSwitchChannel(
	struct _RTMP_ADAPTER *pAd,
	UCHAR Channel,
	BOOLEAN bScan)
{
	CHAR TxPwer = 0; /* Bbp94 = BBPR94_DEFAULT, TxPwer2 = DEFAULT_RF_TX_POWER; */
	UCHAR RFValue = 0;
	UINT32 RegValue = 0;
	UINT32 Index;
	UINT32 rf_phy_mode, rf_bw = RF_BW_20;
	UCHAR bbp_ch_idx, delta_pwr;
	UINT32 ret;
	ULONG Old, New, Diff;
#ifndef MT76x0_TSSI_CAL_COMPENSATION
	UINT32 Value;
#endif /* !MT76x0_TSSI_CAL_COMPENSATION */
#ifdef SINGLE_SKU_V2
	CHAR SkuBasePwr;
	CHAR ChannelPwrAdj;
#endif /* SINGLE_SKU_V2 */
	
	RTMP_GetCurrentSystemTick(&Old);

	bbp_ch_idx = vht_prim_ch_idx(Channel, pAd->CommonCfg.Channel);
			
	DBGPRINT(RT_DEBUG_TRACE, ("%s(): MAC_STATUS_CFG = 0x%08x, bbp_ch_idx = %d, Channel=%d\n",
				__FUNCTION__, RegValue, bbp_ch_idx, Channel));

	if (Channel > 14)
		rf_phy_mode = RF_A_BAND;
	else
		rf_phy_mode = RF_G_BAND;

#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_WAIT(&pAd->hw_atomic, ret);
		if (ret != 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", ret));
			return;
		}
	}
#endif /* RTMP_MAC_USB */

	RTMP_IO_READ32(pAd, EXT_CCA_CFG, &RegValue);
	RegValue &= ~(0xFFF);
	if (pAd->CommonCfg.BBPCurrentBW == BW_80)
	{
		rf_bw = RF_BW_80;
		if (bbp_ch_idx == 0)
		{
			RegValue |= 0x1e4;
		}
		else if (bbp_ch_idx == 1)
		{
			RegValue |= 0x2e1;
		}
		else if (bbp_ch_idx == 2)
		{
			RegValue |= 0x41e;
		}
		else if (bbp_ch_idx == 3)
		{
			RegValue |= 0x81b;
		}
#ifdef MT76x0_TSSI_CAL_COMPENSATION
		delta_pwr = pAd->chipCap.delta_tw_pwr_bw80;
#endif /* MT76x0_TSSI_CAL_COMPENSATION */
	}
	else if (pAd->CommonCfg.BBPCurrentBW == BW_40)
	{
		rf_bw = RF_BW_40;
		if (pAd->CommonCfg.CentralChannel > pAd->CommonCfg.Channel)
			RegValue |= 0x1e4;
		else
			RegValue |= 0x2e1;
#ifdef MT76x0_TSSI_CAL_COMPENSATION
		if (Channel > 14)
			delta_pwr = pAd->chipCap.delta_tw_pwr_bw40_5G;
		else
			delta_pwr = pAd->chipCap.delta_tw_pwr_bw40_2G;
#endif /* MT76x0_TSSI_CAL_COMPENSATION */
	}
	else
	{
		rf_bw = RF_BW_20;
		RegValue |= 0x1e4;
		
	}
	RTMP_IO_WRITE32(pAd, EXT_CCA_CFG, RegValue);
	

	/*
		Configure 2.4/5GHz before accessing other MAC/BB/RF registers
	*/
	SelectBandMT76x0(pAd, Channel);

	/*
		Set RF channel frequency parameters (Rdiv, N, K, D and Ksd)
	*/
	SetRfChFreqParametersMT76x0(pAd, Channel);


	for (Index = 0; Index < MAX_NUM_OF_CHANNELS; Index++)
	{
		if (Channel == pAd->TxPower[Index].Channel)
		{
			TxPwer = pAd->TxPower[Index].Power;
			break;
		}
	}	

	/* set Japan Tx filter at channel 14 */
	RTMP_BBP_IO_READ32(pAd, CORE_R1, &RegValue);
	if (Channel == 14)
		RegValue |= 0x20;		
	else
		RegValue &= (~0x20);
	RTMP_BBP_IO_WRITE32(pAd, CORE_R1, RegValue);

	for (Index = 0; Index < MT76x0_BPP_SWITCH_Tab_Size; Index++)
	{
		if (((rf_phy_mode | rf_bw) & MT76x0_BPP_SWITCH_Tab[Index].BwBand) == (rf_phy_mode | rf_bw))
		{
			if ((MT76x0_BPP_SWITCH_Tab[Index].RegDate.Register == AGC1_R8))
			{
				UINT32 eLNAgain = (MT76x0_BPP_SWITCH_Tab[Index].RegDate.Value & 0x0000FF00) >> 8;

				if (Channel > 14)
				{
					if (Channel < pAd->chipCap.a_band_mid_ch)
						eLNAgain -= (pAd->ALNAGain0*2);
					else if (Channel < pAd->chipCap.a_band_high_ch)
						eLNAgain -= (pAd->ALNAGain1*2);
					else
						eLNAgain -= (pAd->ALNAGain2*2);
				}
				else
					eLNAgain -= (pAd->BLNAGain*2);

				RTMP_BBP_IO_WRITE32(pAd, MT76x0_BPP_SWITCH_Tab[Index].RegDate.Register,
						(MT76x0_BPP_SWITCH_Tab[Index].RegDate.Value&(~0x0000FF00))|(eLNAgain << 8));				
			}
			else
			{
				RTMP_BBP_IO_WRITE32(pAd, MT76x0_BPP_SWITCH_Tab[Index].RegDate.Register,
						MT76x0_BPP_SWITCH_Tab[Index].RegDate.Value);
			}
		}
	}

	/* 
		VCO calibration (mode 3) 
	*/
	MT76x0_VCO_CalibrationMode3(pAd, Channel);
		
	if (bScan)
		MT76x0_Calibration(pAd, Channel, FALSE, FALSE, FALSE);

	RTMPusecDelay(1000);

#ifndef MT76x0_TSSI_CAL_COMPENSATION
	RTMP_IO_READ32(pAd, TX_ALC_CFG_0, &Value);
	Value = Value & (~0x3F3F);
	Value |= TxPwer;
	Value |= (0x2F2F << 16);
	RTMP_IO_WRITE32(pAd, TX_ALC_CFG_0, Value);
#endif /* !MT76x0_TSSI_CAL_COMPENSATION */
	
#ifdef SINGLE_SKU_V2		
		USHORT ee_val = 0;		
		UCHAR delta_power = 0;

		mt76x0_adjust_per_rate_pwr(pAd);
		
		if (Channel > 14) {			
			RT28xx_EEPROM_READ16(pAd, EEPROM_MT76x0_5G_TARGET_POWER, ee_val);
			pAd->DefaultTargetPwr = ee_val & 0x00FF;
#ifdef DOT11_VHT_AC
			if (pAd->CommonCfg.BBPCurrentBW == BW_80)
				delta_power = pAd->chipCap.delta_tw_pwr_bw80;
			else
#endif /* DOT11_VHT_AC */
				delta_power = pAd->chipCap.delta_tw_pwr_bw40_5G;
		} else {
			RT28xx_EEPROM_READ16(pAd, EEPROM_MT76x0_2G_TARGET_POWER, ee_val);
			pAd->DefaultTargetPwr = ee_val & 0x00FF;
			delta_power = pAd->chipCap.delta_tw_pwr_bw40_2G;
		}
		
		if ((pAd->DefaultTargetPwr == 0x00) || (pAd->DefaultTargetPwr == 0xFF)) {
			pAd->DefaultTargetPwr = 0x20;
			DBGPRINT(RT_DEBUG_ERROR, ("%s: get target power error. Use default target power = 0x%x\n", 
					__FUNCTION__, pAd->DefaultTargetPwr));
		} else {
			DBGPRINT(RT_DEBUG_TRACE, ("%s: DefaultTargetPwr = %d\n", 
					__FUNCTION__, pAd->DefaultTargetPwr));
		}

		/*
			EEPROM 0x50 - Power delta for 2.4G HT40
			EEPROM 0x51 - Power delta for 5G HT40
			EEPROM 0xD3 - Power delta for VHT80
			Bit<7>: Enable/disable power delta of this BW
			Bit<6>: 0: decrease power, 1: increase power
			Bit<5:0>: Each step represents 0.5dB, range from 0 to 4

			Increase or decrease 0x13b0<5:0> when bandwidth is changed
		*/
		if ((pAd->CommonCfg.BBPCurrentBW != BW_20) && (delta_power & 0x80)) {
			if (delta_power & 0x40)
				pAd->DefaultTargetPwr += (delta_power & 0x3F);
			else
				pAd->DefaultTargetPwr -= (delta_power & 0x3F);
		}

		DBGPRINT(RT_DEBUG_TRACE, ("DefaultTargetPwr = 0x%x, delta_power = 0x%x\n", 
			pAd->DefaultTargetPwr, delta_power));
		
		SkuBasePwr = MT76x0_GetSkuChannelBasePwr(pAd, Channel);
		
		if (pAd->DefaultTargetPwr > SkuBasePwr)
			ChannelPwrAdj = SkuBasePwr - pAd->DefaultTargetPwr;
		else
			ChannelPwrAdj = 0;

		if (ChannelPwrAdj > 31)
			ChannelPwrAdj = 31;
		if (ChannelPwrAdj < -32)
			ChannelPwrAdj = -32;

		RTMP_IO_READ32(pAd, TX_ALC_CFG_1, &RegValue);
		RegValue = (RegValue & ~0x3F) | (ChannelPwrAdj & 0x3F);
		RTMP_IO_WRITE32(pAd, TX_ALC_CFG_1, RegValue);
		DBGPRINT(RT_DEBUG_TRACE, ("SkuBasePwr = 0x%x,  DefaultTargetPwr = 0x%x, ChannelPwrAdj = 0x%x(%d), 0x13B4: 0x%x\n", 
			SkuBasePwr, pAd->DefaultTargetPwr, ChannelPwrAdj, ChannelPwrAdj, RegValue));

		MT76x0_UpdateSkuPwr(pAd, Channel);
#endif /* SINGLE_SKU_V2 */
	

#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_UP(&pAd->hw_atomic);
	}
#endif /* RTMP_MAC_USB */
	
	if (Channel > 14) {
		RTMP_IO_WRITE32(pAd, XIFS_TIME_CFG, 0x33a41010);
	} else {
		RTMP_IO_WRITE32(pAd, XIFS_TIME_CFG, 0x33a4100A);
	} 

	RTMP_GetCurrentSystemTick(&New);
	Diff = (New - Old) * 1000 / OS_HZ;
	DBGPRINT(RT_DEBUG_TRACE, ("Switch Channel spent %ldms\n", Diff));
	
	return;
}

#ifdef CONFIG_STA_SUPPORT
static VOID MT76x0_NetDevNickNameInit(RTMP_ADAPTER *pAd)
{

#ifdef RTMP_MAC_USB
	if (IS_MT7650U(pAd))
		snprintf((PSTRING) pAd->nickname, sizeof(pAd->nickname), "MT7650U_STA");
	else if (IS_MT7630U(pAd))
		snprintf((PSTRING) pAd->nickname, sizeof(pAd->nickname), "MT7630U_STA");
	else if (IS_MT7610U(pAd))	
		snprintf((PSTRING) pAd->nickname, sizeof(pAd->nickname), "MT7610U_STA");
#endif
}
#endif /* CONFIG_STA_SUPPORT */

VOID MT76x0_NICInitAsicFromEEPROM(
	IN PRTMP_ADAPTER		pAd)
{
	// TODO: wait TC6008 EEPROM format
}

/*
	NOTE: MAX_NUM_OF_CHANNELS shall  equal sizeof(txpwr_chlist))
*/
static UCHAR mt76x0_txpwr_chlist[] = {
	1, 2,3,4,5,6,7,8,9,10,11,12,13,14,
	36,38,40,44,46,48,52,54,56,60,62,64,
	100,102,104,108,110,112,116,118,120,124,126,128,132,134,136,140,
	149,151,153,157,159,161,165,167,169,171,173,
	42, 58, 106, 122, 155,
};

INT MT76x0_ReadChannelPwr(RTMP_ADAPTER *pAd)
{
	UINT32 i, choffset, idx, ss_offset_g, ss_num;
	EEPROM_TX_PWR_STRUC Power;
	CHAR tx_pwr1, tx_pwr2;

	DBGPRINT(RT_DEBUG_TRACE, ("%s()--->\n", __FUNCTION__));
	
	choffset = 0;
	ss_num = 1;

	for (i = 0; i < sizeof(mt76x0_txpwr_chlist); i++)
	{
		pAd->TxPower[i].Channel = mt76x0_txpwr_chlist[i];
		pAd->TxPower[i].Power = DEFAULT_RF_TX_POWER;	
	}


	/* 0. 11b/g, ch1 - ch 14, 1SS */
	ss_offset_g = EEPROM_G_TX_PWR_OFFSET;
	for (i = 0; i < 7; i++)
	{
		idx = i * 2;
		RT28xx_EEPROM_READ16(pAd, ss_offset_g + idx, Power.word);

		tx_pwr1 = tx_pwr2 = DEFAULT_RF_TX_POWER;

		if ((Power.field.Byte0 <= 0x3F) && (Power.field.Byte0 >= 0))
			tx_pwr1 = Power.field.Byte0;

		if ((Power.field.Byte1 <= 0x3F) || (Power.field.Byte1 >= 0))
			tx_pwr2 = Power.field.Byte1;

		pAd->TxPower[idx].Power = tx_pwr1;
		pAd->TxPower[idx + 1].Power = tx_pwr2;
		choffset++;
	}



	{
		/* 1. U-NII lower/middle band: 36, 38, 40; 44, 46, 48; 52, 54, 56; 60, 62, 64 (including central frequency in BW 40MHz)*/
		ASSERT((pAd->TxPower[choffset].Channel == 36));
		choffset = 14;
		ASSERT((pAd->TxPower[choffset].Channel == 36));
		for (i = 0; i < 6; i++)
		{
			idx = i * 2;
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TX_PWR_OFFSET + idx, Power.word);

			if ((Power.field.Byte0 <= 0x3F) && (Power.field.Byte0 >= 0))
				pAd->TxPower[idx + choffset + 0].Power = Power.field.Byte0;

			if ((Power.field.Byte1 <= 0x3F) && (Power.field.Byte1 >= 0))
				pAd->TxPower[idx + choffset + 1].Power = Power.field.Byte1;
		}


		/* 2. HipperLAN 2 100, 102 ,104; 108, 110, 112; 116, 118, 120; 124, 126, 128; 132, 134, 136; 140 (including central frequency in BW 40MHz)*/
		choffset = 14 + 12;
		ASSERT((pAd->TxPower[choffset].Channel == 100));
		for (i = 0; i < 8; i++)
		{

			idx = i * 2;
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TX_PWR_OFFSET + (choffset - 14) + idx, Power.word);
			
			if ((Power.field.Byte0 <= 0x3F) && (Power.field.Byte0 >= 0))
				pAd->TxPower[idx + choffset + 0].Power = Power.field.Byte0;

			if ((Power.field.Byte1 <= 0x3F) && (Power.field.Byte1 >= 0))
				pAd->TxPower[idx + choffset + 1].Power = Power.field.Byte1;
		}


		/* 3. U-NII upper band: 149, 151, 153; 157, 159, 161; 165, 167, 169; 171, 173 (including central frequency in BW 40MHz)*/
		choffset = 14 + 12 + 16;
		ASSERT((pAd->TxPower[choffset].Channel == 149));
		for (i = 0; i < 6; i++)
		{
			idx = i * 2;
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TX_PWR_OFFSET + (choffset - 14) + idx, Power.word);

			if ((Power.field.Byte0 <= 0x3F) && (Power.field.Byte0 >= 0))
				pAd->TxPower[idx + choffset + 0].Power = Power.field.Byte0;

			if ((Power.field.Byte1 <= 0x3F) && (Power.field.Byte1 >= 0))
				pAd->TxPower[idx + choffset + 1].Power = Power.field.Byte1;
		}

		/* choffset = 14 + 12 + 16 + 7; */
		choffset = 14 + 12 + 16 + 11;

#ifdef DOT11_VHT_AC
		ASSERT((pAd->TxPower[choffset].Channel == 42));

		/* For VHT80MHz, we need assign tx power for central channel 42, 58, 106, 122, and 155 */
		DBGPRINT(RT_DEBUG_TRACE, ("%s: Update Tx power control of the central channel (42, 58, 106, 122 and 155) for VHT BW80\n", __FUNCTION__));
		
		NdisMoveMemory(&pAd->TxPower[53], &pAd->TxPower[16], sizeof(CHANNEL_TX_POWER)); // channel 42 = channel 40
		NdisMoveMemory(&pAd->TxPower[54], &pAd->TxPower[22], sizeof(CHANNEL_TX_POWER)); // channel 58 = channel 56
		NdisMoveMemory(&pAd->TxPower[55], &pAd->TxPower[28], sizeof(CHANNEL_TX_POWER)); // channel 106 = channel 104
		NdisMoveMemory(&pAd->TxPower[56], &pAd->TxPower[34], sizeof(CHANNEL_TX_POWER)); // channel 122 = channel 120
		NdisMoveMemory(&pAd->TxPower[57], &pAd->TxPower[44], sizeof(CHANNEL_TX_POWER)); // channel 155 = channel 153

		pAd->TxPower[choffset].Channel = 42;
		pAd->TxPower[choffset+1].Channel = 58;
		pAd->TxPower[choffset+2].Channel = 106;
		pAd->TxPower[choffset+3].Channel = 122;
		pAd->TxPower[choffset+4].Channel = 155;
		
		choffset += 5;		/* the central channel of VHT80 */
		
		choffset = (MAX_NUM_OF_CHANNELS - 1);
#endif /* DOT11_VHT_AC */


		/* 4. Print and Debug*/
		for (i = 0; i < choffset; i++)
		{
			DBGPRINT(RT_DEBUG_TRACE, ("E2PROM: TxPower[%03d], Channel=%d, Power[Tx:%d]\n",
						i, pAd->TxPower[i].Channel, pAd->TxPower[i].Power));
		}
	}

	return TRUE;
}

VOID MT76x0_AsicExtraPowerOverMAC(
	IN PRTMP_ADAPTER pAd)
{
	UINT32 ExtraPwrOverMAC = 0;
	UINT32 ExtraPwrOverTxPwrCfg7 = 0, ExtraPwrOverTxPwrCfg8 = 0, ExtraPwrOverTxPwrCfg9 = 0;

	/* 
		For OFDM_54 and HT_MCS_7, extra fill the corresponding register value into MAC 0x13D4 
		bit 21:16 -> HT/VHT MCS 7
		bit 5:0 -> OFDM 54
	*/
	RTMP_IO_READ32(pAd, TX_PWR_CFG_1, &ExtraPwrOverMAC);  
	ExtraPwrOverTxPwrCfg7 |= (ExtraPwrOverMAC & 0x00003F00) >> 8; /* Get Tx power for OFDM 54 */
	RTMP_IO_READ32(pAd, TX_PWR_CFG_2, &ExtraPwrOverMAC);  
	ExtraPwrOverTxPwrCfg7 |= (ExtraPwrOverMAC & 0x00003F00) << 8; /* Get Tx power for HT MCS 7 */			
	RTMP_IO_WRITE32(pAd, TX_PWR_CFG_7, ExtraPwrOverTxPwrCfg7);

	/*  
		For HT_MCS_15, extra fill the corresponding register value into MAC 0x13D8 
		bit 29:24 -> VHT 1SS MCS 9
		bit 21:16 -> VHT 1SS MCS 8
		bit 5:0 -> HT MCS 15
	*/
	RTMP_IO_READ32(pAd, TX_PWR_CFG_3, &ExtraPwrOverMAC);  
#ifdef DOT11_VHT_AC
	ExtraPwrOverTxPwrCfg8 = pAd->Tx80MPwrCfgABand[0] | (ExtraPwrOverMAC & 0x0000FF00) >> 8; /* Get Tx power for HT MCS 15 */	
#else
	ExtraPwrOverTxPwrCfg8 |= (ExtraPwrOverMAC & 0x0000FF00) >> 8; /* Get Tx power for HT MCS 15 */
#endif /* DOT11_VHT_AC */
	RTMP_IO_WRITE32(pAd, TX_PWR_CFG_8, ExtraPwrOverTxPwrCfg8);

	/* 
		For STBC_MCS_7, extra fill the corresponding register value into MAC 0x13DC 
		bit 5:0 -> STBC MCS 7
	*/
	RTMP_IO_READ32(pAd, TX_PWR_CFG_4, &ExtraPwrOverMAC);  
	ExtraPwrOverTxPwrCfg9 |= (ExtraPwrOverMAC & 0x00003F00) >> 8; /* Get Tx power for STBC MCS 7 */
	RTMP_IO_WRITE32(pAd, TX_PWR_CFG_9, ExtraPwrOverTxPwrCfg9);

	DBGPRINT(RT_DEBUG_INFO, ("0x13D4 = 0x%08X, 0x13D8 = 0x%08X, 0x13D4 = 0x%08X\n", 
			(UINT)ExtraPwrOverTxPwrCfg7, (UINT)ExtraPwrOverTxPwrCfg8, (UINT)ExtraPwrOverTxPwrCfg9));	
}

static VOID calc_bw_delta_pwr(
	IN BOOLEAN is_dec_delta,
	IN USHORT input_pwr,
	IN USHORT bw_delta,
	INOUT CHAR *tx_pwr1,
	INOUT CHAR *tx_pwr2)
{
	CHAR tp_pwr1 = 0, tp_pwr2 = 0;
	
	if (is_dec_delta == FALSE) {
		if (input_pwr & 0x20) {
			tp_pwr1 = (input_pwr & 0x1F) + bw_delta;
			if (tp_pwr1 <= 0x1F)
				tp_pwr1 |= 0x20;
			else
				tp_pwr1 &= ~(0x20);
		} else {
			tp_pwr1 = (input_pwr & 0x1F) + bw_delta;
			if (tp_pwr1 > 0x1F)
				tp_pwr1 = 0x1F;
		}

		if (input_pwr & 0x2000) {
			tp_pwr2 = ((input_pwr & 0x1F00) >> 8) + bw_delta;
			if (tp_pwr2 <= 0x1F)
				tp_pwr2 |= 0x20;
			else
				tp_pwr2 &= ~(0x20);
		} else {
			tp_pwr2 = ((input_pwr & 0x1F00) >> 8) + bw_delta;
			if (tp_pwr2 > 0x1F)
				tp_pwr2 = 0x1F;
		}			
	} else {
		if (input_pwr & 0x20) {
			tp_pwr1 = (input_pwr & 0x1F) - bw_delta;
			tp_pwr1 |= 0x20;
			if (tp_pwr1 > 0x3F)
				tp_pwr1 = 0x3F;
		} else {
			tp_pwr1 = (input_pwr & 0x1F) - bw_delta;
			if (tp_pwr1 < 0)
				tp_pwr1 &= 0x3F;
		}

		if (input_pwr & 0x2000) {
			tp_pwr2 = ((input_pwr & 0x1F00) >> 8) - bw_delta;
			tp_pwr2 |= 0x20;
			if (tp_pwr2 > 0x3F)
				tp_pwr2 = 0x3F;
		} else {
			tp_pwr2 = ((input_pwr & 0x1F00) >> 8) - bw_delta;
			if (tp_pwr2 < 0)
				tp_pwr2 &= 0x3F;
		}			
	}
	
	*tx_pwr1 = tp_pwr1;
	*tx_pwr2 = tp_pwr2;
}

#define EEPROM_TXPOWER_BYRATE_STBC	(0xEC)
#define EEPROM_TXPOWER_BYRATE_5G	(0x120)
//
// VHT BW80 delta power control (+4~-4dBm) for per-rate Tx power control
//
#define EEPROM_VHT_BW80_TX_POWER_DELTA	(0xD3)

//
// Read per-rate Tx power
//
VOID mt76x0_read_per_rate_tx_pwr(
	IN PRTMP_ADAPTER pAd)
{
	UINT32 data;
	USHORT e2p_val = 0, e2p_val2 = 0;;
	UCHAR bw40_gband_delta = 0, bw40_aband_delta = 0, bw80_aband_delta = 0;
	CHAR t1 = 0, t2 = 0, t3 = 0, t4 = 0;
	BOOLEAN dec_aband_bw40_delta = FALSE, dec_aband_bw80_delta = FALSE, dec_gband_bw40_delta = FALSE;

    	DBGPRINT(RT_DEBUG_TRACE, ("%s() -->\n", __FUNCTION__));
	
	/*
		Get power delta for BW40
		bit 5:0 -> 40M BW TX power delta value (MAX=4dBm)
		bit 6 -> 	1: increase 40M BW TX power with the delta value
			     	0: decrease 40M BW TX power with the delta value
		bit 7 -> 	enableTX power compensation
	*/
	RT28xx_EEPROM_READ16(pAd, EEPROM_TXPOWER_DELTA, e2p_val);
	pAd->chipCap.delta_tw_pwr_bw40_2G = (e2p_val & 0xFF) == 0xFF ? 0 : (e2p_val & 0xFF);
	pAd->chipCap.delta_tw_pwr_bw40_5G = (e2p_val & 0xFF00) == 0xFF00 ? 0 : ((e2p_val >> 8) & 0xFF);

	if ((e2p_val & 0xFF) != 0xFF) {
		if (e2p_val & 0x80)
			bw40_gband_delta = (e2p_val & 0x1F);

		if (e2p_val & 0x40)
			dec_gband_bw40_delta = FALSE;
		else
			dec_gband_bw40_delta = TRUE;
	}

	if ((e2p_val & 0xFF00) != 0xFF00) {
		if (e2p_val & 0x8000)
			bw40_aband_delta = ((e2p_val & 0x1F00) >> 8);

		if (e2p_val & 0x4000)
			dec_aband_bw40_delta = FALSE;
		else
			dec_aband_bw40_delta = TRUE;
	}
	
	/*
		Get power delta for BW80
	*/
	// TODO: check if any document to describe this ?
	RT28xx_EEPROM_READ16(pAd, EEPROM_VHT_BW80_TX_POWER_DELTA - 1, e2p_val);
	pAd->chipCap.delta_tw_pwr_bw80 = (e2p_val & 0xFF00) == 0xFF00 ? 0 : (e2p_val & 0xFF00);

	if ((e2p_val & 0xFF00) != 0xFF00) {
		if (e2p_val & 0x8000)
			bw80_aband_delta = ((e2p_val & 0x1F00) >> 8);
	
		if (e2p_val & 0x4000)
			dec_aband_bw80_delta = FALSE;
		else
			dec_aband_bw80_delta = TRUE;
	}

#ifdef SINGLE_SKU_V2
	/*
		We don't need to update bw delta for per rate when SingleSKU is enabled
	*/
	dec_aband_bw40_delta = FALSE;
	dec_aband_bw80_delta = FALSE;
	dec_gband_bw40_delta = FALSE;
	bw40_aband_delta = 0;
	bw80_aband_delta = 0;
	bw40_gband_delta = 0;
#endif /* SINGLE_SKU_V2 */

	DBGPRINT(RT_DEBUG_TRACE, ("%s: dec_gband_bw40_delta = %d, bw40_gband_delta = %d\n", 
		__FUNCTION__, dec_gband_bw40_delta, bw40_gband_delta));	
	DBGPRINT(RT_DEBUG_TRACE, ("%s: dec_aband_bw40_delta = %d, bw40_aband_delta = %d\n", 
		__FUNCTION__, dec_aband_bw40_delta, bw40_aband_delta));
	DBGPRINT(RT_DEBUG_TRACE, ("%s: dec_aband_bw80_delta = %d, bw80_aband_delta = %d\n", 
		__FUNCTION__, dec_aband_bw80_delta, bw80_aband_delta));

	RT28xx_EEPROM_READ16(pAd, 0xDE, e2p_val);
	calc_bw_delta_pwr(dec_gband_bw40_delta, e2p_val, bw40_gband_delta, &t1, &t2);
	RT28xx_EEPROM_READ16(pAd, 0xE0, e2p_val2);
	calc_bw_delta_pwr(dec_gband_bw40_delta, e2p_val2, bw40_gband_delta, &t3, &t4);
	/* 
		bit 29:24 -> OFDM 12M/18M
		bit 21:16 -> OFDM 6M/9M
		bit 13:8 -> CCK 5.5M/11M
		bit 5:0 -> CCK 1M/2M
	*/
	data = (e2p_val2 << 16) | e2p_val;
	pAd->Tx20MPwrCfgGBand[0] = data;
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx20MPwrCfgGBand[0](0x1314) = 0x%08X\n", __FUNCTION__, data));
	data = (t4 << 24) | (t3 << 16) | (t2 << 8) | t1; 
	pAd->Tx40MPwrCfgGBand[0] = data;
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx40MPwrCfgGBand[0](0x1314) = 0x%08X\n", __FUNCTION__, data));

	RT28xx_EEPROM_READ16(pAd, 0xE2, e2p_val);
	calc_bw_delta_pwr(dec_gband_bw40_delta, e2p_val, bw40_gband_delta, &t1, &t2);
	RT28xx_EEPROM_READ16(pAd, 0xE4, e2p_val2);
	calc_bw_delta_pwr(dec_gband_bw40_delta, e2p_val2, bw40_gband_delta, &t3, &t4);
	/* 
		bit 29:24 -> HT MCS=2,3, VHT 1SS MCS=2,3
		bit 21:16 -> HT MCS=0,1, VHT 1SS MCS=0,1
		bit 13:8 -> OFDM 48M
		bit 5:0 -> OFDM 24M/36M
	*/
	data = (e2p_val2 << 16) | e2p_val;
	pAd->Tx20MPwrCfgGBand[1] = data;
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx20MPwrCfgGBand[1](0x1318) = 0x%08X\n", __FUNCTION__, data));
	data = (t4 << 24) | (t3 << 16) | (t2 << 8) | t1; 
	pAd->Tx40MPwrCfgGBand[1] = data; 
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx40MPwrCfgGBand[1](0x1318) = 0x%08X\n", __FUNCTION__, data));

	RT28xx_EEPROM_READ16(pAd, 0xE6, e2p_val);
	calc_bw_delta_pwr(dec_gband_bw40_delta, e2p_val, bw40_gband_delta, &t1, &t2);
	RT28xx_EEPROM_READ16(pAd, 0xE8, e2p_val2);
	calc_bw_delta_pwr(dec_gband_bw40_delta, e2p_val2, bw40_gband_delta, &t3, &t4);
	/*
		bit 29:24 -> HT MCS=10,11 (no need)
		bit 21:16 -> HT MCS=8,9 (no need)
		bit 13:8 -> HT MCS=6, VHT 1SS MCS=6
		bit 5:0 -> MCS=4,5, VHT 1SS MCS=4,5
	*/
	data = (e2p_val2 << 16) | e2p_val;
	pAd->Tx20MPwrCfgGBand[2] = data;
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx20MPwrCfgGBand[2](0x131C) = 0x%08X\n", __FUNCTION__, data));
	data = (t4 << 24) | (t3 << 16) | (t2 << 8) | t1; 
	pAd->Tx40MPwrCfgGBand[2] = data; 
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx40MPwrCfgGBand[2](0x131C) = 0x%08X\n", __FUNCTION__, data));

	RT28xx_EEPROM_READ16(pAd, 0xEA, e2p_val);
	calc_bw_delta_pwr(dec_gband_bw40_delta, e2p_val, bw40_gband_delta, &t1, &t2);
	RT28xx_EEPROM_READ16(pAd, 0xEC, e2p_val2);
	calc_bw_delta_pwr(dec_gband_bw40_delta, e2p_val2, bw40_gband_delta, &t3, &t4);
	/* 
		bit 29:24 -> HT/VHT STBC MCS=2, 3
		bit 21:16 -> HT/VHT STBC MCS=0, 1
		bit 13:8 -> HT MCS=14 (no need)
		bit 5:0 -> HT MCS=12,13 (no need)
	*/
	data = (e2p_val2 << 16) | e2p_val;
	pAd->Tx20MPwrCfgGBand[3] = data;
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx20MPwrCfgGBand[3](0x1320) = 0x%08X\n", __FUNCTION__, data));
	data = (t4 << 24) | (t3 << 16) | (t2 << 8) | t1; 
	pAd->Tx40MPwrCfgGBand[3] = data; 
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx40MPwrCfgGBand[3](0x1320) = 0x%08X\n", __FUNCTION__, data));

	RT28xx_EEPROM_READ16(pAd, 0xEE, e2p_val);
	calc_bw_delta_pwr(dec_gband_bw40_delta, e2p_val, bw40_gband_delta, &t1, &t2);
	/* 
		bit 13:8 -> HT/VHT STBC MCS=6
		bit 5:0 -> HT/VHT STBC MCS=4,5
	*/
	data = e2p_val;
	pAd->Tx20MPwrCfgGBand[4] = data;
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx20MPwrCfgGBand[4](0x1324) = 0x%08X\n", __FUNCTION__, data));
	data = (t2 << 8) | t1;
	pAd->Tx40MPwrCfgGBand[4] = data; 			
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx40MPwrCfgGBand[4](0x1324) = 0x%08X\n", __FUNCTION__, data));
	

	RT28xx_EEPROM_READ16(pAd, 0x120, e2p_val);
	calc_bw_delta_pwr(dec_aband_bw40_delta, e2p_val, bw40_aband_delta, &t3, &t4);
	/* 
		bit 29:24 -> OFDM 12M/18M
		bit 21:16 -> OFDM 6M/9M
	*/
	data = e2p_val;
	data = data << 16;
	pAd->Tx20MPwrCfgABand[0] = data;
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx20MPwrCfgABand[0](0x1314) = 0x%08X\n", __FUNCTION__, data));
	data = (t4 << 24) | (t3 << 16); 
	pAd->Tx40MPwrCfgABand[0] = data;
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx40MPwrCfgABand[0](0x1314) = 0x%08X\n", __FUNCTION__, data));	

	RT28xx_EEPROM_READ16(pAd, 0x122, e2p_val);
	calc_bw_delta_pwr(dec_aband_bw40_delta, e2p_val, bw40_aband_delta, &t1, &t2);
	RT28xx_EEPROM_READ16(pAd, 0x124, e2p_val2);
	calc_bw_delta_pwr(dec_aband_bw40_delta, e2p_val2, bw40_aband_delta, &t3, &t4);
	/* 
		bit 29:24 -> HT MCS=2,3, VHT 1SS MCS=2,3
		bit 21:16 -> HT MCS=0,1, VHT 1SS MCS=0,1
		bit 13:8 -> OFDM 48M
		bit 5:0 -> OFDM 24M/36M
	*/
	data = (e2p_val2 << 16) | e2p_val;
	pAd->Tx20MPwrCfgABand[1] = data;
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx20MPwrCfgABand[1](0x1318) = 0x%08X\n", __FUNCTION__, data));
	data = (t4 << 24) | (t3 << 16) | (t2 << 8) | t1; 
	pAd->Tx40MPwrCfgABand[1] = data;			
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx40MPwrCfgABand[1](0x1318) = 0x%08X\n", __FUNCTION__, data));

	RT28xx_EEPROM_READ16(pAd, 0x126, e2p_val);
	calc_bw_delta_pwr(dec_aband_bw40_delta, e2p_val, bw40_aband_delta, &t1, &t2);
	/*
		bit 13:8 -> HT MCS=6, VHT 1SS MCS=6
		bit 5:0 -> MCS=4,5, VHT 1SS MCS=4,5
	*/
	data = e2p_val;
	pAd->Tx20MPwrCfgABand[2] = data;
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx20MPwrCfgABand[2](0x131C) = 0x%08X\n", __FUNCTION__, data));
	data = (t2 << 8) | t1; 
	pAd->Tx40MPwrCfgABand[2] = data;
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx40MPwrCfgABand[2](0x131C) = 0x%08X\n", __FUNCTION__, data));

	RT28xx_EEPROM_READ16(pAd, 0xEC, e2p_val);
	calc_bw_delta_pwr(dec_aband_bw40_delta, e2p_val, bw40_aband_delta, &t3, &t4);
	/* 
		bit 29:24 -> HT/VHT STBC MCS=2, 3
		bit 21:16 -> HT/VHT STBC MCS=0, 1
	*/
	data = e2p_val;
	data = data << 16;
	pAd->Tx20MPwrCfgABand[3] = data;
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx20MPwrCfgABand[3](0x1320) = 0x%08X\n", __FUNCTION__, data));
	data = (t4 << 24) | (t3 << 16); 
	pAd->Tx40MPwrCfgABand[3] = data;
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx40MPwrCfgABand[3](0x1320) = 0x%08X\n", __FUNCTION__, data));

	RT28xx_EEPROM_READ16(pAd, 0xEE, e2p_val);
	calc_bw_delta_pwr(dec_aband_bw40_delta, e2p_val, bw40_aband_delta, &t1, &t2);
	/* 
		bit 13:8 -> HT/VHT STBC MCS=6
		bit 5:0 -> HT/VHT STBC MCS=4,5
	*/
	data = e2p_val;
	pAd->Tx20MPwrCfgABand[4] = data;	
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx20MPwrCfgABand[4](0x1324) = 0x%08X\n", __FUNCTION__, data));
	data = (t2 << 8) | t1;
	pAd->Tx40MPwrCfgABand[4] = data;	
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx40MPwrCfgABand[4](0x1324) = 0x%08X\n", __FUNCTION__, data));
	
	RT28xx_EEPROM_READ16(pAd, 0x12C, e2p_val);
	calc_bw_delta_pwr(dec_aband_bw80_delta, e2p_val, bw80_aband_delta, &t3, &t4);
	/* 
		bit 29:24 -> VHT 1SS MCS=9
		bit 21:16 -> VHT 1SS MCS=8
	*/
	data = (t3 << 24) | (t3 << 16); 
	pAd->Tx80MPwrCfgABand[0] = data;			
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("%s: Tx80MPwrCfgABand[0](0x13D8) = 0x%08X\n", __FUNCTION__, data));

#ifdef MT76x0_TSSI_CAL_COMPENSATION
	MT76x0_MakeUpTssiTable(pAd);
#endif /* MT76x0_TSSI_CAL_COMPENSATION */

    	DBGPRINT(RT_DEBUG_TRACE, ("%s: <--\n", __FUNCTION__));
}


static VOID MT76x0_AsicGetTxPowerOffset(
	IN PRTMP_ADAPTER pAd,
	INOUT PULONG pTxPwr)
{
	CONFIGURATION_OF_TX_POWER_CONTROL_OVER_MAC CfgOfTxPwrCtrlOverMAC;
	DBGPRINT(RT_DEBUG_INFO, ("-->MT76x0_AsicGetTxPowerOffset\n"));

	NdisZeroMemory(&CfgOfTxPwrCtrlOverMAC, sizeof(CfgOfTxPwrCtrlOverMAC));

	CfgOfTxPwrCtrlOverMAC.NumOfEntries = 5; /* MAC 0x1314, 0x1318, 0x131C, 0x1320 and 1324 */
	CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].MACRegisterOffset = TX_PWR_CFG_0;
	CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].MACRegisterOffset = TX_PWR_CFG_1;
	CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].MACRegisterOffset = TX_PWR_CFG_2;
	CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].MACRegisterOffset = TX_PWR_CFG_3;
	CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].MACRegisterOffset = TX_PWR_CFG_4;
	
	if (pAd->CommonCfg.BBPCurrentBW == BW_20) {
		if (pAd->CommonCfg.CentralChannel > 14) {
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].RegisterValue = pAd->Tx20MPwrCfgABand[0];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].RegisterValue = pAd->Tx20MPwrCfgABand[1];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].RegisterValue = pAd->Tx20MPwrCfgABand[2];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].RegisterValue = pAd->Tx20MPwrCfgABand[3];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].RegisterValue = pAd->Tx20MPwrCfgABand[4];
		} else {
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].RegisterValue = pAd->Tx20MPwrCfgGBand[0];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].RegisterValue = pAd->Tx20MPwrCfgGBand[1];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].RegisterValue = pAd->Tx20MPwrCfgGBand[2];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].RegisterValue = pAd->Tx20MPwrCfgGBand[3];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].RegisterValue = pAd->Tx20MPwrCfgGBand[4];
		}
	} else {
		if (pAd->CommonCfg.CentralChannel > 14) {
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].RegisterValue = pAd->Tx40MPwrCfgABand[0];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].RegisterValue = pAd->Tx40MPwrCfgABand[1];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].RegisterValue = pAd->Tx40MPwrCfgABand[2];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].RegisterValue = pAd->Tx40MPwrCfgABand[3];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].RegisterValue = pAd->Tx40MPwrCfgABand[4];
		} else {
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].RegisterValue = pAd->Tx40MPwrCfgGBand[0];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].RegisterValue = pAd->Tx40MPwrCfgGBand[1];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].RegisterValue = pAd->Tx40MPwrCfgGBand[2];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].RegisterValue = pAd->Tx40MPwrCfgGBand[3];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].RegisterValue = pAd->Tx40MPwrCfgGBand[4];
		}
	}
	
	NdisCopyMemory(pTxPwr, (UCHAR *)&CfgOfTxPwrCtrlOverMAC, sizeof(CfgOfTxPwrCtrlOverMAC));
	DBGPRINT(RT_DEBUG_INFO, ("<--MT76x0_AsicGetTxPowerOffset\n"));
}

/*
========================================================================
Routine Description:
	Initialize MT76x0

Arguments:
	pAd					- WLAN control block pointer

Return Value:
	None

Note:
========================================================================
*/
VOID MT76x0_Init(RTMP_ADAPTER *pAd)
{
	RTMP_CHIP_OP *pChipOps = &pAd->chipOps;
	RTMP_CHIP_CAP *pChipCap = &pAd->chipCap;
	UINT32 Value;

	DBGPRINT(RT_DEBUG_TRACE, ("-->%s():\n", __FUNCTION__));
		
	/* 
		Init chip capabilities
	*/
	RTMP_IO_READ32(pAd, 0x00, &Value);	
	pChipCap->ChipID = Value;

	pChipCap->MaxNss = 1;
	pChipCap->TXWISize = 20;
	pChipCap->RXWISize = 28;
	
	pChipCap->SnrFormula = SNR_FORMULA2;
	pChipCap->FlgIsHwWapiSup = TRUE;
	pChipCap->VcoPeriod = 10;
	pChipCap->FlgIsVcoReCalMode = VCO_CAL_MODE_3;
	pChipCap->FlgIsHwAntennaDiversitySup = FALSE;
#ifdef STREAM_MODE_SUPPORT
	pChipCap->FlgHwStreamMode = FALSE;
#endif /* STREAM_MODE_SUPPORT */
#ifdef TXBF_SUPPORT
	pChipCap->FlgHwTxBfCap = FALSE;
#endif /* TXBF_SUPPORT */
#ifdef FIFO_EXT_SUPPORT
	pChipCap->FlgHwFifoExtCap = TRUE;
#endif /* FIFO_EXT_SUPPORT */


	pChipCap->asic_caps |= (fASIC_CAP_PMF_ENC);

	pChipCap->phy_caps = (fPHY_CAP_24G | fPHY_CAP_5G);
	pChipCap->phy_caps |= (fPHY_CAP_HT | fPHY_CAP_VHT);

	pChipCap->RfReg17WtMethod = RF_REG_WT_METHOD_STEP_ON;
		
	pChipCap->MaxNumOfRfId = MAX_RF_ID;
	pChipCap->pRFRegTable = NULL;

	pChipCap->MaxNumOfBbpId = 200;	
	pChipCap->pBBPRegTable = NULL;
	pChipCap->bbpRegTbSize = 0;

#ifdef DFS_SUPPORT
	pChipCap->DfsEngineNum = 4;
#endif /* DFS_SUPPORT */

#ifdef NEW_MBSSID_MODE
#ifdef ENHANCE_NEW_MBSSID_MODE
	pChipCap->MBSSIDMode = MBSSID_MODE4;
#else
	pChipCap->MBSSIDMode = MBSSID_MODE1;
#endif /* ENHANCE_NEW_MBSSID_MODE */
#else
	pChipCap->MBSSIDMode = MBSSID_MODE0;
#endif /* NEW_MBSSID_MODE */


#ifdef CONFIG_STA_SUPPORT
	pChipCap->init_vga_gain_5G = 0x54; 
	pChipCap->init_vga_gain_2G = 0x4E;
#endif /* CONFIG_STA_SUPPORT */

#ifdef RTMP_EFUSE_SUPPORT
	pChipCap->EFUSE_USAGE_MAP_START = 0x1e0;
	pChipCap->EFUSE_USAGE_MAP_END = 0x1FC;      
	pChipCap->EFUSE_USAGE_MAP_SIZE = 29;
#endif /* RTMP_EFUSE_SUPPORT */

#ifdef CONFIG_ANDES_SUPPORT
	pChipCap->WlanMemmapOffset = 0x410000;
	pChipCap->InbandPacketMaxLen = 192;
	pChipCap->CmdRspRxRing = RX_RING1;
	if (IS_MT7610(pAd))
		pChipCap->IsComboChip = FALSE;
	else
		pChipCap->IsComboChip = TRUE;
	
	pChipCap->load_iv = TRUE;
	pChipCap->ilm_offset = 0x00000;
	pChipCap->dlm_offset = 0x80000;
#endif /* CONFIG_ANDES_SUPPORT */

	pChipCap->MCUType = ANDES;
	pChipCap->cmd_header_len = sizeof(TXINFO_NMAC_CMD);


#ifdef RTMP_USB_SUPPORT
	pChipCap->cmd_padding_len = 4;
	pChipCap->CommandBulkOutAddr = 0x8;
	pChipCap->WMM0ACBulkOutAddr[0] = 0x4;
	pChipCap->WMM0ACBulkOutAddr[1] = 0x5;
	pChipCap->WMM0ACBulkOutAddr[2] = 0x6;
	pChipCap->WMM0ACBulkOutAddr[3] = 0x7;
	pChipCap->WMM1ACBulkOutAddr	= 0x9;
	pChipCap->DataBulkInAddr = 0x84;
	pChipCap->CommandRspBulkInAddr = 0x85;	 
#endif /* RTMP_USB_SUPPORT */

#ifdef MT7650
	if (IS_MT7650(pAd))
		pChipCap->FWImageName = MT7650_FirmwareImage;
#endif

#ifdef MT7630
	if (IS_MT7630(pAd))
		pChipCap->FWImageName = MT7650_FirmwareImage;
#endif

#ifdef MT7610
	if (IS_MT7610(pAd))
		pChipCap->FWImageName = MT7610_FirmwareImage;
#endif

	pChipCap->bDoTemperatureSensor = TRUE;

	pChipCap->MACRegisterVer = "MT7650_CR_setting_1225.xlsx";
	pChipCap->BBPRegisterVer = "MT7650E3_BBP_CR_20121206.xls";
	pChipCap->RFRegisterVer = "MT7650E3_WiFi_RF_CR_20121202.xls";

	RTMP_DRS_ALG_INIT(pAd, RATE_ALG_GRP);
		
	/*
		Following function configure beacon related parameters
		in pChipCap
			FlgIsSupSpecBcnBuf / BcnMaxHwNum / 
			WcidHwRsvNum / BcnMaxHwSize / BcnBase[]
	*/
	rlt_bcn_buf_init(pAd);

	/*
		init operator
	*/

	/* BBP adjust */
	pChipOps->ChipBBPAdjust = MT76x0_ChipBBPAdjust;
	
#ifdef CONFIG_STA_SUPPORT
	pChipOps->ChipAGCAdjust = NULL;
#endif /* CONFIG_STA_SUPPORT */

	/* Channel */
	pChipOps->ChipSwitchChannel = MT76x0_ChipSwitchChannel;
	pChipOps->ChipAGCInit = NULL;

	pChipOps->AsicMacInit = NICInitMT76x0MacRegisters;
	pChipOps->AsicBbpInit = NICInitMT76x0BbpRegisters;
	pChipOps->AsicRfInit = NICInitMT76x0RFRegisters;
	pChipOps->AsicRfTurnOn = NULL;

	pChipOps->AsicHaltAction = NULL;
	pChipOps->AsicRfTurnOff = NULL;
	pChipOps->AsicReverseRfFromSleepMode = NULL;
	pChipOps->AsicResetBbpAgent = NULL;
	
	/* MAC */

	/* EEPROM */
	pChipOps->NICInitAsicFromEEPROM = MT76x0_NICInitAsicFromEEPROM;
	
	/* Antenna */
	pChipOps->AsicAntennaDefaultReset = MT76x0_AsicAntennaDefaultReset;

	/* TX ALC */
	pChipOps->InitDesiredTSSITable = NULL;
 	pChipOps->ATETssiCalibration = NULL;
	pChipOps->ATETssiCalibrationExtend = NULL;
	pChipOps->AsicTxAlcGetAutoAgcOffset = NULL;
	pChipOps->ATEReadExternalTSSI = NULL;
	pChipOps->TSSIRatio = NULL;
	
	/* Others */
#ifdef CONFIG_STA_SUPPORT
	pChipOps->NetDevNickNameInit = MT76x0_NetDevNickNameInit;
#endif /* CONFIG_STA_SUPPORT */
#ifdef CARRIER_DETECTION_SUPPORT
	pAd->chipCap.carrier_func = TONE_RADAR_V3;
	pChipOps->ToneRadarProgram = ToneRadarProgram_v3;
#endif /* CARRIER_DETECTION_SUPPORT */

	/* Chip tuning */
	pChipOps->RxSensitivityTuning = NULL;
	pChipOps->AsicTxAlcGetAutoAgcOffset = NULL;
	pChipOps->AsicGetTxPowerOffset = MT76x0_AsicGetTxPowerOffset;
	pChipOps->AsicExtraPowerOverMAC = MT76x0_AsicExtraPowerOverMAC;

/* 
	Following callback functions already initiailized in RtmpChipOpsHook() 
	1. Power save related
*/

	pChipOps->DisableTxRx = RT65xxDisableTxRx;

#ifdef RTMP_USB_SUPPORT
	pChipOps->AsicRadioOn = RT65xxUsbAsicRadioOn;
	pChipOps->AsicRadioOff = RT65xxUsbAsicRadioOff;
	pChipOps->usb_cfg_read = usb_cfg_read_v1;
	pChipOps->usb_cfg_write = usb_cfg_write_v1;
#endif /* RTMP_USB_SUPPORT */

	
#ifdef HDR_TRANS_SUPPORT
	if (1) {
		/* enable TX/RX Header Translation */
		RTMP_IO_WRITE32(pAd, HT_RX_WCID_EN_BASE , 0xFF);	/* all RX WCID enable */

		/* black list - skip EAP-888e/DLS-890d */
		RTMP_IO_WRITE32(pAd, HT_RX_BL_BASE, 0x888e890d);
		//RTMP_IO_WRITE32(pAd, HT_RX_BL_BASE, 0x08000806);

		/* tsc conrotl */
/*
		RTMP_IO_READ32(pAd, 0x250, &RegVal);
		RegVal |= 0x6000;
		RTMP_IO_WRITE32(pAd, 0x250, RegVal);
*/
	}	
#endif /* HDR_TRANS_SUPPORT */

#ifdef CONFIG_WIFI_TEST
	pChipCap->MemMapStart = 0x1000;
	pChipCap->MemMapEnd = 0x1600;
	pChipCap->MacMemMapOffset = 0x1000;
	pChipCap->MacStart = 0x0000;
	pChipCap->MacEnd = 0x0600;
	pChipCap->BBPMemMapOffset = 0x2000;
	pChipCap->BBPStart = 0x0000;
	pChipCap->BBPEnd = 0x0f00;
	pChipCap->RFBankNum = sizeof(MT76x0_RFBankOffset) / sizeof(struct RF_BANK_OFFSET);
	pChipCap->RFBankOffset = MT76x0_RFBankOffset;
	pChipCap->E2PStart = 0x0000;
	pChipCap->E2PEnd = 0x00fe;
#endif /* CONFIG_WIFI_TEST */
}


VOID MT76x0_AntennaSelCtrl(
	IN RTMP_ADAPTER *pAd)
{
	USHORT e2p_val = 0;
	UINT32 WlanFunCtrl = 0, CmbCtrl = 0, CoexCfg0 = 0, CoexCfg3 = 0;
	UINT32 ret;


#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_WAIT(&pAd->wlan_en_atomic, ret);
		if (ret != 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("wlan_en_atomic get failed(ret=%d)\n", ret));
			return;
		}
	}
#endif /* RTMP_MAC_USB */

	RTMP_IO_READ32(pAd, WLAN_FUN_CTRL, &WlanFunCtrl);
	RTMP_IO_READ32(pAd, CMB_CTRL, &CmbCtrl);
	RTMP_IO_READ32(pAd, COEXCFG0, &CoexCfg0);
	RTMP_IO_READ32(pAd, COEXCFG3, &CoexCfg3);

	CoexCfg0 &= ~BIT2;
	CmbCtrl &= ~(BIT14 | BIT12);
	WlanFunCtrl &= ~(BIT6 | BIT5);
	CoexCfg3 &= ~(BIT5 | BIT4 | BIT3 | BIT2 | BIT1);
	
	/*
		0x23[7]
		0x1: Chip is in dual antenna mode
		0x0: Chip is in single antenna mode
	*/
	RT28xx_EEPROM_READ16(pAd, 0x22, e2p_val);
		
	if (e2p_val & 0x8000)
	{
		if ((pAd->NicConfig2.field.AntOpt == 0) 
			&& (pAd->NicConfig2.field.AntDiversity == 1))
		{
			CmbCtrl |= BIT12; /* 0x20[12]=1 */
		}
		else
		{
			CoexCfg3 |= BIT4; /* 0x4C[4]=1 */
		}
		CoexCfg3 |= BIT3; /* 0x4C[3]=1 */
		
		if (WMODE_CAP_2G(pAd->CommonCfg.PhyMode))
		{
			WlanFunCtrl |= BIT6; /* 0x80[6]=1 */
		}
		DBGPRINT(RT_DEBUG_TRACE, ("%s - Dual antenna mode\n", __FUNCTION__));
	}
	else
	{
		if (WMODE_CAP_5G(pAd->CommonCfg.PhyMode))
		{
			CoexCfg3 |= (BIT3 | BIT4); /* 0x4C[3]=1, 0x4C[4]=1 */
		}
		else
		{
			WlanFunCtrl |= BIT6; /* 0x80[6]=1 */
			CoexCfg3 |= BIT1; /* 0x4C[1]=1 */
		}
		DBGPRINT(RT_DEBUG_TRACE, ("%s - Single antenna mode\n", __FUNCTION__));
	}

	RTMP_IO_WRITE32(pAd, WLAN_FUN_CTRL, WlanFunCtrl);
	RTMP_IO_WRITE32(pAd, CMB_CTRL, CmbCtrl);
	RTMP_IO_WRITE32(pAd, COEXCFG0, CoexCfg0);
	RTMP_IO_WRITE32(pAd, COEXCFG3, CoexCfg3);

#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_UP(&pAd->wlan_en_atomic);
	}
#endif /* RTMP_MAC_USB */

}

VOID MT76x0_dynamic_vga_tuning(
	IN RTMP_ADAPTER 	*pAd)
{


	RTMP_CHIP_CAP *pChipCap = &pAd->chipCap;
	UINT32 reg_val = 0, init_vga = 0, rssi = 0;

	rssi = pAd->StaCfg.RssiSample.AvgRssi0 - pAd->BbpRssiToDbmDelta;

	if (pAd->CommonCfg.CentralChannel > 14)
		init_vga = pChipCap->init_vga_gain_5G;
	else
		init_vga = pChipCap->init_vga_gain_2G;

	if (rssi > -60)
		init_vga -= 0x20;
	else if ((rssi <= -60) && (rssi > -70))
		init_vga -= 0x10;

	RTMP_IO_READ32(pAd, AGC1_R8, &reg_val);
	reg_val &= 0xFFFF80FF;
	reg_val |= (init_vga << 8);
	RTMP_IO_WRITE32(pAd, AGC1_R8, reg_val);

	DBGPRINT(RT_DEBUG_TRACE, ("%s(): RSSI=%d, BBP 2320=0x%x\n", __FUNCTION__, rssi, reg_val));
}

VOID MT76x0_VCO_CalibrationMode3(
	IN RTMP_ADAPTER 	*pAd,
	IN UCHAR 			Channel)
{
	/*
		VCO_Calibration_MT7650E2.docx:
		2.	Calibration Procedure:
			i.	Set the configuration (examples in section 12)
			ii.	Set B0.R04.[7] vcocal_en to "high" (1.2V).  After completing the calibration procedure, it would return to "low" automatically.
	*/

	UCHAR RFValue = 0, Mode = 0;

	rlt_rf_read(pAd, RF_BANK0, RF_R04, &RFValue);
	Mode = (RFValue & 0x70);	
	if (Mode == 0x30)
	{
		DBGPRINT(RT_DEBUG_TRACE, ("%s - Calibration Mode: Open loop, closed loop, and amplitude @ ch%d\n", 
						__FUNCTION__, Channel));
		/*
			Calibration Mode - Open loop, closed loop, and amplitude:
			B0.R06.[0]: 1
			B0.R06.[3:1] bp_close_code: 100
			B0.R05.[7:0] bp_open_code: 0x0
			B0.R04.[2:0] cal_bits: 000
			B0.R03.[2:0] startup_time: 011
			B0.R03.[6:4] settle_time: 
						80MHz channel: 110
						40MHz channel: 101
						20MHz channel: 100
		*/
		rlt_rf_read(pAd, RF_BANK0, RF_R06, &RFValue);
		RFValue &= ~(0x0F);
		RFValue |= 0x09;
		rlt_rf_write(pAd, RF_BANK0, RF_R06, RFValue);

		rlt_rf_read(pAd, RF_BANK0, RF_R05, &RFValue);
		if (RFValue != 0)
			rlt_rf_write(pAd, RF_BANK0, RF_R05, 0x0);

		rlt_rf_read(pAd, RF_BANK0, RF_R04, &RFValue);
		RFValue &= ~(0x07);
		rlt_rf_write(pAd, RF_BANK0, RF_R04, RFValue);

		rlt_rf_read(pAd, RF_BANK0, RF_R03, &RFValue);
		RFValue &= ~(0x77);
		if ((Channel == 1) || (Channel == 7) || (Channel == 9) || (Channel >= 13))
			RFValue |= 0x63;
		else if ((Channel == 3) || (Channel == 4) || (Channel == 10))
			RFValue |= 0x53;
		else if ((Channel == 2) || (Channel == 5) || (Channel == 6) || (Channel == 8) || (Channel == 11) || (Channel == 12))
			RFValue |= 0x43;
		else {
			DBGPRINT(RT_DEBUG_OFF, ("%s - wrong input channel\n", __FUNCTION__));
			return;
		}
		rlt_rf_write(pAd, RF_BANK0, RF_R03, RFValue);

		rlt_rf_read(pAd, RF_BANK0, RF_R04, &RFValue);
		RFValue = ((RFValue & ~(0x80)) | 0x80); 
		rlt_rf_write(pAd, RF_BANK0, RF_R04, RFValue);

		RTMPusecDelay(2200);
	}

	return;
}

VOID MT76x0_Calibration(
	IN RTMP_ADAPTER *pAd,
	IN UCHAR Channel,
	IN BOOLEAN bPowerOn,
	IN BOOLEAN bDoTSSI,
	IN BOOLEAN bFullCal)
{
	UINT32 MacReg = 0, reg_val = 0, reg_tx_alc = 0;
#ifdef RTMP_MAC_USB
	UINT32 ret;
#endif /* RTMP_MAC_USB */

	DBGPRINT(RT_DEBUG_TRACE, ("%s - Channel = %d, bPowerOn = %d, bFullCal = %d\n", __FUNCTION__, Channel, bPowerOn, bFullCal));
	
	
#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_WAIT(&pAd->cal_atomic, ret);
		if (ret != 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("cal_atomic get failed(ret=%d)\n", ret));
			return;
		}
	}
#endif /* RTMP_MAC_USB */

	if (!(bPowerOn || bDoTSSI || bFullCal))
		goto RXDC_Calibration;
		
	if (bPowerOn)
	{	
		/*
			Do Power on calibration.
			The calibration sequence is very important, please do NOT change it.
			1 XTAL Setup (already done in AsicRfInit)
			2 R-calibration
			3 VCO calibration
		*/

		/*
			2 R-calibration 
		*/
		RTMP_CHIP_CALIBRATION(pAd, R_CALIBRATION, 0x0);

		/*
			3 VCO calibration (mode 3) 
		*/
		MT76x0_VCO_CalibrationMode3(pAd, Channel);

#ifdef MT76x0_TSSI_CAL_COMPENSATION
		/* TSSI Calibration */
		if (bPowerOn && pAd->chipCap.bInternalTxALC)
		{
			MT76x0_TSSI_DC_Calibration(pAd);
			RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0xc);
		}
#endif /* MT76x0_TSSI_CAL_COMPENSATION */
	}

	RTMP_IO_READ32(pAd, TX_ALC_CFG_0, &reg_tx_alc); /* We need to restore 0x13b0 after calibration. */
	RTMP_IO_WRITE32(pAd, TX_ALC_CFG_0, 0x0);
	RTMPusecDelay(500);
	
	RTMP_IO_READ32(pAd, 0x2124, &reg_val); /* We need to restore 0x2124 after calibration. */
	MacReg = 0xFFFFFF7E; /* Disable 0x2704, 0x2708 controlled by MAC. */
	RTMP_IO_WRITE32(pAd, 0x2124, MacReg);

	/*
		Do calibration.
		The calibration sequence is very important, please do NOT change it.
		4  RX DCOC calibration
		5  LC tank calibration
		6  TX Filter BW --> not ready yet @20121003
		7  RX Filter BW --> not ready yet @20121003
		8  TX RF LOFT 
		9  TX I/Q
		10 TX Group Delay		
		11 RX I/Q
		12 RX Group Delay
		13 TSSI Zero Reference --> not ready yet @20121016
		14 TX 2G DPD
		15 TX 2G IM3 --> not ready yet @20121016 
		16 On-chip temp sensor reading --> not ready yet @20130129
		17 RX DCOC calibration
	*/
	if (bFullCal)
	{
		/*
			4. RXDC Calibration parameter
				0:Back Ground Disable
		*/
		RTMP_CHIP_CALIBRATION(pAd, RXDCOC_CALIBRATION, 0);
		
		/*
			5. LC-Calibration parameter
				Bit[0:7]
					0: 2G
					1: 5G + External PA
					2: 5G + Internal PA
				Bit[8:15]
					0: Full Calibration
					1: Partial Calibration
					2: G-Band Full Calibration + Save
					3: A-Band (Low) Full Calibration + Save
					4: A-Band (Mid) Full Calibration + Save
					5: A-Band (High) Full Calibration + Save
					6: G-Band Restore Calibration
					7: A-Band (Low) Restore Calibration
					8: A-Band (Mid) Restore Calibration
					9: A-Band (High) Restore Calibration
		*/
		if (Channel > 14) {
			// TODO: check PA setting from EEPROM @20121016
			RTMP_CHIP_CALIBRATION(pAd, LC_CALIBRATION, 0x1);
		} else {
			RTMP_CHIP_CALIBRATION(pAd, LC_CALIBRATION, 0x0);
		}

		/*
			6,7. BW-Calibration
				Bit[0:7] (0:RX, 1:TX)
				Bit[8:15] (0:BW20, 1:BW40, 2:BW80)
				Bit[16:23]
					0: Full Calibration
					1: Partial Calibration
					2: G-Band Full Calibration + Save
					3: A-Band (Low) Full Calibration + Save
					4: A-Band (Mid) Full Calibration + Save
					5: A-Band (High) Full Calibration + Save
					6: G-Band Restore Calibration
					7: A-Band (Low) Restore Calibration
					8: A-Band (Mid) Restore Calibration
					9: A-Band (High) Restore Calibration
		*/

		/*			
			8. RF LOFT-Calibration parameter
				Bit[0:7] (0:G-Band, 1: A-Band)
				Bit[8:15] 
					0: Full Calibration
					1: Partial Calibration
					2: G-Band Full Calibration + Save
					3: A-Band (Low) Full Calibration + Save
					4: A-Band (Mid) Full Calibration + Save
					5: A-Band (High) Full Calibration + Save
					6: G-Band Restore Calibration
					7: A-Band (Low) Restore Calibration
					8: A-Band (Mid) Restore Calibration
					9: A-Band (High) Restore Calibration
		*/
		if (Channel > 14) {
			RTMP_CHIP_CALIBRATION(pAd, LOFT_CALIBRATION, 0x1);
		} else {
			RTMP_CHIP_CALIBRATION(pAd, LOFT_CALIBRATION, 0x0);
		}
		
		/*
			9. TXIQ-Calibration parameter
				Bit[0:7] (0:G-Band, 1: A-Band)
				Bit[8:15] 
					0: Full Calibration
					1: Partial Calibration
					2: G-Band Full Calibration + Save
					3: A-Band (Low) Full Calibration + Save
					4: A-Band (Mid) Full Calibration + Save
					5: A-Band (High) Full Calibration + Save
					6: G-Band Restore Calibration
					7: A-Band (Low) Restore Calibration
					8: A-Band (Mid) Restore Calibration
					9: A-Band (High) Restore Calibration
		*/
		if (Channel > 14) {
			RTMP_CHIP_CALIBRATION(pAd, TXIQ_CALIBRATION, 0x1);
		} else {
			RTMP_CHIP_CALIBRATION(pAd, TXIQ_CALIBRATION, 0x0);
		}
		
		/*
			10. TX Group-Delay Calibation parameter
				Bit[0:7] (0:G-Band, 1: A-Band)
				Bit[8:15] 
					0: Full Calibration
					1: Partial Calibration
					2: G-Band Full Calibration + Save
					3: A-Band (Low) Full Calibration + Save
					4: A-Band (Mid) Full Calibration + Save
					5: A-Band (High) Full Calibration + Save
					6: G-Band Restore Calibration
					7: A-Band (Low) Restore Calibration
					8: A-Band (Mid) Restore Calibration
					9: A-Band (High) Restore Calibration
		*/
		if (Channel > 14) {
			RTMP_CHIP_CALIBRATION(pAd, TX_GROUP_DELAY_CALIBRATION, 0x1);
		} else {
			RTMP_CHIP_CALIBRATION(pAd, TX_GROUP_DELAY_CALIBRATION, 0x0);
		}

		/*
			11. RXIQ-Calibration parameter
				Bit[0:7] (0:G-Band, 1: A-Band)
				Bit[8:15] 
					0: Full Calibration
					1: Partial Calibration
					2: G-Band Full Calibration + Save
					3: A-Band (Low) Full Calibration + Save
					4: A-Band (Mid) Full Calibration + Save
					5: A-Band (High) Full Calibration + Save
					6: G-Band Restore Calibration
					7: A-Band (Low) Restore Calibration
					8: A-Band (Mid) Restore Calibration
					9: A-Band (High) Restore Calibration
		*/
		if (Channel > 14) {
			RTMP_CHIP_CALIBRATION(pAd, RXIQ_CALIBRATION, 0x1);
		} else {
			RTMP_CHIP_CALIBRATION(pAd, RXIQ_CALIBRATION, 0x0);
		}
		
		/*
			12. RX Group-Delay Calibation parameter
				Bit[0:7] (0:G-Band, 1: A-Band)
				Bit[8:15] 
					0: Full Calibration
					1: Partial Calibration
					2: G-Band Full Calibration + Save
					3: A-Band (Low) Full Calibration + Save
					4: A-Band (Mid) Full Calibration + Save
					5: A-Band (High) Full Calibration + Save
					6: G-Band Restore Calibration
					7: A-Band (Low) Restore Calibration
					8: A-Band (Mid) Restore Calibration
					9: A-Band (High) Restore Calibration
		*/
		if (Channel > 14) {
			RTMP_CHIP_CALIBRATION(pAd, RX_GROUP_DELAY_CALIBRATION, 0x1);
		} else {
			RTMP_CHIP_CALIBRATION(pAd, RX_GROUP_DELAY_CALIBRATION, 0x0);
		}

		/* 
			14. TX 2G DPD - Only 2.4G needs to do DPD Calibration. 
				Bit[0:7] (1~14 Channel)
				Bit[8:15] (0:BW20, 1:BW40)
				NOTE: disable DPD calibration for USB products
		*/
		if (IS_MT76x0E(pAd)) {
			UINT32 dpd_val = 0;

			dpd_val = (pAd->CommonCfg.BBPCurrentBW << 8) | Channel;
			RTMP_CHIP_CALIBRATION(pAd, DPD_CALIBRATION, dpd_val);
			DBGPRINT(RT_DEBUG_OFF, ("%s - DPD_CALIBRATION = 0x%x\n", __FUNCTION__, dpd_val));
		}
	}

	/* Restore 0x2124 & TX_ALC_CFG_0 after calibration completed */
	RTMP_IO_WRITE32(pAd, 0x2124, reg_val);
	RTMP_IO_WRITE32(pAd, TX_ALC_CFG_0, reg_tx_alc);
	RTMPusecDelay(100000); // TODO: check response packet from FW

RXDC_Calibration:
	/*
		17. RXDC Calibration parameter
			1:Back Ground Enable
	*/
	RTMP_CHIP_CALIBRATION(pAd, RXDCOC_CALIBRATION, 1);
	

#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_UP(&pAd->cal_atomic);
	}
#endif /* RTMP_MAC_USB */
}

VOID MT76x0_TempSensor(
	IN RTMP_ADAPTER *pAd)
{
	UCHAR rf_b7_73 = 0, rf_b0_66 = 0, rf_b0_67 = 0;
	UINT32 reg_val = 0;
	SHORT temperature = 0;
	INT32 Dout = 0; 
	UINT32 MTxCycle = 0;
#ifdef RTMP_MAC_USB
	UINT32 ret;
#endif /* RTMP_MAC_USB */


#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_WAIT(&pAd->cal_atomic, ret);
		if (ret != 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("cal_atomic get failed(ret=%d)\n", ret));
			return;
		}
	}
#endif /* RTMP_MAC_USB */
	
	rlt_rf_read(pAd, RF_BANK7, RF_R73, &rf_b7_73);
	rlt_rf_read(pAd, RF_BANK0, RF_R66, &rf_b0_66);
	rlt_rf_read(pAd, RF_BANK0, RF_R67, &rf_b0_67);
	
	/*
		1. Set 0dB Gain:
			WIFI_RF_CR_WRITE(7,73,0x02) 
	*/
	rlt_rf_write(pAd, RF_BANK7, RF_R73, 0x02);

	/*
		2. Calibration Switches:
			WIFI_RF_CR_WRITE(0,66,0x23)
	*/
	rlt_rf_write(pAd, RF_BANK0, RF_R66, 0x23);

	/*
		3. Offset-measurement configuration:
			WIFI_RF_CR_WRITE(0,67,0x01)
	*/
	rlt_rf_write(pAd, RF_BANK0, RF_R67, 0x01);

	/*
		4. Select Level meter from ADC.q:
			WIFI_BBP_CR_WRITE(0x2088,0x00080055)
	*/
	RTMP_BBP_IO_WRITE32(pAd, CORE_R34, 0x00080055);

	/*
		5. Wait until it's done:
			wait until 0x2088[4] = 0
	*/
	for (MTxCycle = 0; MTxCycle < 2000; MTxCycle++)
	{
		RTMP_BBP_IO_READ32(pAd, CORE_R34, &reg_val);
		if ((reg_val & 0x10) == 0)
			break;
		RTMPusecDelay(3);
	}

	if (MTxCycle >= 2000)
	{
		reg_val &= ~(0x10);
		RTMP_BBP_IO_WRITE32(pAd, CORE_R34, reg_val);
		goto done;
	}

	/*
		6. Read Dout (0x0041208c<7:0>=adc_out<8:1>):
			WIFI_BBP_CR_READ(0x208c) //$Dout

	*/
	RTMP_BBP_IO_READ32(pAd, CORE_R35, &Dout);
	Dout &= 0xFF;

	if ((Dout & 0x80) == 0x00) 
		Dout &= 0x7F; /* Positive number */
	else 
		Dout |= 0xFFFFFF00; /* Negative number */
				
	/*
		7. Read D25 from EEPROM:
			Read EEPROM 0xD1 // $Offset (signed integer)
	*/

	/*
		8. Calculate temperature:
			T = 3.5*(Dout-D25) + 25
	*/
	temperature = (35*(Dout-pAd->chipCap.TemperatureOffset))/10 + 25;
	DBGPRINT(RT_DEBUG_TRACE, ("%s - Dout=%d, TemperatureOffset = %d, temperature = %d\n", __FUNCTION__, Dout, pAd->chipCap.TemperatureOffset, temperature));
	if (pAd->chipCap.LastTemperatureforVCO == 0x7FFF)
		pAd->chipCap.LastTemperatureforVCO = temperature;
	if (pAd->chipCap.LastTemperatureforCal == 0x7FFF)
		pAd->chipCap.LastTemperatureforCal = temperature;
	pAd->chipCap.NowTemperature = temperature;
	
done:	
	/*
		9. Restore RF CR:
			B7. R73, B0.R66, B0.R67
	*/
	rlt_rf_write(pAd, RF_BANK7, RF_R73, rf_b7_73);
	rlt_rf_write(pAd, RF_BANK0, RF_R66, rf_b0_66);
	rlt_rf_write(pAd, RF_BANK0, RF_R67, rf_b0_67);


#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_UP(&pAd->cal_atomic);
	}
#endif /* RTMP_MAC_USB */
}

#ifdef RTMP_FLASH_SUPPORT
VOID MT76x0_ReadFlashAndInitAsic(
	IN RTMP_ADAPTER *pAd)
{
	USHORT ee_val = 0;
	UINT32 reg_val = 0;


	pAd->chipCap.eebuf = MT76x0_EeBuffer;
	rtmp_nv_init(pAd);

	rtmp_ee_flash_read(pAd, 0x22, &ee_val);
	DBGPRINT(RT_DEBUG_TRACE, ("%s: 0x22 = 0x%x\n", __FUNCTION__, ee_val));
	RTMP_IO_READ32(pAd, CMB_CTRL, &reg_val);
	reg_val &= 0xFFFF0000;
	reg_val |= ee_val;
	RTMP_IO_WRITE32(pAd, CMB_CTRL, reg_val);

	rtmp_ee_flash_read(pAd, 0x24, &ee_val);
	DBGPRINT(RT_DEBUG_TRACE, ("%s: 0x24 = 0x%x\n", __FUNCTION__, ee_val));
	RTMP_IO_READ32(pAd, 0x104, &reg_val);
	reg_val &= 0xFFFF0000;
	reg_val |= ee_val;
	RTMP_IO_WRITE32(pAd, 0x104, reg_val);
	return;
}
#endif /* RTMP_FLASH_SUPPORT */


VOID MT76x0_MakeUpRatePwrTable(
	IN RTMP_ADAPTER *pAd)
{
	UINT32 reg_val;

	RTMP_IO_READ32(pAd, TX_PWR_CFG_0, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_0, reg_val));
	pAd->chipCap.rate_pwr_table.CCK[0].MCS_Power = (CHAR)(reg_val & 0x3F); /* CCK 1M */
	if (pAd->chipCap.rate_pwr_table.CCK[0].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.CCK[0].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.CCK[1].MCS_Power = (CHAR)(reg_val & 0x3F); /* CCK 2M */
	if (pAd->chipCap.rate_pwr_table.CCK[1].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.CCK[1].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.CCK[2].MCS_Power = (CHAR)((reg_val & 0x3F00) >> 8); /* CCK 5.5M */
	if (pAd->chipCap.rate_pwr_table.CCK[2].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.CCK[2].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.CCK[3].MCS_Power = (CHAR)((reg_val & 0x3F00) >> 8); /* CCK 11M */
	if (pAd->chipCap.rate_pwr_table.CCK[3].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.CCK[3].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.OFDM[0].MCS_Power = (CHAR)((reg_val & 0x3F0000) >> 16); /* OFDM 6M */
	if (pAd->chipCap.rate_pwr_table.OFDM[0].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.OFDM[0].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.OFDM[1].MCS_Power = (CHAR)((reg_val & 0x3F0000) >> 16); /* OFDM 9M */
	if (pAd->chipCap.rate_pwr_table.OFDM[1].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.OFDM[1].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.OFDM[2].MCS_Power = (CHAR)((reg_val & 0x3F000000) >> 24); /* OFDM 12M */
	if (pAd->chipCap.rate_pwr_table.OFDM[2].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.OFDM[2].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.OFDM[3].MCS_Power = (CHAR)((reg_val & 0x3F000000) >> 24); /* OFDM 18M */
	if (pAd->chipCap.rate_pwr_table.OFDM[3].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.OFDM[3].MCS_Power -= 64;

	RTMP_IO_READ32(pAd, TX_PWR_CFG_1, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_1, reg_val));
	pAd->chipCap.rate_pwr_table.OFDM[4].MCS_Power = (CHAR)(reg_val & 0x3F); /* OFDM 24M */
	if (pAd->chipCap.rate_pwr_table.OFDM[4].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.OFDM[4].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.OFDM[5].MCS_Power = (CHAR)(reg_val & 0x3F); /* OFDM 36M */
	if (pAd->chipCap.rate_pwr_table.OFDM[5].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.OFDM[5].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.OFDM[6].MCS_Power = (CHAR)((reg_val & 0x3F00) >> 8); /* OFDM 48M */
	if (pAd->chipCap.rate_pwr_table.OFDM[6].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.OFDM[6].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.HT[0].MCS_Power = (CHAR)((reg_val&0x3F0000) >> 16); /* HT/VHT MCS0 */
	if (pAd->chipCap.rate_pwr_table.HT[0].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.HT[0].MCS_Power -= 64;
	pAd->chipCap.rate_pwr_table.VHT[0].MCS_Power = pAd->chipCap.rate_pwr_table.HT[0].MCS_Power;

	pAd->chipCap.rate_pwr_table.MCS32.MCS_Power = pAd->chipCap.rate_pwr_table.HT[0].MCS_Power; /* HT MCS32 */
	if (pAd->chipCap.rate_pwr_table.MCS32.MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.MCS32.MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.HT[1].MCS_Power = (CHAR)((reg_val & 0x3F0000) >> 16); /* HT/VHT MCS1 */
	if (pAd->chipCap.rate_pwr_table.HT[1].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.HT[1].MCS_Power -= 64;
	pAd->chipCap.rate_pwr_table.VHT[1].MCS_Power = pAd->chipCap.rate_pwr_table.HT[1].MCS_Power;
	
	pAd->chipCap.rate_pwr_table.HT[2].MCS_Power = (CHAR)((reg_val & 0x3F000000) >> 24); /* HT/VHT MCS2 */
	if (pAd->chipCap.rate_pwr_table.HT[2].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.HT[2].MCS_Power -= 64;
	pAd->chipCap.rate_pwr_table.VHT[2].MCS_Power = pAd->chipCap.rate_pwr_table.HT[2].MCS_Power;
	
	pAd->chipCap.rate_pwr_table.HT[3].MCS_Power = (CHAR)((reg_val&0x3F000000) >> 24); /* HT/VHT MCS3 */
	if (pAd->chipCap.rate_pwr_table.HT[3].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.HT[3].MCS_Power -= 64;
	pAd->chipCap.rate_pwr_table.VHT[3].MCS_Power = pAd->chipCap.rate_pwr_table.HT[3].MCS_Power;

	RTMP_IO_READ32(pAd, TX_PWR_CFG_2, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_2, reg_val));
	pAd->chipCap.rate_pwr_table.HT[4].MCS_Power = (CHAR)(reg_val & 0x3F); /* HT/VHT MCS4 */
	if (pAd->chipCap.rate_pwr_table.HT[4].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.HT[4].MCS_Power -= 64;
	pAd->chipCap.rate_pwr_table.VHT[4].MCS_Power = pAd->chipCap.rate_pwr_table.HT[4].MCS_Power;
	
	pAd->chipCap.rate_pwr_table.HT[5].MCS_Power = (CHAR)(reg_val&0x3F); /* HT/VHT MCS5 */
	if (pAd->chipCap.rate_pwr_table.HT[5].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.HT[5].MCS_Power -= 64;
	pAd->chipCap.rate_pwr_table.VHT[5].MCS_Power = pAd->chipCap.rate_pwr_table.HT[5].MCS_Power;
	
	pAd->chipCap.rate_pwr_table.HT[6].MCS_Power = (CHAR)((reg_val&0x3F00) >> 8); /* HT/VHT MCS6 */
	if (pAd->chipCap.rate_pwr_table.HT[6].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.HT[6].MCS_Power -= 64;
	pAd->chipCap.rate_pwr_table.VHT[6].MCS_Power = pAd->chipCap.rate_pwr_table.HT[6].MCS_Power;

	RTMP_IO_READ32(pAd, TX_PWR_CFG_3, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_3, reg_val));
	pAd->chipCap.rate_pwr_table.STBC[0].MCS_Power = (CHAR)((reg_val&0x3F0000) >> 16); /* STBC MCS0 */
	if (pAd->chipCap.rate_pwr_table.STBC[0].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.STBC[0].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.STBC[1].MCS_Power = (CHAR)((reg_val&0x3F0000) >> 16); /* STBC MCS1 */
	if (pAd->chipCap.rate_pwr_table.STBC[1].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.STBC[1].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.STBC[2].MCS_Power = (CHAR)((reg_val&0x3F000000) >> 24); /* STBC MCS2 */
	if (pAd->chipCap.rate_pwr_table.STBC[2].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.STBC[2].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.STBC[3].MCS_Power = (CHAR)((reg_val&0x3F000000) >> 24); /* STBC MCS3 */
	if (pAd->chipCap.rate_pwr_table.STBC[3].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.STBC[3].MCS_Power -= 64;

	RTMP_IO_READ32(pAd, TX_PWR_CFG_4, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_4, reg_val));
	pAd->chipCap.rate_pwr_table.STBC[4].MCS_Power = (CHAR)(reg_val & 0x3F); /* STBC MCS4 */
	if (pAd->chipCap.rate_pwr_table.STBC[4].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.STBC[4].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.STBC[5].MCS_Power = (CHAR)(reg_val & 0x3F); /* STBC MCS5 */
	if (pAd->chipCap.rate_pwr_table.STBC[5].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.STBC[5].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.STBC[6].MCS_Power = (CHAR)((reg_val & 0x3F00) >> 8); /* STBC MCS6 */
	if (pAd->chipCap.rate_pwr_table.STBC[6].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.STBC[6].MCS_Power -= 64;

	RTMP_IO_READ32(pAd, TX_PWR_CFG_7, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_7, reg_val));
	pAd->chipCap.rate_pwr_table.OFDM[7].MCS_Power = (CHAR)(reg_val & 0x3F); /* OFDM 54M */
	if (pAd->chipCap.rate_pwr_table.OFDM[7].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.OFDM[7].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.HT[7].MCS_Power = (CHAR)((reg_val & 0x3F0000) >> 16); /* HT/VHT MCS7 */
	if (pAd->chipCap.rate_pwr_table.HT[7].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.HT[7].MCS_Power -= 64;
	pAd->chipCap.rate_pwr_table.VHT[7].MCS_Power = pAd->chipCap.rate_pwr_table.HT[7].MCS_Power;

	RTMP_IO_READ32(pAd, TX_PWR_CFG_8, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_8, reg_val));
	pAd->chipCap.rate_pwr_table.VHT[8].MCS_Power = (CHAR)((reg_val & 0x3F0000) >> 16); /* VHT MCS8 */
	if (pAd->chipCap.rate_pwr_table.VHT[8].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.VHT[8].MCS_Power -= 64;
	
	pAd->chipCap.rate_pwr_table.VHT[9].MCS_Power = (CHAR)((reg_val & 0x3F000000) >> 24); /* VHT MCS9 */
	if ( pAd->chipCap.rate_pwr_table.VHT[9].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.VHT[9].MCS_Power -= 64;

	RTMP_IO_READ32(pAd, TX_PWR_CFG_9, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_9, reg_val));
	pAd->chipCap.rate_pwr_table.STBC[7].MCS_Power = (CHAR)(reg_val & 0x3F); /* STBC MCS7 */
	if (pAd->chipCap.rate_pwr_table.STBC[7].MCS_Power & 0x20)
		pAd->chipCap.rate_pwr_table.STBC[7].MCS_Power -= 64;

	DBGPRINT(RT_DEBUG_TRACE, ("\n"));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.CCK[0].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.CCK[0].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.CCK[1].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.CCK[1].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.CCK[2].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.CCK[2].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.CCK[3].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.CCK[3].MCS_Power));

	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[0].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.OFDM[0].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[1].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.OFDM[1].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[2].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.OFDM[2].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[3].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.OFDM[3].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[4].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.OFDM[4].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[5].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.OFDM[5].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[6].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.OFDM[6].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[7].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.OFDM[7].MCS_Power));

	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[0].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.STBC[0].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[1].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.STBC[1].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[2].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.STBC[2].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[3].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.STBC[3].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[4].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.STBC[4].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[5].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.STBC[5].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[6].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.STBC[6].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[7].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.STBC[7].MCS_Power));

	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[0].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.HT[0].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[1].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.HT[1].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[2].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.HT[2].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[3].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.HT[3].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[4].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.HT[4].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[5].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.HT[5].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[6].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.HT[6].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[7].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.HT[7].MCS_Power));

	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[0].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.VHT[0].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[1].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.VHT[1].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[2].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.VHT[2].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[3].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.VHT[3].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[4].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.VHT[4].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[5].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.VHT[5].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[6].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.VHT[6].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[7].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.VHT[7].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[8].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.VHT[8].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[9].MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.VHT[9].MCS_Power));

	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.MCS32.MCS_Power = %d\n", pAd->chipCap.rate_pwr_table.MCS32.MCS_Power));

	// PA MODE
	RTMP_IO_READ32(pAd, RF_PA_MODE_CFG0, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", RF_PA_MODE_CFG0, reg_val));
	pAd->chipCap.rate_pwr_table.CCK[0].RF_PA_Mode = (UCHAR)(reg_val & 0x00000003);
	pAd->chipCap.rate_pwr_table.CCK[1].RF_PA_Mode = (UCHAR)((reg_val & 0x0000000C) >> 2);
	pAd->chipCap.rate_pwr_table.CCK[2].RF_PA_Mode = (UCHAR)((reg_val & 0x00000030) >> 4);
	pAd->chipCap.rate_pwr_table.CCK[3].RF_PA_Mode = (UCHAR)((reg_val & 0x000000C0) >> 6);
	pAd->chipCap.rate_pwr_table.OFDM[0].RF_PA_Mode = (UCHAR)((reg_val & 0x00000300) >> 8);
	pAd->chipCap.rate_pwr_table.OFDM[1].RF_PA_Mode = (UCHAR)((reg_val & 0x00000C00) >> 10);
	pAd->chipCap.rate_pwr_table.OFDM[2].RF_PA_Mode = (UCHAR)((reg_val & 0x00003000) >> 12);
	pAd->chipCap.rate_pwr_table.OFDM[3].RF_PA_Mode = (UCHAR)((reg_val & 0x0000C000) >> 14);
	pAd->chipCap.rate_pwr_table.OFDM[4].RF_PA_Mode = (UCHAR)((reg_val & 0x00030000) >> 16);
	pAd->chipCap.rate_pwr_table.OFDM[5].RF_PA_Mode = (UCHAR)((reg_val & 0x000C0000) >> 18);
	pAd->chipCap.rate_pwr_table.OFDM[6].RF_PA_Mode = (UCHAR)((reg_val & 0x00300000) >> 20);
	pAd->chipCap.rate_pwr_table.OFDM[7].RF_PA_Mode = (UCHAR)((reg_val & 0x00C00000) >> 22);
	pAd->chipCap.rate_pwr_table.MCS32.RF_PA_Mode = (UCHAR)((reg_val & 0xC0000000) >> 30);

	RTMP_IO_READ32(pAd, RF_PA_MODE_CFG1, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", RF_PA_MODE_CFG1, reg_val));
	pAd->chipCap.rate_pwr_table.HT[0].RF_PA_Mode = (UCHAR)(reg_val & 0x00000003);
	pAd->chipCap.rate_pwr_table.VHT[0].RF_PA_Mode = pAd->chipCap.rate_pwr_table.HT[0].RF_PA_Mode;
	pAd->chipCap.rate_pwr_table.HT[1].RF_PA_Mode = (UCHAR)((reg_val & 0x0000000C) >> 2);
	pAd->chipCap.rate_pwr_table.VHT[1].RF_PA_Mode = pAd->chipCap.rate_pwr_table.HT[1].RF_PA_Mode;
	pAd->chipCap.rate_pwr_table.HT[2].RF_PA_Mode = (UCHAR)((reg_val & 0x00000030) >> 4);
	pAd->chipCap.rate_pwr_table.VHT[2].RF_PA_Mode = pAd->chipCap.rate_pwr_table.HT[2].RF_PA_Mode;
	pAd->chipCap.rate_pwr_table.HT[3].RF_PA_Mode = (UCHAR)((reg_val & 0x000000C0) >> 6);
	pAd->chipCap.rate_pwr_table.VHT[3].RF_PA_Mode = pAd->chipCap.rate_pwr_table.HT[3].RF_PA_Mode;
	pAd->chipCap.rate_pwr_table.HT[4].RF_PA_Mode = (UCHAR)((reg_val & 0x00000300) >> 8);
	pAd->chipCap.rate_pwr_table.VHT[4].RF_PA_Mode = pAd->chipCap.rate_pwr_table.HT[4].RF_PA_Mode;
	pAd->chipCap.rate_pwr_table.HT[5].RF_PA_Mode = (UCHAR)((reg_val & 0x00000C00) >> 10);
	pAd->chipCap.rate_pwr_table.VHT[5].RF_PA_Mode = pAd->chipCap.rate_pwr_table.HT[5].RF_PA_Mode;
	pAd->chipCap.rate_pwr_table.HT[6].RF_PA_Mode = (UCHAR)((reg_val & 0x00003000) >> 12);
	pAd->chipCap.rate_pwr_table.VHT[6].RF_PA_Mode = pAd->chipCap.rate_pwr_table.HT[6].RF_PA_Mode;
	pAd->chipCap.rate_pwr_table.HT[7].RF_PA_Mode = (UCHAR)((reg_val & 0x0000C000) >> 14);
	pAd->chipCap.rate_pwr_table.VHT[7].RF_PA_Mode = pAd->chipCap.rate_pwr_table.HT[7].RF_PA_Mode;
	pAd->chipCap.rate_pwr_table.VHT[8].RF_PA_Mode = (UCHAR)((reg_val & 0x00030000) >> 16);
	pAd->chipCap.rate_pwr_table.VHT[9].RF_PA_Mode = (UCHAR)((reg_val & 0x000C0000) >> 18);

	DBGPRINT(RT_DEBUG_TRACE, ("\n"));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.CCK[0].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.CCK[0].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.CCK[1].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.CCK[1].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.CCK[2].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.CCK[2].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.CCK[3].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.CCK[3].RF_PA_Mode));

	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[0].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.OFDM[0].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[1].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.OFDM[1].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[2].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.OFDM[2].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[3].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.OFDM[3].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[4].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.OFDM[4].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[5].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.OFDM[5].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[6].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.OFDM[6].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.OFDM[7].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.OFDM[7].RF_PA_Mode));

	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[0].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.STBC[0].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[1].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.STBC[1].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[2].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.STBC[2].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[3].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.STBC[3].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[4].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.STBC[4].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[5].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.STBC[5].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[6].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.STBC[6].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.STBC[7].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.STBC[7].RF_PA_Mode));

	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[0].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.HT[0].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[1].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.HT[1].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[2].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.HT[2].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[3].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.HT[3].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[4].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.HT[4].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[5].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.HT[5].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[6].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.HT[6].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.HT[7].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.HT[7].RF_PA_Mode));

	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[0].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.VHT[0].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[1].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.VHT[1].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[2].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.VHT[2].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[3].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.VHT[3].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[4].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.VHT[4].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[5].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.VHT[5].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[6].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.VHT[6].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[7].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.VHT[7].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[8].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.VHT[8].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.VHT[9].RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.VHT[9].RF_PA_Mode));

	DBGPRINT(RT_DEBUG_TRACE, ("rate_pwr_table.MCS32.RF_PA_Mode = %d\n", pAd->chipCap.rate_pwr_table.MCS32.RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("\n"));
}


/******************************* TSSI *********************************/
#ifdef MT76x0_TSSI_CAL_COMPENSATION
#define DEFAULT_BO              4
#define LIN2DB_ERROR_CODE       (-10000)
INT16 lin2dBd(
	IN	unsigned short linearValue)
{
    short exp;
    unsigned int mantisa;
    int app,dBd;

	/* Default backoff ; to enhance leading bit searching time */
	mantisa = linearValue << DEFAULT_BO;
	exp = -(DEFAULT_BO);

	/* Leading bit searching */
	if (mantisa < (0x8000))
	{
		while (mantisa < (0x8000))
		{
			mantisa = mantisa << 1; /* no need saturation */
			exp--;
			if (exp < -20)
			{
				DBGPRINT_ERR(("input too small\n"));
				DBGPRINT_ERR(("exponent = %d\n",exp));

				return LIN2DB_ERROR_CODE;
			}
		}
	}
	else 
	{
		while (mantisa > (0xFFFF))
		{
			mantisa = mantisa >> 1; /* no need saturation */
			exp ++;
			if (exp > 20)
			{
				DBGPRINT_ERR(("input too large\n"));
				DBGPRINT_ERR(("exponent = %d\n",exp));

				return LIN2DB_ERROR_CODE;
			}
		}
	}
/*	printk("exp=0d%d,mantisa=0x%x\n",exp,mantisa); */

	if (mantisa <= 47104)
	{
		app=(mantisa+(mantisa>>3)+(mantisa>>4)-38400); /* S(15,0) */
		if (app<0)
		{
			app=0;
		}
	}
	else
	{
		app=(mantisa-(mantisa>>3)-(mantisa>>6)-23040); /* S(15,0) */
		if (app<0)
		{
			app=0;
		}
	}

	dBd=((15+exp)<<15)+app; /*since 2^15=1 here */
/*	printk("dBd1=%d\n",dBd); */
	dBd=(dBd<<2)+(dBd<<1)+(dBd>>6)+(dBd>>7);
	dBd=(dBd>>10); /* S10.5 */
/*	printk("app=%d,dBd=%d,dBdF=%f\n",app,dBd,(double)dBd/32); */

	return(dBd);
}

VOID MT76x0_MakeUpTssiTable(
	IN  RTMP_ADAPTER *pAd)
{
	UINT32 reg_val;

	// MCS POWER
	RTMP_IO_READ32(pAd, TX_PWR_CFG_0, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_0, reg_val));
	pAd->chipCap.tssi_table.CCK[0].MCS_Power = (CHAR)(reg_val&0x3F);
	if ( pAd->chipCap.tssi_table.CCK[0].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.CCK[0].MCS_Power -= 64;
	pAd->chipCap.tssi_table.CCK[1].MCS_Power = (CHAR)(reg_val&0x3F);
	if ( pAd->chipCap.tssi_table.CCK[1].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.CCK[1].MCS_Power -= 64;
	pAd->chipCap.tssi_table.CCK[2].MCS_Power = (CHAR)((reg_val&0x3F00)>>8);
	if ( pAd->chipCap.tssi_table.CCK[2].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.CCK[2].MCS_Power -= 64;
	pAd->chipCap.tssi_table.CCK[3].MCS_Power = (CHAR)((reg_val&0x3F00)>>8);
	if ( pAd->chipCap.tssi_table.CCK[3].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.CCK[3].MCS_Power -= 64;
	pAd->chipCap.tssi_table.OFDM[0].MCS_Power = (CHAR)((reg_val&0x3F0000)>>16);
	if ( pAd->chipCap.tssi_table.OFDM[0].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.OFDM[0].MCS_Power -= 64;
	pAd->chipCap.tssi_table.OFDM[1].MCS_Power = (CHAR)((reg_val&0x3F0000)>>16);
	if ( pAd->chipCap.tssi_table.OFDM[1].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.OFDM[1].MCS_Power -= 64;
	pAd->chipCap.tssi_table.OFDM[2].MCS_Power = (CHAR)((reg_val&0x3F000000)>>24);
	if ( pAd->chipCap.tssi_table.OFDM[2].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.OFDM[2].MCS_Power -= 64;
	pAd->chipCap.tssi_table.OFDM[3].MCS_Power = (CHAR)((reg_val&0x3F000000)>>24);
	if ( pAd->chipCap.tssi_table.OFDM[3].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.OFDM[3].MCS_Power -= 64;

	RTMP_IO_READ32(pAd, TX_PWR_CFG_1, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_1, reg_val));
	pAd->chipCap.tssi_table.OFDM[4].MCS_Power = (CHAR)(reg_val&0x3F);
	if ( pAd->chipCap.tssi_table.OFDM[4].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.OFDM[4].MCS_Power -= 64;
	pAd->chipCap.tssi_table.OFDM[5].MCS_Power = (CHAR)(reg_val&0x3F);
	if ( pAd->chipCap.tssi_table.OFDM[5].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.OFDM[5].MCS_Power -= 64;
	pAd->chipCap.tssi_table.OFDM[6].MCS_Power = (CHAR)((reg_val&0x3F00)>>8);
	if ( pAd->chipCap.tssi_table.OFDM[6].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.OFDM[6].MCS_Power -= 64;
	pAd->chipCap.tssi_table.HT[0].MCS_Power = (CHAR)((reg_val&0x3F0000)>>16);
	if ( pAd->chipCap.tssi_table.HT[0].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.HT[0].MCS_Power -= 64;
	pAd->chipCap.tssi_table.VHT[0].MCS_Power = pAd->chipCap.tssi_table.HT[0].MCS_Power;
	pAd->chipCap.tssi_table.MCS32.MCS_Power = pAd->chipCap.tssi_table.HT[0].MCS_Power;
	if ( pAd->chipCap.tssi_table.MCS32.MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.MCS32.MCS_Power -= 64;
	pAd->chipCap.tssi_table.HT[1].MCS_Power = (CHAR)((reg_val&0x3F0000)>>16);
	if ( pAd->chipCap.tssi_table.HT[1].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.HT[1].MCS_Power -= 64;
	pAd->chipCap.tssi_table.VHT[1].MCS_Power = pAd->chipCap.tssi_table.HT[1].MCS_Power;
	pAd->chipCap.tssi_table.HT[2].MCS_Power = (CHAR)((reg_val&0x3F000000)>>24);
	if ( pAd->chipCap.tssi_table.HT[2].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.HT[2].MCS_Power -= 64;
	pAd->chipCap.tssi_table.VHT[2].MCS_Power = pAd->chipCap.tssi_table.HT[2].MCS_Power;
	pAd->chipCap.tssi_table.HT[3].MCS_Power = (CHAR)((reg_val&0x3F000000)>>24);
	if ( pAd->chipCap.tssi_table.HT[3].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.HT[3].MCS_Power -= 64;
	pAd->chipCap.tssi_table.VHT[3].MCS_Power = pAd->chipCap.tssi_table.HT[3].MCS_Power;

	RTMP_IO_READ32(pAd, TX_PWR_CFG_2, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_2, reg_val));
	pAd->chipCap.tssi_table.HT[4].MCS_Power = (CHAR)(reg_val&0x3F);
	if ( pAd->chipCap.tssi_table.HT[4].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.HT[4].MCS_Power -= 64;
	pAd->chipCap.tssi_table.VHT[4].MCS_Power = pAd->chipCap.tssi_table.HT[4].MCS_Power;
	pAd->chipCap.tssi_table.HT[5].MCS_Power = (CHAR)(reg_val&0x3F);
	if ( pAd->chipCap.tssi_table.HT[5].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.HT[5].MCS_Power -= 64;
	pAd->chipCap.tssi_table.VHT[5].MCS_Power = pAd->chipCap.tssi_table.HT[5].MCS_Power;
	pAd->chipCap.tssi_table.HT[6].MCS_Power = (CHAR)((reg_val&0x3F00)>>8);
	if ( pAd->chipCap.tssi_table.HT[6].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.HT[6].MCS_Power -= 64;
	pAd->chipCap.tssi_table.VHT[6].MCS_Power = pAd->chipCap.tssi_table.HT[6].MCS_Power;

	RTMP_IO_READ32(pAd, TX_PWR_CFG_3, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_3, reg_val));
	pAd->chipCap.tssi_table.STBC[0].MCS_Power = (CHAR)((reg_val&0x3F0000)>>16);
	if ( pAd->chipCap.tssi_table.STBC[0].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.STBC[0].MCS_Power -= 64;
	pAd->chipCap.tssi_table.STBC[1].MCS_Power = (CHAR)((reg_val&0x3F0000)>>16);
	if ( pAd->chipCap.tssi_table.STBC[1].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.STBC[1].MCS_Power -= 64;
	pAd->chipCap.tssi_table.STBC[2].MCS_Power = (CHAR)((reg_val&0x3F000000)>>24);
	if ( pAd->chipCap.tssi_table.STBC[2].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.STBC[2].MCS_Power -= 64;
	pAd->chipCap.tssi_table.STBC[3].MCS_Power = (CHAR)((reg_val&0x3F000000)>>24);
	if ( pAd->chipCap.tssi_table.STBC[3].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.STBC[3].MCS_Power -= 64;

	RTMP_IO_READ32(pAd, TX_PWR_CFG_4, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_4, reg_val));
	pAd->chipCap.tssi_table.STBC[4].MCS_Power = (CHAR)(reg_val&0x3F);
	if ( pAd->chipCap.tssi_table.STBC[4].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.STBC[4].MCS_Power -= 64;
	pAd->chipCap.tssi_table.STBC[5].MCS_Power = (CHAR)(reg_val&0x3F);
	if ( pAd->chipCap.tssi_table.STBC[5].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.STBC[5].MCS_Power -= 64;
	pAd->chipCap.tssi_table.STBC[6].MCS_Power = (CHAR)((reg_val&0x3F00)>>8);
	if ( pAd->chipCap.tssi_table.STBC[6].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.STBC[6].MCS_Power -= 64;

	RTMP_IO_READ32(pAd, TX_PWR_CFG_7, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_7, reg_val));
	pAd->chipCap.tssi_table.OFDM[7].MCS_Power = (CHAR)(reg_val&0x3F);
	if ( pAd->chipCap.tssi_table.OFDM[7].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.OFDM[7].MCS_Power -= 64;
	pAd->chipCap.tssi_table.HT[7].MCS_Power = (CHAR)((reg_val&0x3F0000)>>16);
	if ( pAd->chipCap.tssi_table.HT[7].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.HT[7].MCS_Power -= 64;
	pAd->chipCap.tssi_table.VHT[0].MCS_Power = pAd->chipCap.tssi_table.HT[7].MCS_Power;

	RTMP_IO_READ32(pAd, TX_PWR_CFG_8, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_8, reg_val));
	pAd->chipCap.tssi_table.VHT[8].MCS_Power = (CHAR)((reg_val&0x3F0000)>>16);;
	if ( pAd->chipCap.tssi_table.VHT[8].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.VHT[8].MCS_Power -= 64;
	pAd->chipCap.tssi_table.VHT[9].MCS_Power = (CHAR)((reg_val&0x3F000000)>>24);;
	if ( pAd->chipCap.tssi_table.VHT[9].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.VHT[9].MCS_Power -= 64;

	RTMP_IO_READ32(pAd, TX_PWR_CFG_9, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", TX_PWR_CFG_9, reg_val));
	pAd->chipCap.tssi_table.STBC[7].MCS_Power = (CHAR)(reg_val&0x3F);
	if ( pAd->chipCap.tssi_table.STBC[7].MCS_Power & 0x20 ) // > 32
		pAd->chipCap.tssi_table.STBC[7].MCS_Power -= 64;

	DBGPRINT(RT_DEBUG_TRACE, ("\n"));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.CCK[0].MCS_Power = %d\n", pAd->chipCap.tssi_table.CCK[0].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.CCK[1].MCS_Power = %d\n", pAd->chipCap.tssi_table.CCK[1].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.CCK[2].MCS_Power = %d\n", pAd->chipCap.tssi_table.CCK[2].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.CCK[3].MCS_Power = %d\n", pAd->chipCap.tssi_table.CCK[3].MCS_Power));

	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[0].MCS_Power = %d\n", pAd->chipCap.tssi_table.OFDM[0].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[1].MCS_Power = %d\n", pAd->chipCap.tssi_table.OFDM[1].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[2].MCS_Power = %d\n", pAd->chipCap.tssi_table.OFDM[2].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[3].MCS_Power = %d\n", pAd->chipCap.tssi_table.OFDM[3].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[4].MCS_Power = %d\n", pAd->chipCap.tssi_table.OFDM[4].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[5].MCS_Power = %d\n", pAd->chipCap.tssi_table.OFDM[5].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[6].MCS_Power = %d\n", pAd->chipCap.tssi_table.OFDM[6].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[7].MCS_Power = %d\n", pAd->chipCap.tssi_table.OFDM[7].MCS_Power));

	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[0].MCS_Power = %d\n", pAd->chipCap.tssi_table.STBC[0].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[1].MCS_Power = %d\n", pAd->chipCap.tssi_table.STBC[1].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[2].MCS_Power = %d\n", pAd->chipCap.tssi_table.STBC[2].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[3].MCS_Power = %d\n", pAd->chipCap.tssi_table.STBC[3].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[4].MCS_Power = %d\n", pAd->chipCap.tssi_table.STBC[4].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[5].MCS_Power = %d\n", pAd->chipCap.tssi_table.STBC[5].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[6].MCS_Power = %d\n", pAd->chipCap.tssi_table.STBC[6].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[7].MCS_Power = %d\n", pAd->chipCap.tssi_table.STBC[7].MCS_Power));

	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[0].MCS_Power = %d\n", pAd->chipCap.tssi_table.HT[0].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[1].MCS_Power = %d\n", pAd->chipCap.tssi_table.HT[1].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[2].MCS_Power = %d\n", pAd->chipCap.tssi_table.HT[2].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[3].MCS_Power = %d\n", pAd->chipCap.tssi_table.HT[3].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[4].MCS_Power = %d\n", pAd->chipCap.tssi_table.HT[4].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[5].MCS_Power = %d\n", pAd->chipCap.tssi_table.HT[5].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[6].MCS_Power = %d\n", pAd->chipCap.tssi_table.HT[6].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[7].MCS_Power = %d\n", pAd->chipCap.tssi_table.HT[7].MCS_Power));

	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[0].MCS_Power = %d\n", pAd->chipCap.tssi_table.VHT[0].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[1].MCS_Power = %d\n", pAd->chipCap.tssi_table.VHT[1].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[2].MCS_Power = %d\n", pAd->chipCap.tssi_table.VHT[2].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[3].MCS_Power = %d\n", pAd->chipCap.tssi_table.VHT[3].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[4].MCS_Power = %d\n", pAd->chipCap.tssi_table.VHT[4].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[5].MCS_Power = %d\n", pAd->chipCap.tssi_table.VHT[5].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[6].MCS_Power = %d\n", pAd->chipCap.tssi_table.VHT[6].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[7].MCS_Power = %d\n", pAd->chipCap.tssi_table.VHT[7].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[8].MCS_Power = %d\n", pAd->chipCap.tssi_table.VHT[8].MCS_Power));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[9].MCS_Power = %d\n", pAd->chipCap.tssi_table.VHT[9].MCS_Power));

	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.MCS32.MCS_Power = %d\n", pAd->chipCap.tssi_table.MCS32.MCS_Power));

	// PA MODE
	RTMP_IO_READ32(pAd, RF_PA_MODE_CFG0, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", RF_PA_MODE_CFG0, reg_val));
	pAd->chipCap.tssi_table.CCK[0].RF_PA_Mode = (UCHAR)(reg_val&0x00000003);
	pAd->chipCap.tssi_table.CCK[1].RF_PA_Mode = (UCHAR)((reg_val&0x0000000C)>>2);
	pAd->chipCap.tssi_table.CCK[2].RF_PA_Mode = (UCHAR)((reg_val&0x00000030)>>4);
	pAd->chipCap.tssi_table.CCK[3].RF_PA_Mode = (UCHAR)((reg_val&0x000000C0)>>6);
	pAd->chipCap.tssi_table.OFDM[0].RF_PA_Mode = (UCHAR)((reg_val&0x00000300)>>8);
	pAd->chipCap.tssi_table.OFDM[1].RF_PA_Mode = (UCHAR)((reg_val&0x00000C00)>>10);
	pAd->chipCap.tssi_table.OFDM[2].RF_PA_Mode = (UCHAR)((reg_val&0x00003000)>>12);
	pAd->chipCap.tssi_table.OFDM[3].RF_PA_Mode = (UCHAR)((reg_val&0x0000C000)>>14);
	pAd->chipCap.tssi_table.OFDM[4].RF_PA_Mode = (UCHAR)((reg_val&0x00030000)>>16);
	pAd->chipCap.tssi_table.OFDM[5].RF_PA_Mode = (UCHAR)((reg_val&0x000C0000)>>18);
	pAd->chipCap.tssi_table.OFDM[6].RF_PA_Mode = (UCHAR)((reg_val&0x00300000)>>20);
	pAd->chipCap.tssi_table.OFDM[7].RF_PA_Mode = (UCHAR)((reg_val&0x00C00000)>>22);
	pAd->chipCap.tssi_table.MCS32.RF_PA_Mode = (UCHAR)((reg_val&0x03000000)>>24);

	RTMP_IO_READ32(pAd, RF_PA_MODE_CFG1, &reg_val);
	DBGPRINT(RT_DEBUG_TRACE, ("0x%x: 0x%x\n", RF_PA_MODE_CFG1, reg_val));
	pAd->chipCap.tssi_table.HT[0].RF_PA_Mode = (UCHAR)(reg_val&0x00000003);
	pAd->chipCap.tssi_table.VHT[0].RF_PA_Mode = pAd->chipCap.tssi_table.HT[0].RF_PA_Mode;
	pAd->chipCap.tssi_table.HT[1].RF_PA_Mode = (UCHAR)((reg_val&0x0000000C)>>2);
	pAd->chipCap.tssi_table.VHT[1].RF_PA_Mode = pAd->chipCap.tssi_table.HT[1].RF_PA_Mode;
	pAd->chipCap.tssi_table.HT[2].RF_PA_Mode = (UCHAR)((reg_val&0x00000030)>>4);
	pAd->chipCap.tssi_table.VHT[2].RF_PA_Mode = pAd->chipCap.tssi_table.HT[2].RF_PA_Mode;
	pAd->chipCap.tssi_table.HT[3].RF_PA_Mode = (UCHAR)((reg_val&0x000000C0)>>6);
	pAd->chipCap.tssi_table.VHT[3].RF_PA_Mode = pAd->chipCap.tssi_table.HT[3].RF_PA_Mode;
	pAd->chipCap.tssi_table.HT[4].RF_PA_Mode = (UCHAR)((reg_val&0x00000300)>>8);
	pAd->chipCap.tssi_table.VHT[4].RF_PA_Mode = pAd->chipCap.tssi_table.HT[4].RF_PA_Mode;
	pAd->chipCap.tssi_table.HT[5].RF_PA_Mode = (UCHAR)((reg_val&0x00000C00)>>10);
	pAd->chipCap.tssi_table.VHT[5].RF_PA_Mode = pAd->chipCap.tssi_table.HT[5].RF_PA_Mode;
	pAd->chipCap.tssi_table.HT[6].RF_PA_Mode = (UCHAR)((reg_val&0x00003000)>>12);
	pAd->chipCap.tssi_table.VHT[6].RF_PA_Mode = pAd->chipCap.tssi_table.HT[6].RF_PA_Mode;
	pAd->chipCap.tssi_table.HT[7].RF_PA_Mode = (UCHAR)((reg_val&0x0000C000)>>14);
	pAd->chipCap.tssi_table.VHT[7].RF_PA_Mode = pAd->chipCap.tssi_table.HT[7].RF_PA_Mode;
	pAd->chipCap.tssi_table.VHT[8].RF_PA_Mode = (UCHAR)((reg_val&0x00030000)>>16);
	pAd->chipCap.tssi_table.VHT[9].RF_PA_Mode = (UCHAR)((reg_val&0x000C0000)>>18);

	DBGPRINT(RT_DEBUG_TRACE, ("\n"));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.CCK[0].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.CCK[0].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.CCK[1].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.CCK[1].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.CCK[2].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.CCK[2].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.CCK[3].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.CCK[3].RF_PA_Mode));

	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[0].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.OFDM[0].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[1].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.OFDM[1].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[2].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.OFDM[2].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[3].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.OFDM[3].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[4].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.OFDM[4].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[5].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.OFDM[5].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[6].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.OFDM[6].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.OFDM[7].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.OFDM[7].RF_PA_Mode));

	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[0].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.STBC[0].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[1].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.STBC[1].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[2].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.STBC[2].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[3].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.STBC[3].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[4].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.STBC[4].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[5].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.STBC[5].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[6].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.STBC[6].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.STBC[7].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.STBC[7].RF_PA_Mode));

	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[0].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.HT[0].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[1].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.HT[1].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[2].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.HT[2].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[3].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.HT[3].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[4].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.HT[4].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[5].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.HT[5].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[6].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.HT[6].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.HT[7].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.HT[7].RF_PA_Mode));

	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[0].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.VHT[0].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[1].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.VHT[1].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[2].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.VHT[2].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[3].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.VHT[3].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[4].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.VHT[4].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[5].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.VHT[5].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[6].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.VHT[6].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[7].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.VHT[7].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[8].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.VHT[8].RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.VHT[9].RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.VHT[9].RF_PA_Mode));

	DBGPRINT(RT_DEBUG_TRACE, ("TSSI: TssiTable.MCS32.RF_PA_Mode = %d\n", pAd->chipCap.tssi_table.MCS32.RF_PA_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("\n"));
}

VOID MT76x0_TSSI_DC_Calibration(
	IN  RTMP_ADAPTER *pAd)
{
	UCHAR RF_Value;
	UINT32 MAC_Value, BBP_Value;
	USHORT i = 0;

	if( pAd->hw_cfg.cent_ch > 14 )
	{
		rlt_rf_read(pAd, RF_BANK0, RF_R67, &RF_Value);
		RF_Value &= 0xF0;
		rlt_rf_write(pAd, RF_BANK0, RF_R67, RF_Value);
	}

	// Enable 9bit I channel ADC and get TSSI DC point from BBP
	{
		// Bypass ADDA controls
		MAC_Value = 0x60002237;
		RTMP_IO_WRITE32(pAd, RF_SETTING_0, MAC_Value);
		MAC_Value = 0xFFFFFFFF;
		RTMP_IO_WRITE32(pAd, RF_BYPASS_0, MAC_Value);

		//********************************************************************//
		// BBP Soft Reset
		RTMP_IO_READ32(pAd, CORE_R4, &BBP_Value);
		BBP_Value |= 0x00000001;
		RTMP_IO_WRITE32(pAd, CORE_R4, BBP_Value);

		RTMPusecDelay(1);

		RTMP_IO_READ32(pAd, CORE_R4, &BBP_Value);
		BBP_Value &= 0xFFFFFFFE;
		RTMP_IO_WRITE32(pAd, CORE_R4, BBP_Value);
		//********************************************************************//

		if( pAd->hw_cfg.cent_ch > 14 )
		{
			// EXT TSSI
			// Set avg mode on Q channel
			BBP_Value = 0x00080055;
			RTMP_IO_WRITE32(pAd, CORE_R34, BBP_Value);
		}
		else
		{
			// Set avg mode on I channel
			BBP_Value = 0x00080050;
			RTMP_IO_WRITE32(pAd, CORE_R34, BBP_Value);
		}

        // Enable TX with 0 DAC inputs
        BBP_Value = 0x80000000;
		RTMP_IO_WRITE32(pAd, TXBE_R6, BBP_Value);

		// Wait until avg done
		do
		{
			RTMP_IO_READ32(pAd, CORE_R34, &BBP_Value);

			if ( (BBP_Value&0x10) == 0 )
				break;

			i++;
			if ( i >= 100 )
				break;

			RTMPusecDelay(10);

		} while (TRUE);

		// Read TSSI value
		RTMP_IO_READ32(pAd, CORE_R35, &BBP_Value);
		pAd->chipCap.tssi_current_DC = (CHAR)(BBP_Value&0xFF);

		// stop bypass ADDA
		//              MAC_Value = 0x0;
		//              rtmp.HwMemoryWriteDword(RA_RF_SETTING_0, MAC_Value, 4);
		MAC_Value = 0x0;
		RTMP_IO_WRITE32(pAd, RF_BYPASS_0, MAC_Value);

		// Stop TX
		BBP_Value = 0x0;
		RTMP_IO_WRITE32(pAd, TXBE_R6, BBP_Value);

		//********************************************************************//
		// BBP Soft Reset
		RTMP_IO_READ32(pAd, CORE_R4, &BBP_Value);
		BBP_Value |= 0x00000001;
		RTMP_IO_WRITE32(pAd, CORE_R4, BBP_Value);

		RTMPusecDelay(1);

		RTMP_IO_READ32(pAd, CORE_R4, &BBP_Value);
		BBP_Value &= 0xFFFFFFFE;
		RTMP_IO_WRITE32(pAd, CORE_R4, BBP_Value);
		//********************************************************************//
	}

	// Restore
	{
		if( pAd->hw_cfg.cent_ch > 14 )
		{
			// EXT TSSI
			// Reset tssi_cal

			rlt_rf_read(pAd, RF_BANK0, RF_R67, &RF_Value);
			RF_Value &= 0xF0;
			RF_Value |= 0x04;
			rlt_rf_write(pAd, RF_BANK0, RF_R67, RF_Value);

		}
	}

	DBGPRINT(RT_DEBUG_TRACE, ("%s(): Current_TSSI_DC = %d\n", __FUNCTION__, pAd->chipCap.tssi_current_DC));
}

BOOLEAN MT76x0_Enable9BitIchannelADC(
	IN  RTMP_ADAPTER *pAd,
	IN  UCHAR Channel,
	IN  SHORT *pTSSI_Linear)
{
	UINT32 bbp_val;
	UINT32 MTxCycle = 0;

	DBGPRINT(RT_DEBUG_TRACE, ("%s(): Channel = %d\n", __FUNCTION__, Channel));

	if(Channel > 14)
	{
		/*
			EXT TSSI
			Set avg mode on Q channel
		*/
		bbp_val = 0x00080055;
	}
	else
	{
		/*
			Set avg mode on I channel
		*/
		bbp_val = 0x00080050;
	}

	RTMP_BBP_IO_WRITE32(pAd, CORE_R34, bbp_val);

	/*
		Wait until it's done
		wait until 0x2088[4] = 0
	*/
	for (MTxCycle = 0; MTxCycle < 200; MTxCycle++)
	{
		RTMP_BBP_IO_READ32(pAd, CORE_R34, &bbp_val);
		if ((bbp_val & 0x10) == 0)
			break;
		RTMPusecDelay(10);
	}

	if (MTxCycle == 100)
	{
		DBGPRINT(RT_DEBUG_TRACE, ("%s: We cannot wait too long, give up!\n", __FUNCTION__));
		bbp_val &= ~(0x10);
		RTMP_BBP_IO_WRITE32(pAd, CORE_R34, bbp_val);
		return FALSE;
	}
	
	/* 
		Read TSSI value 
	*/
	RTMP_BBP_IO_READ32(pAd, CORE_R35, &bbp_val);

	*pTSSI_Linear = (CHAR)(bbp_val&0xFF);
	DBGPRINT(RT_DEBUG_TRACE, ("%s: CORE_R35 = 0x%X, TSSI_Linear = (CHAR)(BBP_Value&0xFF) = 0x%X\n", __FUNCTION__, bbp_val, *pTSSI_Linear));

	if (Channel > 14)
	{
		*pTSSI_Linear = *pTSSI_Linear + 128;
		DBGPRINT(RT_DEBUG_TRACE, ("%s: TSSI_Linear = TSSI_Linear + 128 = 0x%X\n", __FUNCTION__, *pTSSI_Linear));
	}

	/*
		Set Packet Info#1 mode
	*/
	bbp_val = 0x00080041;
	RTMP_BBP_IO_WRITE32(pAd, CORE_R34, bbp_val);

	/*
		Read Info #1
	*/
	RTMP_BBP_IO_READ32(pAd, CORE_R35, &bbp_val);
	pAd->chipCap.tssi_info_1 = (UCHAR)(bbp_val&0xFF);

    /*
    	Set Packet Info#2 mode
    */
    bbp_val = 0x00080042;
	RTMP_BBP_IO_WRITE32(pAd, CORE_R34, bbp_val);

	/*
		Read Info #2
	*/
	RTMP_BBP_IO_READ32(pAd, CORE_R35, &bbp_val);
	pAd->chipCap.tssi_info_2 = (UCHAR)(bbp_val&0xFF);

	/*
		Set Packet Info#3 mode
	*/
	bbp_val = 0x00080043;
	RTMP_BBP_IO_WRITE32(pAd, CORE_R34, bbp_val);

	/* 
		Read Info #3
	*/
	RTMP_BBP_IO_READ32(pAd, CORE_R35, &bbp_val);
	pAd->chipCap.tssi_info_3 = (UCHAR)(bbp_val&0xFF);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: TSSI_Linear = 0x%X\n", __FUNCTION__, *pTSSI_Linear));
	DBGPRINT(RT_DEBUG_TRACE, ("%s: INFO_1 = 0x%X\n", __FUNCTION__, pAd->chipCap.tssi_info_1));
	DBGPRINT(RT_DEBUG_TRACE, ("%s: INFO_2 = 0x%X\n", __FUNCTION__, pAd->chipCap.tssi_info_2));
	DBGPRINT(RT_DEBUG_TRACE, ("%s: INFO_3 = 0x%X\n", __FUNCTION__, pAd->chipCap.tssi_info_3));
	return TRUE;
}

BOOLEAN MT76x0_GetTargetPower(
	IN  RTMP_ADAPTER *pAd,
	IN  CHAR *pTSSI_Tx_Mode,
	IN  CHAR *pTargetPower,
	IN  CHAR *pTargetPA_mode)
{
	UCHAR Tx_Rate, CurrentPower0;
	USHORT index;
	UINT32 reg_val = 0;
	CHAR Eas_power_adj = 0;

	RTMP_IO_READ32(pAd, TX_ALC_CFG_0, &reg_val);
	CurrentPower0 = (UCHAR)(reg_val&0x3F);

	*pTSSI_Tx_Mode = (pAd->chipCap.tssi_info_1 & 0x7);
	Eas_power_adj = (pAd->chipCap.tssi_info_3 & 0xF);

	if (*pTSSI_Tx_Mode == 0)
	{
		/*
			0: 1 Mbps, 1: 2 Mbps, 2: 5.5 Mbps, 3: 11 Mbps
		*/
		Tx_Rate = ((pAd->chipCap.tssi_info_1 & 0x60) >> 5);

		if (Tx_Rate > 3)
		{
			DBGPRINT(RT_DEBUG_ERROR, ("%s ==> CCK Mode :: Unknown Tx_Rate = %d, return here.\n", __FUNCTION__, Tx_Rate));
			return FALSE;
		}

		*pTargetPower = (CHAR)(CurrentPower0 + pAd->chipCap.tssi_table.CCK[Tx_Rate].MCS_Power);
		*pTargetPA_mode = (CHAR) pAd->chipCap.tssi_table.CCK[Tx_Rate].RF_PA_Mode;

		DBGPRINT(RT_DEBUG_TRACE, ("==> CCK Mode :: TargetPower = %d\n", *pTargetPower));
	}
	else if (*pTSSI_Tx_Mode == 1)
	{
		Tx_Rate = ((pAd->chipCap.tssi_info_1 & 0xF0) >> 4);
		if ( Tx_Rate == 0xB )
			index = 0;
		else if ( Tx_Rate == 0xF )
			index = 1;
		else if ( Tx_Rate == 0xA )
			index = 2;
		else if ( Tx_Rate == 0xE )
			index = 3;
		else if ( Tx_Rate == 0x9 )
			index = 4;
		else if ( Tx_Rate == 0xD )
			index = 5;
		else if ( Tx_Rate == 0x8 )
			index = 6;
		else if ( Tx_Rate == 0xC )
			index = 7;
		else
		{
			DBGPRINT(RT_DEBUG_ERROR, ("%s ==> OFDM Mode :: Unknown Tx_Rate = 0x%x, return here.\n", __FUNCTION__, Tx_Rate));
			return FALSE;
		}

		*pTargetPower = (CHAR)(CurrentPower0 + pAd->chipCap.tssi_table.OFDM[index].MCS_Power);
		*pTargetPA_mode = pAd->chipCap.tssi_table.OFDM[index].RF_PA_Mode;

		DBGPRINT(RT_DEBUG_TRACE, ("==> OFDM Mode :: TargetPower0 = %d\n", *pTargetPower));
	}
	else if (*pTSSI_Tx_Mode == 4)
	{
		Tx_Rate = (pAd->chipCap.tssi_info_2 & 0x0F);

		if (Tx_Rate > 9)
		{
			DBGPRINT(RT_DEBUG_ERROR, ("%s ==> VHT Mode :: Unknown Tx_Rate = %d, return here.\n", __FUNCTION__, Tx_Rate));
			return FALSE;
		}

		DBGPRINT(RT_DEBUG_TRACE, ("==> VHT Mode :: CurrentPower0 = %d, pAd->chipCap.tssi_table.VHT[%d].MCS_Power = %d\n", 
			CurrentPower0, Tx_Rate, pAd->chipCap.tssi_table.VHT[Tx_Rate].MCS_Power));
		
		*pTargetPower = (CHAR)(CurrentPower0 + pAd->chipCap.tssi_table.VHT[Tx_Rate].MCS_Power);
		*pTargetPA_mode = (CHAR) pAd->chipCap.tssi_table.VHT[Tx_Rate].RF_PA_Mode;
		
		DBGPRINT(RT_DEBUG_TRACE, ("==> VHT Mode :: TargetPower0 = %d\n", *pTargetPower));
	}
    else
    {
		Tx_Rate = (pAd->chipCap.tssi_info_2 & 0x7F);

		if ( Tx_Rate == 32 ) // MCS32
		{
			*pTargetPower = (CHAR)(CurrentPower0 + pAd->chipCap.tssi_table.MCS32.MCS_Power);
			*pTargetPA_mode = pAd->chipCap.tssi_table.MCS32.RF_PA_Mode;

		}
		else
		{
			if (Tx_Rate > 9)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("%s ==> HT Mode :: Unknown Tx_Rate = %d, return here.\n", __FUNCTION__, Tx_Rate));
				return FALSE;
			}
			
			*pTargetPower = (CHAR)(CurrentPower0 + pAd->chipCap.tssi_table.HT[Tx_Rate].MCS_Power);
			*pTargetPA_mode = pAd->chipCap.tssi_table.HT[Tx_Rate].RF_PA_Mode;
		}
		DBGPRINT(RT_DEBUG_TRACE, ("==> HT Mode :: TargetPower0 = %d\n", *pTargetPower));
		return TRUE;
	}
	return TRUE;
}

VOID MT76x0_EstimateDeltaPower(
	IN  RTMP_ADAPTER *pAd,
	IN  CHAR TSSI_Tx_Mode,
	IN  SHORT TSSI_Linear,
	IN  CHAR TargetPower,
	IN  CHAR TargetPA_mode,
	IN  INT *tssi_delta0)
{
	INT tssi_slope=0;
	INT tssi_offset=0;
	INT tssi_target=0, tssi_delta_tmp;
	INT tssi_meas=0;
	INT tssi_dc;
	INT pkt_type_delta=0, bbp_6db_power=0;
	UINT32 BBP_Value;
	CHAR idx = 0;

	// a.  tssi_dc gotten from Power on calibration

	// b.  Read Slope: u.2.6 (MT7601)
	// c.  Read offset: s.3.4 (MT7601)
	if (pAd->hw_cfg.cent_ch > 14)
	{
		for (idx = 0; idx < 7; idx++)
		{
			if ((pAd->hw_cfg.cent_ch <= pAd->chipCap.tssi_5G_channel_boundary[idx])
				|| (pAd->chipCap.tssi_5G_channel_boundary[idx] == 0))
			{
				tssi_slope = pAd->chipCap.tssi_slope_5G[idx];
				tssi_offset = pAd->chipCap.tssi_offset_5G[idx];
				DBGPRINT(RT_DEBUG_TRACE, ("==> tssi_5G_channel_boundary[%d] = %d\n", idx, pAd->chipCap.tssi_5G_channel_boundary[idx]));
				DBGPRINT(RT_DEBUG_TRACE, ("==> tssi_slope_5G[%d] = %d\n", idx, pAd->chipCap.tssi_slope_5G[idx]));
				DBGPRINT(RT_DEBUG_TRACE, ("==> tssi_offset_5G[%d] = %d\n", idx, pAd->chipCap.tssi_offset_5G[idx]));
				DBGPRINT(RT_DEBUG_TRACE, ("==> tssi_slope = %d\n", tssi_slope));
				DBGPRINT(RT_DEBUG_TRACE, ("==> tssi_offset = %d\n", tssi_offset));
				break;
			}
		}
		if (idx == 7)
		{
			tssi_slope = pAd->chipCap.tssi_slope_5G[idx];
			tssi_offset = pAd->chipCap.tssi_offset_5G[idx];
			DBGPRINT(RT_DEBUG_TRACE, ("==> tssi_slope_5G[%d] = %d\n", idx, tssi_slope));
			DBGPRINT(RT_DEBUG_TRACE, ("==> tssi_offset_5G[%d] = %d\n", idx, tssi_offset));
		}
	}
	else
	{
		tssi_slope = pAd->chipCap.tssi_slope_2G;
		tssi_offset = pAd->chipCap.tssi_offset_2G;
	}

	DBGPRINT(RT_DEBUG_TRACE, ("==> 1) tssi_offset0 = %d (0x%x)\n", tssi_offset, tssi_offset));

	DBGPRINT(RT_DEBUG_TRACE, ("\n"));
	DBGPRINT(RT_DEBUG_TRACE, ("==> EstimateDeltaPower\n"));
	DBGPRINT(RT_DEBUG_TRACE, ("==> TSSI_Tx_Mode = %d\n", TSSI_Tx_Mode));
	DBGPRINT(RT_DEBUG_TRACE, ("==> TargetPower = %d\n", TargetPower));
	DBGPRINT(RT_DEBUG_TRACE, ("==> TSSI_Linear = %d\n", TSSI_Linear));
	DBGPRINT(RT_DEBUG_TRACE, ("==> Current_TSSI_DC = %d\n", pAd->chipCap.tssi_current_DC));
	DBGPRINT(RT_DEBUG_TRACE, ("==> tssi_slope0 = %d\n", tssi_slope));
	DBGPRINT(RT_DEBUG_TRACE, ("==> 2) tssi_offset0 = %d\n", tssi_offset));

	// d.
	// Cal delta0
	tssi_target = TargetPower*4096;
	DBGPRINT(RT_DEBUG_TRACE, ("\n"));
	DBGPRINT(RT_DEBUG_TRACE, ("==> (tssi_target = TargetPower0*4096) = %d\n", tssi_target));
	DBGPRINT(RT_DEBUG_TRACE, ("==> TargetPA_mode = %d\n", TargetPA_mode));
	
	switch(TargetPA_mode)
	{
		case 0: 
			tssi_target = tssi_target;
			DBGPRINT(RT_DEBUG_TRACE, ("==> (tssi_target = tssi_target) = %d\n", tssi_target));
			break;
		case 1: 
			if ( pAd->hw_cfg.cent_ch > 14 )
			{
				tssi_target = tssi_target + 0;
				DBGPRINT(RT_DEBUG_TRACE, ("==> (tssi_target = tssi_target + 0) = %d\n", tssi_target));
			}
			else
			{
				tssi_target = tssi_target + 29491; // 3.6 * 8192
				DBGPRINT(RT_DEBUG_TRACE, ("==> (tssi_target = tssi_target + 29491) = %d\n", tssi_target));
			}
			break;
		default: 
			tssi_target = tssi_target +  4424; // 0.54 * 8192
			DBGPRINT(RT_DEBUG_TRACE, ("==> (tssi_target = tssi_target +  4424) = %d\n", tssi_target));
			break;
	}

	RTMP_BBP_IO_READ32(pAd, CORE_R1, &BBP_Value);
	switch(TSSI_Tx_Mode)
	{
		case 0:
			/*
				CCK power offset	With Japan filter	Without Japan filter
				7630E				+2.3db (2.3 * 8192)	+1.5db (1.5 * 8192)
				Other project		+0.8db (0.8 * 8192)	+0db
			*/
			{
				if (BBP_Value&0x20)
					pkt_type_delta = 6554;//0.8 * 8192;
				else
					pkt_type_delta = 0;//0 * 8192;
			}
			break;
		default:
			pkt_type_delta = 0;
			break;
	}

	tssi_target = tssi_target + pkt_type_delta;

	RTMP_BBP_IO_READ32(pAd, TXBE_R4, &BBP_Value);
	DBGPRINT(RT_DEBUG_TRACE, ("==> TXBE_OFFSET+R4 = 0x%X\n", BBP_Value));
	switch( (BBP_Value&0x3) )
	{
		case 0: 
			bbp_6db_power = 0; 
			break;
		case 1: 
			bbp_6db_power = -49152; 
			break; //-6 dB*8192;
		case 2: 
			bbp_6db_power = -98304; 
			break; //-12 dB*8192;
		case 3: 
			bbp_6db_power = 49152; 
			break;  //6 dB*8192;
	}
	DBGPRINT(RT_DEBUG_TRACE, ("==> bbp_6db_power = %d\n", bbp_6db_power));
	
	tssi_target = tssi_target + bbp_6db_power;
	DBGPRINT(RT_DEBUG_TRACE, ("==> (tssi_target = tssi_target + bbp_6db_power) = %d\n", tssi_target));

	DBGPRINT(RT_DEBUG_TRACE, ("==> tssi_target = %d\n", tssi_target / 8192));
	tssi_dc = pAd->chipCap.tssi_current_DC;
	DBGPRINT(RT_DEBUG_TRACE, ("==> TSSI_Linear0 = %d\n", TSSI_Linear)); 
	DBGPRINT(RT_DEBUG_TRACE, ("==> tssi_dc = %d\n", tssi_dc)); 
	
	tssi_meas = lin2dBd( (TSSI_Linear - tssi_dc));
	DBGPRINT(RT_DEBUG_TRACE, ("==> Linear to dB = %d\n", tssi_meas)); 

	tssi_meas = tssi_meas *tssi_slope;
	DBGPRINT(RT_DEBUG_TRACE, ("==> dB x slope = %d (0x%x), tssi_offset = %d(0x%x)\n", tssi_meas, tssi_meas, tssi_offset, tssi_offset));
	DBGPRINT(RT_DEBUG_TRACE, ("==> (tssi_offset-50) = (%d)(0x%x)\n", (tssi_offset-50), (tssi_offset-50)));
	DBGPRINT(RT_DEBUG_TRACE, ("==> (tssi_offset-50)<< 10 = (%d)(0x%x)\n", ((tssi_offset-50) << 10), ((tssi_offset-50) << 10)));
	if( pAd->hw_cfg.cent_ch > 14 )
		tssi_meas += ((tssi_offset-50) << 10); // 5G: offset s4.3
	else
		tssi_meas += (tssi_offset << 9); // 2G: offset s3.4
	DBGPRINT(RT_DEBUG_TRACE, ("==> measure db = %d (0x%x) %d\n", tssi_meas, tssi_meas, tssi_meas/8192));

	tssi_delta_tmp = tssi_target - tssi_meas;
	DBGPRINT(RT_DEBUG_TRACE, ("==> delta db = %d\n", tssi_delta_tmp));

	DBGPRINT(RT_DEBUG_TRACE, ("\n"));
	DBGPRINT(RT_DEBUG_TRACE, ("==> TSSI_Linear0 = %d\n", TSSI_Linear));
	DBGPRINT(RT_DEBUG_TRACE, ("==> tssi_delta_tmp = %d\n", tssi_delta_tmp));

	if( pAd->hw_cfg.cent_ch > 14 )
	{
		if((TSSI_Linear > 254) && (tssi_delta_tmp > 0)) //upper saturate
			tssi_delta_tmp = 0;
	}
	else
	{
		if((TSSI_Linear > 126) && (tssi_delta_tmp > 0)) //upper saturate
			tssi_delta_tmp = 0;
		if(((TSSI_Linear - tssi_dc) < 1  ) && (tssi_delta_tmp < 0)) //lower saturate
			tssi_delta_tmp = 0;
	}

	// stablize the compensation value
	// if previous compensation result is better than current, skip the compensation
	if( ((pAd->chipCap.tssi_pre_delta_pwr^tssi_delta_tmp) < 0) 
		&& ((tssi_delta_tmp < 4096) && (tssi_delta_tmp > -4096))
		&& ((pAd->chipCap.tssi_pre_delta_pwr < 4096) && (pAd->chipCap.tssi_pre_delta_pwr > -4096)) )
	{
		if((tssi_delta_tmp>0)&&((tssi_delta_tmp +pAd->chipCap.tssi_pre_delta_pwr) <= 0))
		    tssi_delta_tmp = 0;
		else if((tssi_delta_tmp<0)&&((tssi_delta_tmp +pAd->chipCap.tssi_pre_delta_pwr) > 0))
		    tssi_delta_tmp = 0;
		else
		    pAd->chipCap.tssi_pre_delta_pwr = tssi_delta_tmp;
	}
	else
		pAd->chipCap.tssi_pre_delta_pwr = tssi_delta_tmp;

	DBGPRINT(RT_DEBUG_TRACE, ("==> TSSI_DELTA_PRE = %d\n", pAd->chipCap.tssi_pre_delta_pwr));
	DBGPRINT(RT_DEBUG_TRACE, ("==> tssi_delta_tmp = %d\n", tssi_delta_tmp));

	// make the compensate value to the nearest compensate code
	tssi_delta_tmp = tssi_delta_tmp + ((tssi_delta_tmp > 0 ) ? 2048 : -2048);
	DBGPRINT(RT_DEBUG_TRACE, ("==> delta db = %d\n", tssi_delta_tmp));
	tssi_delta_tmp = tssi_delta_tmp / 4096;
	DBGPRINT(RT_DEBUG_TRACE, ("==> delta db = %d\n", tssi_delta_tmp));

	*tssi_delta0 = *tssi_delta0 + tssi_delta_tmp;
	DBGPRINT(RT_DEBUG_TRACE, ("==> *tssi_delta0 = %d\n", *tssi_delta0));
	if(*tssi_delta0 > 31)
		*tssi_delta0 = 31;
	else if(*tssi_delta0 < -32)
		*tssi_delta0 = -32;

	DBGPRINT(RT_DEBUG_TRACE, ("\n"));
	DBGPRINT(RT_DEBUG_TRACE, ("==> tssi_delta0 = %d\n", *tssi_delta0));
	DBGPRINT(RT_DEBUG_TRACE, ("\n"));
}

VOID MT76x0_IntTxAlcProcess(
	IN  RTMP_ADAPTER *pAd)
{
	INT tssi_delta0 = 0;
	UINT32 reg_val = 0;
	CHAR tssi_write = 0;
	CHAR TargetPower = 0, TargetPA_mode = 0;
	SHORT TSSI_Linear = 0;
	CHAR TSSI_Tx_Mode = 0;

	if (MT76x0_Enable9BitIchannelADC(pAd, pAd->hw_cfg.cent_ch, &TSSI_Linear) == FALSE)
		return;

	if (MT76x0_GetTargetPower(pAd, &TSSI_Tx_Mode, &TargetPower, &TargetPA_mode) == FALSE)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s ==> Get target power failed, return here.\n", __FUNCTION__));
		return;
	}

	RTMP_IO_READ32(pAd, TX_ALC_CFG_1, &reg_val);
	DBGPRINT(RT_DEBUG_ERROR, ("(0x13B4) Before compensation 0x%08X\n", reg_val));
	tssi_delta0 = (CHAR)(reg_val&0x3F);
	if ( (tssi_delta0 &0x20) )
		tssi_delta0 -= 0x40;

	MT76x0_EstimateDeltaPower(pAd, TSSI_Tx_Mode, TSSI_Linear, TargetPower, TargetPA_mode, &tssi_delta0);

	tssi_write = tssi_delta0;

	reg_val &= 0xFFFFFFC0;
	reg_val |= (tssi_write&0x3F);
	DBGPRINT(RT_DEBUG_ERROR, ("%s ==> reg_val = 0x%08X\n", __FUNCTION__, reg_val));
	RTMP_IO_WRITE32(pAd, TX_ALC_CFG_1, reg_val);
	RTMP_IO_READ32(pAd, TX_ALC_CFG_1, &reg_val);
	DBGPRINT(RT_DEBUG_ERROR, ("(0x13B4) After compensation 0x%08X\n", reg_val));
}

#endif /* MT76x0_TSSI_CAL_COMPENSATION */
/******************************* TSSI end **********************************/


BOOLEAN mt76x0_get_tssi_report(
	IN PRTMP_ADAPTER pAd,
	IN BOOLEAN bResetTssiInfo,
	OUT PCHAR pTssiReport)
{
	UINT32 wait = 0, reg_val = 0;
	UCHAR rf_b7_73 = 0, rf_b0_66 = 0, rf_b0_67 = 0;
	BOOLEAN status;
	
	rlt_rf_read(pAd, RF_BANK7, RF_R73, &rf_b7_73);
	rlt_rf_read(pAd, RF_BANK0, RF_R66, &rf_b0_66);
	rlt_rf_read(pAd, RF_BANK0, RF_R67, &rf_b0_67);
	
	/*
		1. Set 0dB Gain:
			WIFI_RF_CR_WRITE(7,73,0x02) 
	*/
	rlt_rf_write(pAd, RF_BANK7, RF_R73, 0x02);

	/*
		2. Calibration Switches:
			WIFI_RF_CR_WRITE(0,66,0x23)
	*/
	rlt_rf_write(pAd, RF_BANK0, RF_R66, 0x23);

	/*
		3. Offset-measurement configuration:
			WIFI_RF_CR_WRITE(0,67,0x01)
	*/
	rlt_rf_write(pAd, RF_BANK0, RF_R67, 0x01);

	/*
		4. Select Level meter from ADC.q:
			WIFI_BBP_CR_WRITE(0x2088,0x00080055)
	*/
	RTMP_BBP_IO_WRITE32(pAd, CORE_R34, 0x00080055);

	/*
		5. Wait until it's done:
			wait until 0x2088[4] = 0
	*/
	for (wait = 0; wait < 2000; wait++) 
	{
		RTMP_BBP_IO_READ32(pAd, CORE_R34, &reg_val);
		if ((reg_val & 0x10) == 0)
			break;
		RTMPusecDelay(3);
	}

	if (wait >= 2000) {
		reg_val &= ~(0x10);
		RTMP_BBP_IO_WRITE32(pAd, CORE_R34, reg_val);
		status = FALSE;
		goto done;
	}

	/*
		6. Read Dout (0x0041208c<7:0>=adc_out<8:1>):
			WIFI_BBP_CR_READ(0x208c) //$Dout

	*/
	RTMP_BBP_IO_READ32(pAd, CORE_R35, &reg_val);
	reg_val &= 0xFF;
	if ((reg_val & 0x80) == 0x80) 
		reg_val |= 0xFFFFFF00; /* Negative number */
	*pTssiReport = reg_val;
	
	status = TRUE;

done:	
	/*
		Restore RF CR
			B7. R73, B0.R66, B0.R67
	*/
	rlt_rf_write(pAd, RF_BANK7, RF_R73, rf_b7_73);
	rlt_rf_write(pAd, RF_BANK0, RF_R66, rf_b0_66);
	rlt_rf_write(pAd, RF_BANK0, RF_R67, rf_b0_67);

	return status;
}


#ifdef SINGLE_SKU_V2
UCHAR MT76x0_GetSkuChannelBasePwr(
	IN PRTMP_ADAPTER 	pAd,
	IN UCHAR 			channel)
{
	CH_POWER *ch, *ch_temp;
	UCHAR base_pwr = pAd->DefaultTargetPwr;
	int i;
	
	DlListForEachSafe(ch, ch_temp, &pAd->SingleSkuPwrList, CH_POWER, List)
	{
		if (channel == ch->channel) {
			DBGPRINT(RT_DEBUG_TRACE, ("%s ==> channel = %d, ch->channel = %d\n", 
				__FUNCTION__, channel, ch->channel));
			
			if (channel <= 14) {
				for (i= 0 ; i < SINGLE_SKU_TABLE_CCK_LENGTH ; i++)
				{
					if ( base_pwr > ch->PwrCCK[i] )
						base_pwr = ch->PwrCCK[i];
				}
			}

			for (i= 0; i < SINGLE_SKU_TABLE_OFDM_LENGTH; i++)
			{
				if ( base_pwr > ch->PwrOFDM[i] )
					base_pwr = ch->PwrOFDM[i];
			}

			for (i= 0; i < SINGLE_SKU_TABLE_HT_LENGTH; i++)
			{
				if ( base_pwr > ch->PwrHT20[i] )
					base_pwr = ch->PwrHT20[i];
			}
				
			if (pAd->CommonCfg.BBPCurrentBW == BW_40) {
				for (i= 0; i < SINGLE_SKU_TABLE_HT_LENGTH; i++)
				{
					if (ch->PwrHT40[i] == 0)
						break;

					if (base_pwr > ch->PwrHT40[i])
						base_pwr = ch->PwrHT40[i];
				}
			}
			
			if (pAd->CommonCfg.BBPCurrentBW == BW_80) {
				for (i= 0; i < SINGLE_SKU_TABLE_VHT_LENGTH; i++)
				{
					if (ch->PwrVHT80[i] == 0)
						break;

					if ( base_pwr > ch->PwrVHT80[i] )
						base_pwr = ch->PwrVHT80[i];
				}
			}
			
			break;
		}
	}

	return base_pwr;

}

VOID MT76x0_WriteNewPerRatePwr(
	IN RTMP_ADAPTER 	*pAd)
{
	UINT32 data;
	UCHAR t1, t2, t3, t4;

	/* 
		Bit 29:24 -> OFDM 12M/18M
		Bit 21:16 -> OFDM 6M/9M
		Bit 13:8 -> CCK 5.5M/11M
		Bit 5:0 -> CCK 1M/2M
	*/
	t1 = pAd->chipCap.rate_pwr_table.CCK[0].MCS_Power;
	t1 = (t1 & 0x80) ? ((t1 & 0x1f) | 0x20) : (t1 & 0x3f);
	
	t2 = pAd->chipCap.rate_pwr_table.CCK[2].MCS_Power;
	t2 = (t2 & 0x80) ? ((t2 & 0x1f) | 0x20) : (t2 & 0x3f);

	t3 = pAd->chipCap.rate_pwr_table.OFDM[0].MCS_Power;
	t3 = (t3 & 0x80) ? ((t3 & 0x1f) | 0x20) : (t3 & 0x3f);
	
	t4 = pAd->chipCap.rate_pwr_table.OFDM[2].MCS_Power;
	t4 = (t4 & 0x80) ? ((t4 & 0x1f) | 0x20) : (t4 & 0x3f);
	data = (t4 << 24)|(t3 << 16)|(t2 << 8)|t1; 

	RTMP_IO_WRITE32(pAd, TX_PWR_CFG_0, data);
	RTMP_IO_READ32(pAd, TX_PWR_CFG_0, &data);
	DBGPRINT(RT_DEBUG_TRACE, ("%s - 0x%x: 0x%08X\n", __FUNCTION__, TX_PWR_CFG_0, data));

	/* 
		Bit 29:24 -> HT/VHT MCS 2/3
		Bit 21:16 -> HT/VHT MCS 0/1
		Bit 13:8 -> OFDM 48M
		Bit 5:0 -> OFDM 24M/36M
	*/	
	t1 = pAd->chipCap.rate_pwr_table.OFDM[4].MCS_Power;
	t1 = (t1 & 0x80) ? ((t1 & 0x1f) | 0x20) : (t1 & 0x3f);
	
	t2 = pAd->chipCap.rate_pwr_table.OFDM[6].MCS_Power;
	t2 = (t2 & 0x80) ? ((t2 & 0x1f) | 0x20) : (t2 & 0x3f);

	t3 = pAd->chipCap.rate_pwr_table.HT[0].MCS_Power;
	t3 = (t3 & 0x80) ? ((t3 & 0x1f) | 0x20) : (t3 & 0x3f);
	
	t4 = pAd->chipCap.rate_pwr_table.HT[2].MCS_Power;
	t4 = (t4 & 0x80) ? ((t4 & 0x1f) | 0x20) : (t4 & 0x3f);
	data = (t4 << 24)|(t3 << 16)|(t2 << 8)|t1; 

	RTMP_IO_WRITE32(pAd, TX_PWR_CFG_1, data);
	RTMP_IO_READ32(pAd, TX_PWR_CFG_1, &data);
	DBGPRINT(RT_DEBUG_TRACE, ("%s - 0x%x: 0x%08X\n", __FUNCTION__, TX_PWR_CFG_1, data));

	/*
		Bit 13:8 -> HT/VHT MCS 6
		Bit 5:0 -> HT/VHT MCS 4/5
	*/
	RTMP_IO_READ32(pAd, TX_PWR_CFG_2, &data);
	t1 = pAd->chipCap.rate_pwr_table.HT[4].MCS_Power;
	t1 = (t1 & 0x80) ? ((t1 & 0x1f) | 0x20) : (t1 & 0x3f);
	
	t2 = pAd->chipCap.rate_pwr_table.HT[6].MCS_Power;
	t2 = (t2 & 0x80) ? ((t2 & 0x1f) | 0x20) : (t2 & 0x3f);
	
	data &= 0xFFFF0000;
	data = (t2 << 8) | t1; 
	RTMP_IO_WRITE32(pAd, TX_PWR_CFG_2, data);
	RTMP_IO_READ32(pAd, TX_PWR_CFG_2, &data);
	DBGPRINT(RT_DEBUG_TRACE, ("%s - 0x%x: 0x%08X\n", __FUNCTION__, TX_PWR_CFG_2, data));

	/* 
		Bit 29:24 -> HT/VHT STBC MCS 2/3
		Bit 21:16 -> HT/VHT STBC MCS 0/1
	*/
	RTMP_IO_READ32(pAd, TX_PWR_CFG_3, &data);
	t3 = pAd->chipCap.rate_pwr_table.STBC[0].MCS_Power;
	t3 = (t3 & 0x80) ? ((t3 & 0x1f) | 0x20) : (t3 & 0x3f);
	
	t4 = pAd->chipCap.rate_pwr_table.STBC[2].MCS_Power;
	t4 = (t4 & 0x80) ? ((t4 & 0x1f) | 0x20) : (t4 & 0x3f);

	data &= 0xFFFF;
	data = (t4 << 24) | (t3 << 16);
	RTMP_IO_WRITE32(pAd, TX_PWR_CFG_3, data);
	RTMP_IO_READ32(pAd, TX_PWR_CFG_3, &data);
	DBGPRINT(RT_DEBUG_TRACE, ("%s - 0x%x: 0x%08X\n", __FUNCTION__, TX_PWR_CFG_3, data));

	/* 
		bit 13:8 -> HT/VHT STBC MCS 6
		bit 5:0 -> HT/VHT STBC MCS 4/5
	*/
	RTMP_IO_READ32(pAd, TX_PWR_CFG_4, &data);
	t1 = pAd->chipCap.rate_pwr_table.STBC[4].MCS_Power;
	t1 = (t1 & 0x80) ? ((t1 & 0x1f) | 0x20) : (t1 & 0x3f);
	
	t2 = pAd->chipCap.rate_pwr_table.STBC[6].MCS_Power;
	t2 = (t2 & 0x80) ? ((t2 & 0x1f) | 0x20) : (t2 & 0x3f);	

	data &= 0xFFFF0000;
	data = (t2 << 8) | t1; 
	RTMP_IO_WRITE32(pAd, TX_PWR_CFG_4, data);
	RTMP_IO_READ32(pAd, TX_PWR_CFG_4, &data);
	DBGPRINT(RT_DEBUG_TRACE, ("%s - 0x%x: 0x%08X\n", __FUNCTION__, TX_PWR_CFG_4, data));

	/* 
		Bit 21:16 -> HT/VHT MCS 7
		Bit 5:0 -> OFDM 54M
	*/
	RTMP_IO_READ32(pAd, TX_PWR_CFG_7, &data);
	t1 = pAd->chipCap.rate_pwr_table.OFDM[7].MCS_Power;
	t1 = (t1 & 0x80) ? ((t1 & 0x1f) | 0x20) : (t1 & 0x3f);
	
	t3 = pAd->chipCap.rate_pwr_table.HT[7].MCS_Power;
	t3 = (t3 & 0x80) ? ((t3 & 0x1f) | 0x20) : (t3 & 0x3f);

	data &= 0xFF00FF00;
	data = (t3 << 16) | t1; 
	RTMP_IO_WRITE32(pAd, TX_PWR_CFG_7, data);
	RTMP_IO_READ32(pAd, TX_PWR_CFG_7, &data);
	DBGPRINT(RT_DEBUG_TRACE, ("%s - 0x%x: 0x%08X\n", __FUNCTION__, TX_PWR_CFG_7, data));

	/* 
		Bit 29:24 -> VHT 1SS MCS 9
		Bit 21:16 -> VHT 1SS MCS 8
	*/
	RTMP_IO_READ32(pAd, TX_PWR_CFG_8, &data);
	t3 = pAd->chipCap.rate_pwr_table.VHT[8].MCS_Power;
	t3 = (t3 & 0x80) ? ((t3 & 0x1f) | 0x20) : (t3 & 0x3f);
	
	t4 = pAd->chipCap.rate_pwr_table.VHT[9].MCS_Power;
	t4 = (t4 & 0x80) ? ((t4 & 0x1f) | 0x20) : (t4 & 0x3f);

	data &= 0xFFFF;
	data = (t4 << 24) | (t3 << 16);
	RTMP_IO_WRITE32(pAd, TX_PWR_CFG_8, data);
	RTMP_IO_READ32(pAd, TX_PWR_CFG_8, &data);
	DBGPRINT(RT_DEBUG_TRACE, ("%s - 0x%x: 0x%08X\n", __FUNCTION__, TX_PWR_CFG_8, data));

	/* 
		Bit 5:0 -> HT/VHT STBC MCS 7
	*/
	RTMP_IO_READ32(pAd, TX_PWR_CFG_9, &data);
	t1= pAd->chipCap.rate_pwr_table.STBC[7].MCS_Power;
	t1 = (t1 & 0x80) ? ((t1 & 0x1f) | 0x20) : (t1 & 0x3f);

	data &= 0xFFFFFF00;
	data |= t1; 	
	RTMP_IO_WRITE32(pAd, TX_PWR_CFG_9, data);
	RTMP_IO_READ32(pAd, TX_PWR_CFG_9, &data);
	DBGPRINT(RT_DEBUG_TRACE, ("%s - 0x%x: 0x%08X\n", __FUNCTION__, TX_PWR_CFG_9, data));
}

UCHAR MT76x0_UpdateSkuPwr(
	IN PRTMP_ADAPTER 	pAd,
	IN UCHAR 			channel)
{
	CH_POWER *ch, *ch_temp;
	INT32 i, pwr_delta = 0;
	UINT32 reg_val; 
	UCHAR ch_init_pwr = 0;
	CHAR ch_delta_pwr = 0;
	INT32 rate_pwr = 0;
	BOOLEAN bFound = FALSE;
	CHAR SkuBasePwr;
	const CHAR DefaultTargetPwr = pAd->DefaultTargetPwr;

	/*
		Get channel initial transmission gain.
	*/
	RTMP_IO_READ32(pAd, TX_ALC_CFG_0, &reg_val);
	ch_init_pwr = (UCHAR)(reg_val & 0x3F);
	if ( ch_init_pwr & 0x20 )
		ch_init_pwr -= 64;	
	DBGPRINT(RT_DEBUG_TRACE, ("%s ==> 0x%08X = 0x%08X, ch_init_pwr = %d\n", __FUNCTION__, TX_ALC_CFG_0, reg_val, ch_init_pwr));

	RTMP_IO_READ32(pAd, TX_ALC_CFG_1, &reg_val);
	ch_delta_pwr = (UCHAR)(reg_val & 0x3F);
	if ( ch_delta_pwr & 0x20 )
		ch_delta_pwr -= 64;	
	DBGPRINT(RT_DEBUG_TRACE, ("%s ==> 0x%08X = 0x%08X, ch_delta_pwr = %d\n", __FUNCTION__, TX_ALC_CFG_1, reg_val, ch_delta_pwr));

	SkuBasePwr = MT76x0_GetSkuChannelBasePwr(pAd, channel);
	
	/*
		Read per rate power from EEPROM.
	*/
	mt76x0_read_per_rate_tx_pwr(pAd);
	/*
		Get per rate register setting.
	*/
	MT76x0_MakeUpRatePwrTable(pAd);
	
	DlListForEachSafe(ch, ch_temp, &pAd->SingleSkuPwrList, CH_POWER, List)
	{
		DBGPRINT(RT_DEBUG_TRACE, ("%s ==> channel = %d, ch->channel = %d\n", __FUNCTION__, channel, ch->channel));
		if (channel == ch->channel) {
			for (i = 0; i < SINGLE_SKU_TABLE_CCK_LENGTH; i++)
			{
				pwr_delta = 0;
				
				DBGPRINT(RT_DEBUG_TRACE, ("%s ==> CCK[%d].MCS_Power = %d, DefaultTargetPwr = %d, ch_delta_pwr = %d\n", 
					__FUNCTION__, i, pAd->chipCap.rate_pwr_table.CCK[i].MCS_Power, DefaultTargetPwr, ch_delta_pwr));

				rate_pwr = pAd->chipCap.rate_pwr_table.CCK[i].MCS_Power + DefaultTargetPwr + ch_delta_pwr;
				pwr_delta = rate_pwr - ch->PwrCCK[i];
				if ( pwr_delta > 0) //Power Exceed
					pAd->chipCap.rate_pwr_table.CCK[i].MCS_Power -= pwr_delta;

				DBGPRINT(RT_DEBUG_TRACE, ("%s ==> rate_pwr (%d) - ch->PwrCCK[%d] (%d) = rate_delta (%d)\n", 
					__FUNCTION__, rate_pwr, i, ch->PwrCCK[i], pwr_delta));
				
				DBGPRINT(RT_DEBUG_TRACE, ("%s ==> new CCK[%d].MCS_Power = %d\n\n", 
					__FUNCTION__, i, pAd->chipCap.rate_pwr_table.CCK[i].MCS_Power));
			}
			
			for (i = 0; i < SINGLE_SKU_TABLE_OFDM_LENGTH; i++)
			{
				pwr_delta = 0;

				DBGPRINT(RT_DEBUG_TRACE, ("%s ==> OFDM[%d].MCS_Power = %d, DefaultTargetPwr = %d, ch_delta_pwr = %d\n", 
					__FUNCTION__, i, pAd->chipCap.rate_pwr_table.OFDM[i].MCS_Power, DefaultTargetPwr, ch_delta_pwr));

				rate_pwr = pAd->chipCap.rate_pwr_table.OFDM[i].MCS_Power + DefaultTargetPwr + ch_delta_pwr;
				pwr_delta = rate_pwr - ch->PwrOFDM[i];
				if ( pwr_delta > 0) //Power Exceed
					pAd->chipCap.rate_pwr_table.OFDM[i].MCS_Power -= pwr_delta;

				DBGPRINT(RT_DEBUG_TRACE, ("%s ==> rate_pwr (%d) - ch->PwrOFDM[%d] (%d) = rate_delta (%d)\n", 
					__FUNCTION__, rate_pwr, i, ch->PwrOFDM[i], pwr_delta));
				
				DBGPRINT(RT_DEBUG_TRACE, ("%s ==> new OFDM[%d].MCS_Power = %d\n\n", 
					__FUNCTION__, i, pAd->chipCap.rate_pwr_table.OFDM[i].MCS_Power));
			}

			if (pAd->CommonCfg.BBPCurrentBW != BW_80) {
				for (i = 0; i < (SINGLE_SKU_TABLE_HT_LENGTH >> 1); i++)
				{
					pwr_delta = 0;
					rate_pwr = pAd->chipCap.rate_pwr_table.HT[i].MCS_Power + DefaultTargetPwr + ch_delta_pwr;

					DBGPRINT(RT_DEBUG_TRACE, ("%s ==> HT[%d].MCS_Power = %d, DefaultTargetPwr = %d, ch_delta_pwr = %d\n", 
						__FUNCTION__, i, pAd->chipCap.rate_pwr_table.HT[i].MCS_Power, DefaultTargetPwr, ch_delta_pwr));		
			
					if (pAd->CommonCfg.BBPCurrentBW == BW_20) {									
						pwr_delta = rate_pwr - ch->PwrHT20[i];

						DBGPRINT(RT_DEBUG_TRACE, ("%s ==> rate_pwr (%d) - ch->PwrHT20[%d] (%d) = rate_delta (%d)\n", 
							__FUNCTION__, rate_pwr, i, ch->PwrHT20[i], pwr_delta));
					
					} else if (pAd->CommonCfg.BBPCurrentBW == BW_40) {					
						pwr_delta = rate_pwr - ch->PwrHT40[i];

						DBGPRINT(RT_DEBUG_TRACE, ("%s ==> rate_pwr (%d) - ch->PwrHT40[%d] (%d) = rate_delta (%d)\n", 
							__FUNCTION__, rate_pwr, i, ch->PwrHT40[i], pwr_delta));
					}

					if ( pwr_delta > 0)
						pAd->chipCap.rate_pwr_table.HT[i].MCS_Power -= pwr_delta;
					
					DBGPRINT(RT_DEBUG_TRACE, ("%s ==> new HT[%d].MCS_Power = %d\n\n", 
						__FUNCTION__, i, pAd->chipCap.rate_pwr_table.HT[i].MCS_Power));
				}
			}else if (pAd->CommonCfg.BBPCurrentBW == BW_80) {
				for (i = 0; i < SINGLE_SKU_TABLE_VHT_LENGTH; i++)
				{
					pwr_delta = 0;
									
					DBGPRINT(RT_DEBUG_TRACE, ("%s ==> VHT[%d].MCS_Power = %d, DefaultTargetPwr = %d, ch_delta_pwr = %d\n", 
						__FUNCTION__, i, pAd->chipCap.rate_pwr_table.VHT[i].MCS_Power, DefaultTargetPwr, ch_delta_pwr));

					rate_pwr = pAd->chipCap.rate_pwr_table.VHT[i].MCS_Power + DefaultTargetPwr + ch_delta_pwr;

					if (pAd->CommonCfg.BBPCurrentBW == BW_80)
						pwr_delta = rate_pwr - ch->PwrVHT80[i];

					DBGPRINT(RT_DEBUG_TRACE, ("%s ==> rate_pwr (%d) - ch->PwrVHT80[%d] (%d) = rate_delta (%d)\n", 
						__FUNCTION__, rate_pwr, i, ch->PwrVHT80[i], pwr_delta));
				
					if (pwr_delta > 0) {
						pAd->chipCap.rate_pwr_table.VHT[i].MCS_Power -= pwr_delta;
						pAd->chipCap.rate_pwr_table.HT[i].MCS_Power = pAd->chipCap.rate_pwr_table.VHT[i].MCS_Power;
					}
					
					DBGPRINT(RT_DEBUG_TRACE, ("%s ==> new VHT[%d].MCS_Power = %d\n\n", 
						__FUNCTION__, i, pAd->chipCap.rate_pwr_table.VHT[i].MCS_Power));
				}
			}
			
			bFound = TRUE;
			break;
		}
	}

	if (bFound) {
		MT76x0_WriteNewPerRatePwr(pAd);
		return TRUE;
	}
	else
		return 0;
}
#endif /* SINGLE_SKU_V2 */


#ifdef RTMP_TEMPERATURE_TX_ALC
BOOLEAN get_temp_tx_alc_level(
	IN PRTMP_ADAPTER pAd,
	IN BOOLEAN enable_tx_alc,
	IN CHAR temp_ref,
	IN PCHAR temp_minus_bdy,
	IN PCHAR temp_plus_bdy,
	IN UINT8 max_bdy_level,
	IN UINT8 tx_alc_step,
	IN CHAR current_temp,
	OUT PCHAR comp_level)
{
	INT idx = 0;

	if ((temp_minus_bdy == NULL) || (temp_plus_bdy == NULL)) {
		DBGPRINT(RT_DEBUG_ERROR, ("%s(): temp table boundary is NULL\n", __FUNCTION__)); 
		return FALSE;
	}
	
	if (enable_tx_alc) {
		if (current_temp < temp_minus_bdy[1]) {
			/* 	
				Reading is larger than the reference value check
				for how large we need to decrease the Tx power		
			*/
			for (idx = 1; idx < max_bdy_level; idx++)
			{
				if (current_temp >= temp_minus_bdy[idx]) 
					break; /* level range found */
			}

			/* The index is the step we should decrease, idx = 0 means there is nothing to compensate */
			*comp_level = -(tx_alc_step * (idx-1));
			DBGPRINT(RT_DEBUG_TRACE, 
				("-- Tx Power:: current_temp=%d, temp_ref=%d, tx_alc_step=%d, step = -%d, comp_level = %d\n",
			    	current_temp, temp_ref, tx_alc_step, idx-1, *comp_level));                    
		} else if (current_temp > temp_plus_bdy[1]) {
			/*	
				Reading is smaller than the reference value check
				for how large we need to increase the Tx power		
			*/
			for (idx = 1; idx < max_bdy_level; idx++)
			{
				if (current_temp <= temp_plus_bdy[idx])
					break; /* level range found */
			}

			/* The index is the step we should increase, idx = 0 means there is nothing to compensate */
			*comp_level = tx_alc_step * (idx-1);
			DBGPRINT(RT_DEBUG_TRACE,
				("++ Tx Power:: current_temp=%d, temp_ref=%d, tx_alc_step=%d, step = +%d, , comp_level = %d\n",
				current_temp, temp_ref, tx_alc_step, idx-1, *comp_level));
		} else {
			*comp_level = 0;
			DBGPRINT(RT_DEBUG_TRACE,
				("  Tx Power:: current_temp=%d, temp_ref=%d, tx_alc_step=%d, step = +%d\n",
				current_temp, temp_ref, tx_alc_step, 0));
		}
	} else {
		DBGPRINT(RT_DEBUG_ERROR, ("%s(): enable_tx_alc = %s\n", 
			__FUNCTION__, (enable_tx_alc) == TRUE ? "TRUE" : "FALSE")); 
		return FALSE;
	}

	return TRUE;
}


void mt76x0_temp_tx_alc(PRTMP_ADAPTER pAd)
{
	BOOLEAN bResetTssiInfo = TRUE, enable_tx_alc;
	PUCHAR temp_minus_bdy, temp_plus_bdy, tx_alc_comp;
	UCHAR temp_ref;
	
	if ((pAd->CommonCfg.Channel > 14) ? 
		(pAd->bAutoTxAgcA == FALSE) : (pAd->bAutoTxAgcG == FALSE))
		return;

	if (pAd->CommonCfg.Channel <= 14) {
		/* Use group settings of G band */
		temp_ref = pAd->TssiRefG;
		enable_tx_alc = pAd->bAutoTxAgcG;
		tx_alc_comp = &pAd->TxAgcCompensateG;
		temp_minus_bdy = pAd->TssiMinusBoundaryG;
		temp_plus_bdy = pAd->TssiPlusBoundaryG;
	} else if (pAd->CommonCfg.Channel <= pAd->ChBndryIdx) {
		/* Use group#1 settings of A band */
		temp_ref = pAd->TssiRefA;
		enable_tx_alc = pAd->bAutoTxAgcA;
		tx_alc_comp = &pAd->TxAgcCompensateA;
		temp_minus_bdy = pAd->TssiMinusBoundaryA[0];
		temp_plus_bdy = pAd->TssiPlusBoundaryA[0];
	} else {
		/* Use group#2 settings of A band */
		temp_ref = pAd->TssiRefA;
		enable_tx_alc = pAd->bAutoTxAgcA;
		tx_alc_comp = &pAd->TxAgcCompensateA;
		temp_minus_bdy = pAd->TssiMinusBoundaryA[1];
		temp_plus_bdy = pAd->TssiPlusBoundaryA[1];
	}

	if (mt76x0_get_tssi_report(pAd, bResetTssiInfo, &pAd->CurrTemperature) == TRUE) {
		if (get_temp_tx_alc_level(	
					pAd,
					enable_tx_alc,
					temp_ref,
					temp_minus_bdy,
					temp_plus_bdy,
					8, /* to do: make a definition */
					2,
					pAd->CurrTemperature,
					tx_alc_comp) == TRUE) 
		{
			UINT32 mac_val;
			CHAR last_delta_pwr, delta_pwr = 0;
			
			/* adjust compensation value by MP temperature readings (i.e., e2p[77h]) */
			if (pAd->CommonCfg.Channel <= 14) 
				delta_pwr = pAd->TxAgcCompensateG - pAd->mp_delta_pwr;
			else
				delta_pwr = pAd->TxAgcCompensateA - pAd->mp_delta_pwr; 
			
			RTMP_IO_READ32(pAd, TX_ALC_CFG_1, &mac_val);
			/* 6-bit representation ==> 8-bit representation (2's complement) */
			pAd->DeltaPwrBeforeTempComp = (mac_val & 0x20) ? \
											((mac_val & 0x3F) | 0xC0): (mac_val & 0x3f);		

			last_delta_pwr = pAd->LastTempCompDeltaPwr;
			pAd->LastTempCompDeltaPwr = delta_pwr;
			pAd->DeltaPwrBeforeTempComp -= last_delta_pwr;
			delta_pwr += pAd->DeltaPwrBeforeTempComp;
			/* 8-bit representation ==> 6-bit representation (2's complement) */
			delta_pwr = (delta_pwr & 0x80) ? \
							((delta_pwr & 0x1f) | 0x20) : (delta_pwr & 0x3f);						
			/*	
				Write compensation value into TX_ALC_CFG_1, 
				delta_pwr (unit: 0.5dB) will be compensated by TX_ALC_CFG_1 
			*/     
			RTMP_IO_READ32(pAd, TX_ALC_CFG_1, &mac_val);
			mac_val = (mac_val & (~0x3f)) | delta_pwr;
			RTMP_IO_WRITE32(pAd, TX_ALC_CFG_1, mac_val);

			DBGPRINT(RT_DEBUG_TRACE, 
				("%s - delta_pwr = %d, TssiCalibratedOffset = %d, TssiMpOffset = %d, 0x13B4 = 0x%08x, %s = %d, DeltaPwrBeforeTempComp = %d, LastTempCompDeltaPwr =%d\n",
				__FUNCTION__,
				pAd->LastTempCompDeltaPwr,
				pAd->TssiCalibratedOffset,
				pAd->mp_delta_pwr,
				mac_val,
				(pAd->CommonCfg.Channel <= 14) ? "TxAgcCompensateG" : "TxAgcCompensateA", 
				(pAd->CommonCfg.Channel <= 14) ? pAd->TxAgcCompensateG : pAd->TxAgcCompensateA, 
				pAd->DeltaPwrBeforeTempComp, 
				last_delta_pwr));	
		} else {
			DBGPRINT(RT_DEBUG_ERROR, ("%s(): failed to get the compensation level\n", __FUNCTION__)); 
		}
	}
}


static void adjust_temp_tx_alc_table(
	IN RTMP_ADAPTER *pAd,
	IN CHAR band,
	INOUT PCHAR temp_minus_bdy,
	INOUT PCHAR temp_plus_bdy,
	IN CHAR temp_reference)
{
	INT idx = 0;
	CHAR upper_bound = 127, lower_bound = -128;

	DBGPRINT(RT_DEBUG_OFF,("%s: upper_bound = 0x%02x (%d), lower_bound = 0x%02x (%d)\n",
		__FUNCTION__, upper_bound, upper_bound, lower_bound, lower_bound));
	
	DBGPRINT(RT_DEBUG_OFF,("*** %s: %s_temp_bdy_table[-7 .. +7] = %d %d %d %d %d %d %d * %d * %d %d %d %d %d %d %d, temp_reference=%d\n",
		__FUNCTION__,
		(band == A_BAND) ? "5G" : "2.4G",
		temp_minus_bdy[7], temp_minus_bdy[6], temp_minus_bdy[5],
		temp_minus_bdy[4], temp_minus_bdy[3], temp_minus_bdy[2], temp_minus_bdy[1],
		(band == A_BAND) ? (CHAR)pAd->TssiRefA : (CHAR)pAd->TssiRefG,
		temp_plus_bdy[1], temp_plus_bdy[2], temp_plus_bdy[3], temp_plus_bdy[4],
		temp_plus_bdy[5], temp_plus_bdy[6], temp_plus_bdy[7], temp_reference));

	for (idx = 0; idx < 8; idx++)
	{
		if ((lower_bound - temp_minus_bdy[idx]) <= temp_reference)
			temp_minus_bdy[idx] += temp_reference;
		else
			temp_minus_bdy[idx] = lower_bound;

		if ((upper_bound - temp_plus_bdy[idx]) >= temp_reference)
			temp_plus_bdy[idx] += temp_reference;
		else
			temp_plus_bdy[idx] = upper_bound;

		ASSERT(temp_minus_bdy[idx] >= lower_bound);
		ASSERT(temp_plus_bdy[idx] <= upper_bound);
	}

	if (band == A_BAND)
		pAd->TssiRefA = temp_minus_bdy[0];
	else
		pAd->TssiRefG = temp_minus_bdy[0];

	DBGPRINT(RT_DEBUG_OFF,("%s: %s_temp_bdy_table[-7 .. +7] = %d %d %d %d %d %d %d * %d * %d %d %d %d %d %d %d, temp_reference=%d\n",
		__FUNCTION__,
		(band == A_BAND) ? "5G" : "2.4G",
		temp_minus_bdy[7], temp_minus_bdy[6], temp_minus_bdy[5],
		temp_minus_bdy[4], temp_minus_bdy[3], temp_minus_bdy[2], temp_minus_bdy[1],
		(band == A_BAND) ? (CHAR)pAd->TssiRefA : (CHAR)pAd->TssiRefG,
		temp_plus_bdy[1], temp_plus_bdy[2], temp_plus_bdy[3], temp_plus_bdy[4],
		temp_plus_bdy[5], temp_plus_bdy[6], temp_plus_bdy[7], temp_reference));
}


static void adjust_mp_temp(
	IN RTMP_ADAPTER *pAd,
	IN PCHAR temp_minus_bdy,
	IN PCHAR temp_plus_bdy)
{
	EEPROM_TX_PWR_STRUC e2p_value;
	CHAR mp_temp, idx = 0, mp_offset = 0;
	
	RT28xx_EEPROM_READ16(pAd, 0x10C, e2p_value);
	mp_temp = e2p_value.field.Byte1;			

	if (mp_temp < temp_minus_bdy[1]) {
		/* 
			mp_temperature is larger than the reference value
			check for how large we need to adjust the Tx power 
		*/
		for (idx = 1; idx < 8; idx++)
		{
			if (mp_temp >= temp_minus_bdy[idx]) /* the range has been found */
				break;
		}

		/* 
			The index is the step we should decrease, 
			idx = 0 means there is no need to adjust the Tx power
		*/
		mp_offset = -(2 * (idx-1));
		pAd->mp_delta_pwr = mp_offset;
		DBGPRINT(RT_DEBUG_OFF, ("mp_temperature=0x%02x, step = -%d\n", mp_temp, idx-1));                    
	} else if (mp_temp > temp_plus_bdy[1]) {
		/* 
			mp_temperature is smaller than the reference value
			check for how large we need to adjust the Tx power 
		*/
		for (idx = 1; idx < 8; idx++)
		{
		    	if (mp_temp <= temp_plus_bdy[idx]) /* the range has been found */
	            		break;
		}

		/* 
			The index is the step we should increase, 
			idx = 0 means there is no need to adjust the Tx power
		*/
		mp_offset = 2 * (idx-1);
		pAd->mp_delta_pwr = mp_offset;
		DBGPRINT(RT_DEBUG_OFF, ("mp_temperature=0x%02x, step = +%d\n", mp_temp, idx-1));
	} else {
		pAd->mp_delta_pwr = 0;
		DBGPRINT(RT_DEBUG_OFF, ("mp_temperature=0x%02x, step = +%d\n", mp_temp, 0));
	}
}


BOOLEAN load_temp_tx_alc_table(
	IN RTMP_ADAPTER	*pAd,
	IN CHAR band,
	IN USHORT e2p_start_addr,
	IN USHORT e2p_end_addr,
	OUT	PUCHAR bdy_table,
	IN const INT start_idx,
	IN const UINT32 table_size)
{
	USHORT e2p_value;
	INT e2p_idx = 0, table_idx = 0;
	CHAR table_sign; /* +1 for plus table; -1 for minus table */

	table_sign = (e2p_start_addr < e2p_end_addr) ? 1 : (-1);

	if (start_idx < table_size) {
		table_idx = start_idx;
	} else {
		DBGPRINT(RT_DEBUG_ERROR, ("%s(): ERROR - incorrect start index (%d)\n",
			__FUNCTION__, start_idx));
		return FALSE;
	}

	DBGPRINT(RT_DEBUG_OFF, ("%s(): load %s %s table from eeprom 0x%x to 0x%x (start_idx = %d)\n",
		__FUNCTION__, 
		(band == A_BAND) ? "5G" : "2.4G",
		(table_sign == 1) ? "plus" : "minus",
		e2p_start_addr, e2p_end_addr, start_idx));

	for (e2p_idx = e2p_start_addr;
		 e2p_idx != (e2p_end_addr + (2*table_sign));
		 e2p_idx = e2p_idx + (2*table_sign))
	{
		if ((e2p_start_addr % 2) != 0) {
			e2p_start_addr--;
			e2p_idx--;
		}
		
		RT28xx_EEPROM_READ16(pAd, e2p_idx, e2p_value);

		if (e2p_idx == e2p_start_addr) {
			if (table_sign > 0) 
				bdy_table[table_idx++] = (UCHAR)((e2p_value >> 8) & 0xFF);
			else
 				bdy_table[table_idx++] = (UCHAR)(e2p_value & 0xFF);
		} else {
			if (table_sign > 0) {
				bdy_table[table_idx++] = (UCHAR)(e2p_value & 0xFF);
				bdy_table[table_idx++] = (UCHAR)((e2p_value >> 8) & 0xFF);
			} else {
				bdy_table[table_idx++] = (UCHAR)((e2p_value >> 8) & 0xFF);
				bdy_table[table_idx++] = (UCHAR)(e2p_value & 0xFF);
			}
		}
		
		if (table_idx >= table_size)
			break;
	}

	if (table_idx > table_size) {
		DBGPRINT(RT_DEBUG_ERROR, ("%s(): WARNING - eeprom table may not be loaded completely\n", __FUNCTION__));
		return FALSE;
	} else {	
		for (table_idx = 0; table_idx < table_size; table_idx++)
			DBGPRINT(RT_DEBUG_TRACE, ("\tboundary_table[%d] = %3d (0x%02X)\n", 
				table_idx, (CHAR)bdy_table[table_idx], bdy_table[table_idx]));
	}

	return TRUE;
}


void mt76x0_temp_tx_alc_init(PRTMP_ADAPTER pAd)
{
	/* Initialize group settings of A band */
	pAd->TxAgcCompensateA = 0;
	pAd->TssiRefA = 0;
	pAd->TssiMinusBoundaryA[0][0] = 0;
	pAd->TssiMinusBoundaryA[1][0] = 0;
	pAd->TssiPlusBoundaryA[0][0] = 0;
	pAd->TssiPlusBoundaryA[1][0] = 0;

	/* Initialize group settings of G band */
	pAd->TxAgcCompensateG = 0;
	pAd->TssiRefG = 0;
	pAd->TssiMinusBoundaryG[0] = 0;
	pAd->TssiPlusBoundaryG[0] = 0;
	
	pAd->DeltaPwrBeforeTempComp = 0;
	pAd->LastTempCompDeltaPwr = 0;
	
	adjust_temp_tx_alc_table(pAd, A_BAND, pAd->TssiMinusBoundaryA[0], 
								pAd->TssiPlusBoundaryA[0], pAd->TssiCalibratedOffset);
	adjust_mp_temp(pAd, pAd->TssiMinusBoundaryA[0], pAd->TssiPlusBoundaryA[0]);

	adjust_temp_tx_alc_table(pAd, A_BAND, pAd->TssiMinusBoundaryA[1], 
								pAd->TssiPlusBoundaryA[1], pAd->TssiCalibratedOffset);
	adjust_mp_temp(pAd, pAd->TssiMinusBoundaryA[1], pAd->TssiPlusBoundaryA[1]);

	adjust_temp_tx_alc_table(pAd, BG_BAND, pAd->TssiMinusBoundaryG, 
								pAd->TssiPlusBoundaryG, pAd->TssiCalibratedOffset);
	adjust_mp_temp(pAd, pAd->TssiMinusBoundaryG, pAd->TssiPlusBoundaryG); 
}
#endif /* RTMP_TEMPERATURE_TX_ALC */


void mt76x0_read_tx_alc_info_from_eeprom(PRTMP_ADAPTER pAd)
{
	BOOLEAN status = TRUE;
	USHORT e2p_value = 0;

	if (IS_MT76x0(pAd)) {
		RT28xx_EEPROM_READ16(pAd, 0xD0, e2p_value);
		e2p_value = (e2p_value & 0xFF00) >> 8;
		DBGPRINT(RT_DEBUG_OFF, ("%s: EEPROM_MT76x0_TEMPERATURE_OFFSET (0xD1) = 0x%x\n", 
			__FUNCTION__, e2p_value));
		
		if ((e2p_value & 0xFF) == 0xFF) {
			pAd->chipCap.TemperatureOffset = -10;
		} else {
			if ((e2p_value & 0x80) == 0x80) /* Negative number */
				e2p_value |= 0xFF00; 						
				
			pAd->chipCap.TemperatureOffset = (SHORT)e2p_value;			
		}
		DBGPRINT(RT_DEBUG_OFF, ("%s: TemperatureOffset = 0x%x\n", 
			__FUNCTION__, pAd->chipCap.TemperatureOffset));
	}

#ifdef RTMP_TEMPERATURE_TX_ALC
	if (pAd->bAutoTxAgcG | pAd->bAutoTxAgcA) {	
		RT28xx_EEPROM_READ16(pAd, 0xD0, e2p_value);
		pAd->TssiCalibratedOffset = (e2p_value >> 8);
	
		/* 5G Tx power compensation channel boundary index */
		RT28xx_EEPROM_READ16(pAd, 0x10C, e2p_value);
		pAd->ChBndryIdx = (UCHAR)(e2p_value & 0xFF);
		DBGPRINT(RT_DEBUG_OFF, ("%s(): channel boundary index = %u, temp reference offset = %d\n",
			__FUNCTION__, pAd->ChBndryIdx, pAd->TssiCalibratedOffset));

		/* Load group#1 settings of A band */
		load_temp_tx_alc_table(
			pAd, A_BAND, 0xF6, 0xF0, pAd->TssiMinusBoundaryA[0], 1, sizeof(pAd->TssiMinusBoundaryA[0]));
		load_temp_tx_alc_table(
			pAd, A_BAND, 0xF7, 0xFD, pAd->TssiPlusBoundaryA[0], 1, sizeof(pAd->TssiPlusBoundaryA[0]));

		/* Load group#2 settings of A band */
		load_temp_tx_alc_table(
			pAd, A_BAND, 0x104, 0xFE, pAd->TssiMinusBoundaryA[1], 1, sizeof(pAd->TssiMinusBoundaryA[1]));
		load_temp_tx_alc_table(
			pAd, A_BAND, 0x105, 0x10B, pAd->TssiPlusBoundaryA[1], 1, sizeof(pAd->TssiPlusBoundaryA[1]));

		/* Load group settings of G band */
		load_temp_tx_alc_table(
			pAd, BG_BAND, 0x1B6, 0x1B0, pAd->TssiMinusBoundaryG, 1, sizeof(pAd->TssiMinusBoundaryG));
		load_temp_tx_alc_table(
			pAd, BG_BAND, 0x1B7, 0x1BD, pAd->TssiPlusBoundaryG, 1, sizeof(pAd->TssiPlusBoundaryG));

		mt76x0_temp_tx_alc_init(pAd);
	}
	else
#endif /* RTMP_TEMPERATURE_TX_ALC */
		DBGPRINT(RT_DEBUG_ERROR, ("Temperature Tx ALC not enabled\n"));
}


void mt76x0_adjust_per_rate_pwr(PRTMP_ADAPTER pAd)
{
	CONFIGURATION_OF_TX_POWER_CONTROL_OVER_MAC CfgOfTxPwrCtrlOverMAC = {0};	
	INT32 mac_idx = 0;

	DBGPRINT(RT_DEBUG_INFO,("-->%s\n", __FUNCTION__));

	/* Update per tx rate table */
	RTMP_CHIP_ASIC_TX_POWER_OFFSET_GET(pAd, (PULONG)&CfgOfTxPwrCtrlOverMAC);

	/* Set new tx power per tx rate */
	for (mac_idx = 0; mac_idx < CfgOfTxPwrCtrlOverMAC.NumOfEntries; mac_idx++)
	{
		TX_POWER_CONTROL_OVER_MAC_ENTRY *pTxPwrEntry;
		pTxPwrEntry = &CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[mac_idx];
		
		if (pTxPwrEntry->RegisterValue != 0xFFFFFFFF) {
			RTMP_IO_WRITE32(pAd, pTxPwrEntry->MACRegisterOffset, pTxPwrEntry->RegisterValue);
		}
	}

	/* Extra set MAC CRs to compensate tx power if any */
	RTMP_CHIP_ASIC_EXTRA_POWER_OVER_MAC(pAd);
	
	DBGPRINT(RT_DEBUG_INFO, ("<--%s\n", __FUNCTION__));
}

/******************************* Command API *******************************/
INT Set_AntennaSelect_Proc(
	IN RTMP_ADAPTER		*pAd,
	IN PSTRING			arg)
{
	UINT8 val = (UINT8)simple_strtol(arg, 0, 10);
	UINT32 reg_val = 0;

	/*
		0x2300[5] Default Antenna:
		0 for WIFI main antenna
		1  for WIFI aux  antenna

	*/
	RTMP_IO_READ32(pAd, AGC1_R0, &reg_val);
	reg_val &= ~(0x00000020);
	if (val != 0)
		reg_val |= 0x20;
	RTMP_IO_WRITE32(pAd, AGC1_R0, reg_val);

	RTMP_IO_READ32(pAd, AGC1_R0, &reg_val);

	RTMP_CHIP_CALIBRATION(pAd, RXDCOC_CALIBRATION, 1);
	DBGPRINT(RT_DEBUG_TRACE, ("Set_AntennaSelect_Proc:: AntennaSelect = %d (0x%08x=0x%08x)\n", val, AGC1_R0, reg_val));

	return TRUE;
}
/******************************* Command API end ***************************/


