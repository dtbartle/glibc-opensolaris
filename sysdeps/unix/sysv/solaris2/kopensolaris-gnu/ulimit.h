/* Copyright (C) 1997, 1998, 1999 Free Software Foundation, Inc.
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

#ifndef _ULIMIT_H
#define _ULIMIT_H	1

#include <features.h>

/* Constants used as the first parameter for `ulimit'.  They denote limits
   which can be set or retrieved using this function.  */
enum
{
  UL_GETFSIZE = 1,			/* Return limit on the size of a file,
					   in units of 512 bytes.  */
#define UL_GETFSIZE	UL_GETFSIZE
  UL_SETFSIZE,				/* Set limit on the size of a file to
					   second argument.  */
#define UL_SETFSIZE	UL_SETFSIZE

  UL_GMEMLIM,
#define UL_GMEMLIM	UL_GMEMLIM

  UL_GDESLIM
#define UL_GDESLIM	UL_GDESLIM
};


__BEGIN_DECLS

/* Control process limits according to CMD.  */
extern long int ulimit (int __cmd, ...) __THROW;

__END_DECLS

#endif /* ulimit.h */