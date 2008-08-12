#ifndef _LOWLEVELLOCK_H
#define _LOWLEVELLOCK_H	1

#include <stddef.h>
#include <inline-syscall.h>

/* XXX: lll_define is used by desr.h so we can't use bits/libc-lock.h */
#define lll_define(class, futex) \
    class pthread_mutex_t futex;

#include <bits/libc-lock.h>

#define lll_define_initialized(class, futex) \
    __libc_lock_define_initialized (class, futex)

#define lll_init(futex) \
    __libc_lock_init (futex)

#define lll_lock(futex, private) \
    __libc_lock_lock (futex)

#define lll_unlock(futex, private) \
    __libc_lock_unlock (futex)

DECLARE_INLINE_SYSCALL (int, lwp_wait, pthread_t tid, pthread_t *departed);

/* XXX: we really shouldn't assume the existence of result */
#define lll_wait_tid(tid) \
    result = INLINE_SYSCALL (lwp_wait, 2, (tid), NULL)

DECLARE_INLINE_SYSCALL (int, lwp_kill, pthread_t tid, int sig);

#define lll_tryjoin(tid) \
    (INLINE_SYSCALL (lwp_kill, 2, (tid), 0) != ESRCH)

#endif /* _LOWLEVELLOCK_H */
