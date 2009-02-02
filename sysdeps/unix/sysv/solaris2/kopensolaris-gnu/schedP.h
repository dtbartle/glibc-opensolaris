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

#ifndef _SCHEDP_H
#define _SCHEDP_H

#include <sys/types.h>
#include <sys/procset.h>
#include <sched.h>

typedef struct rtparms
  {
	pri_t rt_pri;
	unsigned int rt_tqsecs;
	int rt_tqnsecs;
  } rtparms_t;

#define RT_TQINF	-2

typedef struct fxparms
  {
	pri_t fx_upri;
	pri_t fx_uprilim;
	unsigned int fx_tqsecs;
	int fx_tqnsecs;
  } fxparms_t;

#define FX_TQINF	-2

extern int __sched_policy_to_class (int policy);
extern int __sched_class_to_policy (int cid);
extern int __sched_getparam_id (int idtype, id_t id, int *priority);
extern int __sched_setparam_id (int idtype, id_t id, int priority);
extern int __sched_getscheduler_id (int idtype, id_t id, int *policy,
    int *priority);
extern int __sched_setscheduler_id (int idtype, id_t id, int policy,
    int priority);
extern long __internal_priocntl_4 (int *errval, idtype_t idtype, id_t id,
    int cmd, ...);

#endif /* _SCHEDP_H */
