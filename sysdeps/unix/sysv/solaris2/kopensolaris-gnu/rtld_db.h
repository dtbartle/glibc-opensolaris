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

#ifndef _RTLD_DB_H
#define _RTLD_DB_H

#include <sys/types.h>
#include <features.h>
#include <proc_service.h>

typedef unsigned long Lmid_t;

typedef struct rd_agent rd_agent_t;

typedef struct rd_loadobj
  {
	psaddr_t rl_nameaddr;
	unsigned int rl_flags;
	psaddr_t rl_base;
	psaddr_t rl_data_base;
	Lmid_t rl_lmident;
	psaddr_t rl_refnameaddr;
	psaddr_t rl_plt_base;
	unsigned int rl_plt_size;
	psaddr_t rl_bend;
	psaddr_t rl_padstart;
	psaddr_t rl_padend;
	psaddr_t rl_dynamic;
	unsigned long rl_tlsmodid;
  } rd_loadobj_t;

typedef int rl_iter_f (const rd_loadobj_t *, void *);

#endif /* _RTLD_DB_H */
