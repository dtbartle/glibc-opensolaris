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

#ifndef _SYS_CORECTL_H
#define _SYS_CORECTL_H

#include <sys/types.h>
#include <features.h>

typedef unsigned long long core_content_t;

/* Options.  */
#define CC_GLOBAL_PATH		0x01
#define CC_PROCESS_PATH		0x02
#define CC_GLOBAL_SETID		0x04
#define CC_PROCESS_SETID	0x08
#define CC_GLOBAL_LOG		0x10

/* core_content_t values.  */
#define CC_CONTENT_STACK	0x0001ULL
#define CC_CONTENT_HEAP		0x0002ULL
#define CC_CONTENT_SHFILE	0x0004ULL
#define CC_CONTENT_SHANON	0x0008ULL
#define CC_CONTENT_TEXT		0x0010ULL
#define CC_CONTENT_DATA		0x0020ULL
#define CC_CONTENT_RODATA	0x0040ULL
#define CC_CONTENT_ANON		0x0080ULL
#define CC_CONTENT_SHM		0x0100ULL
#define CC_CONTENT_ISM		0x0200ULL
#define CC_CONTENT_DISM		0x0400ULL
#define CC_CONTENT_CTF		0x0800ULL
#define CC_CONTENT_SYMTAB	0x1000ULL
#define CC_CONTENT_ALL		0x1FFFULL
#define CC_CONTENT_NONE		0x0000ULL
#define CC_CONTENT_DEFAULT \
	(CC_CONTENT_STACK | CC_CONTENT_HEAP | CC_CONTENT_ISM | \
	 CC_CONTENT_DISM | CC_CONTENT_SHM | CC_CONTENT_SHANON | \
	 CC_CONTENT_TEXT | CC_CONTENT_DATA | CC_CONTENT_RODATA | \
	 CC_CONTENT_ANON | CC_CONTENT_CTF)
#define CC_CONTENT_INVALID  (-1ULL)

__BEGIN_DECLS

extern  int core_set_options (int);
extern  int core_get_options (void);
extern  int core_set_global_path (const char *, size_t);
extern  int core_get_global_path (char *, size_t);
extern  int core_set_default_path (const char *, size_t);
extern  int core_get_default_path (char *, size_t);
extern  int core_set_process_path (const char *, size_t, pid_t);
extern  int core_get_process_path (char *, size_t, pid_t);
extern  int core_set_global_content (const core_content_t *);
extern  int core_get_global_content (core_content_t *);
extern  int core_set_default_content (const core_content_t *);
extern  int core_get_default_content (core_content_t *);
extern  int core_set_process_content (const core_content_t *, pid_t);
extern  int core_get_process_content (core_content_t *, pid_t);

__END_DECLS

#endif /* _SYS_CORECTL_H */
