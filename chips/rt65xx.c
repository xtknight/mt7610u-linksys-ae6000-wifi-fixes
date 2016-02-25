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


#ifdef RT65xx

#include	"rt_config.h"


/*
	========================================================================
	
	Routine Description:
		Enable Wlan function. this action will enable wlan clock so that chip can accept command. So MUST put in the 
		very beginning of Initialization. And put in the very LAST in the Halt function.

	Arguments:
		pAd		Pointer to our adapter

	Return Value:
		None

	IRQL <= DISPATCH_LEVEL
	
	Note:
		Before Enable RX, make sure you have enabled Interrupt.
	========================================================================
*/
VOID ral_wlan_chip_onoff(
	IN RTMP_ADAPTER *pAd,
	IN BOOLEAN bOn,
	IN BOOLEAN bResetWLAN)
{
	// TODO: check the functionality of the WLAN_FUN_CTRL here, now we just bring up it bu no fine tune.
	WLAN_FUN_CTRL_STRUC WlanFunCtrl = {.word=0};


#ifdef RTMP_MAC_USB
	UINT32 ret;

	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_WAIT(&pAd->wlan_en_atomic, ret);
		if (ret != 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("wlan_en_atomic get failed(ret=%d)\n", ret));
			return;
		}
	}
#endif /* RTMP_MAC_USB */

	RTMP_IO_READ32(pAd, WLAN_FUN_CTRL, &WlanFunCtrl.word);
	DBGPRINT(RT_DEBUG_OFF, ("==>%s(): OnOff:%d, pAd->WlanFunCtrl:0x%x, Reg-WlanFunCtrl=0x%x\n",
				__FUNCTION__, bOn, pAd->WlanFunCtrl.word, WlanFunCtrl.word));

	if (bResetWLAN == TRUE)
	{
		WlanFunCtrl.field.GPIO0_OUT_OE_N = 0xFF;
		WlanFunCtrl.field.FRC_WL_ANT_SET = 0;
	}

	if (bOn == TRUE)
	{
		WlanFunCtrl.field.WLAN_CLK_EN = 1;
		WlanFunCtrl.field.WLAN_EN = 1;
	}
	else
	{
		WlanFunCtrl.field.PCIE_APP0_CLK_REQ = 0;
		WlanFunCtrl.field.WLAN_EN = 0;
		WlanFunCtrl.field.WLAN_CLK_EN = 0;
	}

	DBGPRINT(RT_DEBUG_ERROR, ("WlanFunCtrl.word = 0x%x\n", WlanFunCtrl.word));
	RTMP_IO_FORCE_WRITE32(pAd, WLAN_FUN_CTRL, WlanFunCtrl.word);	
	pAd->WlanFunCtrl.word = WlanFunCtrl.word;
	RTMPusecDelay(2);
	
	RTMP_IO_READ32(pAd, WLAN_FUN_CTRL, &WlanFunCtrl.word);
				DBGPRINT(RT_DEBUG_ERROR, 
		("<== %s():  pAd->WlanFunCtrl.word = 0x%x, Reg->WlanFunCtrl=0x%x!\n",
		__FUNCTION__, pAd->WlanFunCtrl.word, WlanFunCtrl.word));


#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_UP(&pAd->wlan_en_atomic);
	}
#endif /* RTMP_MAC_USB */
}

VOID dump_bw_info(RTMP_ADAPTER *pAd)
{
		UINT32 core_r1, agc_r0, be_r0, band_cfg;
		static UCHAR *bw_str[]={"20", "10", "40", "80"};
		UCHAR bw, prim_ch_idx, decode_cap;
		static UCHAR *decode_str[] = {"0", "20", "40", "20/40",
									"80", "20/80", "40/80", "20/40/80"};
		UCHAR tx_prim;
		RTMP_CHIP_CAP *pChipCap = &pAd->chipCap;


		RTMP_BBP_IO_READ32(pAd, CORE_R1, &core_r1);
		RTMP_BBP_IO_READ32(pAd, AGC1_R0, &agc_r0);
		RTMP_BBP_IO_READ32(pAd, TXBE_R0, &be_r0);
		RTMP_IO_READ32(pAd, TX_BAND_CFG, &band_cfg);
		
		/*  Tx/RX : control channel setting */
		DBGPRINT(RT_DEBUG_TRACE, ("%s():RegisterSetting: TX_BAND_CFG=0x%x, CORE_R1=0x%x, AGC1_R0=0x%x, TXBE_R0=0x%x\n",
				__FUNCTION__, band_cfg, core_r1, agc_r0, be_r0));
		bw = ((core_r1 & 0x18) >> 3) & 0xff;
		DBGPRINT(RT_DEBUG_TRACE, ("[CORE_R1]\n"));
		DBGPRINT(RT_DEBUG_TRACE, ("\tTx/Rx BandwidthCtrl(CORE_R1[4:3])=%d(%s MHz)\n", 
					bw, bw_str[bw]));

		DBGPRINT(RT_DEBUG_TRACE, ("[AGC_R0]\n"));
		prim_ch_idx = ((agc_r0 & 0x300) >> 8) & 0xff;
		DBGPRINT(RT_DEBUG_TRACE, ("\tPrimary Channel Idx(AGC_R0[9:8])=%d\n", prim_ch_idx));
		decode_cap = ((agc_r0 & 0x7000) >> 12);
		DBGPRINT(RT_DEBUG_TRACE, ("\tDecodeBWCap(AGC_R0[14:12])=%d(%s MHz Data)\n",
					decode_cap, decode_str[decode_cap]));

		DBGPRINT(RT_DEBUG_TRACE, ("[TXBE_R0]\n"));
		tx_prim = (be_r0 & 0x3);
		DBGPRINT(RT_DEBUG_TRACE, ("\tTxPrimary(TXBE_R0[1:0])=%d\n", tx_prim));
		DBGPRINT(RT_DEBUG_TRACE, ("\n%s\n", pChipCap->MACRegisterVer));
		DBGPRINT(RT_DEBUG_TRACE, ("%s\n", pChipCap->BBPRegisterVer));
		DBGPRINT(RT_DEBUG_TRACE, ("%s\n\n", pChipCap->RFRegisterVer));
}


#ifdef RTMP_USB_SUPPORT
VOID RT65xxUsbAsicRadioOff(RTMP_ADAPTER *pAd, UCHAR Stage)
{
	UINT32 ret;

	DBGPRINT(RT_DEBUG_TRACE, ("--> %s\n", __FUNCTION__));

	DISABLE_TX_RX(pAd, RTMP_HALT);

	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_WAIT(&pAd->hw_atomic, ret);
		if (ret != 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", ret));
			return;
		}
	}
	
	RTMP_SET_PSFLAG(pAd, fRTMP_PS_MCU_SLEEP);
	RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_MCU_SEND_IN_BAND_CMD);

	if (!IS_MT76x0(pAd)) 
	{
		if (Stage == MLME_RADIO_OFF)
			PWR_SAVING_OP(pAd, RADIO_OFF, 1, 0, 0, 0, 0);
	}

	MCU_CTRL_EXIT(pAd);
	RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_RADIO_OFF);
	RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF);

	/* Stop bulkin pipe*/
	//if((pAd->PendingRx > 0) && (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)))
	if((!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)))
	{
		RTUSBCancelPendingBulkInIRP(pAd);
		//pAd->PendingRx = 0;
	}

	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_UP(&pAd->hw_atomic);
	}

	DBGPRINT(RT_DEBUG_TRACE, ("<== %s\n", __FUNCTION__));
}


VOID RT65xxUsbAsicRadioOn(RTMP_ADAPTER *pAd, UCHAR Stage)
{
	UINT32 MACValue = 0;
	UINT32 rx_filter_flag;
	UINT32 ret;

	RTMP_CLEAR_PSFLAG(pAd, fRTMP_PS_MCU_SLEEP);
#ifdef CONFIG_PM
#ifdef USB_SUPPORT_SELECTIVE_SUSPEND
	POS_COOKIE  pObj = (POS_COOKIE) pAd->OS_Cookie;

	DBGPRINT(RT_DEBUG_TRACE, ("--> %s\n", __FUNCTION__));
	
	if( (RTMP_Usb_AutoPM_Get_Interface(pObj->pUsb_Dev,pObj->intf)) == 1)
	{
		DBGPRINT(RT_DEBUG_TRACE, ("%s: autopm_resume success\n", __FUNCTION__));
		RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_SUSPEND);
	}
	else if ((RTMP_Usb_AutoPM_Get_Interface(pObj->pUsb_Dev,pObj->intf)) == (-1))
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s: autopm_resume fail ------\n", __FUNCTION__));
		RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_SUSPEND);
		return;
	}
	else
		DBGPRINT(RT_DEBUG_TRACE, ("%s: autopm_resume do nothing\n", __FUNCTION__));

#endif /* USB_SUPPORT_SELECTIVE_SUSPEND */
#endif /* CONFIG_PM */
	
	if (pAd->WlanFunCtrl.field.WLAN_EN == 0)
		RT65xx_WLAN_ChipOnOff(pAd, TRUE, FALSE);

	/* make some traffic to invoke EvtDeviceD0Entry callback function*/
	RTUSBReadMACRegister(pAd,0x1000, &MACValue);
	DBGPRINT(RT_DEBUG_TRACE,("A MAC query to invoke EvtDeviceD0Entry, MACValue = 0x%x\n",MACValue));

	/* enable RX of MAC block*/
#ifdef XLINK_SUPPORT
	if (pAd->StaCfg.PSPXlink)
		rx_filter_flag = PSPXLINK;
	else
#endif /* XLINK_SUPPORT */	
		rx_filter_flag = STANORMAL;     /* Staion not drop control frame will fail WiFi Certification.*/
	
	
	RTMP_IO_WRITE32(pAd, RX_FILTR_CFG, rx_filter_flag);
	RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0x0c);

	/* 4. Clear idle flag*/
	RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF);
	RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_RADIO_OFF);
	RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_SUSPEND);
	
	/* Send Bulkin IRPs after flag fRTMP_ADAPTER_IDLE_RADIO_OFF is cleared.*/
#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		RTUSBBulkReceive(pAd);
	}
#endif /* CONFIG_STA_SUPPORT */

	MCU_CTRL_INIT(pAd);

	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_WAIT(&pAd->hw_atomic, ret);
		if (ret != 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", ret));
			return;
		}
	}

	RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0x0c);

	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_UP(&pAd->hw_atomic);
	}
	
	RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_MCU_SEND_IN_BAND_CMD);

	if (!IS_MT76x0(pAd)) {
		if (Stage == MLME_RADIO_ON)
			PWR_SAVING_OP(pAd, RADIO_ON, 1, 0, 0, 0, 0);
	}

	DBGPRINT(RT_DEBUG_TRACE, ("<== %s\n", __FUNCTION__));
}
#endif

VOID RT65xxDisableTxRx(
	RTMP_ADAPTER *pAd,
	UCHAR Level)
{
	UINT32 MacReg = 0;
	UINT32 MTxCycle;
	BOOLEAN bResetWLAN = FALSE;
	BOOLEAN bFree = TRUE;
	UINT8 CheckFreeTimes = 0;

	if (!IS_RT65XX(pAd))
		return;

	DBGPRINT(RT_DEBUG_TRACE, ("----> %s\n", __FUNCTION__));

	if (Level == RTMP_HALT)
	{
		RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_ACTIVE);
	}

	DBGPRINT(RT_DEBUG_TRACE, ("%s Tx success = %ld\n", 
		__FUNCTION__, (ULONG)pAd->WlanCounters.TransmittedFragmentCount.u.LowPart));
	DBGPRINT(RT_DEBUG_TRACE, ("%s Rx success = %ld\n", 
		__FUNCTION__, (ULONG)pAd->WlanCounters.ReceivedFragmentCount.QuadPart));

	StopDmaTx(pAd, Level);

	/*
		Check page count in TxQ,
	*/
	for (MTxCycle = 0; MTxCycle < 2000; MTxCycle++)
	{
		bFree = TRUE;
		RTMP_IO_READ32(pAd, 0x438, &MacReg);
		if (MacReg != 0)
			bFree = FALSE;
		RTMP_IO_READ32(pAd, 0xa30, &MacReg);
		if (MacReg & 0x000000FF)
			bFree = FALSE;
		RTMP_IO_READ32(pAd, 0xa34, &MacReg);
		if (MacReg & 0xFF00FF00)
			bFree = FALSE;
		if (bFree)
			break;
		if (MacReg == 0xFFFFFFFF)
		{
			RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST);
			return;
		}
	}

	if (MTxCycle >= 2000)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Check TxQ page count max\n"));
		RTMP_IO_READ32(pAd, 0x0a30, &MacReg);
		DBGPRINT(RT_DEBUG_TRACE, ("0x0a30 = 0x%08x\n", MacReg));

		RTMP_IO_READ32(pAd, 0x0a34, &MacReg);
		DBGPRINT(RT_DEBUG_TRACE, ("0x0a34 = 0x%08x\n", MacReg));

		RTMP_IO_READ32(pAd, 0x438, &MacReg);
		DBGPRINT(RT_DEBUG_TRACE, ("0x438 = 0x%08x\n", MacReg));
		bResetWLAN = TRUE;
	}

	/*
		Check MAC Tx idle
	*/
	for (MTxCycle = 0; MTxCycle < 2000; MTxCycle++)
	{
		RTMP_IO_READ32(pAd, MAC_STATUS_CFG, &MacReg);
		if (MacReg & 0x1)
			RTMPusecDelay(50);
		else
			break;

		if (MacReg == 0xFFFFFFFF)
		{
			RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST);
			return;
		}
	}

	if (MTxCycle >= 2000)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Check MAC Tx idle max(0x%08x)\n", MacReg));
		bResetWLAN = TRUE;
	}
	
	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST) == FALSE)
	{
		if (Level == RTMP_HALT)
		{
			/*
				Disable MAC TX/RX
			*/
			RTMP_IO_READ32(pAd, MAC_SYS_CTRL, &MacReg);
			MacReg &= ~(0x0000000c);
			RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, MacReg);
		}
		else
		{
			/*
				Disable MAC RX
			*/
			RTMP_IO_READ32(pAd, MAC_SYS_CTRL, &MacReg);
			MacReg &= ~(0x00000008);
			RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, MacReg);
		}
	}

	/*
		Check page count in RxQ,
	*/
	for (MTxCycle = 0; MTxCycle < 2000; MTxCycle++)
	{
		bFree = TRUE;
		RTMP_IO_READ32(pAd, 0x430, &MacReg);
		
		if (MacReg & (0x00FF0000))
			bFree = FALSE;
		
		RTMP_IO_READ32(pAd, 0xa30, &MacReg);
		
		if (MacReg != 0)
			bFree = FALSE;
		
		RTMP_IO_READ32(pAd, 0xa34, &MacReg);
		
		if (MacReg != 0)
			bFree = FALSE;
		
		if (bFree && (CheckFreeTimes > 20) && (!is_inband_cmd_processing(pAd)))
			break;
		
		if (bFree)
			CheckFreeTimes++;
		
		if (MacReg == 0xFFFFFFFF)
		{
			RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST);
			return;
		}
#ifdef RTMP_MAC_USB
		RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_POLL_IDLE);
		usb_rx_cmd_msgs_receive(pAd);
		RTUSBBulkReceive(pAd);
#endif /* RTMP_MAC_USB */
	}
	
	RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_POLL_IDLE);
	
	if (MTxCycle >= 2000)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Check RxQ page count max\n"));
		
		RTMP_IO_READ32(pAd, 0x0a30, &MacReg);
		DBGPRINT(RT_DEBUG_TRACE, ("0x0a30 = 0x%08x\n", MacReg));

		RTMP_IO_READ32(pAd, 0x0a34, &MacReg);
		DBGPRINT(RT_DEBUG_TRACE, ("0x0a34 = 0x%08x\n", MacReg));

		RTMP_IO_READ32(pAd, 0x0430, &MacReg);
		DBGPRINT(RT_DEBUG_TRACE, ("0x0430 = 0x%08x\n", MacReg));
		bResetWLAN = TRUE;
	}

	/*
		Check MAC Rx idle
	*/
	for (MTxCycle = 0; MTxCycle < 2000; MTxCycle++)
	{
		RTMP_IO_READ32(pAd, MAC_STATUS_CFG, &MacReg);
		if (MacReg & 0x2)
			RTMPusecDelay(50);
		else
			break;
		if (MacReg == 0xFFFFFFFF)
		{
			RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST);
			return;
		}
	}
	
	if (MTxCycle >= 2000)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Check MAC Rx idle max(0x%08x)\n", MacReg));
		bResetWLAN = TRUE;
	}

	StopDmaRx(pAd, Level);

	if ((Level == RTMP_HALT) &&
		(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST) == FALSE))
	{
		if (!pAd->chipCap.IsComboChip)
			NICEraseFirmware(pAd);
		
		/*
 		 * Disable RF/MAC and do not do reset WLAN under below cases
 		 * 1. Combo card
 		 * 2. suspend including wow application
 		 * 3. radion off command
 		 */
		if ((pAd->chipCap.IsComboChip) || RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_SUSPEND)
				|| RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_CMD_RADIO_OFF))
			bResetWLAN = 0;

		RT65xx_WLAN_ChipOnOff(pAd, FALSE, bResetWLAN);
	}
	
	DBGPRINT(RT_DEBUG_TRACE, ("<---- %s\n", __FUNCTION__));
}

VOID RT65xx_WLAN_ChipOnOff(
	IN RTMP_ADAPTER *pAd,
	IN BOOLEAN bOn,
	IN BOOLEAN bResetWLAN)
{
	WLAN_FUN_CTRL_STRUC WlanFunCtrl = {.word=0};


#ifdef RTMP_MAC_USB
	UINT32 ret;

	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_WAIT(&pAd->wlan_en_atomic, ret);
		if (ret != 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("wlan_en_atomic get failed(ret=%d)\n", ret));
			return;
		}
	}
#endif /* RTMP_MAC_USB */

	RTMP_IO_READ32(pAd, WLAN_FUN_CTRL, &WlanFunCtrl.word);
	DBGPRINT(RT_DEBUG_OFF, ("==>%s(): OnOff:%d, Reset= %d, pAd->WlanFunCtrl:0x%x, Reg-WlanFunCtrl=0x%x\n",
				__FUNCTION__, bOn, bResetWLAN, pAd->WlanFunCtrl.word, WlanFunCtrl.word));

	if (bResetWLAN == TRUE)
	{
		WlanFunCtrl.field.GPIO0_OUT_OE_N = 0xFF;
		WlanFunCtrl.field.FRC_WL_ANT_SET = 0;

		if (pAd->WlanFunCtrl.field.WLAN_EN)
		{
			/*
				Restore all HW default value and reset RF.
			*/					
			WlanFunCtrl.field.WLAN_RESET = 1;
			WlanFunCtrl.field.WLAN_RESET_RF = 1;
			DBGPRINT(RT_DEBUG_TRACE, ("Reset(1) WlanFunCtrl.word = 0x%x\n", WlanFunCtrl.word));
			RTMP_IO_WRITE32(pAd, WLAN_FUN_CTRL, WlanFunCtrl.word);	
			RTMPusecDelay(20);
			WlanFunCtrl.field.WLAN_RESET = 0;
			WlanFunCtrl.field.WLAN_RESET_RF = 0;
			DBGPRINT(RT_DEBUG_TRACE, ("Reset(2) WlanFunCtrl.word = 0x%x\n", WlanFunCtrl.word));
			RTMP_IO_WRITE32(pAd, WLAN_FUN_CTRL, WlanFunCtrl.word);
			RTMPusecDelay(20);
		}
	}

	if (bOn == TRUE)
	{
		/*
			Enable WLAN function and clock
			WLAN_FUN_CTRL[1:0] = 0x3
		*/
		ENABLE_WLAN_FUN(WlanFunCtrl);
	}
	else
	{
		/*
			Diable WLAN function and clock
			WLAN_FUN_CTRL[1:0] = 0x0
		*/
		DISABLE_WLAN_FUN(WlanFunCtrl);
	}

	DBGPRINT(RT_DEBUG_TRACE, ("WlanFunCtrl.word = 0x%x\n", WlanFunCtrl.word));
	RTMP_IO_WRITE32(pAd, WLAN_FUN_CTRL, WlanFunCtrl.word);	
	RTMPusecDelay(20);

	if (bOn)
	{
		RTMP_IO_READ32(pAd, MAC_CSR0, &pAd->MACVersion);
		DBGPRINT(RT_DEBUG_TRACE, ("MACVersion = 0x%08x\n", pAd->MACVersion));
	}

	if (bOn == TRUE)
	{
		UINT index = 0;		
		CMB_CTRL_STRUC CmbCtrl;
		
		CmbCtrl.word = 0;
				
		do
		{
			do 
			{
				RTMP_IO_READ32(pAd, CMB_CTRL, &CmbCtrl.word);

				/*
					Check status of PLL_LD & XTAL_RDY.
					HW issue: Must check PLL_LD&XTAL_RDY when setting EEP to disable PLL power down
				*/
				if ((CmbCtrl.field.PLL_LD == 1) && (CmbCtrl.field.XTAL_RDY == 1))
					break;

				RTMPusecDelay(20);
			} while (index++ < MAX_CHECK_COUNT);

			if (index >= MAX_CHECK_COUNT)
			{
				DBGPRINT(RT_DEBUG_ERROR, 
						("Lenny:[boundary]Check PLL_LD ..CMB_CTRL 0x%08x, index=%d!\n",
						CmbCtrl.word, index));
				/*
					Disable WLAN then enable WLAN again
				*/
				DISABLE_WLAN_FUN(WlanFunCtrl);
				RTMP_IO_WRITE32(pAd, WLAN_FUN_CTRL, WlanFunCtrl.word);
				RTMPusecDelay(20);

				ENABLE_WLAN_FUN(WlanFunCtrl);
				RTMP_IO_WRITE32(pAd, WLAN_FUN_CTRL, WlanFunCtrl.word);
				RTMPusecDelay(20);
			}
			else
			{
				break;
			}
		}			
		while (TRUE);
	}

	pAd->WlanFunCtrl.word = WlanFunCtrl.word;
	RTMP_IO_READ32(pAd, WLAN_FUN_CTRL, &WlanFunCtrl.word);
	DBGPRINT(RT_DEBUG_TRACE,
		("<== %s():  pAd->WlanFunCtrl.word = 0x%x, Reg->WlanFunCtrl=0x%x!\n",
		__FUNCTION__, pAd->WlanFunCtrl.word, WlanFunCtrl.word));


#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_UP(&pAd->wlan_en_atomic);
	}
#endif /* RTMP_MAC_USB */
}

#endif /* RT65xx */
