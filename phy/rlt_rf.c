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


#ifdef RLT_RF

#include "rt_config.h"

NDIS_STATUS rlt_rf_write(
	IN PRTMP_ADAPTER pAd,
	IN UCHAR bank,
	IN UCHAR regID,
	IN UCHAR value)
{
	NDIS_STATUS	 ret = 0;

	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_MCU_SEND_IN_BAND_CMD)) {
		BANK_RF_REG_PAIR reg;
		reg.Bank = bank;
		reg.Register = regID;
		reg.Value = value;

		RF_RANDOM_WRITE(pAd, &reg, 1);
	} else {
		RLT_RF_CSR_CFG rfcsr = { { 0 } };
		UINT i = 0;
	

#ifdef RTMP_MAC_USB
		if (IS_USB_INF(pAd)) {
			RTMP_SEM_EVENT_WAIT(&pAd->reg_atomic, ret);
			if (ret != 0) {
				DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", ret));
				return STATUS_UNSUCCESSFUL;
			}
		}
#endif /* RTMP_MAC_USB */

		ASSERT((regID <= pAd->chipCap.MaxNumOfRfId));

		ret = STATUS_UNSUCCESSFUL;
		do
		{
			RTMP_IO_READ32(pAd, RF_CSR_CFG, &rfcsr.word);

			if (!rfcsr.field.RF_CSR_KICK)
				break;
			i++;
		}
		while ((i < MAX_BUSY_COUNT) && (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)));

		if ((i == MAX_BUSY_COUNT) || (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)))
		{
			DBGPRINT_RAW(RT_DEBUG_ERROR, ("Retry count exhausted or device removed!!!\n"));
			goto done;
		}

		rfcsr.field.RF_CSR_WR = 1;
		rfcsr.field.RF_CSR_KICK = 1;
		rfcsr.field.RF_CSR_REG_BANK = bank;
		rfcsr.field.RF_CSR_REG_ID = regID;


		rfcsr.field.RF_CSR_DATA = value;
		RTMP_IO_WRITE32(pAd, RF_CSR_CFG, rfcsr.word);

		ret = NDIS_STATUS_SUCCESS;

done:
#ifdef RTMP_MAC_USB
		if (IS_USB_INF(pAd)) {
			RTMP_SEM_EVENT_UP(&pAd->reg_atomic);
		}
#endif /* RTMP_MAC_USB */
	}

	return ret;
}

/*
	========================================================================
	
	Routine Description: Read RT30xx RF register through MAC

	Arguments:

	Return Value:

	IRQL = 
	
	Note:
	
	========================================================================
*/
NDIS_STATUS rlt_rf_read(
	IN RTMP_ADAPTER *pAd,
	IN UCHAR bank,
	IN UCHAR regID,
	IN UCHAR *pValue)
{
	NDIS_STATUS	 ret = 0;
	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_MCU_SEND_IN_BAND_CMD)) {
		BANK_RF_REG_PAIR reg;
		reg.Bank = bank;
		reg.Register = regID;
		RF_RANDOM_READ(pAd, &reg, 1);
	
		*pValue = reg.Value;
	} else {
	
		RLT_RF_CSR_CFG rfcsr = { { 0 } };
		UINT i=0, k=0;


#ifdef RTMP_MAC_USB
		if (IS_USB_INF(pAd)) {
			RTMP_SEM_EVENT_WAIT(&pAd->reg_atomic, i);
			if (i != 0) {
				DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", i));
				return STATUS_UNSUCCESSFUL;
			}
		}
#endif /* RTMP_MAC_USB */

		ASSERT((regID <= pAd->chipCap.MaxNumOfRfId));

		for (i=0; i<MAX_BUSY_COUNT; i++)
		{
			if(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
				goto done;
			
			RTMP_IO_READ32(pAd, RF_CSR_CFG, &rfcsr.word);

			if (rfcsr.field.RF_CSR_KICK == BUSY)
					continue;
		
			rfcsr.word = 0;
			rfcsr.field.RF_CSR_WR = 0;
			rfcsr.field.RF_CSR_KICK = 1;
			rfcsr.field.RF_CSR_REG_ID = regID;
			rfcsr.field.RF_CSR_REG_BANK = bank;
			RTMP_IO_WRITE32(pAd, RF_CSR_CFG, rfcsr.word);
		
			for (k=0; k<MAX_BUSY_COUNT; k++)
			{
				if(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
					goto done;
				
				RTMP_IO_READ32(pAd, RF_CSR_CFG, &rfcsr.word);

				if (rfcsr.field.RF_CSR_KICK == IDLE)
					break;
			}
		
			if ((rfcsr.field.RF_CSR_KICK == IDLE) &&
				(rfcsr.field.RF_CSR_REG_ID == regID) &&
				(rfcsr.field.RF_CSR_REG_BANK == bank))
			{
				*pValue = (UCHAR)(rfcsr.field.RF_CSR_DATA);
				break;
			}
		}

		if (rfcsr.field.RF_CSR_KICK == BUSY)
		{																	
			DBGPRINT_ERR(("RF read R%d=0x%X fail, i[%d], k[%d]\n", regID, rfcsr.word,i,k));
			goto done;
		}
		ret = STATUS_SUCCESS;

done:
#ifdef RTMP_MAC_USB
		if (IS_USB_INF(pAd)) {
			RTMP_SEM_EVENT_UP(&pAd->reg_atomic);
		}
#endif /* RTMP_MAC_USB */
	}

	return ret;
}
#endif /* RLT_RF */

