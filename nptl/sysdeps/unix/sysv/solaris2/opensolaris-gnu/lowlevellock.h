#ifndef _LOWLEVELLOCK_H
#define _LOWLEVELLOCK_H	1

#include <stddef.h>
#include <inline-syscall.h>

#define lll_define(class, futex) \
    class pthread_mutex_t futex

#define lll_define_initialized(class, futex) \
    class pthread_mutex_t futex = PTHREAD_MUTEX_INITIALIZER

#define lll_init(futex) \
    pthread_mutex_init (&(futex), NULL)

#define lll_lock(futex, private) \
    pthread_mutex_lock (&(futex))

#define lll_unlock(futex, private) \
    pthread_mutex_unlock (&(futex))

DECLARE_INLINE_SYSCALL (int, lwp_wait, pthread_t tid, pthread_t *departed);

/* XXX: we really shouldn't assume the existence of result */
#define lll_wait_tid(tid) \
    result = INLINE_SYSCALL (lwp_wait, 2, (tid), NULL)

DECLARE_INLINE_SYSCALL (int, lwp_kill, pthread_t tid, int sig);

#define lll_tryjoin(tid) \
    (INLINE_SYSCALL (lwp_kill, 2, (tid), 0) != ESRCH)

#endif /* _LOWLEVELLOCK_H */
