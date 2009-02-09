/* Declarations of zone functions and types.
   Copyright (C) 2009 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef _SYS_BYTEORDER_H
#define _SYS_BYTEORDER_H

#include <byteswap.h>
#include <features.h>
#include <sys/types.h>

#define BSWAP_8(x)	__bswap_8(x)
#define BSWAP_16(x)	__bswap_16(x)
#define BSWAP_32(x)	__bswap_32(x)
#define BSWAP_64(x)	__bswap_64(x)

extern uint64_t htonll (uint64_t __hostlonglong)
     __THROW __attribute__ ((__const__));
extern uint64_t ntohll (uint64_t __netlonglong)
     __THROW __attribute__ ((__const__));

#ifdef __OPTIMIZE__
# if __BYTE_ORDER == __BIG_ENDIAN
# define ntohll(x)	(x)
# else
#  if __BYTE_ORDER == __LITTLE_ENDIAN
#   define ntohll(x)	__bswap_64 (x)
#  endif
# endif
#endif

#endif /* _SYS_BYTEORDER_H */
