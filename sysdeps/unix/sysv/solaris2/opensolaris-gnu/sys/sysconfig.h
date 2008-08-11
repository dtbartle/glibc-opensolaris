/* Definitions for sysconfig found on Solaris systems.
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

#ifndef _BITS_SYSCONFIG_H
#define _BITS_SYSCONFIG_H

#define _CONFIG_NGROUPS             2
#define _CONFIG_CHILD_MAX           3
#define _CONFIG_OPEN_FILES          4
#define _CONFIG_POSIX_VER           5
#define _CONFIG_PAGESIZE            6
#define _CONFIG_CLK_TCK             7
#define _CONFIG_XOPEN_VER           8
#define _CONFIG_PROF_TCK            10
#define _CONFIG_NPROC_CONF          11
#define _CONFIG_NPROC_ONLN          12
#define _CONFIG_AIO_LISTIO_MAX      13
#define _CONFIG_AIO_MAX             14
#define _CONFIG_AIO_PRIO_DELTA_MAX  15
#define _CONFIG_DELAYTIMER_MAX      16
#define _CONFIG_MQ_OPEN_MAX         17
#define _CONFIG_MQ_PRIO_MAX         18
#define _CONFIG_RTSIG_MAX           19
#define _CONFIG_SEM_NSEMS_MAX       20
#define _CONFIG_SEM_VALUE_MAX       21
#define _CONFIG_SIGQUEUE_MAX        22
#define _CONFIG_SIGRT_MIN           23
#define _CONFIG_SIGRT_MAX           24
#define _CONFIG_TIMER_MAX           25
#define _CONFIG_PHYS_PAGES          26
#define _CONFIG_AVPHYS_PAGES        27
#define _CONFIG_COHERENCY           28
#define _CONFIG_SPLIT_CACHE         29
#define _CONFIG_ICACHESZ            30
#define _CONFIG_DCACHESZ            31
#define _CONFIG_ICACHELINESZ        32
#define _CONFIG_DCACHELINESZ        33
#define _CONFIG_ICACHEBLKSZ         34
#define _CONFIG_DCACHEBLKSZ         35
#define _CONFIG_DCACHETBLKSZ        36
#define _CONFIG_ICACHE_ASSOC        37
#define _CONFIG_DCACHE_ASSOC        38
#define _CONFIG_MAXPID              42
#define _CONFIG_STACK_PROT          43
#define _CONFIG_NPROC_MAX           44
#define _CONFIG_CPUID_MAX           45
#define _CONFIG_SYMLOOP_MAX         46
#define _CONFIG_EPHID_MAX           47

#endif /* _BITS_SYSCONFIG_H */
