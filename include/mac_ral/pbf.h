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


#ifndef __PBF_H__
#define __PBF_H__


#ifdef RLT_MAC
#include "mac_ral/nmac/ral_nmac_pbf.h"
#endif /* RLT_MAC */

#ifdef RTMP_MAC
#include "mac_ral/omac/ral_omac_pbf.h"
#endif /* RTMP_MAC */


/* ================================================================================= */
/* Register format  for PBF                                                                                                                                                     */
/* ================================================================================= */


#define WPDMA_GLO_CFG 	0x208
#ifdef RT_BIG_ENDIAN
typedef	union _WPDMA_GLO_CFG_STRUC	{
	struct	{
		UINT32 rx_2b_offset:1;
		UINT32 clk_gate_dis:1;
		UINT32 rsv:14;
		UINT32 HDR_SEG_LEN:8;
		UINT32 BigEndian:1;
		UINT32 EnTXWriteBackDDONE:1;
		UINT32 WPDMABurstSIZE:2;
		UINT32 RxDMABusy:1;
		UINT32 EnableRxDMA:1;
		UINT32 TxDMABusy:1;
		UINT32 EnableTxDMA:1;
	}	field;
	UINT32 word;
}WPDMA_GLO_CFG_STRUC, *PWPDMA_GLO_CFG_STRUC;
#else
typedef	union _WPDMA_GLO_CFG_STRUC	{
	struct {
		UINT32 EnableTxDMA:1;
		UINT32 TxDMABusy:1;
		UINT32 EnableRxDMA:1;
		UINT32 RxDMABusy:1;
		UINT32 WPDMABurstSIZE:2;
		UINT32 EnTXWriteBackDDONE:1;
		UINT32 BigEndian:1;
		UINT32 HDR_SEG_LEN:8;
		UINT32 rsv:14;
		UINT32 clk_gate_dis:1;
		UINT32 rx_2b_offset:1;
	} field;
	UINT32 word;
} WPDMA_GLO_CFG_STRUC, *PWPDMA_GLO_CFG_STRUC;
#endif


#define PBF_CTRL			0x0410
#define MCU_INT_STA		0x0414
#define MCU_INT_ENA	0x0418
#define TXRXQ_PCNT		0x0438
#define PBF_DBG			0x043c


#endif /* __PBF_H__ */

