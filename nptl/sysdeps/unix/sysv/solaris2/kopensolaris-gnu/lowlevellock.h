#ifndef _LOWLEVELLOCK_H
#define _LOWLEVELLOCK_H	1

#include <pthread.h>

#define lll_define(class, futex) \
    class pthread_mutex_t futex

#define LLL_LOCK_INITIALIZER PTHREAD_MUTEX_INITIALIZER

#define lll_define_initialized(class, futex) \
    class pthread_mutex_t futex = PTHREAD_MUTEX_INITIALIZER

#include <stddef.h>
#include <inline-syscall.h>
#include <bits/libc-lock.h>

#define lll_init(futex) \
    __libc_lock_init (futex)

#define lll_lock(futex, private) \
    __libc_lock_lock (futex)

#define lll_trylock(futex) \
    __libc_lock_trylock (futex)

#define lll_unlock(futex, private) \
    __libc_lock_unlock (futex)

DECLARE_INLINE_SYSCALL (int, lwp_wait, pthread_t tid, pthread_t *departed);

/* XXX: we really shouldn't assume the existence of result */
#define lll_wait_tid(tid) \
    do {                                                        \
      result = INLINE_SYSCALL (lwp_wait, 2, (tid), NULL);       \
    } while (result == EINTR);

DECLARE_INLINE_SYSCALL (int, lwp_kill, pthread_t tid, int sig);

#define lll_tryjoin(tid) \
    (INLINE_SYSCALL (lwp_kill, 2, (tid), 0) != ESRCH)

#endif /* _LOWLEVELLOCK_H */
