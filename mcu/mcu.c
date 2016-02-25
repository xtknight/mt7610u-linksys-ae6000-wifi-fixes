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


#include	"rt_config.h"

INT MCUBurstWrite(PRTMP_ADAPTER pAd, UINT32 Offset, UINT32 *Data, UINT32 Cnt)
{
#ifdef RTMP_USB_SUPPORT
	RTUSBMultiWrite_nBytes(pAd, Offset, Data, Cnt * 4, 64); 
#endif /* RTMP_USB_SUPPORT */
}

INT MCURandomWrite(PRTMP_ADAPTER pAd, RTMP_REG_PAIR *RegPair, UINT32 Num)
{
	UINT32 Index;
	
	for (Index = 0; Index < Num; Index++)
		RTMP_IO_WRITE32(pAd, RegPair->Register, RegPair->Value);
}

VOID ChipOpsMCUHook(PRTMP_ADAPTER pAd, enum MCU_TYPE MCUType)
{

	RTMP_CHIP_OP *pChipOps = &pAd->chipOps;



#ifdef CONFIG_ANDES_SUPPORT
	if (MCUType == ANDES) 
	{

#ifdef RTMP_USB_SUPPORT
		pChipOps->loadFirmware = andes_usb_loadfw;
#endif
		//pChipOps->sendCommandToMcu = andes_send_cmd_msg;
		pChipOps->MCUCtrlInit = andes_ctrl_init;
		pChipOps->MCUCtrlExit = andes_ctrl_exit;
		pChipOps->Calibration = andes_calibration;
		pChipOps->BurstWrite =  andes_burst_write;
		pChipOps->BurstRead = andes_burst_read;
		pChipOps->RandomRead = andes_random_read;
		pChipOps->RFRandomRead = andes_rf_random_read;
		pChipOps->ReadModifyWrite = andes_read_modify_write;
		pChipOps->RFReadModifyWrite = andes_rf_read_modify_write;
		pChipOps->RandomWrite = andes_random_write;
		pChipOps->RFRandomWrite = andes_rf_random_write;
		pChipOps->PwrSavingOP = andes_pwr_saving;
	}
#endif
}
