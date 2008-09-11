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

#ifndef _SYS_RCTL_IMPL_H
#define _SYS_RCTL_IMPL_H

#include <sys/rctl.h>
#include <sys/resource.h>

#define RCTLCTL_GET	0
#define RCTLCTL_SET	1

typedef struct rctl_opaque
  {
	rctl_qty_t rcq_value;
	rctl_qty_t rcq_enforced_value;
	rctl_priv_t rcq_privilege;
	int rcq_global_flagaction;
	int rcq_global_syslog_level;
	int rcq_local_flagaction;
	int rcq_local_signal;
	id_t rcq_local_recipient_pid;
	hrtime_t rcq_firing_time;
  } rctl_opaque_t;

#define RCTLBLK_INC(blk, n)	\
	(rctlblk_t *)((char *)(blk) + ((n) * rctlblk_size ()))

#endif /* _SYS_RCTL_IMPL_H */
