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

#ifndef _PRIVP_H
#define _PRIVP_H

#include <priv.h>

typedef struct priv_data
  {
	size_t pd_setsize;
	uint32_t pd_setnames_cnt;
	char **pd_setnames;
	uint32_t pd_privnames_cnt;
	char **pd_privnames;
	priv_chunk_t *pd_basicprivs;
  } priv_data_t;

extern const priv_data_t * __priv_parse_data_cached (void);

#define __NPRIVBITS	(8 * sizeof (priv_chunk_t))
#define __PRIVELT(pr)	((pr) / __NPRIVBITS)
#define __PRIVMASK(pr)	((priv_chunk_t) 1 << ((pr) % __NPRIVBITS))
#define __PRIVSETCHUNKS	(getprivimplinfo()->priv_setsize)
#define __PRIVSETSIZE	(__PRIVSETCHUNKS * sizeof (priv_chunk_t))

#endif /* _PRIVP_H */
