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


#include <rt_config.h>


VOID mgmt_tb_set_mcast_entry(RTMP_ADAPTER *pAd)
{
	MAC_TABLE_ENTRY *pEntry = &pAd->MacTab.Content[MCAST_WCID];
	
	pEntry->Sst = SST_ASSOC;
	pEntry->Aid = MCAST_WCID;	/* Softap supports 1 BSSID and use WCID=0 as multicast Wcid index*/
	pEntry->PsMode = PWR_ACTIVE;
	pEntry->CurrTxRate = pAd->CommonCfg.MlmeRate; 
}


VOID set_entry_phy_cfg(RTMP_ADAPTER *pAd, MAC_TABLE_ENTRY *pEntry)
{

	if (pEntry->MaxSupportedRate < RATE_FIRST_OFDM_RATE)
	{
		pEntry->MaxHTPhyMode.field.MODE = MODE_CCK;
		pEntry->MaxHTPhyMode.field.MCS = pEntry->MaxSupportedRate;
		pEntry->MinHTPhyMode.field.MODE = MODE_CCK;
		pEntry->MinHTPhyMode.field.MCS = pEntry->MaxSupportedRate;
		pEntry->HTPhyMode.field.MODE = MODE_CCK;
		pEntry->HTPhyMode.field.MCS = pEntry->MaxSupportedRate;
	}
	else
	{
		pEntry->MaxHTPhyMode.field.MODE = MODE_OFDM;
		pEntry->MaxHTPhyMode.field.MCS = OfdmRateToRxwiMCS[pEntry->MaxSupportedRate];
		pEntry->MinHTPhyMode.field.MODE = MODE_OFDM;
		pEntry->MinHTPhyMode.field.MCS = OfdmRateToRxwiMCS[pEntry->MaxSupportedRate];
		pEntry->HTPhyMode.field.MODE = MODE_OFDM;
		pEntry->HTPhyMode.field.MCS = OfdmRateToRxwiMCS[pEntry->MaxSupportedRate];
	}
}



/*
	==========================================================================
	Description:
		Look up the MAC address in the MAC table. Return NULL if not found.
	Return:
		pEntry - pointer to the MAC entry; NULL is not found
	==========================================================================
*/
MAC_TABLE_ENTRY *MacTableLookup(
	IN PRTMP_ADAPTER pAd,
	PUCHAR pAddr)
{
	ULONG HashIdx;
	MAC_TABLE_ENTRY *pEntry = NULL;
	
	HashIdx = MAC_ADDR_HASH_INDEX(pAddr);
	pEntry = pAd->MacTab.Hash[HashIdx];

	while (pEntry && !IS_ENTRY_NONE(pEntry))
	{
		if (MAC_ADDR_EQUAL(pEntry->Addr, pAddr))
		{
			break;
		}
		else
			pEntry = pEntry->pNext;
	}

	return pEntry;
}


MAC_TABLE_ENTRY *MacTableInsertEntry(
	IN  PRTMP_ADAPTER   pAd,
	IN  PUCHAR			pAddr,
	IN	UCHAR			apidx,
	IN	UCHAR			OpMode,
	IN BOOLEAN	CleanAll)
{
	UCHAR HashIdx;
	int i, FirstWcid;
	MAC_TABLE_ENTRY *pEntry = NULL, *pCurrEntry;
/*	USHORT	offset;*/
/*	ULONG	addr;*/
	BOOLEAN Cancelled;
	UINT32 MaxWcidNum = MAX_LEN_OF_MAC_TABLE;
#ifdef MAC_REPEATER_SUPPORT
	BOOLEAN bAPCLI = FALSE;
#endif /* MAC_REPEATER_SUPPORT */

#ifdef MAC_REPEATER_SUPPORT
	if ((apidx >= MIN_NET_DEVICE_FOR_APCLI) && 
		(apidx < MIN_NET_DEVICE_FOR_MESH) &&
		(pAd->ApCfg.bMACRepeaterEn == TRUE))
	{
		MaxWcidNum = MAX_LEN_OF_MAC_TABLE + (MAX_EXT_MAC_ADDR_SIZE * MAX_APCLI_NUM);
		bAPCLI = TRUE;
	}
#endif /* MAC_REPEATER_SUPPORT */

	/* if FULL, return*/
	if (pAd->MacTab.Size >= MaxWcidNum)
		return NULL;

#ifdef MAC_REPEATER_SUPPORT
	if (bAPCLI)
		FirstWcid = 3;
	else
#endif /* MAC_REPEATER_SUPPORT */
	FirstWcid = 1;
#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	if (pAd->StaCfg.BssType == BSS_INFRA)
		FirstWcid = 2;
#endif /* CONFIG_STA_SUPPORT */

	/* allocate one MAC entry*/
	NdisAcquireSpinLock(&pAd->MacTabLock);
	for (i = FirstWcid; i< MaxWcidNum; i++)   /* skip entry#0 so that "entry index == AID" for fast lookup*/
	{
		/* pick up the first available vacancy*/
		if (IS_ENTRY_NONE(&pAd->MacTab.Content[i]))
		{
			pEntry = &pAd->MacTab.Content[i];

			/* ENTRY PREEMPTION: initialize the entry */
			RTMPCancelTimer(&pEntry->RetryTimer, &Cancelled);
			RTMPCancelTimer(&pEntry->EnqueueStartForPSKTimer, &Cancelled);

			NdisZeroMemory(pEntry, sizeof(MAC_TABLE_ENTRY));

#ifdef WFA_VHT_PF
#ifdef IP_ASSEMBLY
			if (pEntry->ip_queue_inited == 0) {
				int q_idx, ac_idx;
				struct ip_frag_q *fragQ = &pEntry->ip_fragQ[q_idx];
				
				for (ac_idx = 0; ac_idx < 4; ac_idx++) {
					InitializeQueueHeader(&pEntry->ip_queue1[ac_idx]);
					InitializeQueueHeader(&pEntry->ip_queue2[ac_idx]);
					pEntry->ip_id1[ac_idx] = pEntry->ip_id2[ac_idx] = -1;
					pEntry->ip_id1_FragSize[ac_idx] = pEntry->ip_id2_FragSize[ac_idx] = -1;
				}
				pEntry->ip_queue_inited = 1;
			}
#endif /* IP_ASSEMBLY */
#endif /* WFA_VHT_PF */

			if (CleanAll == TRUE)
			{
				pEntry->MaxSupportedRate = RATE_11;
				pEntry->CurrTxRate = RATE_11;
				NdisZeroMemory(pEntry, sizeof(MAC_TABLE_ENTRY));
				pEntry->PairwiseKey.KeyLen = 0;
				pEntry->PairwiseKey.CipherAlg = CIPHER_NONE;
			}

			do
			{
#ifdef CONFIG_STA_SUPPORT
#ifdef QOS_DLS_SUPPORT
			if (apidx >= MIN_NET_DEVICE_FOR_DLS)
			{
				SET_ENTRY_DLS(pEntry);
				pEntry->isCached = FALSE;
				break;
			}
			else
#endif /* QOS_DLS_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */



						SET_ENTRY_CLIENT(pEntry);

		} while (FALSE);

			pEntry->bIAmBadAtheros = FALSE;

			RTMPInitTimer(pAd, &pEntry->EnqueueStartForPSKTimer, GET_TIMER_FUNCTION(EnqueueStartForPSKExec), pEntry, FALSE);

#ifdef CONFIG_STA_SUPPORT
#endif /* CONFIG_STA_SUPPORT */


#ifdef TXBF_SUPPORT
			if (pAd->chipCap.FlgHwTxBfCap)
				RTMPInitTimer(pAd, &pEntry->eTxBfProbeTimer, GET_TIMER_FUNCTION(eTxBfProbeTimerExec), pEntry, FALSE);
#endif /* TXBF_SUPPORT */

			pEntry->pAd = pAd;
			pEntry->CMTimerRunning = FALSE;
			pEntry->EnqueueEapolStartTimerRunning = EAPOL_START_DISABLE;
			pEntry->RSNIE_Len = 0;
			NdisZeroMemory(pEntry->R_Counter, sizeof(pEntry->R_Counter));
			pEntry->ReTryCounter = PEER_MSG1_RETRY_TIMER_CTR;

			if (IS_ENTRY_MESH(pEntry))
				pEntry->apidx = (apidx - MIN_NET_DEVICE_FOR_MESH);
			else if (IS_ENTRY_APCLI(pEntry))
				pEntry->apidx = (apidx - MIN_NET_DEVICE_FOR_APCLI);
			else if (IS_ENTRY_WDS(pEntry))
				pEntry->apidx = (apidx - MIN_NET_DEVICE_FOR_WDS);
#ifdef CONFIG_STA_SUPPORT
#ifdef QOS_DLS_SUPPORT
			else if (IS_ENTRY_DLS(pEntry))
				pEntry->apidx = (apidx - MIN_NET_DEVICE_FOR_DLS);
#endif /* QOS_DLS_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */
			else
				pEntry->apidx = apidx;


			do
			{


#ifdef CONFIG_STA_SUPPORT
				IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
				{
					pEntry->AuthMode = pAd->StaCfg.AuthMode;
					pEntry->WepStatus = pAd->StaCfg.WepStatus;
					pEntry->PrivacyFilter = Ndis802_11PrivFilterAcceptAll;
				}
#endif /* CONFIG_STA_SUPPORT */
			} while (FALSE);

			pEntry->GTKState = REKEY_NEGOTIATING;
			pEntry->PairwiseKey.KeyLen = 0;
			pEntry->PairwiseKey.CipherAlg = CIPHER_NONE;
#ifdef CONFIG_STA_SUPPORT
#ifdef QOS_DLS_SUPPORT
			if (IS_ENTRY_DLS(pEntry))
				pEntry->PortSecured = WPA_802_1X_PORT_SECURED;
			else
#endif /* QOS_DLS_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */
				pEntry->PortSecured = WPA_802_1X_PORT_NOT_SECURED;

			pEntry->PMKID_CacheIdx = ENTRY_NOT_FOUND;
			COPY_MAC_ADDR(pEntry->Addr, pAddr);
			COPY_MAC_ADDR(pEntry->HdrAddr1, pAddr);

			do
			{
#ifdef APCLI_SUPPORT
				if (IS_ENTRY_APCLI(pEntry))
				{
					COPY_MAC_ADDR(pEntry->HdrAddr2, pAd->ApCfg.ApCliTab[pEntry->apidx].CurrentAddress);
					COPY_MAC_ADDR(pEntry->HdrAddr3, pAddr);
					break;
				}
#endif // APCLI_SUPPORT //
#ifdef WDS_SUPPORT
				if (IS_ENTRY_WDS(pEntry))
				{
					COPY_MAC_ADDR(pEntry->HdrAddr2, pAd->ApCfg.MBSSID[MAIN_MBSSID].Bssid);
					COPY_MAC_ADDR(pEntry->HdrAddr3, pAd->ApCfg.MBSSID[MAIN_MBSSID].Bssid);
					break;
				}
#endif // WDS_SUPPORT //
#ifdef CONFIG_STA_SUPPORT
				if (OpMode == OPMODE_STA)
				{
					COPY_MAC_ADDR(pEntry->HdrAddr2, pAd->CurrentAddress);
					COPY_MAC_ADDR(pEntry->HdrAddr3, pAddr);
					break;
				}
#endif // CONFIG_STA_SUPPORT //
			} while (FALSE);

			pEntry->Sst = SST_NOT_AUTH;
			pEntry->AuthState = AS_NOT_AUTH;
			pEntry->Aid = (USHORT)i;  /*0;*/
			pEntry->CapabilityInfo = 0;
			pEntry->PsMode = PWR_ACTIVE;
			pEntry->PsQIdleCount = 0;
			pEntry->NoDataIdleCount = 0;
			pEntry->AssocDeadLine = MAC_TABLE_ASSOC_TIMEOUT;
			pEntry->ContinueTxFailCnt = 0;
#ifdef WDS_SUPPORT
			pEntry->LockEntryTx = FALSE;
#endif /* WDS_SUPPORT */
			pEntry->TimeStamp_toTxRing = 0;
			InitializeQueueHeader(&pEntry->PsQueue);

#ifdef STREAM_MODE_SUPPORT
			/* Enable Stream mode for first three entries in MAC table */

#endif /* STREAM_MODE_SUPPORT */


			pAd->MacTab.Size ++;

			/* Set the security mode of this entry as OPEN-NONE in ASIC */
			RTMP_REMOVE_PAIRWISE_KEY_ENTRY(pAd, (UCHAR)i);

			/* Add this entry into ASIC RX WCID search table */
			RTMP_STA_ENTRY_ADD(pAd, pEntry);



#ifdef TXBF_SUPPORT
			if (pAd->chipCap.FlgHwTxBfCap)
				NdisAllocateSpinLock(pAd, &pEntry->TxSndgLock);
#endif /* TXBF_SUPPORT */

			DBGPRINT(RT_DEBUG_TRACE, ("MacTableInsertEntry - allocate entry #%d, Total= %d\n",i, pAd->MacTab.Size));
			break;
		}
	}

	/* add this MAC entry into HASH table */
	if (pEntry)
	{

		HashIdx = MAC_ADDR_HASH_INDEX(pAddr);
		if (pAd->MacTab.Hash[HashIdx] == NULL)
		{
			pAd->MacTab.Hash[HashIdx] = pEntry;
		}
		else
		{
			pCurrEntry = pAd->MacTab.Hash[HashIdx];
			while (pCurrEntry->pNext != NULL)
				pCurrEntry = pCurrEntry->pNext;
			pCurrEntry->pNext = pEntry;
		}


	}

	NdisReleaseSpinLock(&pAd->MacTabLock);
	return pEntry;
}


/*
	==========================================================================
	Description:
		Delete a specified client from MAC table
	==========================================================================
 */
BOOLEAN MacTableDeleteEntry(
	IN PRTMP_ADAPTER pAd,
	IN USHORT wcid,
	IN PUCHAR pAddr)
{
	USHORT HashIdx;
	MAC_TABLE_ENTRY *pEntry, *pPrevEntry, *pProbeEntry;
	BOOLEAN Cancelled;
	/*USHORT	offset;	 unused variable*/
	/*UCHAR	j;			 unused variable*/

	if (wcid >= MAX_LEN_OF_MAC_TABLE)
		return FALSE;

	NdisAcquireSpinLock(&pAd->MacTabLock);

	HashIdx = MAC_ADDR_HASH_INDEX(pAddr);
	/*pEntry = pAd->MacTab.Hash[HashIdx];*/
	pEntry = &pAd->MacTab.Content[wcid];

	if (pEntry && !IS_ENTRY_NONE(pEntry))
	{
		/* ENTRY PREEMPTION: Cancel all timers */
		RTMPCancelTimer(&pEntry->RetryTimer, &Cancelled);
		RTMPCancelTimer(&pEntry->EnqueueStartForPSKTimer, &Cancelled);

		if (MAC_ADDR_EQUAL(pEntry->Addr, pAddr))
		{

			/* Delete this entry from ASIC on-chip WCID Table*/
			RTMP_STA_ENTRY_MAC_RESET(pAd, wcid);

#ifdef DOT11_N_SUPPORT
			/* free resources of BA*/
			BASessionTearDownALL(pAd, pEntry->Aid);
#endif /* DOT11_N_SUPPORT */

#ifdef TXBF_SUPPORT
			if (pAd->chipCap.FlgHwTxBfCap)
				RTMPReleaseTimer(&pEntry->eTxBfProbeTimer, &Cancelled);
#endif /* TXBF_SUPPORT */

#ifdef STREAM_MODE_SUPPORT
			/* Clear Stream Mode register for this client */
			if (pEntry->StreamModeMACReg != 0)
				RTMP_IO_WRITE32(pAd, pEntry->StreamModeMACReg+4, 0);
#endif // STREAM_MODE_SUPPORT //


#ifdef CONFIG_STA_SUPPORT
#endif /* CONFIG_STA_SUPPORT */

           
			pPrevEntry = NULL;
			pProbeEntry = pAd->MacTab.Hash[HashIdx];
			ASSERT(pProbeEntry);
			if (pProbeEntry != NULL)
			{
				/* update Hash list*/
				do
				{
					if (pProbeEntry == pEntry)
					{
						if (pPrevEntry == NULL)
						{
							pAd->MacTab.Hash[HashIdx] = pEntry->pNext;
						}
						else
						{
							pPrevEntry->pNext = pEntry->pNext;
						}
						break;
					}

					pPrevEntry = pProbeEntry;
					pProbeEntry = pProbeEntry->pNext;
				} while (pProbeEntry);
			}

			/* not found !!!*/
			ASSERT(pProbeEntry != NULL);

			/*RTMP_REMOVE_PAIRWISE_KEY_ENTRY(pAd, wcid);*/

#ifdef WFA_VHT_PF
#ifdef IP_ASSEMBLY
			if (pAd->ip_assemble == TRUE)
			{
				if (pEntry->ip_queue_inited)
				{
					PQUEUE_ENTRY qe;
					PNDIS_PACKET q_pkt;

					qe = pEntry->ip_queue1;
					while (qe->Head)
					{
						DBGPRINT(RT_DEBUG_TRACE, ("%s():%ld...\n", __FUNCTION__, qe->Number));

						pEntry = RemoveHeadQueue(qe);
						/*pPacket = CONTAINING_RECORD(pEntry, NDIS_PACKET, MiniportReservedEx); */
						q_pkt = QUEUE_ENTRY_TO_PACKET(pEntry);
						RELEASE_NDIS_PACKET(pAd, q_pkt, NDIS_STATUS_FAILURE);
					}
					pEntry->ip_queue_inited = 0;
				}
			}
#endif /* IP_ASSEMBLY */
#endif /* WFA_VHT_PF */

#ifdef UAPSD_SUPPORT
#endif /* UAPSD_SUPPORT */

		if (pEntry->EnqueueEapolStartTimerRunning != EAPOL_START_DISABLE)
		{
            RTMPCancelTimer(&pEntry->EnqueueStartForPSKTimer, &Cancelled);
			pEntry->EnqueueEapolStartTimerRunning = EAPOL_START_DISABLE;
        }
		RTMPReleaseTimer(&pEntry->EnqueueStartForPSKTimer, &Cancelled);




//   			NdisZeroMemory(pEntry, sizeof(MAC_TABLE_ENTRY));
//			NdisZeroMemory(pEntry->Addr, MAC_ADDR_LEN);
//			/* invalidate the entry */
//			SET_ENTRY_NONE(pEntry);

//                      NdisZeroMemory(pEntry, sizeof(MAC_TABLE_ENTRY));
                        NdisZeroMemory(pEntry->Addr, MAC_ADDR_LEN);
                        /* invalidate the entry */
                        SET_ENTRY_NONE(pEntry);

			pAd->MacTab.Size --;
#ifdef TXBF_SUPPORT
			if (pAd->chipCap.FlgHwTxBfCap)
				NdisFreeSpinLock(&pEntry->TxSndgLock);
#endif /* TXBF_SUPPORT */
			DBGPRINT(RT_DEBUG_TRACE, ("MacTableDeleteEntry1 - Total= %d\n", pAd->MacTab.Size));
		}
		else
		{
			DBGPRINT(RT_DEBUG_OFF, ("\n%s: Impossible Wcid = %d !!!!!\n", __FUNCTION__, wcid));
		}
	}

	NdisReleaseSpinLock(&pAd->MacTabLock);

	/*Reset operating mode when no Sta.*/
	if (pAd->MacTab.Size == 0)
	{
#ifdef DOT11_N_SUPPORT
		pAd->CommonCfg.AddHTInfo.AddHtInfo2.OperaionMode = 0;
#endif /* DOT11_N_SUPPORT */
		RTMP_UPDATE_PROTECT(pAd, 0, ALLN_SETPROTECT, TRUE, 0);
	}

	pAd->chipCap.pWeakestEntry = NULL;
	return TRUE;
}


/*
	==========================================================================
	Description:
		This routine reset the entire MAC table. All packets pending in
		the power-saving queues are freed here.
	==========================================================================
 */
VOID MacTableReset(
	IN  PRTMP_ADAPTER  pAd)
{
	int         i;
	BOOLEAN     Cancelled;    

	DBGPRINT(RT_DEBUG_TRACE, ("MacTableReset\n"));
	/*NdisAcquireSpinLock(&pAd->MacTabLock);*/


	for (i=1; i<MAX_LEN_OF_MAC_TABLE; i++)
	{
		if (IS_ENTRY_CLIENT(&pAd->MacTab.Content[i]))
	   {
	   		/* Delete a entry via WCID */

			/*MacTableDeleteEntry(pAd, i, pAd->MacTab.Content[i].Addr);*/
			RTMPReleaseTimer(&pAd->MacTab.Content[i].EnqueueStartForPSKTimer, &Cancelled);
#ifdef CONFIG_STA_SUPPORT
#endif /* CONFIG_STA_SUPPORT */
            pAd->MacTab.Content[i].EnqueueEapolStartTimerRunning = EAPOL_START_DISABLE;


			/* Delete a entry via WCID */
			MacTableDeleteEntry(pAd, i, pAd->MacTab.Content[i].Addr);
		}
		else
		{
			/* Delete a entry via WCID */
			MacTableDeleteEntry(pAd, i, pAd->MacTab.Content[i].Addr);
		}
	}

	return;
}

#ifdef MAC_REPEATER_SUPPORT
MAC_TABLE_ENTRY *InsertMacRepeaterEntry(
	IN  PRTMP_ADAPTER   pAd,
	IN  PUCHAR			pAddr,
	IN  UCHAR			IfIdx)
{
	MAC_TABLE_ENTRY *pEntry = NULL;
	PAPCLI_STRUCT pApCliEntry = NULL;

	os_alloc_mem(NULL, &pEntry, sizeof(MAC_TABLE_ENTRY));

	if (pEntry)
	{
		pApCliEntry = &pAd->ApCfg.ApCliTab[IfIdx];
		pEntry->Aid = pApCliEntry->MacTabWCID + 1; // TODO: We need to record count of STAs
		COPY_MAC_ADDR(pEntry->Addr, pApCliEntry->ApCliMlmeAux.Bssid);
		printk("sn - InsertMacRepeaterEntry: Aid = %d\n", pEntry->Aid);
		hex_dump("sn - InsertMacRepeaterEntry pEntry->Addr", pEntry->Addr, 6);
		/* Add this entry into ASIC RX WCID search table */
		RTMP_STA_ENTRY_ADD(pAd, pEntry);
		os_free_mem(NULL, pEntry);
	}

	return pEntry;
}

#endif /* MAC_REPEATER_SUPPORT */

