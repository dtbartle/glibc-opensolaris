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

#ifndef _SYS_LWP_H
#define _SYS_LWP_H

#include <sys/types.h>
#include <features.h>
#define __need_timespec
#include <time.h>

struct lwpinfo
{
    struct timespec lwp_utime;
    struct timespec lwp_stime;
    long lwpinfo_pad[64];
};

#define LWP_DAEMON		0x00000020
#define LWP_DETACHED	0x00000040
#define LWP_SUSPENDED	0x00000080

#define _LWP_FSBASE		0
#define _LWP_GSBASE		1

#define _LWP_SETPRIVATE		0
#define _LWP_GETPRIVATE		1

__BEGIN_DECLS

int _lwp_kill (lwpid_t, int);
int _lwp_info (struct lwpinfo *);
lwpid_t _lwp_self (void);
int _lwp_suspend (lwpid_t);
int _lwp_continue (lwpid_t);

__END_DECLS

#endif /* _SYS_LWP_H */
