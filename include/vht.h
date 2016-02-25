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


#include "dot11ac_vht.h"


struct _RTMP_ADAPTER;
struct _RT_PHY_INFO;


VOID dump_vht_cap(struct _RTMP_ADAPTER *pAd, VHT_CAP_IE *vht_ie);
VOID dump_vht_op(struct _RTMP_ADAPTER *pAd, VHT_OP_IE *vht_ie);

INT build_vht_ies(struct _RTMP_ADAPTER *pAd, UCHAR *buf, UCHAR frm);
INT build_vht_cap_ie(RTMP_ADAPTER *pAd, UCHAR *buf);

UCHAR vht_prim_ch_idx(UCHAR vht_cent_ch, UCHAR prim_ch);
UCHAR vht_cent_ch_freq(struct _RTMP_ADAPTER *pAd, UCHAR prim_ch);
INT vht_mode_adjust(struct _RTMP_ADAPTER *pAd, MAC_TABLE_ENTRY *pEntry, VHT_CAP_IE *cap, VHT_OP_IE *op);
INT SetCommonVHT(struct _RTMP_ADAPTER *pAd);
VOID rtmp_set_vht(struct _RTMP_ADAPTER *pAd, struct _RT_PHY_INFO *phy_info);

void assoc_vht_info_debugshow(
	IN RTMP_ADAPTER *pAd,
	IN MAC_TABLE_ENTRY *pEntry,
	IN VHT_CAP_IE *vht_cap,
	IN VHT_OP_IE *vht_op);

