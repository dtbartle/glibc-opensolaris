/* Declarations of privilege functions and types.
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

#ifndef _SYS_RCTL_H
#define _SYS_RCTL_H

#include <features.h>

typedef struct rctlblk rctlblk_t;

__BEGIN_DECLS

int setrctl (const char *controlname, rctlblk_t *old_blk, rctlblk_t *new_blk,
    unsigned int flags);

int getrctl (const char *controlname, rctlblk_t *old_blk, rctlblk_t *new_blk,
    unsigned int flags);

__END_DECLS

#endif /* _SYS_RCTL_H */