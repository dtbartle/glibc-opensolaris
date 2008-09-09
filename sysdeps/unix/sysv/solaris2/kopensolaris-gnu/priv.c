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
#include <priv.h>
#include <privP.h>
#include <sys/priocntl.h>
#include <alloca.h>
#include <bits/libc-lock.h>

DECLARE_INLINE_SYSCALL (int, privsys, int code, priv_op_t op,
    priv_ptype_t type, void *buf, size_t bufsize, int itype);

/* Docs: http://docs.sun.com/app/docs/doc/816-5168/6mbb3hrjc?a=view
         http://docs.sun.com/app/docs/doc/816-5167/setppriv-2?a=view */

__libc_lock_define (static, privimplinfo_lock);

libc_freeres_ptr (static priv_impl_info_t *__info);

const priv_impl_info_t * getprivimplinfo (void)
{
  if (__info)
    return __info;

  __libc_lock_lock (privimplinfo_lock);

  /* First call: get header.  */
  priv_impl_info_t _info;
  int result = INLINE_SYSCALL (privsys, 6, PRIVSYS_GETIMPLINFO, 0, 0, &_info,
      sizeof(_info), 0);
  if (result == 0)
    {
      /* Second call: alloc and get full priv_impl_info_t.  */
      size_t info_size = PRIV_IMPL_INFO_SIZE (&_info);
      __info = malloc (info_size);
      result = INLINE_SYSCALL (privsys, 6, PRIVSYS_GETIMPLINFO, 0, 0, __info,
          info_size, 0);
      if (result != 0)
        {
          free (__info);
          __info = NULL;
        }
    }

  __libc_lock_unlock (privimplinfo_lock);
  return __info;
}
