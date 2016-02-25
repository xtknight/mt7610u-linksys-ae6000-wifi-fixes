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


#ifndef __MT76X0_H__
#define __MT76X0_H__

#include "../mcu/mcu_and.h"

struct _RTMP_ADAPTER;

#define MAX_RF_ID	127
#define MAC_RF_BANK 7

/* b'00: 2.4G+5G external PA, b'01: 5G external PA, b'10: 2.4G external PA, b'11: Internal PA */
#define EXT_PA_2G_5G		0x0
#define EXT_PA_5G_ONLY		0x1
#define EXT_PA_2G_ONLY		0x2
#define INT_PA_2G_5G		0x3

#ifdef RTMP_FLASH_SUPPORT

#ifdef RTMP_MAC_USB
#define EEPROM_DEFAULT_FILE_PATH                     "/etc_ro/Wireless/RT2870AP/MT7610U_ePA_V0_3.bin"
#endif /* RTMP_MAC_USB */

#define RF_OFFSET					0x48000

#endif /* RTMP_FLASH_SUPPORT */


/*
	rsv: Reserved
	tcp: packet type, tcp : 1, udp:0
	tups: TCP/UDP header start offset (in unit of DWORD)
	ips: IP start offset (in unit of byte), base address of ips is the beginning of TXWI
	mss: Max Segment size (in unit of byte)
*/
#ifdef RT_BIG_ENDIAN
typedef struct _TSO_INFO_{
	UINT32 mss:16;
	UINT32 ips:8;
	UINT32 tups:6;	
	UINT32 tcp:1;	
	UINT32 rsv:1;
}TSO_INFO;
#else
typedef struct _TSO_INFO_{
	UINT32 rsv:1;
	UINT32 tcp:1;
	UINT32 tups:6;
	UINT32 ips:8;
	UINT32 mss:16;
}TSO_INFO;
#endif /* RT_BIG_ENDIAN */


/* 
 * Frequency plan item  for RT85592 
 * N: R9[4], R8[7:0]
 * K: R7[7], R9[3:0]
 * mod: R9[7:5], R11[3:2] (eg. mod=8 => 0x0, mod=10 => 0x2)
 * R: R11[1:0] (eg. R=1 => 0x0, R=3 => 0x2)
 */
typedef struct _RT8592_FREQ_ITEM {
	UINT8 Channel;
	UINT16 N;
	UINT8 K;
	UINT8 mod;
	UINT8 R;
} RT8592_FREQ_ITEM;
	
/* 
	R37
	R36
	R35
	R34
	R33
	R32<7:5>
	R32<4:0> pll_den: (Denomina - 8)
	R31<7:5>
	R31<4:0> pll_k(Nominator)
	R30<7> sdm_reset_n
	R30<6:2> sdmmash_prbs,sin
	R30<1> sdm_bp
	R30<0> R29<7:0> (hex) pll_n
	R28<7:6> isi_iso
	R28<5:4> pfd_dly
	R28<3:2> clksel option
	R28<1:0> R27<7:0> R26<7:0> (hex) sdm_k
	R24<1:0> xo_div
*/
typedef struct _MT76x0_FREQ_ITEM {
	UINT8 Channel;
	UINT32 Band;
	UINT8 pllR37;
	UINT8 pllR36;
	UINT8 pllR35;
	UINT8 pllR34;
	UINT8 pllR33;
	UINT8 pllR32_b7b5;
	UINT8 pllR32_b4b0; /* PLL_DEN */
	UINT8 pllR31_b7b5;
	UINT8 pllR31_b4b0; /* PLL_K */
	UINT8 pllR30_b7; /* sdm_reset_n */
	UINT8 pllR30_b6b2; /* sdmmash_prbs,sin */
	UINT8 pllR30_b1; /* sdm_bp */
	UINT16 pll_n; /* R30<0>, R29<7:0> (hex) */	
	UINT8 pllR28_b7b6; /* isi,iso */
	UINT8 pllR28_b5b4; /* pfd_dly */
	UINT8 pllR28_b3b2; /* clksel option */
	UINT32 Pll_sdm_k; /* R28<1:0>, R27<7:0>, R26<7:0> (hex) SDM_k */
	UINT8 pllR24_b1b0; /* xo_div */
} MT76x0_FREQ_ITEM;

#define RF_G_BAND 		0x0100
#define RF_A_BAND 		0x0200
#define RF_A_BAND_LB	0x0400
#define RF_A_BAND_MB	0x0800
#define RF_A_BAND_HB	0x1000
#define RF_A_BAND_11J	0x2000
#define RF_A_G_BAND (RF_G_BAND | RF_A_BAND | RF_A_BAND_LB | RF_A_BAND_MB | RF_A_BAND_HB | RF_A_BAND_11J)

enum PA_TYPE {
	EXT_TYPE_PA = 0x01,
	INT_TYPE_PA = 0x02,
	ALL_TYPE_PA = (EXT_TYPE_PA | INT_TYPE_PA),
	UNKNOWN_TYPE_PA = 0x04,
};

typedef struct _RT6590_RF_SWITCH_ITEM {
	UCHAR Bank;
	UCHAR Register;
	UINT32 BwBand; /* (BW_20, BW_40, BW_80) | (G_Band, A_Band_LB, A_Band_MB, A_Band_HB) */
	UCHAR Value;
} MT76x0_RF_SWITCH_ITEM, *PMT76x0_RF_SWITCH_ITEM;

typedef struct _MT76x0_BBP_Table {
	UINT32 BwBand; /* (BW_20, BW_40, BW_80) | (G_Band, A_Band_LB, A_Band_MB, A_Band_HB) */
	RTMP_REG_PAIR RegDate;
} MT76x0_BBP_Table, *PMT76x0_BBP_Table;

typedef struct _MT76x0_RATE_PWR_ITEM {
	CHAR MCS_Power;
	UCHAR RF_PA_Mode;
} MT76x0_RATE_PWR_ITEM, *PMT76x0_RATE_PWR_ITEM;

typedef struct _MT76x0_RATE_PWR_TABLE {
	MT76x0_RATE_PWR_ITEM CCK[4];
	MT76x0_RATE_PWR_ITEM OFDM[8];
	MT76x0_RATE_PWR_ITEM HT[8];
	MT76x0_RATE_PWR_ITEM VHT[10];
	MT76x0_RATE_PWR_ITEM STBC[8];
	MT76x0_RATE_PWR_ITEM MCS32;
} MT76x0_RATE_PWR_Table, *PMT76x0_RATE_PWR_Table;

VOID MT76x0_Init(struct _RTMP_ADAPTER *pAd);
INT MT76x0_ReadChannelPwr(struct _RTMP_ADAPTER *pAd);

VOID MT76x0_AsicExtraPowerOverMAC(struct _RTMP_ADAPTER *pAd);

#ifdef DBG
VOID MT76x0_ShowDmaIndexCupIndex(
	struct _RTMP_ADAPTER *pAd);
#endif /* DBG */

#ifdef RT8592
#endif /* RT8592 */
VOID mt76x0_read_per_rate_tx_pwr(struct _RTMP_ADAPTER *pAd);

VOID dump_bw_info(struct _RTMP_ADAPTER *pAd);

VOID MT76x0_WLAN_ChipOnOff(
	IN struct _RTMP_ADAPTER *pAd,
	IN BOOLEAN bOn,
	IN BOOLEAN bResetWLAN);


VOID MT76x0_AntennaSelCtrl(
	IN struct _RTMP_ADAPTER *pAd);

VOID MT76x0_dynamic_vga_tuning(
	IN struct _RTMP_ADAPTER *pAd);

VOID MT76x0_VCO_CalibrationMode3(
	IN struct _RTMP_ADAPTER *pAd,
	IN UCHAR Channel);

VOID MT76x0_Calibration(
	IN struct _RTMP_ADAPTER *pAd,
	IN UCHAR Channel,
	IN BOOLEAN bPowerOn,
	IN BOOLEAN bDoTSSI,
	IN BOOLEAN bFullCal);

VOID MT76x0_TempSensor(
	IN struct _RTMP_ADAPTER *pAd);

#ifdef DFS_SUPPORT
VOID MT76x0_DFS_CR_Init(
	IN struct _RTMP_ADAPTER *pAd);
#endif /* DFS_SUPPORT */
#ifdef RTMP_FLASH_SUPPORT
VOID MT76x0_ReadFlashAndInitAsic(
	IN struct _RTMP_ADAPTER *pAd);
#endif /* RTMP_FLASH_SUPPORT */

INT Set_AntennaSelect_Proc(
	IN struct _RTMP_ADAPTER		*pAd,
	IN PSTRING			arg);

#ifdef RTMP_TEMPERATURE_TX_ALC
void mt76x0_temp_tx_alc(struct _RTMP_ADAPTER *pAd);
#endif /* RTMP_TEMPERATURE_TX_ALC */

void mt76x0_adjust_per_rate_pwr(struct _RTMP_ADAPTER *pAd);

void mt76x0_read_tx_alc_info_from_eeprom(struct _RTMP_ADAPTER *pAd);

#ifdef MT76x0_TSSI_CAL_COMPENSATION
VOID MT76x0_TSSI_DC_Calibration(
	IN  struct _RTMP_ADAPTER *pAd);

VOID MT76x0_MakeUpTssiTable(
	IN  struct _RTMP_ADAPTER *pAd);

VOID MT76x0_IntTxAlcProcess(
	IN  struct _RTMP_ADAPTER *pAd);
#endif /* MT76x0_TSSI_CAL_COMPENSATION */

VOID MT76x0_MakeUpRatePwrTable(
	IN struct _RTMP_ADAPTER *pAd);

#ifdef SINGLE_SKU_V2
UCHAR MT76x0_GetSkuChannelBasePwr(
	IN struct _RTMP_ADAPTER *pAd,
	IN UCHAR channel);

UCHAR MT76x0_UpdateSkuPwr(
	IN struct _RTMP_ADAPTER *pAd,
	IN UCHAR channel);
#endif /* SINGLE_SKU_V2 */

#endif /* __MT76x0_H__ */
