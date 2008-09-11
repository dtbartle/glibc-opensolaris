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

#ifndef _RCTL_H
#define _RCTL_H

#include <sys/rctl.h>
#include <sys/types.h>
#include <features.h>

__BEGIN_DECLS

int rctl_walk(int (*)(const char *, void *), void *);

hrtime_t rctlblk_get_firing_time (rctlblk_t *);
unsigned int rctlblk_get_global_action (rctlblk_t *);
unsigned int rctlblk_get_global_flags (rctlblk_t *);
unsigned int rctlblk_get_local_action (rctlblk_t *, int *);
unsigned int rctlblk_get_local_flags (rctlblk_t *);
rctl_priv_t rctlblk_get_privilege (rctlblk_t *);
id_t rctlblk_get_recipient_pid (rctlblk_t *);
rctl_qty_t rctlblk_get_value(rctlblk_t *);
rctl_qty_t rctlblk_get_enforced_value (rctlblk_t *);
void rctlblk_set_local_action (rctlblk_t *, unsigned int, int);
void rctlblk_set_local_flags (rctlblk_t *, unsigned int);
void rctlblk_set_privilege (rctlblk_t *, rctl_priv_t);
void rctlblk_set_recipient_pid (rctlblk_t *, id_t);
size_t rctlblk_size (void);

__END_DECLS

#endif /* _RCTL_H */
