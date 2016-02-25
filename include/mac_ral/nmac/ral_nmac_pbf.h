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


#ifndef __RAL_NMAC_PBF_H__
#define __RAL_NMAC_PBF_H__



/* ================================================================================= */
/* Register format  for PBF                                                                                                                                                     */
/* ================================================================================= */


/* Most are for debug. Driver doesn't touch PBF register. */
#define PBF_SYS_CTRL 	 0x0400

#ifdef RT_BIG_ENDIAN
typedef union _PBF_SYS_CTRL_STRUC {
	struct {
		UINT32 rsv5:7; /* Reserved */
		UINT32 CSR_TEST_EN:1;
		UINT32 MAC_CLKSEL:2; /* MAC clock selection */
		UINT32 PWRSV_EN:2;
		UINT32 SHRM_SEL:1; /* Shared memory access selection */
		UINT32 PBF_MSEL:2; /* Packet buffer memory access selection */
		UINT32 rsv4:5;
		UINT32 PBF_CLK_EN:1; /* PBF clock enable */
		UINT32 MAC_CLK_EN:1; /* MAC clock enable */
		UINT32 rsv3:6;
		UINT32 PBF_RESET:1; /* PBF hardware reset */
		UINT32 MAC_RESET:1; /* MAC hardware reset */
		UINT32 rsv:2;
	} field;
	UINT32 word;
} PBF_SYS_CTRL_STRUC;
#else
typedef union _PBF_SYS_CTRL_STRUC{
	struct {
                UINT32 rsv5:7; /* Reserved */
                UINT32 CSR_TEST_EN:1;
                UINT32 MAC_CLKSEL:2; /* MAC clock selection */
                UINT32 PWRSV_EN:2;
                UINT32 SHRM_SEL:1; /* Shared memory access selection */
                UINT32 PBF_MSEL:2; /* Packet buffer memory access selection */
                UINT32 rsv4:5;
                UINT32 PBF_CLK_EN:1; /* PBF clock enable */
                UINT32 MAC_CLK_EN:1; /* MAC clock enable */
                UINT32 rsv3:6;
                UINT32 PBF_RESET:1; /* PBF hardware reset */
                UINT32 MAC_RESET:1; /* MAC hardware reset */
                UINT32 rsv:2;
	}field;
	UINT32 word;
} PBF_SYS_CTRL_STRUC;
#endif


#define PBF_CFG			0x0404
#define TX_MAX_PCNT	0x0408
#define RX_MAX_PCNT	0x040c
#define RXQ_STA			0x0430
#define TXQ_STA			0x0434

#define BCN_OFFSET0		0x041c
#define BCN_OFFSET1		0x0420
#define BCN_OFFSET2		0x0424
#define BCN_OFFSET3		0x0428
#endif /* __RAL_NMAC_PBF_H__ */

