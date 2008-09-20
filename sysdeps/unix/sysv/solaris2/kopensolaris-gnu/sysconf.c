/* Get file-specific information about a file.  OpenSolaris version.
   Copyright (C) 2003, 2004, 2006, 2008 Free Software Foundation, Inc.
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

#include <inline-syscall.h>
#include <unistd.h>
#include <sys/sysconfig.h>

extern long _sysconfig (int which);

static long int posix_sysconf (int name);


/* Get the value of the system variable NAME.  */
long int
__sysconf (int name)
{
  switch (name)
    {
    case _SC_NGROUPS_MAX:
      return _sysconfig (_CONFIG_NGROUPS);
    case _SC_STREAM_MAX:
      return __getdtablesize ();
    case _SC_NPROCESSORS_MAX:
      return _sysconfig (_CONFIG_NPROC_MAX);
    case _SC_STACK_PROT:
      return _sysconfig (_CONFIG_STACK_PROT);
    case _SC_AIO_LISTIO_MAX:
      return _sysconfig (_CONFIG_AIO_LISTIO_MAX);
    case _SC_AIO_MAX:
      return _sysconfig (_CONFIG_AIO_MAX);
    case _SC_AIO_PRIO_DELTA_MAX:
      return _sysconfig (_CONFIG_AIO_PRIO_DELTA_MAX);
    case _SC_DELAYTIMER_MAX:
      return _sysconfig (_CONFIG_DELAYTIMER_MAX);
    case _SC_MQ_OPEN_MAX:
      return _sysconfig (_CONFIG_MQ_OPEN_MAX);
    case _SC_MQ_PRIO_MAX:
      return _sysconfig (_CONFIG_MQ_PRIO_MAX);
    case _SC_RTSIG_MAX:
      return _sysconfig (_CONFIG_RTSIG_MAX);
    case _SC_SEM_NSEMS_MAX:
      return _sysconfig (_CONFIG_SEM_NSEMS_MAX);
    case _SC_SEM_VALUE_MAX:
      return _sysconfig (_CONFIG_SEM_VALUE_MAX);
    case _SC_SIGQUEUE_MAX:
      return _sysconfig (_CONFIG_SIGQUEUE_MAX);
    case _SC_SIGRT_MAX:
      return _sysconfig (_CONFIG_SIGRT_MAX);
    case _SC_SIGRT_MIN:
      return _sysconfig (_CONFIG_SIGRT_MIN);
    case _SC_TIMER_MAX:
      return _sysconfig (_CONFIG_TIMER_MAX);
    case _SC_COHER_BLKSZ:
      return _sysconfig (_CONFIG_COHERENCY);
    case _SC_SPLIT_CACHE:
      return _sysconfig (_CONFIG_SPLIT_CACHE);
    case _SC_ICACHE_SZ:
      return _sysconfig (_CONFIG_ICACHESZ);
    case _SC_DCACHE_SZ:
      return _sysconfig (_CONFIG_DCACHESZ);
    case _SC_ICACHE_LINESZ:
      return _sysconfig (_CONFIG_ICACHELINESZ);
    case _SC_DCACHE_LINESZ:
      return _sysconfig (_CONFIG_DCACHELINESZ);
    case _SC_ICACHE_BLKSZ:
      return _sysconfig (_CONFIG_ICACHEBLKSZ);
    case _SC_DCACHE_BLKSZ:
      return _sysconfig (_CONFIG_DCACHEBLKSZ);
    case _SC_ICACHE_ASSOC:
      return _sysconfig (_CONFIG_ICACHE_ASSOC);
    case _SC_DCACHE_ASSOC:
      return _sysconfig (_CONFIG_DCACHE_ASSOC);
    case _SC_MAXPID:
      return _sysconfig (_CONFIG_MAXPID);
    case _SC_CPUID_MAX:
      return _sysconfig (_CONFIG_CPUID_MAX);
    case _SC_EPHID_MAX:
      return _sysconfig (_CONFIG_EPHID_MAX);
    case _SC_SYMLOOP_MAX:
      return _sysconfig (_CONFIG_SYMLOOP_MAX);
    default:
      return posix_sysconf (name);
  }
}

/* Now the POSIX version.  */
#undef __sysconf
#define __sysconf static posix_sysconf
#include <sysdeps/posix/sysconf.c>

weak_alias (__sysconf, _sysconf)
