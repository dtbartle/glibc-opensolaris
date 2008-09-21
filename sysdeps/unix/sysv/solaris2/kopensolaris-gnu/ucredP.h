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

#ifndef _UCREDP_H
#define _UCREDP_H

#include <sys/types.h>
#include <auditP.h>
#include <privP.h>

typedef struct prcred
  {
	uid_t pr_euid;
	uid_t pr_ruid;
	uid_t pr_suid;
	gid_t pr_egid;
	gid_t pr_rgid;
	gid_t pr_sgid;
	int pr_ngroups;
	gid_t pr_groups[1];
  } prcred_t;

typedef struct ucred_s
  {
	uint32_t uc_size;
	uint32_t uc_credoff;
	uint32_t uc_privoff;
	pid_t uc_pid;
	uint32_t uc_audoff;
	zoneid_t uc_zoneid;
	projid_t uc_projid;
	uint32_t uc_labeloff;
  } ucred_t;

#define BSLABEL_T_SIZE		36

extern size_t ucred_size (void);

#endif /* _UCREDP_H */
