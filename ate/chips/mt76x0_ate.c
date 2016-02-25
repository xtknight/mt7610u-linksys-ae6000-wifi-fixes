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

#ifndef RLT_RF
#error "You Should Enable compile flag RLT_RF for this chip"
#endif /* RLT_RF */

extern MT76x0_BBP_Table MT76x0_BPP_SWITCH_Tab[];
extern UCHAR MT76x0_BPP_SWITCH_Tab_Size;

extern VOID SelectBandMT76x0(PRTMP_ADAPTER pAd, UCHAR Channel);
extern VOID SetRfChFreqParametersMT76x0(PRTMP_ADAPTER pAd, UCHAR Channel);
extern VOID MT76x0_AsicExtraPowerOverMAC(struct _RTMP_ADAPTER *pAd);
extern VOID MT76x0_VCO_CalibrationMode3(struct _RTMP_ADAPTER *pAd, UCHAR Channel);
extern VOID MT76x0_Calibration(struct _RTMP_ADAPTER *pAd, 
			UCHAR Channel, BOOLEAN bPowerOn, BOOLEAN bDoTSSI, BOOLEAN bFullCal);
#ifdef RTMP_TEMPERATURE_TX_ALC
extern BOOLEAN mt76x0_get_tssi_report(PRTMP_ADAPTER pAd, 
			BOOLEAN bResetTssiInfo, PCHAR pTssiReport);
extern BOOLEAN get_temp_tx_alc_level(PRTMP_ADAPTER pAd, BOOLEAN enable_tx_alc,
			CHAR temp_ref, PCHAR temp_minus_bdy, PCHAR temp_plus_bdy, 
			UINT8 max_bdy_level, UINT8 tx_alc_step, CHAR current_temp, PCHAR comp_level);
#endif /* RTMP_TEMPERATURE_TX_ALC */


static INT ate_bbp_set_ctrlch(struct _RTMP_ADAPTER *pAd, INT ext_ch)
{
	UINT32 agc, agc_r0 = 0;
	UINT32 be, be_r0 = 0;

	RTMP_BBP_IO_READ32(pAd, AGC1_R0, &agc_r0);
	agc = agc_r0 & (~0x300);
	RTMP_BBP_IO_READ32(pAd, TXBE_R0, &be_r0);
	be = (be_r0 & (~0x03));

	switch (ext_ch)
	{
		case EXTCHA_BELOW:
			agc |= 0x100;
			be |= 0x01;
			break;
		case EXTCHA_ABOVE:
			agc &= (~0x300);
			be &= (~0x03);
			break;
		case EXTCHA_NONE:
			default:
			agc &= (~0x300);
			be &= (~0x03);
			break;
	}
	
	if (agc != agc_r0)
		RTMP_BBP_IO_WRITE32(pAd, AGC1_R0, agc);

	if (be != be_r0)
		RTMP_BBP_IO_WRITE32(pAd, TXBE_R0, be);

	return TRUE;
}


static VOID mt76x0_ate_bbp_adjust(
	IN PRTMP_ADAPTER	pAd)
{
	PATE_INFO pATEInfo = &(pAd->ate);
	UCHAR rf_bw, ext_ch = EXTCHA_NONE;

	rf_bw = pATEInfo->TxWI.TXWI_N.BW;

	rtmp_bbp_set_bw(pAd, rf_bw);

	/* Tx/Rx : control channel setting */
	rtmp_mac_set_ctrlch(pAd, ext_ch);
	ate_bbp_set_ctrlch(pAd, ext_ch);
}


/*
	==========================================================================
    Description:

	AsicSwitchChannel() dedicated for MT76x0 ATE.
    
	==========================================================================
*/
static VOID mt76x0_ate_switch_channel(
    	IN PRTMP_ADAPTER	pAd)
{	
	PATE_INFO pATEInfo = &(pAd->ate);
	UINT32 idx = 0, rf_phy_mode, rf_bw = RF_BW_20;
	UCHAR channel = 0;
	
	SYNC_CHANNEL_WITH_QA(pATEInfo, &channel);
	mt76x0_ate_bbp_adjust(pAd);

	DBGPRINT(RT_DEBUG_TRACE, ("%s::Channel = %d, TXWI_N.BW = %d , RFFreqOffset = %d, TxPower0 = %d\n", 
					__FUNCTION__, channel, pATEInfo->TxWI.TXWI_N.BW, pATEInfo->RFFreqOffset, pATEInfo->TxPower0));

	if (channel > 14)
		rf_phy_mode = RF_A_BAND;
	else
		rf_phy_mode = RF_G_BAND;

	if (pATEInfo->TxWI.TXWI_N.BW == BW_80)
		rf_bw = RF_BW_80;
	else if (pATEInfo->TxWI.TXWI_N.BW == BW_40)
		rf_bw = RF_BW_40;
	else
		rf_bw = RF_BW_20;

	/*
		Configure 2.4/5GHz before accessing other MAC/BB/RF registers
	*/
	SelectBandMT76x0(pAd, channel);

	/*
		Set RF channel frequency parameters (Rdiv, N, K, D and Ksd)
	*/
	SetRfChFreqParametersMT76x0(pAd, channel);

	for (idx = 0; idx < MT76x0_BPP_SWITCH_Tab_Size; idx++)
	{
		if (((rf_phy_mode | rf_bw) & MT76x0_BPP_SWITCH_Tab[idx].BwBand) == (rf_phy_mode | rf_bw))
		{
			if ((MT76x0_BPP_SWITCH_Tab[idx].RegDate.Register == AGC1_R8))
			{
				UINT32 eLNAgain = (MT76x0_BPP_SWITCH_Tab[idx].RegDate.Value & 0x0000FF00) >> 8;

				if (channel > 14)
				{
					if (channel < 100)
						eLNAgain -= (pAd->ALNAGain0*2);
					else if (channel < 137)
						eLNAgain -= (pAd->ALNAGain1*2);
					else
						eLNAgain -= (pAd->ALNAGain2*2);
				}
				else
					eLNAgain -= (pAd->BLNAGain*2);
				
				RTMP_BBP_IO_WRITE32(pAd, MT76x0_BPP_SWITCH_Tab[idx].RegDate.Register,
						(MT76x0_BPP_SWITCH_Tab[idx].RegDate.Value&(~0x0000FF00))|(eLNAgain << 8));
			}
			else
			{
				RTMP_BBP_IO_WRITE32(pAd, MT76x0_BPP_SWITCH_Tab[idx].RegDate.Register,
						MT76x0_BPP_SWITCH_Tab[idx].RegDate.Value);
			}
		}
	}

	/* 
		VCO calibration (mode 3) 
	*/
	MT76x0_VCO_CalibrationMode3(pAd, channel);

	MT76x0_Calibration(pAd, channel, TRUE, TRUE, TRUE);

	pAd->LatchRfRegs.Channel = channel;
	
	RTMPusecDelay(100000);
}


static INT mt76x0_ate_tx_pwr_handler(
	IN PRTMP_ADAPTER 	pAd,
	IN CHAR 				index)
{
	PATE_INFO pATEInfo = &(pAd->ate);
	UINT32 mac_val = 0, tx_pwr = 0;

#ifdef RALINK_QA
	if (pATEInfo->bQAEnabled == TRUE)
		return 0;
#endif /* RALINK_QA */

	RTMP_IO_READ32(pAd, TX_ALC_CFG_0, &mac_val);
	if (index == 0) {
		tx_pwr = pATEInfo->TxPower0;
		mac_val &= (~0x0000003F);
		mac_val |= tx_pwr;
	} else if (index == 1) {
		tx_pwr = pATEInfo->TxPower1;
		mac_val &= (~0x00003F00);
		mac_val |= (tx_pwr << 8);
	} else {
		DBGPRINT_ERR(("%s::Only TxPower0 and TxPower1 can be adjustable\n", __FUNCTION__));
		DBGPRINT_ERR(("%s::TxPower%d is out of range\n", __FUNCTION__, index));
		return FALSE;
	}
	mac_val |= (0x2F2F << 16);
	RTMP_IO_WRITE32(pAd, TX_ALC_CFG_0, mac_val);
	
	DBGPRINT(RT_DEBUG_TRACE, ("%s::TxPower%d=%d\n", __FUNCTION__, index, tx_pwr));
	return TRUE;
}


VOID mt76x0_ate_update_per_rate_pwr(
	IN PRTMP_ADAPTER 	pAd,
	INOUT PULONG 		per_rate_pwr)
{
	PATE_INFO pATEInfo = &(pAd->ate);
	CONFIGURATION_OF_TX_POWER_CONTROL_OVER_MAC rate_pwr_table;
	INT32 idx = 0;
	
	DBGPRINT(RT_DEBUG_INFO, ("-->%s\n", __FUNCTION__));

	NdisZeroMemory(&rate_pwr_table, sizeof(rate_pwr_table));

	rate_pwr_table.NumOfEntries = 5; /* MAC 0x1314, 0x1318, 0x131C, 0x1320 and 1324 */
	rate_pwr_table.TxPwrCtrlOverMAC[0].MACRegisterOffset = TX_PWR_CFG_0;
	rate_pwr_table.TxPwrCtrlOverMAC[1].MACRegisterOffset = TX_PWR_CFG_1;
	rate_pwr_table.TxPwrCtrlOverMAC[2].MACRegisterOffset = TX_PWR_CFG_2;
	rate_pwr_table.TxPwrCtrlOverMAC[3].MACRegisterOffset = TX_PWR_CFG_3;
	rate_pwr_table.TxPwrCtrlOverMAC[4].MACRegisterOffset = TX_PWR_CFG_4;
	
	if (pATEInfo->TxWI.TXWI_N.BW == BW_20) {
		if (pATEInfo->Channel > 14) {
			for (idx = 0; idx < rate_pwr_table.NumOfEntries; idx++)
				rate_pwr_table.TxPwrCtrlOverMAC[idx].RegisterValue = pAd->Tx20MPwrCfgABand[idx];
		} else {
			for (idx = 0; idx < rate_pwr_table.NumOfEntries; idx++)
				rate_pwr_table.TxPwrCtrlOverMAC[idx].RegisterValue = pAd->Tx20MPwrCfgGBand[idx];
		}
	} else {
		if (pATEInfo->Channel > 14) {
			for (idx = 0; idx < rate_pwr_table.NumOfEntries; idx++)
				rate_pwr_table.TxPwrCtrlOverMAC[idx].RegisterValue = pAd->Tx40MPwrCfgABand[idx];
		} else {
			for (idx = 0; idx < rate_pwr_table.NumOfEntries; idx++)
				rate_pwr_table.TxPwrCtrlOverMAC[idx].RegisterValue = pAd->Tx40MPwrCfgGBand[idx];
		}
	}
	
	NdisCopyMemory(per_rate_pwr, (UCHAR *)&rate_pwr_table, sizeof(rate_pwr_table));
	DBGPRINT(RT_DEBUG_INFO, ("<--%s\n", __FUNCTION__));
}


void mt76x0_ate_adjust_per_rate_pwr(
	IN PRTMP_ADAPTER 	pAd)
{
	CONFIGURATION_OF_TX_POWER_CONTROL_OVER_MAC rate_pwr_table = {0};	
	INT32 mac_idx = 0;

	DBGPRINT(RT_DEBUG_INFO,("-->%s\n", __FUNCTION__));

	mt76x0_ate_update_per_rate_pwr(pAd, (PULONG)&rate_pwr_table);

	for (mac_idx = 0; mac_idx < rate_pwr_table.NumOfEntries; mac_idx++)
	{
		TX_POWER_CONTROL_OVER_MAC_ENTRY *rate_pwr_entry;
		rate_pwr_entry = &rate_pwr_table.TxPwrCtrlOverMAC[mac_idx];
		
		if (rate_pwr_entry->RegisterValue != 0xFFFFFFFF) {
			RTMP_IO_WRITE32(pAd, rate_pwr_entry->MACRegisterOffset, rate_pwr_entry->RegisterValue);
		}
	}

	MT76x0_AsicExtraPowerOverMAC(pAd);

	DBGPRINT(RT_DEBUG_INFO, ("<--%s\n", __FUNCTION__));
}


#ifdef RTMP_TEMPERATURE_TX_ALC
void mt76x0_ate_asic_adjust_tx_pwr(
	IN PRTMP_ADAPTER 	pAd)
{
	PATE_INFO pATEInfo = &(pAd->ate);
	BOOLEAN bResetTssiInfo = TRUE, enable_tx_alc;
	PUCHAR temp_minus_bdy, temp_plus_bdy, tx_alc_comp;
	UCHAR temp_ref;
	
	if ((pATEInfo->Channel > 14) ? 
		(pAd->bAutoTxAgcA == FALSE) : (pAd->bAutoTxAgcG == FALSE))
		return;

	if (pATEInfo->Channel <= 14) {
		/* Use group settings of G band */
		temp_ref = pAd->TssiRefG;
		enable_tx_alc = pAd->bAutoTxAgcG;
		tx_alc_comp = &pAd->TxAgcCompensateG;
		temp_minus_bdy = pAd->TssiMinusBoundaryG;
		temp_plus_bdy = pAd->TssiPlusBoundaryG;
	} else if (pATEInfo->Channel <= pAd->ChBndryIdx) {
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
			if (pATEInfo->Channel <= 14) 
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

			DBGPRINT(RT_DEBUG_OFF, 
				("%s - delta_pwr = %d, TssiCalibratedOffset = %d, TssiMpOffset = %d, 0x13B4 = 0x%08x, %s = %d, DeltaPwrBeforeTempComp = %d, LastTempCompDeltaPwr =%d\n",
				__FUNCTION__,
				pAd->LastTempCompDeltaPwr,
				pAd->TssiCalibratedOffset,
				pAd->mp_delta_pwr,
				mac_val,
				(pATEInfo->Channel <= 14) ? "TxAgcCompensateG" : "TxAgcCompensateA", 
				(pATEInfo->Channel <= 14) ? pAd->TxAgcCompensateG : pAd->TxAgcCompensateA, 
				pAd->DeltaPwrBeforeTempComp, 
				last_delta_pwr));	
		} else {
			DBGPRINT(RT_DEBUG_OFF, ("%s(): failed to get the compensation level\n", __FUNCTION__)); 
		}
	}
}
#endif /* RTMP_TEMPERATURE_TX_ALC */


/* 
	==========================================================================
    Description:
        Set MT76x0 ATE RF BW
        
    Return:
        TRUE if all parameters are OK, FALSE otherwise
	==========================================================================
*/
static INT mt76x0_ate_set_tx_bw_proc(
	IN PRTMP_ADAPTER	pAd, 
	IN PSTRING			arg)
{
	PATE_INFO pATEInfo = &(pAd->ate);
	UCHAR current_bw = simple_strtol(arg, 0, 10);

	if (current_bw == 0)
		pATEInfo->TxWI.TXWI_N.BW = BW_20;
	else if (current_bw == 1)
		pATEInfo->TxWI.TXWI_N.BW = BW_40;
	else if (current_bw == 2)
		pATEInfo->TxWI.TXWI_N.BW = BW_80;
	else
		return FALSE;
	
	return TRUE;
}


/* 
	==========================================================================
    Description:
        Set MT76x0 ATE RF central frequency offset
        
    Return:
        TRUE if all parameters are OK, FALSE otherwise
	==========================================================================
*/
static INT mt76x0_ate_set_tx_freq_offset_proc(
	IN PRTMP_ADAPTER	pAd, 
	IN PSTRING			arg)
{
	PATE_INFO pATEInfo = &(pAd->ate);
	UCHAR rf_val = 0;
	pATEInfo->RFFreqOffset = simple_strtol(arg, 0, 10);

	if (pATEInfo->RFFreqOffset > 0xBF) {
		DBGPRINT_ERR(("%s::Out of range (Value=%d)\n", __FUNCTION__, pATEInfo->RFFreqOffset));
		DBGPRINT_ERR(("%s::Range of frequency offset should be 0~191\n", __FUNCTION__));
		return FALSE;
	}
	
	rf_val = (UCHAR)(pATEInfo->RFFreqOffset & 0xFF); 
	rf_val = min(rf_val, 0xBF);
	rlt_rf_write(pAd, RF_BANK0, RF_R22, rf_val);

	return TRUE;
}

 
struct _ATE_CHIP_STRUCT mt76x0ate =
{
	/* Functions */
	.ChannelSwitch = mt76x0_ate_switch_channel,
	.TxPwrHandler = mt76x0_ate_tx_pwr_handler,
	.TssiCalibration = NULL,
	.ExtendedTssiCalibration = NULL,
	.RxVGAInit = NULL,
	.AsicSetTxRxPath = NULL,
#ifdef RTMP_TEMPERATURE_TX_ALC
	.AdjustTxPower = mt76x0_ate_asic_adjust_tx_pwr,
#endif /* RTMP_TEMPERATURE_TX_ALC */
	.AsicExtraPowerOverMAC = MT76x0_AsicExtraPowerOverMAC,
	
	/* Command handlers */
	.Set_BW_Proc = mt76x0_ate_set_tx_bw_proc,
	.Set_FREQ_OFFSET_Proc = mt76x0_ate_set_tx_freq_offset_proc,

	/* Variables */
	.maxTxPwrCnt = 5,
	.bBBPStoreTXCARR = FALSE,
	.bBBPStoreTXCARRSUPP = FALSE,	
	.bBBPStoreTXCONT = FALSE,
	.bBBPLoadATESTOP = FALSE,
};

