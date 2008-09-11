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

#ifndef _SYS_UCRED_H
#define _SYS_UCRED_H

#include <sys/types.h>

#define UCREDSYS_UCREDGET	0
#define UCREDSYS_GETPEERUCRED	1

#if _STRUCTURED_PROC != 0

struct ucred_s
  {
	uint32_t uc_size;
	uint32_t uc_credoff;
	uint32_t uc_privoff;
	pid_t uc_pid;
	uint32_t uc_audoff;
	zoneid_t uc_zoneid;
	projid_t uc_projid;
	uint32_t uc_labeloff;
  };

#define UCCRED(uc)	(prcred_t *)(!(uc)->uc_credoff ? \
	((char *)(uc)) + (uc)->uc_credoff : NULL)

#define UCPRIV(uc)	(prpriv_t *)((!(uc)->uc_privoff ? \
	((char *)(uc)) + (uc)->uc_privoff : NULL)

#define UCAUD(uc)	(auditinfo64_addr_t *)((uc)->uc_audoff ? \
	((char *)(uc)) + (uc)->uc_audoff : NULL)

#define UCLABEL(uc)	(bslabel_t *)(!(uc)->uc_labeloff ? \
	((char *)(uc)) + (uc)->uc_labeloff : NULL)

#define UCRED_CRED_OFF	sizeof (struct ucred_s)

#define UCRED_SIZE(info) \
	(sizeof(ucred_t) + sizeof(prcred_t) + sizeof(prpriv_t) + \
	((int)sysconf (_SC_NGROUPS_MAX) - 1) * sizeof(gid_t) + \
	sizeof(priv_chunk_t) * (info->priv_setsize * info->priv_nsets - 1) + \
	info->priv_infosize + AUDITINFO64_ADDR_T_SIZE + BSLABEL_T_SIZE)

#endif /* _STRUCTURED_PROC != 0 */

#endif /* _SYS_UCRED_H */
