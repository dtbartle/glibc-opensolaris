/* Declarations of SID functions and types.
   Copyright (C) 2008 Free Software Foundation, Inc.
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

#ifndef _SYS_SID_H
#define _SYS_SID_H

#include <sys/types.h>
#include <features.h>

#define SIDSYS_ALLOC_IDS	0
#define SIDSYS_IDMAP_REG	1
#define SIDSYS_IDMAP_UNREG	2

/* allocids flags.  */
#define SID_EXTEND_RANGE	0
#define SID_NEW_RANGE	1

#define SIDSYS_SID2ID	0
#define SIDSYS_ID2SID	1

__BEGIN_DECLS

int allocids (int, int, uid_t *, int, gid_t *);
int idmap_reg (int);
int idmap_unreg (int);

__END_DECLS

#endif /* _SYS_SID_H */
