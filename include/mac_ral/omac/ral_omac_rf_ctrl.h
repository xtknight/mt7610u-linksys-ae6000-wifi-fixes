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


#ifndef __RAL_OMAC_RF_CTRL_H__
#define __RAL_OMAC_RF_CTRL_H__



/* ================================================================================= */
/* Register format  for RFCTRL                                                       */
/* ================================================================================= */

#define OSC_CTRL		0x5a4
#define PCIE_PHY_TX_ATTENUATION_CTRL		0x05C8
#define INTERNAL_1		0x05C8

#ifdef RT_BIG_ENDIAN
typedef union _INTERNAL_1_STRUCT
{
	struct
	{
		UINT32 Reserve1:10;
		UINT32 CSO_RX_IPV6_CHKSUM_EN:1;
		UINT32 CSO_TX_IPV6_CHKSUM_EN:1;
		UINT32 CSO_HW_PARSE_TCP:1;
		UINT32 CSO_HW_PARSE_IP:1;
		UINT32 CSO_RX_CHKSUM_EN:1;
		UINT32 CSO_TX_CHKSUM_EN:1;
		UINT32 CSO_TIMEOUT_VALUE:4;
		UINT32 PCIE_PHY_TX_ATTEN_EN:1;
		UINT32 PCIE_PHY_TX_ATTEN_VALUE:3;
		UINT32 Reserve2:7;
		UINT32 RF_ISOLATION_ENABLE:1;
	} field;

	UINT32 word;
} INTERNAL_1_STRUCT, *PINTERNAL_1_STRUCT;
#else
typedef union _TX_ATTENUATION_CTRL_STRUC {
	struct
	{
		UINT32 RF_ISOLATION_ENABLE:1;
		UINT32 Reserve2:7;
		UINT32 PCIE_PHY_TX_ATTEN_VALUE:3;
		UINT32 PCIE_PHY_TX_ATTEN_EN:1;
		UINT32 CSO_TIMEOUT_VALUE:4;
		UINT32 CSO_TX_CHKSUM_EN:1;
		UINT32 CSO_RX_CHKSUM_EN:1;
		UINT32 CSO_HW_PARSE_IP:1;
		UINT32 CSO_HW_PARSE_TCP:1;
		UINT32 CSO_TX_IPV6_CHKSUM_EN:1;
		UINT32 CSO_RX_IPV6_CHKSUM_EN:1;
		UINT32 Reserve1:10;		
	} field;
	
	UINT32 word;
} INTERNAL_1_STRUCT, *PINTERNAL_1_STRUCT;
#endif

#define LDO_CFG0 				0x05d4
#define GPIO_SWITCH				0x05dc

#define DEBUG_INDEX				0x05e8	


#endif /* __RAL_OMAC_RF_CTRL_H__ */

