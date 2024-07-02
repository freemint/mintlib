/* Copyright (C) 1996-2024 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <sys/types.h>
#include <stdint.h>
#include <sys/socket.h>
#include <net/ethernet.h>
#include <netinet/ether.h>


char *ether_ntoa(const struct ether_addr *addr)
{
	static char asc[ETHER_ADDR_LEN * 3];

	return ether_ntoa_r(addr, asc);
}
