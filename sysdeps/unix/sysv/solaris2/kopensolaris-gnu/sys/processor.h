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

/* p_online flag values */
enum
{
	P_OFFLINE = 1,
#define P_OFFLINE	P_OFFLINE
	P_ONLINE = 2,
#define P_ONLINE	P_ONLINE
	P_STATUS = 3,
#define P_STATUS	P_STATUS
	P_FAULTED = 4,
#define P_FAULTED	P_FAULTED
#define P_BAD		P_FAULTED
	P_POWEROFF = 5,
#define P_POWEROFF	P_POWEROFF
	P_NOINTR = 6,
#define P_NOINTR	P_NOINTR
	P_SPARE = 7,
#define P_SPARE		P_SPARE
	P_FORCED = 0x10000000
#define P_FORCED	P_FORCED
};

#define PS_OFFLINE	"off-line"
#define PS_ONLINE	"on-line"
#define PS_FAULTED	"faulted"
#define PS_POWEROFF	"powered-off"
#define PS_NOINTR	"no-intr"
#define PS_SPARE	"spare"

#define PBIND_NONE	-1
#define PBIND_QUERY	-2
#define PBIND_HARD	-3
#define PBIND_SOFT	-4
#define PBIND_QUERY_TYPE	-5

__BEGIN_DECLS

extern int processor_info (processorid_t processorid, processor_info_t *infop);
extern int processor_bind (idtype_t idtype, id_t id, processorid_t processorid,
     processorid_t *obind);
extern int p_online (processorid_t processorid, int flag);
extern processorid_t getcpuid (void);

__END_DECLS

#endif /* _SYS_PROCESSOR_H */
