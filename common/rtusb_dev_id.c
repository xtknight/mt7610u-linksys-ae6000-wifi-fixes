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
	{USB_DEVICE(0x148F,0x7610)}, /* MT7610U */
	{USB_DEVICE(0x13B1,0x003E)}, /* MT7610U */
    {USB_DEVICE(0x0E8D,0x7610)}, /* Sabrent NTWLAC */
    {USB_DEVICE(0x7392,0xa711)}, /* edimax 7711mac */
	{USB_DEVICE_AND_INTERFACE_INFO(0x0E8D, 0x7630, 0xff, 0x2, 0xff)}, /* MT7630U */
	{USB_DEVICE_AND_INTERFACE_INFO(0x0E8D, 0x7650, 0xff, 0x2, 0xff)}, /* MT7650U */
#endif
	{ }/* Terminating entry */
};

INT const rtusb_usb_id_len = sizeof(rtusb_dev_id) / sizeof(USB_DEVICE_ID);
MODULE_DEVICE_TABLE(usb, rtusb_dev_id);
