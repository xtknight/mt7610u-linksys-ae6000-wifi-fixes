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


#ifndef	__WFD_H__
#define	__WFD_H__

#ifdef WFD_SUPPORT

#include "rtmp_type.h"

INT Set_WfdEnable_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

#ifdef RT_CFG80211_SUPPORT
INT Set_WfdInsertIe_Proc
(
	IN	PRTMP_ADAPTER		pAd, 
	IN	PSTRING 		arg);
#endif /* RT_CFG80211_SUPPORT */

INT Set_WfdDeviceType_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

INT Set_WfdCouple_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

INT Set_WfdSessionAvailable_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

INT Set_WfdCP_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

INT	Set_WfdRtspPort_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

INT	Set_WfdMaxThroughput_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

INT Set_WfdLocalIp_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

INT Set_PeerRtspPort_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

VOID WfdMakeWfdIE(
	IN	PRTMP_ADAPTER	pAd,
	IN 	ULONG			WfdIeBitmap,
	OUT	PUCHAR			pOutBuf,
	OUT	PULONG			pIeLen);

ULONG InsertWfdSubelmtTlv(
	IN PRTMP_ADAPTER 	pAd,
	IN UCHAR			SubId,
	IN PUCHAR			pInBuffer,
	IN PUCHAR			pOutBuffer,
	IN UINT				Action);

VOID WfdParseSubElmt(
	IN PRTMP_ADAPTER 	pAd, 
	IN PWFD_ENTRY_INFO	pWfdEntryInfo,
	IN VOID 				*Msg, 
	IN ULONG 			MsgLen);

VOID WfdCfgInit(
	IN PRTMP_ADAPTER pAd);

#endif /* WFD_SUPPORT */
#endif /* __WFD_H__ */

