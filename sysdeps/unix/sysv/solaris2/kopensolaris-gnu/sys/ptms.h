/* Copyright (C) 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by David Bartley <dtbartle@csclub.uwaterloo.ca>, 2008.

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

#ifndef _PTMS_SYS_H
#define _PTMS_SYS_H

#include <sys/types.h>

typedef struct pt_own
  {
	uid_t pto_ruid;
	gid_t pto_rgid;
  } pt_own_t;

#define ISPTM	(('P'<<8)|1)
#define UNLKPT	(('P'<<8)|2)
#define PTSSTTY	(('P'<<8)|3)
#define ZONEPT	(('P'<<8)|4)
#define OWNERPT	(('P'<<8)|5)

#endif /* _PTMS_SYS_H */
