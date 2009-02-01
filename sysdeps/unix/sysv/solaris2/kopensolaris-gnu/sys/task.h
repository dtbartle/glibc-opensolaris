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

#ifndef _SYS_TASK_H
#define _SYS_TASK_H

#include <sys/types.h>
#include <sys/rctl.h>
#include <sys/param.h>
#include <features.h>

#define TASK_NORMAL	0x00
#define TASK_FINAL	0x01
#define TASK_MASK	0x01

#define TASK_PROJ_PURGE	0x00100000
#define TASK_PROJ_MASK	0x00100000

struct task;

__BEGIN_DECLS

extern taskid_t settaskid (projid_t, unsigned int);
extern taskid_t gettaskid (void);

__END_DECLS

#endif /* _SYS_TASK_H */
