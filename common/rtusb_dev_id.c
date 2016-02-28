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


#define RTMP_MODULE_OS

/*#include "rt_config.h"*/
#include "rtmp_comm.h"
#include "rt_os_util.h"
#include "rt_os_net.h"


/* module table */
USB_DEVICE_ID rtusb_dev_id[] = {
#ifdef MT76x0
	{USB_DEVICE(0x148F,0x7610)}, /* MT7610U Ralink VID */
	{USB_DEVICE(0x0E8D,0x7610)}, /* MT7610U MediaTek VID / Sabrent NTWLAC */
	{USB_DEVICE(0x13B1,0x003E)}, /* Cisco Linksys AE6000 */
   	{USB_DEVICE(0x7392,0xA711)}, /* Edimax 7711ULC/7711MAC */
   	{USB_DEVICE(0x7392,0xB711)}, /* Elecom WDC-433SU2M */
	{USB_DEVICE(0x148F,0x761A)}, /* TP-LINK Archer T2UH */
	{USB_DEVICE(0x148F,0x760A)}, /* TP-LINK */
	{USB_DEVICE(0x0B05,0x17D1)}, /* ASUS USB-AC51 */
	{USB_DEVICE(0x0B05,0x17DB)}, /* ASUS USB-AC50 */
	{USB_DEVICE(0x0DF6,0x0075)}, /* Edimax EW-7811UTC AC600 / Sitecom WLA-3100 */
	{USB_DEVICE(0x2001,0x3D02)}, /* D-Link DWA-171 rev B1 */
	{USB_DEVICE(0x0586,0x3425)}, /* ZyXEL NWD6505 */
	{USB_DEVICE(0x07B8,0x7610)}, /* AboCom AU7212 */
	{USB_DEVICE(0x04BB,0x0951)}, /* IO DATA WN-AC433UK */
	{USB_DEVICE(0x057C,0x8502)}, /* AVM FRITZ!WLAN USB Stick AC 430 */
	{USB_DEVICE(0x293C,0x5702)}, /* Comcast Xfinity KXW02AAA */
	{USB_DEVICE(0x2019,0xAB31)}, /* Planex GW-450D/GW-450D-KATANA */
	{USB_DEVICE(0x20F4,0x806B)}, /* TRENDnet TEW-806UBH AC600 */

	{USB_DEVICE_AND_INTERFACE_INFO(0x0E8D, 0x7630, 0xff, 0x2, 0xff)}, /* MT7630U */
	{USB_DEVICE_AND_INTERFACE_INFO(0x0E8D, 0x7650, 0xff, 0x2, 0xff)}, /* MT7650U */
#endif
	{ }/* Terminating entry */
};

INT const rtusb_usb_id_len = sizeof(rtusb_dev_id) / sizeof(USB_DEVICE_ID);
MODULE_DEVICE_TABLE(usb, rtusb_dev_id);
