/* Declarations of processor-related types/macros.
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

#ifndef _SYS_PROCESSOR_H
#define _SYS_PROCESSOR_H

#include <features.h>
#include <sys/procset.h>

typedef int processorid_t;

typedef struct
{
	int pi_state;
#define PI_TYPELEN	16
	char pi_processor_type[PI_TYPELEN];
#define PI_FPUTYPE	32
	char pi_fputypes[PI_FPUTYPE];
	int pi_clock;
} processor_info_t;

__BEGIN_DECLS

extern int processor_info (processorid_t processorid, processor_info_t *infop);

extern int processor_bind (idtype_t idtype, id_t id, processorid_t processorid,
     processorid_t *obind);

extern int p_online (processorid_t processorid, int flag);

extern processorid_t getcpuid (void);

__END_DECLS

#endif /* _SYS_PROCESSOR_H */
