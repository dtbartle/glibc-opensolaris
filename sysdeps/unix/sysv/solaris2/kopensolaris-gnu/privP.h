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

#include <sys/types.h>
#include <stdint.h>

typedef uint32_t priv_chunk_t;
typedef struct priv_set priv_set_t;
typedef const char *priv_ptype_t;

typedef struct prpriv
  {
	uint32_t pr_nsets;
	uint32_t pr_setsize;
	uint32_t pr_infosize;
	priv_chunk_t pr_sets[1];
  } prpriv_t;

typedef struct priv_impl_info
  {
	uint32_t priv_headersize;
	uint32_t priv_flags;
	uint32_t priv_nsets;
	uint32_t priv_setsize;
	uint32_t priv_max;
	uint32_t priv_infosize;
	uint32_t priv_globalinfosize;
  } priv_impl_info_t;

#define PRIV_IMPL_INFO_SIZE(p) \
	((p)->priv_headersize + (p)->priv_globalinfosize)

typedef struct priv_info
  {
	uint32_t priv_info_type;
	uint32_t priv_info_size;
  } priv_info_t;

typedef struct priv_info_uint
  {
	priv_info_t info;
	unsigned int val;
  } priv_info_uint_t;

typedef struct priv_info_set
  {
	priv_info_t info;
	priv_chunk_t set[1];
  } priv_info_set_t;

typedef struct priv_info_names
  {
	priv_info_t info;
	int cnt;
	char names[1];
  } priv_info_names_t;

#define PRIV_INFO_SETNAMES	1
#define PRIV_INFO_PRIVNAMES	2
#define PRIV_INFO_BASICPRIVS	3
#define PRIV_INFO_FLAGS		4

typedef struct priv_data
  {
	size_t pd_setsize;
	uint32_t pd_setnames_cnt;
	char **pd_setnames;
	uint32_t pd_privnames_cnt;
	char **pd_privnames;
	priv_chunk_t *pd_basicprivs;
  } priv_data_t;

typedef enum priv_op
{
	PRIV_ON,
	PRIV_OFF,
	PRIV_SET
} priv_op_t;

#define PRIV_EFFECTIVE		"Effective"
#define PRIV_INHERITABLE	"Inheritable"
#define PRIV_PERMITTED		"Permitted"
#define PRIV_LIMIT		"Limit"

#define __NPRIVBITS	(8 * sizeof (priv_chunk_t))
#define __PRIVELT(pr)	((pr) / __NPRIVBITS)
#define __PRIVMASK(pr)	((priv_chunk_t) 1 << ((pr) % __NPRIVBITS))
#define __PRIVSETCHUNKS	(getprivimplinfo()->priv_setsize)
#define __PRIVSETSIZE	(__PRIVSETCHUNKS * sizeof (priv_chunk_t))

extern const priv_data_t * __priv_parse_data_cached (void);
extern const priv_impl_info_t *getprivimplinfo (void);
extern int setppriv (priv_op_t, priv_ptype_t, const priv_set_t *);
extern int getppriv (priv_ptype_t, priv_set_t *);
extern int priv_getsetbyname (const char *);

#endif /* _PRIVP_H */
