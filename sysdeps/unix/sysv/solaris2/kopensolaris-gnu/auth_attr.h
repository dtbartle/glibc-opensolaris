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

#ifndef _AUTH_ATTR_H
#define _AUTH_ATTR_H

#include <features.h>

#define NSS_BUFLEN_AUTHATTR	1024

typedef struct authstr_s
  {
	char *name;
	char *res1;
	char *res2;
	char *short_desc;
	char *long_desc;
	char *attr;
} authstr_t;

typedef struct kv_s kva_t;

typedef struct authattr_s
  {
	char *name;
	char *res1;
	char *res2;
	char *short_desc;
	char *long_desc;
	kva_t *attr;
 } authattr_t;

extern authattr_t *getauthnam (const char *);
extern authattr_t *getauthattr (void);
extern void getauthlist (const char *, char **, int *);
extern void setauthattr (void);
extern void endauthattr (void);
extern void free_authattr (authattr_t *);
extern void free_authlist (char **, int);

#endif /* _AUTH_ATTR_H */
