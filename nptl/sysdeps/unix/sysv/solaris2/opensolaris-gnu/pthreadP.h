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

#ifndef _OPENSOLARIS_PTHREADP_H
#define _OPENSOLARIS_PTHREADP_H

/* use tid as pthread_t (instead of descr) */
#define PTHREAD_T_IS_TID

/* pthread_setXid not supported */
#define NO_SETXID_SUPPORT

/* disable robust list */
#define NO_ROBUST_LIST_SUPPORT

/* disable futex support */
#define NO_FUTEX_SUPPORT

/* make sure SIGCANCEL sanity check compiles */
#define SI_TKILL SI_LWP
#define __ASSUME_CORRECT_SI_PID

/* we support tkill */
#undef __NR_tgkill
#undef __ASSUME_TGKILL

/* rwlock macros */
#define _RWLOCK_WR_LOCK		0x80000000
#define _RWLOCK_RD_MASK		0x7FFFFFFF
#define _RWLOCK_RD_MAX      0x7FFFFFFF

#include <nptl/pthreadP.h>

/* Flags in mutex attr.  */
#undef PTHREAD_MUTEXATTR_PROTOCOL_SHIFT
#define PTHREAD_MUTEXATTR_PROTOCOL_SHIFT	28
#undef PTHREAD_MUTEXATTR_PROTOCOL_MASK
#define PTHREAD_MUTEXATTR_PROTOCOL_MASK		0x30000000
#undef PTHREAD_MUTEXATTR_PRIO_CEILING_SHIFT
#define PTHREAD_MUTEXATTR_PRIO_CEILING_SHIFT	12
#undef PTHREAD_MUTEXATTR_PRIO_CEILING_MASK
#define PTHREAD_MUTEXATTR_PRIO_CEILING_MASK	0x00fff000
#undef PTHREAD_MUTEXATTR_FLAG_ROBUST
#define PTHREAD_MUTEXATTR_FLAG_ROBUST		0x40
#undef PTHREAD_MUTEXATTR_FLAG_PSHARED
#define PTHREAD_MUTEXATTR_FLAG_PSHARED		0x01 /* LOCK_SHARED */
#undef PTHREAD_MUTEXATTR_FLAG_BITS
#define PTHREAD_MUTEXATTR_FLAG_BITS \
  (PTHREAD_MUTEXATTR_FLAG_ROBUST | PTHREAD_MUTEXATTR_FLAG_PSHARED \
   | PTHREAD_MUTEXATTR_PROTOCOL_MASK | PTHREAD_MUTEXATTR_PRIO_CEILING_MASK)

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <inline-syscall.h>
#include <synch_priv.h>

DECLARE_INLINE_SYSCALL (pthread_t, lwp_self, void);
DECLARE_INLINE_SYSCALL (int, lwp_kill, pthread_t lwpid, int sig);

static inline int __internal_kill_1 (int *errval, int sig)
{
  int saved_errno = errno;
  int result = kill (THREAD_SELF->pid, sig);
  if (result != 0)
    *errval = errno;
  __set_errno (saved_errno);
  return result;
}

static inline int __internal_set_tid_address_1 (int *errval, pthread_t *tid)
{
  return INLINE_SYSCALL (lwp_self, 0);
}

static inline int __internal_rt_sigprocmask_4 (int *errval, int how,
    const sigset_t *set, sigset_t *oldset, int setsize)
{
  int saved_errno = errno;
  int result = sigprocmask (how, set, oldset);
  if (result != 0)
    *errval = errno;
  __set_errno (saved_errno);
  return result;
}

static inline int __internal_write_3 (int *errval, int fd, const void *buf,
    size_t count)
{
  int saved_errno = errno;
  int result = write (fd, buf, count);
  if (result != 0)
    *errval = errno;
  __set_errno (saved_errno);
  return result;
}

static inline int __internal_tkill_2 (int *errval, pthread_t tid, int sig)
{
  return *errval = INLINE_SYSCALL (lwp_kill, 2, tid, sig);
}

static inline int __cond_has_waiters (pthread_cond_t *cond)
{
  return cond->cond_waiters_kernel;
}

#endif /* _OPENSOLARIS_PTHREADP_H */
