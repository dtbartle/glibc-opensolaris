ifeq ($(subdir),nptl)
headers += synch.h bits/synch.h sys/synch.h thread.h sys/lwp.h
sysdep_routines += register-atfork unregister-atfork libc_pthread_init \
    libc_multiple_threads fastlock
libpthread-sysdep_routines += pt-fork fastlock clock_gettime \
    sys_lwp_mutex_timedlock sys_lwp_mutex_trylock sys_lwp_mutex_unlock \
    sys_lwp_mutex_register sys_lwp_cond_wait sys_lwp_cond_signal \
    sys_lwp_cond_broadcast sys_lwp_sema_post sys_lwp_sema_trywait \
    sys_lwp_sema_timedwait sys_lwp_create sys_lwp_wait sys_lwp_exit \
    sys_lwp_kill sys_lwp_suspend sys_lwp_continue sys_lwp_sigmask

# solaris threads/synch
libpthread-routines += mutex_init mutex_lock mutex_trylock mutex_unlock \
    mutex_destroy mutex_timedlock mutex_reltimedlock mutex_consistent \
    _mutex_held cond_init cond_wait cond_timedwait cond_reltimedwait \
    cond_signal cond_broadcast cond_destroy rwlock_init rwlock_destroy \
    rw_rdlock rw_wrlock rw_unlock rw_tryrdlock rw_trywrlock rw_timedrdlock \
    rw_timedwrlock sema_init sema_destroy sema_wait sema_trywait sema_post \
    sema_timedwait thr_create thr_join thr_exit thr_self thr_yield \
    thr_sigsetmask thr_getspecific thr_setspecific thr_keycreate \
    thr_keycreate_once thr_min_stack thr_getconcurrency thr_setconcurrency \
    thr_continue thr_suspend thr_getprio thr_setprio _lwp_sema_init _lwp_info \
    __nthreads pthread_cond_reltimedwait_np pthread_mutex_reltimedlock_np
endif

ifeq ($(subdir),posix)
CFLAGS-fork.c = -D_IO_MTSAFE_IO
sysdep_routines += sys_forkx
endif

ifeq ($(subdir),misc)
sysdep_routines += thr_main thr_stksegment
endif

# Needed in both the signal and nptl subdir.
# We also need to enable exceptions.
CFLAGS-sigaction.c = -DWRAPPER_INCLUDE='<nptl/sigaction.c>' -fexceptions

# The following are cancellation points.  Some of the functions can
# block and therefore temporarily enable asynchronous cancellation.
# Those must be compiled asynchronous unwind tables.
CFLAGS-cond_reltimedwait.c = -fexceptions -fasynchronous-unwind-tables
CFLAGS-cond_timedwait.c = -fexceptions -fasynchronous-unwind-tables
CFLAGS-cond_wait.c = -fexceptions -fasynchronous-unwind-tables
