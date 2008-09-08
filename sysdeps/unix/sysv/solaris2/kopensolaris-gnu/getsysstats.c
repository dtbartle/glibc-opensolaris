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

#include <inline-syscall.h>
#include <sys/sysinfo.h>
#include <sys/sysconfig.h>

extern long _sysconfig (int which);

int
__get_nprocs ()
{
  return (int)_sysconfig (_CONFIG_NPROC_ONLN);
}
weak_alias (__get_nprocs, get_nprocs)


int
__get_nprocs_conf ()
{
  return (int)_sysconfig (_CONFIG_NPROC_CONF);
}
weak_alias (__get_nprocs_conf, get_nprocs_conf)


long int
__get_phys_pages ()
{
  return (int)_sysconfig (_CONFIG_PHYS_PAGES);
}
weak_alias (__get_phys_pages, get_phys_pages)


long int
__get_avphys_pages ()
{
  return (int)_sysconfig (_CONFIG_AVPHYS_PAGES);
}
weak_alias (__get_avphys_pages, get_avphys_pages)
