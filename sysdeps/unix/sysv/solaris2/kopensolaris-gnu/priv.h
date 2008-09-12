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

extern int setppriv (priv_op_t, priv_ptype_t, const priv_set_t *);
extern int getppriv (priv_ptype_t, priv_set_t *);
extern int setpflags (unsigned int, unsigned int);
extern unsigned int getpflags (unsigned int);
extern const priv_impl_info_t *getprivimplinfo (void);

extern int priv_set (priv_op_t, priv_ptype_t, ...);
extern boolean_t priv_ineffect(const char *);

extern priv_set_t *priv_str_to_set (const char *, const char *, const char **);
extern char *priv_set_to_str (const priv_set_t *, char, int);

extern int priv_getbyname (const char *);
extern const char *priv_getbynum (int);
extern int priv_getsetbyname (const char *);
extern const char *priv_getsetbynum (int);

extern char *priv_gettext (const char *);

extern priv_set_t *priv_allocset (void);
extern void priv_freeset (priv_set_t *);

extern void priv_emptyset (priv_set_t *);
extern void priv_fillset (priv_set_t *);

extern boolean_t priv_isemptyset (const priv_set_t *);
extern boolean_t priv_isfullset (const priv_set_t *);
extern boolean_t priv_isequalset (const priv_set_t *, const priv_set_t *);
extern boolean_t priv_issubset (const priv_set_t *, const priv_set_t *);
extern boolean_t priv_ismember (const priv_set_t *, const char *);

extern void priv_intersect (const priv_set_t *, priv_set_t *);
extern void priv_union (const priv_set_t *, priv_set_t *);
extern void priv_inverse (priv_set_t *);

extern int priv_addset (priv_set_t *, const char *);
extern void priv_copyset (const priv_set_t *, priv_set_t *);
extern int priv_delset (priv_set_t *, const char *);

__END_DECLS

#endif /* _PRIV_H */
