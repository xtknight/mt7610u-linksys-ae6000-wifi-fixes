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


#ifdef SCAN_SUPPORT
static INT scan_ch_restore(RTMP_ADAPTER *pAd, UCHAR OpMode)
{
#ifdef CONFIG_STA_SUPPORT
	USHORT Status;
#endif /* CONFIG_STA_SUPPORT */
	INT bw, ch;
	
	//printk("pAd->hw_cfg.bbp_bw = %d\n", pAd->hw_cfg.bbp_bw);	
	if (pAd->CommonCfg.BBPCurrentBW != pAd->hw_cfg.bbp_bw)
	{	
		rtmp_bbp_set_bw(pAd, pAd->hw_cfg.bbp_bw);

		AsicSwitchChannel(pAd, pAd->CommonCfg.CentralChannel, FALSE);
		AsicLockChannel(pAd, pAd->CommonCfg.CentralChannel);

		ch = pAd->CommonCfg.CentralChannel;
	}
	else
	{
		AsicSwitchChannel(pAd, pAd->CommonCfg.Channel, FALSE);
		AsicLockChannel(pAd, pAd->CommonCfg.Channel);
		ch = pAd->CommonCfg.Channel;

	}

	switch(pAd->CommonCfg.BBPCurrentBW)
	{
		case BW_80:
			bw = 80;
			break;
		case BW_40:
			bw = 40;
			break;
		case BW_10:
			bw = 10;
			break;
		case BW_20:
		default:
			bw =20;
			break;
	}
	DBGPRINT(RT_DEBUG_TRACE, ("SYNC - End of SCAN, restore to %dMHz channel %d, Total BSS[%02d]\n",
				bw, ch, pAd->ScanTab.BssNr));

#ifdef CONFIG_STA_SUPPORT
	if (OpMode == OPMODE_STA)
	{
		/*
		If all peer Ad-hoc clients leave, driver would do LinkDown and LinkUp.
		In LinkUp, CommonCfg.Ssid would copy SSID from MlmeAux. 
		To prevent SSID is zero or wrong in Beacon, need to recover MlmeAux.SSID here.
		*/
		if (ADHOC_ON(pAd))
		{
			NdisZeroMemory(pAd->MlmeAux.Ssid, MAX_LEN_OF_SSID);
			pAd->MlmeAux.SsidLen = pAd->CommonCfg.SsidLen;
			NdisMoveMemory(pAd->MlmeAux.Ssid, pAd->CommonCfg.Ssid, pAd->CommonCfg.SsidLen);
		}


		/*
		To prevent data lost.
		Send an NULL data with turned PSM bit on to current associated AP before SCAN progress.
		Now, we need to send an NULL data with turned PSM bit off to AP, when scan progress done 
		*/
		if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_MEDIA_STATE_CONNECTED) && (INFRA_ON(pAd)))
		{
			RTMPSendNullFrame(pAd, 
								pAd->CommonCfg.TxRate, 
								(OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_WMM_INUSED) ? TRUE:FALSE),
								pAd->CommonCfg.bAPSDForcePowerSave ? PWR_SAVE : pAd->StaCfg.Psm);
			DBGPRINT(RT_DEBUG_TRACE, ("%s -- Send null frame\n", __FUNCTION__));
		}

		/* keep the latest scan channel, could be 0 for scan complete, or other channel*/
		pAd->StaCfg.LastScanChannel = pAd->MlmeAux.Channel;

		pAd->StaCfg.ScanChannelCnt = 0;

		/* Suspend scanning and Resume TxData for Fast Scanning*/
		if ((pAd->MlmeAux.Channel != 0) &&
		(pAd->StaCfg.bImprovedScan))	/* it is scan pending*/
		{
			pAd->Mlme.SyncMachine.CurrState = SCAN_PENDING;
			Status = MLME_SUCCESS;
			DBGPRINT(RT_DEBUG_WARN, ("bFastRoamingScan ~~~ Get back to send data ~~~\n"));

			RTMPResumeMsduTransmission(pAd);
		}
		else
		{
			pAd->StaCfg.BssNr = pAd->ScanTab.BssNr;
			pAd->StaCfg.bImprovedScan = FALSE;

			pAd->Mlme.SyncMachine.CurrState = SYNC_IDLE;
			Status = MLME_SUCCESS;
			MlmeEnqueue(pAd, MLME_CNTL_STATE_MACHINE, MT2_SCAN_CONF, 2, &Status, 0);
			RTMP_MLME_HANDLER(pAd);
		}

#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
		RTEnqueueInternalCmd(pAd, CMDTHREAD_SCAN_END, NULL, 0);
#endif /* RT_CFG80211_SUPPORT */
#endif /* LINUX */
	}
#endif /* CONFIG_STA_SUPPORT */



	return TRUE;
}



static INT scan_active(RTMP_ADAPTER *pAd, UCHAR OpMode, UCHAR ScanType)
{
	UCHAR *frm_buf = NULL;
	HEADER_802_11 Hdr80211;
	ULONG FrameLen = 0;
	UCHAR SsidLen = 0;
#ifdef CONFIG_STA_SUPPORT
	USHORT Status;
#endif /* CONFIG_STA_SUPPORT */


	if (MlmeAllocateMemory(pAd, &frm_buf) != NDIS_STATUS_SUCCESS)
	{
		DBGPRINT(RT_DEBUG_TRACE, ("SYNC - ScanNextChannel() allocate memory fail\n"));
#ifdef CONFIG_STA_SUPPORT
		if (OpMode == OPMODE_STA)
		{
			pAd->Mlme.SyncMachine.CurrState = SYNC_IDLE;
			Status = MLME_FAIL_NO_RESOURCE;
			MlmeEnqueue(pAd, MLME_CNTL_STATE_MACHINE, MT2_SCAN_CONF, 2, &Status, 0);
		}
#endif /* CONFIG_STA_SUPPORT */

		return FALSE;
	}

#ifdef DOT11_N_SUPPORT
#ifdef DOT11N_DRAFT3
	if (ScanType == SCAN_2040_BSS_COEXIST)
	{
		DBGPRINT(RT_DEBUG_INFO, ("SYNC - SCAN_2040_BSS_COEXIST !! Prepare to send Probe Request\n"));
	}
#endif /* DOT11N_DRAFT3 */
#endif /* DOT11_N_SUPPORT */
	
	/* There is no need to send broadcast probe request if active scan is in effect.*/
	SsidLen = 0;
	if ((ScanType == SCAN_ACTIVE) || (ScanType == FAST_SCAN_ACTIVE)
		)
		SsidLen = pAd->MlmeAux.SsidLen;

	{
#ifdef CONFIG_STA_SUPPORT
		/*IF_DEV_CONFIG_OPMODE_ON_STA(pAd) */
		if (OpMode == OPMODE_STA)
		{
			MgtMacHeaderInit(pAd, &Hdr80211, SUBTYPE_PROBE_REQ, 0, BROADCAST_ADDR, 
								BROADCAST_ADDR);
		}
#endif /* CONFIG_STA_SUPPORT */

		MakeOutgoingFrame(frm_buf,               &FrameLen,
						  sizeof(HEADER_802_11),    &Hdr80211,
						  1,                        &SsidIe,
						  1,                        &SsidLen,
						  SsidLen,			        pAd->MlmeAux.Ssid,
						  1,                        &SupRateIe,
						  1,                        &pAd->CommonCfg.SupRateLen,
						  pAd->CommonCfg.SupRateLen,  pAd->CommonCfg.SupRate, 
						  END_OF_ARGS);

		if (pAd->CommonCfg.ExtRateLen)
		{
			ULONG Tmp;
			MakeOutgoingFrame(frm_buf + FrameLen,            &Tmp,
							  1,                                &ExtRateIe,
							  1,                                &pAd->CommonCfg.ExtRateLen,
							  pAd->CommonCfg.ExtRateLen,          pAd->CommonCfg.ExtRate, 
							  END_OF_ARGS);
			FrameLen += Tmp;
		}
	}
#ifdef DOT11_N_SUPPORT
	if (WMODE_CAP_N(pAd->CommonCfg.PhyMode))
	{
		ULONG	Tmp;
		UCHAR	HtLen;
		UCHAR	BROADCOM[4] = {0x0, 0x90, 0x4c, 0x33};
#ifdef RT_BIG_ENDIAN
		HT_CAPABILITY_IE HtCapabilityTmp;
#endif
		if (pAd->bBroadComHT == TRUE)
		{
			HtLen = pAd->MlmeAux.HtCapabilityLen + 4;
#ifdef RT_BIG_ENDIAN
			NdisMoveMemory(&HtCapabilityTmp, &pAd->MlmeAux.HtCapability, SIZE_HT_CAP_IE);
			*(USHORT *)(&HtCapabilityTmp.HtCapInfo) = SWAP16(*(USHORT *)(&HtCapabilityTmp.HtCapInfo));
#ifdef UNALIGNMENT_SUPPORT
			{
				EXT_HT_CAP_INFO extHtCapInfo;

				NdisMoveMemory((PUCHAR)(&extHtCapInfo), (PUCHAR)(&HtCapabilityTmp.ExtHtCapInfo), sizeof(EXT_HT_CAP_INFO));
				*(USHORT *)(&extHtCapInfo) = cpu2le16(*(USHORT *)(&extHtCapInfo));
				NdisMoveMemory((PUCHAR)(&HtCapabilityTmp.ExtHtCapInfo), (PUCHAR)(&extHtCapInfo), sizeof(EXT_HT_CAP_INFO));		
			}
#else				
			*(USHORT *)(&HtCapabilityTmp.ExtHtCapInfo) = cpu2le16(*(USHORT *)(&HtCapabilityTmp.ExtHtCapInfo));
#endif /* UNALIGNMENT_SUPPORT */

			MakeOutgoingFrame(frm_buf + FrameLen,          &Tmp,
							1,                                &WpaIe,
							1,                                &HtLen,
							4,                                &BROADCOM[0],
							pAd->MlmeAux.HtCapabilityLen,     &HtCapabilityTmp, 
							END_OF_ARGS);
#else
			MakeOutgoingFrame(frm_buf + FrameLen,          &Tmp,
							1,                                &WpaIe,
							1,                                &HtLen,
							4,                                &BROADCOM[0],
							pAd->MlmeAux.HtCapabilityLen,     &pAd->MlmeAux.HtCapability, 
							END_OF_ARGS);
#endif /* RT_BIG_ENDIAN */
		}
		else				
		{
			HtLen = sizeof(HT_CAPABILITY_IE);
#ifdef RT_BIG_ENDIAN
			NdisMoveMemory(&HtCapabilityTmp, &pAd->CommonCfg.HtCapability, SIZE_HT_CAP_IE);
			*(USHORT *)(&HtCapabilityTmp.HtCapInfo) = SWAP16(*(USHORT *)(&HtCapabilityTmp.HtCapInfo));
#ifdef UNALIGNMENT_SUPPORT
			{
				EXT_HT_CAP_INFO extHtCapInfo;

				NdisMoveMemory((PUCHAR)(&extHtCapInfo), (PUCHAR)(&HtCapabilityTmp.ExtHtCapInfo), sizeof(EXT_HT_CAP_INFO));
				*(USHORT *)(&extHtCapInfo) = cpu2le16(*(USHORT *)(&extHtCapInfo));
				NdisMoveMemory((PUCHAR)(&HtCapabilityTmp.ExtHtCapInfo), (PUCHAR)(&extHtCapInfo), sizeof(EXT_HT_CAP_INFO));		
			}
#else				
			*(USHORT *)(&HtCapabilityTmp.ExtHtCapInfo) = cpu2le16(*(USHORT *)(&HtCapabilityTmp.ExtHtCapInfo));
#endif /* UNALIGNMENT_SUPPORT */

			MakeOutgoingFrame(frm_buf + FrameLen,          &Tmp,
							1,                                &HtCapIe,
							1,                                &HtLen,
							HtLen,                            &HtCapabilityTmp, 
							END_OF_ARGS);
#else
			MakeOutgoingFrame(frm_buf + FrameLen,          &Tmp,
							1,                                &HtCapIe,
							1,                                &HtLen,
							HtLen,                            &pAd->CommonCfg.HtCapability, 
							END_OF_ARGS);
#endif /* RT_BIG_ENDIAN */
		}
		FrameLen += Tmp;

#ifdef DOT11N_DRAFT3
		if ((pAd->MlmeAux.Channel <= 14) && (pAd->CommonCfg.bBssCoexEnable == TRUE))
		{
			ULONG Tmp;
			HtLen = 1;
			MakeOutgoingFrame(frm_buf + FrameLen,            &Tmp,
							  1,					&ExtHtCapIe,
							  1,					&HtLen,
							  1,          			&pAd->CommonCfg.BSSCoexist2040.word, 
							  END_OF_ARGS);

			FrameLen += Tmp;
		}
#endif /* DOT11N_DRAFT3 */
	}
#endif /* DOT11_N_SUPPORT */

#ifdef DOT11_VHT_AC
	if (WMODE_CAP_AC(pAd->CommonCfg.PhyMode) &&
		(pAd->MlmeAux.Channel > 14)) {		
		FrameLen += build_vht_ies(pAd, (UCHAR *)(frm_buf + FrameLen), SUBTYPE_PROBE_REQ);
	}
#endif /* DOT11_VHT_AC */


#ifdef WPA_SUPPLICANT_SUPPORT
	if ((OpMode == OPMODE_STA) &&
		(pAd->StaCfg.WpaSupplicantUP != WPA_SUPPLICANT_DISABLE) &&
		(pAd->StaCfg.WpsProbeReqIeLen != 0))
	{
		ULONG 		WpsTmpLen = 0;
		
		MakeOutgoingFrame(frm_buf + FrameLen,              &WpsTmpLen,
						pAd->StaCfg.WpsProbeReqIeLen,	pAd->StaCfg.pWpsProbeReqIe,
						END_OF_ARGS);

		FrameLen += WpsTmpLen;
	}
#endif /* WPA_SUPPLICANT_SUPPORT */


	MiniportMMRequest(pAd, 0, frm_buf, FrameLen);

#ifdef CONFIG_STA_SUPPORT
	if (OpMode == OPMODE_STA)
	{
		/*
			To prevent data lost.
			Send an NULL data with turned PSM bit on to current associated AP when SCAN in the channel where
			associated AP located.
		*/
		if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_MEDIA_STATE_CONNECTED) && 
			(INFRA_ON(pAd)) &&
			(pAd->CommonCfg.Channel == pAd->MlmeAux.Channel))
		{
			RTMPSendNullFrame(pAd, 
						  pAd->CommonCfg.TxRate, 
						  (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_WMM_INUSED) ? TRUE:FALSE),
						  PWR_SAVE);
			DBGPRINT(RT_DEBUG_TRACE, ("ScanNextChannel():Send PWA NullData frame to notify the associated AP!\n"));
		}
	}
#endif /* CONFIG_STA_SUPPORT */

	MlmeFreeMemory(pAd, frm_buf);

	return TRUE;
}


/*
	==========================================================================
	Description:
		Scan next channel
	==========================================================================
 */
VOID ScanNextChannel(
	IN PRTMP_ADAPTER pAd,
	IN UCHAR OpMode) 
{
	UCHAR ScanType = pAd->MlmeAux.ScanType;
	UINT ScanTimeIn5gChannel = SHORT_CHANNEL_TIME;
	BOOLEAN ScanPending = FALSE;
	RALINK_TIMER_STRUCT *sc_timer;
	UINT stay_time = 0;
	UCHAR ImprovedScan_MaxScanChannelCnt;
			

#ifdef RALINK_ATE
	/* Nothing to do in ATE mode. */
	if (ATE_ON(pAd))
		return;
#endif /* RALINK_ATE */


#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		if (MONITOR_ON(pAd))
			return;
	}

#ifdef WIFI_P2P_CONCURRENT_FAST_SCAN
	ImprovedScan_MaxScanChannelCnt = 3;
#else
	ImprovedScan_MaxScanChannelCnt = 7;
#endif /* WIFI_P2P_CONCURRENT_FAST_SCAN */
	ScanPending = ((pAd->StaCfg.bImprovedScan) && (pAd->StaCfg.ScanChannelCnt>=ImprovedScan_MaxScanChannelCnt));
#endif /* CONFIG_STA_SUPPORT */


	if ((pAd->MlmeAux.Channel == 0) || ScanPending) 
	{
		scan_ch_restore(pAd, OpMode);
	} 
#ifdef RTMP_MAC_USB
#ifdef CONFIG_STA_SUPPORT
	else if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST) &&
		(OpMode == OPMODE_STA))
	{
		pAd->Mlme.SyncMachine.CurrState = SYNC_IDLE;
		MlmeCntlConfirm(pAd, MT2_SCAN_CONF, MLME_FAIL_NO_RESOURCE);
	}	
#endif /* CONFIG_STA_SUPPORT */
#endif /* RTMP_MAC_USB */
	else 
	{
#ifdef CONFIG_STA_SUPPORT
		if (OpMode == OPMODE_STA)
		{
			/* BBP and RF are not accessible in PS mode, we has to wake them up first*/
			if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_DOZE))
				AsicForceWakeup(pAd, TRUE);

			/* leave PSM during scanning. otherwise we may lost ProbeRsp & BEACON*/
			if (pAd->StaCfg.Psm == PWR_SAVE)
				RTMP_SET_PSM_BIT(pAd, PWR_ACTIVE);
		}
#endif /* CONFIG_STA_SUPPORT */

		AsicSwitchChannel(pAd, pAd->MlmeAux.Channel, TRUE);
		AsicLockChannel(pAd, pAd->MlmeAux.Channel);

#ifdef CONFIG_STA_SUPPORT
		if (OpMode == OPMODE_STA)
		{
			BOOLEAN bScanPassive = FALSE;
			if (pAd->MlmeAux.Channel > 14)
			{
				if ((pAd->CommonCfg.bIEEE80211H == 1)
					&& RadarChannelCheck(pAd, pAd->MlmeAux.Channel))
					bScanPassive = TRUE;
			}
#ifdef CARRIER_DETECTION_SUPPORT
			if (pAd->CommonCfg.CarrierDetect.Enable == TRUE)
				bScanPassive = TRUE;
#endif /* CARRIER_DETECTION_SUPPORT */ 

			if (bScanPassive)
			{
				ScanType = SCAN_PASSIVE;
				ScanTimeIn5gChannel = MIN_CHANNEL_TIME;
			}
		}

#endif /* CONFIG_STA_SUPPORT */

		/* Check if channel if passive scan under current regulatory domain */
		if (CHAN_PropertyCheck(pAd, pAd->MlmeAux.Channel, CHANNEL_PASSIVE_SCAN) == TRUE)
			ScanType = SCAN_PASSIVE;


		if (OpMode == OPMODE_AP)
			sc_timer = &pAd->MlmeAux.APScanTimer;
		else
			sc_timer = &pAd->MlmeAux.ScanTimer;
			
		/* We need to shorten active scan time in order for WZC connect issue */
		/* Chnage the channel scan time for CISCO stuff based on its IAPP announcement */
		if (ScanType == FAST_SCAN_ACTIVE)
			stay_time = FAST_ACTIVE_SCAN_TIME;
		else /* must be SCAN_PASSIVE or SCAN_ACTIVE*/
		{
#ifdef CONFIG_STA_SUPPORT
			pAd->StaCfg.ScanChannelCnt++;
#endif /* CONFIG_STA_SUPPORT */

			if (WMODE_CAP_2G(pAd->CommonCfg.PhyMode) &&
				WMODE_CAP_5G(pAd->CommonCfg.PhyMode))
			{
				if (pAd->MlmeAux.Channel > 14)
					stay_time = ScanTimeIn5gChannel;
				else
					stay_time = MIN_CHANNEL_TIME;
			}
#ifdef WIFI_P2P_CONCURRENT_FAST_SCAN
            /* If this is not PASSIVE scan && Fast scan is enabled, we shorten the chanenl dwell time */
            else if (ScanType != SCAN_PASSIVE && pAd->StaCfg.bImprovedScan)
                stay_time = FAST_ACTIVE_SCAN_TIME;
#endif /* WIFI_P2P_CONCURRENT_FAST_SCAN */
			else
				stay_time = MAX_CHANNEL_TIME;
		}
				
		RTMPSetTimer(sc_timer, stay_time);
			
		if (SCAN_MODE_ACT(ScanType))
		{
			if (scan_active(pAd, OpMode, ScanType) == FALSE)
				return;
		}

		/* For SCAN_CISCO_PASSIVE, do nothing and silently wait for beacon or other probe reponse*/
		
#ifdef CONFIG_STA_SUPPORT
		if (OpMode == OPMODE_STA)
			pAd->Mlme.SyncMachine.CurrState = SCAN_LISTEN;
#endif /* CONFIG_STA_SUPPORT */
	}
}


BOOLEAN ScanRunning(
		IN PRTMP_ADAPTER pAd)
{
	BOOLEAN	rv = FALSE;

#ifdef CONFIG_STA_SUPPORT
		IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
		{
			if ((pAd->Mlme.SyncMachine.CurrState == SCAN_LISTEN) || (pAd->Mlme.SyncMachine.CurrState == SCAN_PENDING))
				rv = TRUE;
		}
#endif /* CONFIG_STA_SUPPORT */

	return rv;
}

#endif /* SCAN_SUPPORT */

