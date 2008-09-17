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

#ifndef _USER_ATTR_H
#define _USER_ATTR_H

#include <features.h>
#include <sys/types.h>
#include <stdio.h>

#define NSS_BUFLEN_USERATTR	1024

typedef struct userstr_s
  {
	char *name;
    char *qualifier;
	char *res1;
	char *res2;
	char *attr;
} userstr_t;

typedef struct kva_s kva_t;

typedef struct userattr_s
  {
	char *name;
    char *qualifier;
	char *res1;
	char *res2;
	kva_t *attr;
 } userattr_t;

__BEGIN_DECLS

extern userattr_t *getusernam (const char *);
extern userattr_t *getuseruid (uid_t);
extern userattr_t *getuserattr (void);
extern userattr_t *fgetuserattr (FILE *);
extern void setuserattr (void);
extern void enduserattr (void);
extern void free_userattr (userattr_t *);

__END_DECLS

#endif /* _USER_ATTR_H */
