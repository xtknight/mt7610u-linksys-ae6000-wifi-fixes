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


#ifndef __RAL_OMAC_USB_H__
#define __RAL_OMAC_USB_H__


#define USB_DMA_CFG 0x02a0
#ifdef RT_BIG_ENDIAN
typedef	union _USB_DMA_CFG_STRUC {
	struct {
		UINT32 TxBusy:1;   	/*USB DMA TX FSM busy. debug only */
		UINT32 RxBusy:1;        /*USB DMA RX FSM busy. debug only */
		UINT32 EpoutValid:6;        /*OUT endpoint data valid. debug only */
		UINT32 TxBulkEn:1;        /*Enable USB DMA Tx */
		UINT32 RxBulkEn:1;        /*Enable USB DMA Rx */
		UINT32 RxBulkAggEn:1;        /*Enable Rx Bulk Aggregation */
		UINT32 TxopHalt:1;        /*Halt TXOP count down when TX buffer is full. */
		UINT32 TxClear:1;        /*Clear USB DMA TX path */
		UINT32 rsv:2;        
		UINT32 phyclear:1;        		/*phy watch dog enable. write 1 */
		UINT32 RxBulkAggLmt:8;        /*Rx Bulk Aggregation Limit  in unit of 1024 bytes */
		UINT32 RxBulkAggTOut:8;        /*Rx Bulk Aggregation TimeOut  in unit of 33ns */
	} field;
	UINT32 word;
} USB_DMA_CFG_STRUC, *PUSB_DMA_CFG_STRUC;
#else
typedef	union _USB_DMA_CFG_STRUC {
	struct {
		UINT32 RxBulkAggTOut:8;        /*Rx Bulk Aggregation TimeOut  in unit of 33ns */
		UINT32 RxBulkAggLmt:8;        /*Rx Bulk Aggregation Limit  in unit of 256 bytes */
		UINT32 phyclear:1;        		/*phy watch dog enable. write 1 */
		UINT32 rsv:2;
		UINT32 TxClear:1;        /*Clear USB DMA TX path */
		UINT32 TxopHalt:1;        /*Halt TXOP count down when TX buffer is full. */
		UINT32 RxBulkAggEn:1;        /*Enable Rx Bulk Aggregation */
		UINT32 RxBulkEn:1;        /*Enable USB DMA Rx */
		UINT32 TxBulkEn:1;        /*Enable USB DMA Tx */
		UINT32 EpoutValid:6;        /*OUT endpoint data valid */
		UINT32 RxBusy:1;        /*USB DMA RX FSM busy */
		UINT32 TxBusy:1;   	/*USB DMA TX FSM busy */
	} field;
	UINT32 word;
} USB_DMA_CFG_STRUC, *PUSB_DMA_CFG_STRUC;
#endif

#endif /*__RAL_OMAC_USB_H__ */

