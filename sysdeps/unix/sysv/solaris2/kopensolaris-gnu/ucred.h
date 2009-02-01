/* Copyright (C) 2008 Free Software Foundation, Inc.
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

#ifndef _UCRED_H
#define _UCRED_H

#include <features.h>
#include <sys/types.h>
#include <sys/priv.h>

typedef struct _mac_label_impl m_label_t;

typedef struct ucred_s ucred_t;

__BEGIN_DECLS

extern ucred_t *ucred_get (pid_t pid);
extern void ucred_free (ucred_t *uc);
extern size_t ucred_size (void);

extern uid_t ucred_geteuid (const ucred_t *uc);
extern uid_t ucred_getruid (const ucred_t *uc);
extern uid_t ucred_getsuid (const ucred_t *uc);
extern gid_t ucred_getegid (const ucred_t *uc);
extern gid_t ucred_getrgid (const ucred_t *uc);
extern gid_t ucred_getsgid (const ucred_t *uc);
extern pid_t ucred_getpid (const ucred_t *uc);
extern projid_t ucred_getprojid (const ucred_t *uc);
extern zoneid_t ucred_getzoneid (const ucred_t *uc);

extern int ucred_getgroups (const ucred_t *uc, const gid_t **groups);
extern const priv_set_t *ucred_getprivset (const ucred_t *uc, const char *set);
extern unsigned int ucred_getpflags (const ucred_t *uc, unsigned int flags);
extern m_label_t *ucred_getlabel (const ucred_t *uc);

extern int getpeerucred (int fd, ucred_t **ucred);

__END_DECLS

#endif /* _UCRED_H */
