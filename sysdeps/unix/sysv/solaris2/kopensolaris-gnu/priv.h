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

#ifndef _PRIV_H
#define _PRIV_H

#include <sys/priv.h>
#include <features.h>

#define PRIV_STR_PORT	0x00
#define PRIV_STR_LIT	0x01
#define PRIV_STR_SHORT	0x02

#define PRIV_ALLSETS	(priv_ptype_t)0

__BEGIN_DECLS

extern int getppriv (priv_ptype_t which, priv_set_t *set);

extern int setppriv (priv_op_t op, priv_ptype_t which, priv_set_t *set);

extern unsigned int getpflags (unsigned int flag);

extern int setpflags (unsigned int flag, unsigned int value);

extern priv_set_t *priv_str_to_set (const char *buf, const char *sep,
     const char **endptr);

extern char *priv_set_to_str (const priv_set_t *set, char sep, int flag);

extern int priv_getbyname (const char *privname);

extern const char *priv_getbynum (int privnum);

extern int priv_getsetbyname (const char *privsetname);

extern const char *priv_getsetbynum (int privname);

extern char *priv_gettext (const char *privname);

extern const priv_impl_info_t * getprivimplinfo (void);

__END_DECLS

#endif /* _PRIV_H */
