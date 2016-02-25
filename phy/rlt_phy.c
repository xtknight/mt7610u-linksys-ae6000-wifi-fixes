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


#ifdef RLT_MAC

NDIS_STATUS NICInitBBP(RTMP_ADAPTER *pAd)
{
	INT idx;
	
	/* Read BBP register, make sure BBP is up and running before write new data*/
	if (rlt_bbp_is_ready(pAd) == FALSE)
		return NDIS_STATUS_FAILURE;

	DBGPRINT(RT_DEBUG_TRACE, ("%s(): Init BBP Registers\n", __FUNCTION__));

	/* re-config specific BBP registers for individual chip */
	if (pAd->chipCap.pBBPRegTable)
	{
		RTMP_REG_PAIR *reg = (RTMP_REG_PAIR *)pAd->chipCap.pBBPRegTable;
		
		for (idx = 0; idx < pAd->chipCap.bbpRegTbSize; idx++)
		{
			RTMP_BBP_IO_WRITE32(pAd, reg[idx].Register, reg[idx].Value);
			DBGPRINT(RT_DEBUG_TRACE, ("BBP[%x]=0x%x\n", 
					reg[idx].Register, reg[idx].Value));
		}
	}

	if (pAd->chipOps.AsicBbpInit != NULL)
		pAd->chipOps.AsicBbpInit(pAd);

	// TODO: shiang-6590, check these bbp registers if need to remap to new BBP_Registers

	return NDIS_STATUS_SUCCESS;
	
}


INT rtmp_bbp_get_temp(struct _RTMP_ADAPTER *pAd, CHAR *temp_val)
{
	UINT32 bbp_val;	

#if defined(RTMP_INTERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION) 
	RTMP_BBP_IO_READ32(pAd, CORE_R35, &bbp_val);
	*temp_val = (CHAR)(bbp_val & 0xff);

	pAd->curr_temp = (bbp_val & 0xff);
#endif
	return TRUE;
}


INT 	rtmp_bbp_tx_comp_init(RTMP_ADAPTER *pAd, INT adc_insel, INT tssi_mode)
{
	UINT32 bbp_val;
	UCHAR rf_val;

#if defined(RTMP_INTERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION) 
	RTMP_BBP_IO_READ32(pAd, CORE_R34, &bbp_val);
	bbp_val = (bbp_val & 0xe7);
	bbp_val = (bbp_val | 0x80);
	RTMP_BBP_IO_WRITE32(pAd, CORE_R34, bbp_val);
	
	RT30xxReadRFRegister(pAd, RF_R27, &rf_val);
	rf_val = ((rf_val & 0x3f) | 0x40);
	RT30xxWriteRFRegister(pAd, RF_R27, rf_val);

	DBGPRINT(RT_DEBUG_TRACE, ("[temp. compensation] Set RF_R27 to 0x%x\n", rf_val));
#endif
	return 0;
}


INT rtmp_bbp_set_txdac(struct _RTMP_ADAPTER *pAd, INT tx_dac)
{
	UINT32 txbe, txbe_r5 = 0;
	
	RTMP_BBP_IO_READ32(pAd, TXBE_R5, &txbe_r5);
	txbe = txbe_r5 & (~0x3);
	switch (tx_dac)
	{
		case 2:
			txbe |= 0x3;
			break;
		case 1:
		case 0:
		default:		
			txbe &= (~0x3);
			break;
	}

	if (txbe != txbe_r5)
		RTMP_BBP_IO_WRITE32(pAd, TXBE_R5, txbe);

	return TRUE;
}


INT rtmp_bbp_set_rxpath(struct _RTMP_ADAPTER *pAd, INT rxpath)
{
	UINT32 agc, agc_r0 = 0;

	RTMP_BBP_IO_READ32(pAd, AGC1_R0, &agc_r0);
	agc = agc_r0 & (~0x18);
	if(rxpath == 2)
		agc |= (0x8);
	else if(rxpath == 1)
		agc |= (0x0);

#ifdef RT85592
	if (IS_RT8592(pAd))
		agc |= (0x8);
#endif /* RT85592 */

	if (agc != agc_r0)
		RTMP_BBP_IO_WRITE32(pAd, AGC1_R0, agc);

//DBGPRINT(RT_DEBUG_OFF, ("%s(): rxpath=%d, Set AGC1_R0=0x%x, agc_r0=0x%x\n", __FUNCTION__, rxpath, agc, agc_r0));
//		RTMP_BBP_IO_READ32(pAd, AGC1_R0, &agc);
//DBGPRINT(RT_DEBUG_OFF, ("%s(): rxpath=%d, After write, Get AGC1_R0=0x%x,\n", __FUNCTION__, rxpath, agc));

	return TRUE;
}


static UCHAR vht_prim_ch_val[] = {
	42, 36, 0,
	42, 40, 1,
	42, 44, 2,
	42, 48, 3,
	58, 52, 0,
	58, 56, 1,
	58, 60, 2,
	58, 64, 3,
	106, 100, 0,
	106, 104, 1,
	106, 108, 2,
	106, 112, 3,
	122, 116, 0,
	122, 120, 1,
	122, 124, 2,
	122, 128, 3,
	138, 132, 0,
	138, 136, 1,
	138, 140, 2,
	138, 144, 3,
	155, 149, 0,
	155, 153, 1,
	155, 157, 2,
	155, 161, 3
};

	
INT rtmp_bbp_set_ctrlch(struct _RTMP_ADAPTER *pAd, INT ext_ch)
{
	UINT32 agc, agc_r0 = 0;
	UINT32 be, be_r0 = 0;


	RTMP_BBP_IO_READ32(pAd, AGC1_R0, &agc_r0);
	agc = agc_r0 & (~0x300);
	RTMP_BBP_IO_READ32(pAd, TXBE_R0, &be_r0);
	be = (be_r0 & (~0x03));
#ifdef DOT11_VHT_AC
	if (pAd->CommonCfg.BBPCurrentBW == BW_80 && 
		pAd->CommonCfg.Channel >= 36 &&
		pAd->CommonCfg.vht_cent_ch)
	{
		if (pAd->CommonCfg.Channel < pAd->CommonCfg.vht_cent_ch)
		{
			switch (pAd->CommonCfg.vht_cent_ch - pAd->CommonCfg.Channel)
			{
				case 6:
					be |= 0;
					agc |=0x000;
					break;
				case 2:
					be |= 1;
					agc |=0x100;
					break;

			}
		}
		else if (pAd->CommonCfg.Channel > pAd->CommonCfg.vht_cent_ch)
		{
			switch (pAd->CommonCfg.Channel - pAd->CommonCfg.vht_cent_ch)
			{
				case 6:
					be |= 0x3;
					agc |=0x300;
					break;
				case 2:
					be |= 0x2;
					agc |=0x200;
					break;
			}
		}
	}
	else
#endif /* DOT11_VHT_AC */
	{
		switch (ext_ch)
		{
			case EXTCHA_BELOW:
				agc |= 0x100;
				be |= 0x01;
				break;
			case EXTCHA_ABOVE:
				agc &= (~0x300);
				be &= (~0x03);
				break;
			case EXTCHA_NONE:
			default:
				agc &= (~0x300);
				be &= (~0x03);
				break;
		}
	}
	if (agc != agc_r0)
		RTMP_BBP_IO_WRITE32(pAd, AGC1_R0, agc);

	if (be != be_r0)
		RTMP_BBP_IO_WRITE32(pAd, TXBE_R0, be);

//DBGPRINT(RT_DEBUG_OFF, ("%s(): ext_ch=%d, Set AGC1_R0=0x%x, agc_r0=0x%x\n", __FUNCTION__, ext_ch, agc, agc_r0));
//		RTMP_BBP_IO_READ32(pAd, AGC1_R0, &agc);
//DBGPRINT(RT_DEBUG_OFF, ("%s(): ext_ch=%d, After write, Get AGC1_R0=0x%x,\n", __FUNCTION__, ext_ch, agc));

	return TRUE;
}


INT rtmp_bbp_set_bw(struct _RTMP_ADAPTER *pAd, INT bw)
{
	andes_fun_set(pAd, BW_SETTING, bw);
	pAd->CommonCfg.BBPCurrentBW = bw;
	return TRUE;
}



INT rtmp_bbp_set_mmps(struct _RTMP_ADAPTER *pAd, BOOLEAN ReduceCorePower)
{
	UINT32 bbp_val, org_val;

	RTMP_BBP_IO_READ32(pAd, AGC1_R0, &org_val);
	bbp_val = org_val;
	if (ReduceCorePower)
		bbp_val |= 0x04;
	else
		bbp_val &= ~0x04;

	if (bbp_val != org_val)
		RTMP_BBP_IO_WRITE32(pAd, AGC1_R0, bbp_val);

	return TRUE;
}


INT rtmp_bbp_get_agc(struct _RTMP_ADAPTER *pAd, CHAR *agc, RX_CHAIN_IDX chain)
{
	UCHAR idx, val;
	UINT32 bbp_val, bbp_reg = AGC1_R8;


	if (((pAd->MACVersion & 0xffff0000) < 0x28830000) || 
		(pAd->Antenna.field.RxPath == 1))
	{
		chain = RX_CHAIN_0;
	}

	idx = val = 0;
	while(chain != 0)
	{
		if (idx >= pAd->Antenna.field.RxPath)
			break;

		if (chain & 0x01)
		{
			RTMP_BBP_IO_READ32(pAd, bbp_reg, &bbp_val);
			val = ((bbp_val & (0x0000ff00)) >> 8) & 0xff;
			break;
		}
		chain >>= 1;
		bbp_reg += 4;
		idx++;
	}

	*agc = val;

	return NDIS_STATUS_SUCCESS;
}


INT rtmp_bbp_set_agc(struct _RTMP_ADAPTER *pAd, UCHAR agc, RX_CHAIN_IDX chain)
{
	UCHAR idx = 0;
	UINT32 bbp_val, bbp_reg = AGC1_R8;
	
	if (((pAd->MACVersion & 0xf0000000) < 0x28830000) || 
		(pAd->Antenna.field.RxPath == 1))
	{
		chain = RX_CHAIN_0;
	}

	while (chain != 0)
	{
		if (idx >= pAd->Antenna.field.RxPath)
			break;
		
		if (idx & 0x01)
		{
			RTMP_BBP_IO_READ32(pAd, bbp_reg, &bbp_val);
			bbp_val = (bbp_val & 0xffff00ff) | (agc << 8);
			RTMP_BBP_IO_WRITE32(pAd, bbp_reg, bbp_val);

			DBGPRINT(RT_DEBUG_INFO, 
					("%s(Idx):Write(R%d,val:0x%x) to Chain(0x%x, idx:%d)\n",
						__FUNCTION__, bbp_reg, bbp_val, chain, idx));
		}
		chain >>= 1;
		bbp_reg += 4;
		idx++;
	}

	return TRUE;
}


INT rtmp_bbp_set_filter_coefficient_ctrl(RTMP_ADAPTER *pAd, UCHAR Channel)
{
	UINT32 bbp_val = 0, org_val = 0;

	if (Channel == 14)
	{
		/* when Channel==14 && Mode==CCK && BandWidth==20M, BBP R4 bit5=1 */
		RTMP_BBP_IO_READ32(pAd, CORE_R1, &org_val);
		bbp_val = org_val;
		if (WMODE_EQUAL(pAd->CommonCfg.PhyMode, WMODE_B))
			bbp_val |= 0x20;
		else
			bbp_val &= (~0x20);

		if (bbp_val != org_val)
			RTMP_BBP_IO_WRITE32(pAd, CORE_R1, bbp_val);
	}

	return TRUE;
}


UCHAR rtmp_bbp_get_random_seed(RTMP_ADAPTER *pAd)
{
	UINT32 value, value2;
	UCHAR seed;

	RTMP_BBP_IO_READ32(pAd, AGC1_R16, &value);
	seed = (UCHAR)((value & 0xff) ^ ((value & 0xff00) >> 8)^ 
					((value & 0xff0000) >> 16));
	RTMP_BBP_IO_READ32(pAd, RXO_R9, &value2);

	return (UCHAR)(seed ^ (value2 & 0xff)^ ((value2 & 0xff00) >> 8));
}


INT rlt_bbp_is_ready(struct _RTMP_ADAPTER *pAd)
{
	INT idx = 0;
	UINT32 val;
	
	do 
	{
		RTMP_BBP_IO_READ32(pAd, CORE_R0, &val);
		if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))			
			return FALSE;
		DBGPRINT(RT_DEBUG_TRACE, ("BBP version = %x\n", val));
	} while ((++idx < 20) && ((val == 0xffffffff) || (val == 0x0)));

	return (((val == 0xffffffff) || (val == 0x0)) ? FALSE : TRUE);
}

#endif /* RLT_MAC */

