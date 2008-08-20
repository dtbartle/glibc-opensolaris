#ifndef _LOWLEVELLOCK_H
#define _LOWLEVELLOCK_H	1

#include <stddef.h>
#include <inline-syscall.h>
#include <pthread.h>

#define lll_define(class, futex) \
    class pthread_mutex_t futex

#define LLL_LOCK_INITIALIZER PTHREAD_MUTEX_INITIALIZER

#define lll_define_initialized(class, futex) \
    class pthread_mutex_t futex = PTHREAD_MUTEX_INITIALIZER

#define lll_init(futex) \
    __pthread_mutex_init (&(futex), NULL)

#define lll_lock(futex, private) \
    __pthread_mutex_lock (&(futex))

#define lll_trylock(futex) \
    __pthread_mutex_trylock (&(futex))

#define lll_unlock(futex, private) \
    __pthread_mutex_unlock (&(futex))

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
