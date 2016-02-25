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


#ifndef __VR_UBICOM_H__
#define __VR_UBICOM_H__

#ifdef PLATFORM_UBM_IPX8

#include <asm/cachectl.h>

#undef RTMP_UTIL_DCACHE_FLUSH
#define RTMP_UTIL_DCACHE_FLUSH(__AddrStart, __Size)						\
	flush_dcache_range((ULONG)(__AddrStart),							\
						(ULONG)(((UCHAR *)(__AddrStart)) + __Size - 1))

#endif /* PLATFORM_UBM_IPX8 */

#endif /* __VR_UBICOM_H__ */

/* End of vrut_ubm.h */

