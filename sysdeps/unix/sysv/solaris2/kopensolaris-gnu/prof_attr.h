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

#ifndef _PROF_ATTR_H
#define _PROF_ATTR_H

#include <features.h>

#define NSS_BUFLEN_PROFATTR	1024
#define MAXPROFS		4096

#define PROFATTR_AUTHS_KW	"auths"
#define PROFATTR_PROFS_KW	"profiles"
#define PROFATTR_PRIVS_KW	"privs"

#define DEF_PROF	"PROFS_GRANTED="
#define DEF_CONSUSER	"CONSOLE_USER="

typedef struct profstr_s
  {
	char *name;
	char *res1;
	char *res2;
	char *desc;
	char *attr;
} profstr_t;

typedef struct kva_s kva_t;

typedef struct profattr_s
  {
	char *name;
	char *res1;
	char *res2;
	char *desc;
	kva_t *attr;
 } profattr_t;

__BEGIN_DECLS

extern profattr_t *getprofnam (const char *);
extern profattr_t *getprofattr (void);
extern void getproflist (const char *, char **, int *);
extern void setprofattr (void);
extern void endprofattr (void);
extern void free_profattr (profattr_t *);
extern void free_proflist (char **, int);

__END_DECLS

#endif /* _PROF_ATTR_H */
