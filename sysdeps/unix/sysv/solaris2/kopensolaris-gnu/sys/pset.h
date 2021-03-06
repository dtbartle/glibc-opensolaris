/* Declarations of processor sets.
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

#ifndef _SYS_PSET_H
#define _SYS_PSET_H

#include <sys/processor.h>
#include <features.h>

typedef int psetid_t;

/* Syscall sub-call numbers.  */
#define PSET_CREATE		0
#define PSET_DESTROY		1
#define PSET_ASSIGN		2
#define PSET_INFO		3
#define PSET_BIND		4
#define PSET_GETLOADAVG		5
#define PSET_LIST		6
#define PSET_SETATTR		7
#define PSET_GETATTR		8
#define PSET_ASSIGN_FORCED	9

#define PS_NONE		-1
#define PS_QUERY	-2
#define PS_MYID		-3
#define PS_SOFT		-4
#define PS_HARD		-5
#define PS_QUERY_TYPE	-6

/* types of processor sets */
#define PS_SYSTEM	1
#define PS_PRIVATE	2

__BEGIN_DECLS

extern int  pset_create (psetid_t *newpset);
extern int  pset_destroy (psetid_t pset);
extern int  pset_assign (psetid_t pset, processorid_t cpu, psetid_t *opset);
extern int  pset_info (psetid_t pset, int *type, unsigned int *numcpus,
    processorid_t *cpulist);
extern int  pset_bind (psetid_t pset, idtype_t idtype, id_t id,
    psetid_t *opset);
extern int  pset_getloadavg (psetid_t pset, double loadavg[], int nelem);
extern int  pset_list (psetid_t *psetlist, unsigned int *numpsets);
extern int  pset_setattr (psetid_t pset, unsigned int attr);
extern int  pset_getattr (psetid_t pset, unsigned int *attr);

__END_DECLS

#endif /* _SYS_PSET_H */
