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


#ifndef __CHLIST_H__
#define __CHLIST_H__

#include "rtmp_type.h"
#include "rtmp_def.h"


typedef struct _CH_DESC
{
    UCHAR FirstChannel;
    UCHAR NumOfCh;
    UCHAR ChannelProp;
} CH_DESC, *PCH_DESC;

typedef struct _COUNTRY_REGION_CH_DESC
{
    UCHAR RegionIndex;
    PCH_DESC pChDesc;
} COUNTRY_REGION_CH_DESC, *PCOUNTRY_REGION_CH_DESC;

#define ODOR			0
#define IDOR			1
#define BOTH			2

typedef struct _CH_DESP
{
    UCHAR FirstChannel;
    UCHAR NumOfCh;
    CHAR MaxTxPwr;			/* dBm */
    UCHAR Geography;			/* 0:out door, 1:in door, 2:both */
    BOOLEAN DfsReq;			/* Dfs require, 0: No, 1: yes. */
} CH_DESP, *PCH_DESP;

typedef struct _CH_REGION
{
    UCHAR CountReg[3];
    UCHAR DfsType;			/* 0: CE, 1: FCC, 2: JAP, 3:JAP_W53, JAP_W56 */
    CH_DESP *pChDesp;
} CH_REGION, *PCH_REGION;

extern CH_REGION ChRegion[];


typedef struct _CH_FREQ_MAP_
{
    UINT16		channel;
    UINT16		freqKHz;
} CH_FREQ_MAP;

extern CH_FREQ_MAP CH_HZ_ID_MAP[];
extern int CH_HZ_ID_MAP_NUM;


#define     MAP_CHANNEL_ID_TO_KHZ(_ch, _khz)                 \
			RTMP_MapChannelID2KHZ(_ch, (UINT32 *)&(_khz))
#define     MAP_KHZ_TO_CHANNEL_ID(_khz, _ch)                 \
			RTMP_MapKHZ2ChannelID(_khz, (INT *)&(_ch))

/* Check if it is Japan W53(ch52,56,60,64) channel. */
#define JapanChannelCheck(_ch)  ((_ch == 52) || (_ch == 56) || (_ch == 60) || (_ch == 64))


VOID BuildChannelListEx(
    IN PRTMP_ADAPTER pAd);

VOID BuildBeaconChList(
    IN PRTMP_ADAPTER pAd,
    OUT PUCHAR pBuf,
    OUT	PULONG pBufLen);

VOID N_ChannelCheck(RTMP_ADAPTER *pAd);
UCHAR N_SetCenCh(RTMP_ADAPTER *pAd, UCHAR channel);
BOOLEAN N_ChannelGroupCheck(RTMP_ADAPTER *pAd, UCHAR channel);


UINT8 GetCuntryMaxTxPwr(
    IN PRTMP_ADAPTER pAd,
    IN UINT8 channel);

VOID RTMP_MapChannelID2KHZ(
    IN UCHAR Ch,
    OUT UINT32 *pFreq);

VOID RTMP_MapKHZ2ChannelID(
    IN ULONG Freq,
    OUT INT *pCh);

UCHAR GetChannel_5GHZ(
    IN PCH_DESC pChDesc,
    IN UCHAR index);

UCHAR GetChannel_2GHZ(
    IN PCH_DESC pChDesc,
    IN UCHAR index);

UCHAR GetChannelFlag(
    IN PCH_DESC pChDesc,
    IN UCHAR index);

UINT16 TotalChNum(
    IN PCH_DESC pChDesc);

#endif /* __CHLIST_H__ */

