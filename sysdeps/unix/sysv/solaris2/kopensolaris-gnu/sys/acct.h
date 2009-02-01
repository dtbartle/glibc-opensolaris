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

#ifndef _SYS_ACCT_H
#define _SYS_ACCT_H

#include <features.h>
#include <sys/types.h>
#include <sys/types32.h>

#define AFORK		0001
#define ASU		0002
#ifdef SUN_SRC_COMPAT
# define ACOMPAT	0004
# define ACORE		0010
# define AXSIG		0020
#endif
#define AEXPND		0040
#define ACCTF		0300

typedef unsigned short comp_t;

struct acct
  {
	char ac_flag;
	char ac_stat;
	uid32_t ac_uid;
	gid32_t ac_gid;
	dev32_t ac_tty;
	time32_t ac_btime;
	comp_t ac_utime;
	comp_t ac_stime;
	comp_t ac_etime;
	comp_t ac_mem;
	comp_t ac_io;
	comp_t ac_rw;
	char ac_comm[8];
};

__BEGIN_DECLS

extern int acct (const char *);

__END_DECLS

#endif /* _SYS_ACCT_H */
