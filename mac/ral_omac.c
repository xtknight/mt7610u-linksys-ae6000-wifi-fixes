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


INT get_pkt_phymode_by_rxwi(RXWI_STRUC *rxwi)
{
	return rxwi->RXWI_O.phy_mode;
}

INT get_pkt_rssi_by_rxwi(RXWI_STRUC *rxwi, INT size, CHAR *rssi)
{
	switch (size) {
		case 3:
			rssi[2] = rxwi->RxWIRSSI2;
		case 2:
			rssi[1] = rxwi->RxWIRSSI1;
		case 1:
		default:
			rssi[0] = rxwi->RxWIRSSI0;
			break;
	}

	return 0;
}


INT get_pkt_snr_by_rxwi(RXWI_STRUC *rxwi, INT size, UCHAR *snr)
{
	switch (size) {
		case 3:
			snr[2] = rxwi->RxWISNR2;
		case 2:
			snr[1] = rxwi->RxWISNR1;
		case 1:
		default:
			snr[0] = rxwi->RxWISNR0;
			break;
	}
	
	return 0;
}

