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


#ifndef __AGS_H__
#define __AGS_H__


extern UCHAR AGS1x1HTRateTable[];
extern UCHAR AGS2x2HTRateTable[];
extern UCHAR AGS3x3HTRateTable[];
#ifdef DOT11_VHT_AC
extern UCHAR Ags1x1VhtRateTable[];
extern UCHAR Ags2x2VhtRateTable[];
#endif /* DOT11_VHT_AC */

#define AGS_TX_QUALITY_WORST_BOUND       8
#define AGS_QUICK_RA_TIME_INTERVAL        50	/* 50ms */

/* The size, in bytes, of an AGS entry in the rate switch table */
#define SIZE_OF_AGS_RATE_TABLE_ENTRY	9

typedef struct _RTMP_RA_AGS_TB {
	UCHAR	ItemNo;

	UCHAR	STBC:1;
	UCHAR	ShortGI:1;
	UCHAR	BW:2;
	UCHAR	Mode:3;
	UCHAR	Rsv1:1;

	UCHAR Nss:2; // NSS_XXX (VHT only)
	UCHAR rsv2:6; // Reserved
	
	UCHAR	CurrMCS;
	UCHAR	TrainUp;
	UCHAR	TrainDown;
	UCHAR	downMcs;
	UCHAR	upMcs3;
	UCHAR	upMcs2;
	UCHAR	upMcs1;
}RTMP_RA_AGS_TB;


/* AGS control */
typedef struct _AGS_CONTROL {
	UCHAR MCSGroup; /* The MCS group under testing */
	UCHAR lastRateIdx;
} AGS_CONTROL,*PAGS_CONTROL;


/* The statistics information for AGS */
typedef struct _AGS_STATISTICS_INFO {
	CHAR	RSSI;
	ULONG	TxErrorRatio;
	ULONG	AccuTxTotalCnt;
	ULONG	TxTotalCnt;
	ULONG	TxSuccess;
	ULONG	TxRetransmit;
	ULONG	TxFailCount;
} AGS_STATISTICS_INFO, *PAGS_STATISTICS_INFO;


/* Support AGS (Adaptive Group Switching) */
#define SUPPORT_AGS(__pAd)		((__pAd)->rateAlg == RATE_ALG_AGS)

#ifdef DOT11_VHT_AC
#define AGS_IS_USING(__pAd, __pRateTable)	\
    (SUPPORT_AGS(__pAd) && \
     ((__pRateTable == AGS1x1HTRateTable) ||\
      (__pRateTable == AGS2x2HTRateTable) ||\
      (__pRateTable == AGS3x3HTRateTable) ||\
      (__pRateTable == Ags1x1VhtRateTable) ||\
      (__pRateTable == Ags2x2VhtRateTable))) 
#else
#define AGS_IS_USING(__pAd, __pRateTable)	\
    (SUPPORT_AGS(__pAd) && \
     ((__pRateTable == AGS1x1HTRateTable) || \
      (__pRateTable == AGS2x2HTRateTable) || \
      (__pRateTable == AGS3x3HTRateTable))) 
#endif /* DOT11_VHT_AC */

#endif /* __AGS_H__ */

