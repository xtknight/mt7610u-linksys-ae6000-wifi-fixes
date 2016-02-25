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


#include "rt_config.h"


#ifdef DOT11_VHT_AC

VOID rtmp_set_vht(RTMP_ADAPTER *pAd, RT_PHY_INFO *phy_info)
{
	if (!phy_info)
		return;

	if (phy_info->bVhtEnable)
		phy_info->vht_bw = VHT_BW_80;

}


INT SetCommonVHT(RTMP_ADAPTER *pAd)
{
	UCHAR cent_ch = 0;

	if (!WMODE_CAP_AC(pAd->CommonCfg.PhyMode))
	{
		/* Clear previous VHT information */
		return FALSE;
	}

	
	pAd->CommonCfg.vht_cent_ch = vht_cent_ch_freq(pAd, pAd->CommonCfg.Channel);
		
	DBGPRINT(RT_DEBUG_TRACE, ("%s(): Config VHT parameters!cent_ch=%d!vht_cent_ch = %d, vht_cent_ch2 = %d\n",
				__FUNCTION__, cent_ch, pAd->CommonCfg.vht_cent_ch, pAd->CommonCfg.vht_cent_ch2));
	return TRUE;
}

#endif /* DOT11_VHT_AC */
