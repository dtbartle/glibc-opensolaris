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
#include <errno.h>
#include <unistd.h>
#include <sys/gmon.h>
#include <ldsodefs.h>
#include <dlfcn.h>

DECLARE_INLINE_SYSCALL (int, brk, __caddr_t *addr);

/*
  Solaris will round the break up to an 8 - 16 byte alignment. We don't take
  this into account, which is safe; we will always just assume a slightly
  smaller amount of core than we actually have available.

  Solaris doesn't return the current break via brk, so we track it here.

  For dynamic executables, the kernel does not set the initial break. It
  expects libc to set the initial break to the tail of the executable being
  loaded. For static executables we use &_end.

  See uts/common/exec/elf/elf.c, line 800.
*/

#define BRK_ALIGN(addr) (void *)(((uintptr_t)addr + 0x7) & ~(uintptr_t)0x7)

void *__curbrk = 0;
extern int _end;

int
__brk (addr)
     void *addr;
{
    int result = 0;

  if (__curbrk == 0)
    {
#ifndef SHARED
      /* If we are statically compiled we can use &_end.  */
      addr = &_end;
#else
      if (GL(dl_ns)[LM_ID_BASE]._ns_loaded)
        {
          /* The dynamic executable has been mapped in.  */
          addr = (void*)GL(dl_ns)[LM_ID_BASE]._ns_loaded->l_map_end;
        }
      else if (GL(dl_rtld_map).l_addr == 0)
        {
          /* This must be ld.so.1 being run directly.  */
          addr = &_end;
        }
      else
        {
          /* The executable has not been mapped in.  */
          return -1;
        }
#endif
      }
    else if (addr == 0)
      {
        /* We have multiple libc's.  */
        return 0;
    }

    addr = BRK_ALIGN (addr);
    result = INLINE_SYSCALL (brk, 1, addr);
    if (result == 0)
        __curbrk = addr;

    return result;
}

weak_alias (__brk, brk)
