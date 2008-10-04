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

#ifndef _MNTENTP_H
#define _MNTENTP_H

#include <stdio.h>

#define MNTIOC	('m' << 8)
#define MNTIOC_GETMNTENT	(MNTIOC|7)

struct mnttab;
extern int __getmntent_sun (FILE *fp, struct mnttab *mt);
extern char * __hasmntopt_sun (struct mnttab *mt, char *opt);

#endif /* _MNTENTP_H */
