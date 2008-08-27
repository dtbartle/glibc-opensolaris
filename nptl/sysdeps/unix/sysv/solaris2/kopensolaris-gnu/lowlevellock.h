#ifndef _LOWLEVELLOCK_H
#define _LOWLEVELLOCK_H	1

#define lll_define(class, futex) \
    class pthread_mutex_t futex

#define LLL_LOCK_INITIALIZER PTHREAD_MUTEX_INITIALIZER

#define lll_define_initialized(class, futex) \
    class pthread_mutex_t futex = PTHREAD_MUTEX_INITIALIZER

#include <pthread.h>
#include <stddef.h>
#include <sys/syscall.h>
#include <bits/libc-lock.h>

#define lll_init(futex) \
    __libc_lock_init (futex)

#define lll_lock(futex, private) \
    __libc_lock_lock (futex)

#define lll_trylock(futex) \
    __libc_lock_trylock (futex)

#define lll_unlock(futex, private) \
    __libc_lock_unlock (futex)

/* XXX: We emulate futex_wait/wake via busy waiting.  */

#define lll_futex_wait(futex, val, private) \
    sched_yield ()

#define lll_futex_wake(futex, nr, private) \
    sched_yield ()

/* XXX: We really shouldn't assume the existence of result.  */
#define lll_wait_tid(tid) \
    do {                                                            \
      sysret_t __ret;                                               \
      result = __systemcall (&__ret, SYS_lwp_wait, (tid), NULL);    \
    } while (result == EINTR);

#define lll_tryjoin(tid) \
    ({sysret_t __ret;                                               \
    __systemcall (&__ret, SYS_lwp_kill, (tid), 0) != ESRCH;})

#endif /* _LOWLEVELLOCK_H */
