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

/* rwlock macros.  */
#define _RWLOCK_WR_LOCK		0x80000000
#define _RWLOCK_RD_MASK		0x7FFFFFFF
#define _RWLOCK_RD_MAX      0x7FFFFFFF

#include <nptl/pthreadP.h>
#include <sys/synch.h>

/* Flags in mutex attr.  */
#undef PTHREAD_MUTEXATTR_PROTOCOL_SHIFT
#define PTHREAD_MUTEXATTR_PROTOCOL_SHIFT	0
#undef PTHREAD_MUTEXATTR_PROTOCOL_MASK
#define PTHREAD_MUTEXATTR_PROTOCOL_MASK \
  (PTHREAD_PRIO_INHERIT | PTHREAD_PRIO_PROTECT)
#undef PTHREAD_MUTEXATTR_PRIO_CEILING_SHIFT
#define PTHREAD_MUTEXATTR_PRIO_CEILING_SHIFT	12
#undef PTHREAD_MUTEXATTR_PRIO_CEILING_MASK
#define PTHREAD_MUTEXATTR_PRIO_CEILING_MASK	0x0ffff000
#undef PTHREAD_MUTEXATTR_FLAG_ROBUST
#define PTHREAD_MUTEXATTR_FLAG_ROBUST		LOCK_ROBUST
#undef PTHREAD_MUTEXATTR_FLAG_PSHARED
#define PTHREAD_MUTEXATTR_FLAG_PSHARED		LOCK_SHARED
#undef PTHREAD_MUTEXATTR_FLAG_BITS
#define PTHREAD_MUTEXATTR_FLAG_BITS \
  (PTHREAD_MUTEXATTR_FLAG_ROBUST | PTHREAD_MUTEXATTR_FLAG_PSHARED \
   | PTHREAD_MUTEXATTR_PROTOCOL_MASK | PTHREAD_MUTEXATTR_PRIO_CEILING_MASK)

#define PTHREAD_RWLOCK_TYPE_MASK    0x00000006
#define PTHREAD_RWLOCK_TYPE_SHIFT   1
#undef PTHREAD_RWLOCK_PREFER_READER_P
#define PTHREAD_RWLOCK_PREFER_READER_P(rwlock) \
    (((rwlock->type >> PTHREAD_RWLOCK_TYPE_SHIFT) & \
    PTHREAD_RWLOCK_TYPE_MASK) != PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP)

#define MUTEX_IS_OWNER(mutex) \
       (mutex->mutex_lockbyte == LOCKBYTE_SET &&                        \
     (((mutex)->mutex_type & LOCK_SHARED) == 0 ||                       \
      (mutex)->mutex_ownerpid == THREAD_GETMEM (THREAD_SELF, pid)) &&   \
     ((mutex)->mutex_owner == THREAD_GETMEM (THREAD_SELF, tid)))

#define MUTEX_NOT_OWNER(mutex)  (! MUTEX_IS_OWNER (mutex))

#define INVALID_TIMESPEC(tv)    ((tv) && ((tv)->tv_sec < 0 || \
    (tv)->tv_nsec < 0 || (tv)->tv_nsec >= 1000000000))

#include <sys/types.h>
#include <sys/syscall.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <inline-syscall.h>
#include <synchP.h>
#include <synch.h>
#include <schedP.h>

/* These are the result of the macro expansion of INTERNAL_SYSCALL.  */

/* XXX: These are really gross and should die.  */

static inline int __internal_kill_1 (int *errval, int sig)
{
  sysret_t ret;
  *errval = __systemcall (&ret, SYS_kill, sig);
  return ret.sys_rval1;
}

static inline pthread_t __internal_set_tid_address_1 (int *errval, pthread_t *tid)
{
  sysret_t ret;
  *errval = __systemcall (&ret, SYS_lwp_self);
  return *tid = ret.sys_rval1;
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
  sysret_t ret;
  *errval = __systemcall (&ret, SYS_write, fd, buf, count);
  return ret.sys_rval1;
}

static inline int __internal_tkill_2 (int *errval, pthread_t tid, int sig)
{
  sysret_t ret;
  *errval = __systemcall (&ret, SYS_lwp_kill, tid, sig);
  return ret.sys_rval1;
}

static inline int __internal_pause_1 (int *errval, int unused)
{
  sysret_t ret;
  *errval = __systemcall (&ret, SYS_pause);
  return ret.sys_rval1;
}

static inline int __internal_nanosleep_2 (int *errval,
    const struct timespec *req, struct timespec *rem)
{
  sysret_t ret;
  *errval = __systemcall (&ret, SYS_nanosleep, req, rem);
  return ret.sys_rval1;
}

static inline int __internal_sched_get_priority_min_1 (int *errval, int policy)
{
  int saved_errno = errno;
  int result = sched_get_priority_min (policy);
  if (result != 0)
    *errval = errno;
  __set_errno (saved_errno);
  return result;
}

static inline int __internal_sched_get_priority_max_1 (int *errval, int policy)
{
  int saved_errno = errno;
  int result = sched_get_priority_max (policy);
  if (result != 0)
    *errval = errno;
  __set_errno (saved_errno);
  return result;
}

/* These are used by the "real" associated functions.  */

static inline int __pthread_setschedparam_internal (pthread_t threadid,
    int policy, const struct sched_param *param)
{
  return __sched_setscheduler_id (P_LWPID, threadid, policy,
      param->__sched_priority);
}

static inline int __pthread_setschedprio_internal (pthread_t threadid,
    int prio)
{
  return __sched_setparam_id (P_LWPID, threadid, prio);
}

static inline int __pthread_getschedparam_internal (pthread_t threadid,
    int *policy, struct sched_param *param)
{
  return __sched_getscheduler_id (P_LWPID, threadid, policy,
      &param->__sched_priority);
}

static inline int __cond_has_waiters (pthread_cond_t *cond)
{
  return cond->cond_waiters_kernel;
}

/* These functions are used to implement the "real" associated functions.  */
extern int __cond_reltimedwait_internal (cond_t *cond, mutex_t *mutex,
    struct timespec *reltime, int cancel);
extern int __mutex_reltimedlock (mutex_t *mutex,
    const struct timespec *reltime);
extern int __mutex_timedlock (mutex_t *mutex, const struct timespec *abstime);
extern int __rw_timedrdlock (rwlock_t *rwlock, struct timespec *abstime);
extern int __rw_timedwrlock (rwlock_t *rwlock, struct timespec *abstime);
extern int __sema_timedwait (sema_t *sem, struct timespec *abstime);

#endif /* _OPENSOLARIS_PTHREADP_H */
