/* Declarations of zone functions and types.
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

#ifndef _ZONEP_H
#define _ZONEP_H

#include <sys/types.h>
#include <auditP.h>
#include <privP.h>

#define ZONE_ATTR_NAME	2

typedef struct
  {
	const char *zone_name;
	const char *zone_root;
	const struct priv_set *zone_privs;
	size_t zone_privssz;
	const char *rctlbuf;
	size_t rctlbufsz;
	int *extended_error;
	const char *zfsbuf;
	size_t zfsbufsz;
	int match;
	uint32_t doi;
	const bslabel_t *label;
	int flags;
  } zone_def;

extern ssize_t zone_getattr (zoneid_t, int, void *, size_t);

#endif /* _ZONEP_H */
