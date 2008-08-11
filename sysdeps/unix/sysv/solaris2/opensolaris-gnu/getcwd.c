/* Determine current working directory.  OpenSolaris version.
   Copyright (C) 1997,1998,1999,2000,2002,2003,2006,2008
   Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Based on Linux version contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.
   OpenSolaris bits contributed by David Bartley
    <dtbartle@csclub.uwaterloo.ca>, 2008.

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
#include <stddef.h>
#include <limits.h>
#include <memory.h>
#include <bp-checks.h>
#include <signal.h>
#include <assert.h>
#include <bits/libc-lock.h>

DECLARE_INLINE_SYSCALL (int, getcwd, char *buf, size_t buflen);

#if 0
#ifndef IS_IN_rtld
__libc_lock_define_initialized (, cwd_lock);
#endif
#endif

#ifndef MAX
# define MAX(a, b) ((a) < (b) ? (b) : (a))
#endif

/* If we compile the file for use in ld.so we don't need the feature
   that getcwd() allocates the buffers itself.  */
#ifdef IS_IN_rtld
# define NO_ALLOCATION 1
#endif

char *
__getcwd (char *buf, size_t size)
{
    char *path;

#ifndef NO_ALLOCATION
    size_t alloc_size = size;
    if (size == 0)
    {
        if (buf != NULL)
        {
            __set_errno (EINVAL);
            return NULL;
        }
        alloc_size = MAX (PATH_MAX, __getpagesize ());
    }

    if (buf == NULL)
    {
        path = malloc (alloc_size);
        if (path == NULL)
            return NULL;
    }
    else
#else
# define alloc_size size
#endif
    path = buf;

#if 0
#ifndef IS_IN_rtld
    /* block all signals and lock cwd */
    sigset_t fillset, oldset;
    if(sigfillset(&fillset) != 0)
        return -1;
    if(sigprocmask(SIG_SETMASK, &fillset, &oldset) != 0)
        return -1;
    __libc_lock_lock(cwd_lock);
#endif
#endif

    if (INLINE_SYSCALL (getcwd, 2, CHECK_STRING (path), alloc_size) == -1)
    {
        if (buf == NULL && path != NULL)
            free(path);
        path = NULL;
    }

#if 0
#ifndef IS_IN_rtld
    /* unlock cwd and restore signals */
    __libc_lock_unlock (cwd_lock);
    assert (sigprocmask (SIG_SETMASK, &oldset, NULL) == 0);
#endif
#endif

    return path;
}

weak_alias (__getcwd, getcwd)
