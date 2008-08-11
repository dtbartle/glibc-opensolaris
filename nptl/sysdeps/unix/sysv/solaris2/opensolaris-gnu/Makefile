ifeq ($(subdir),nptl)
headers += bits/synch.h thread.h sys/synch.h
sysdep_routines += register-atfork unregister-atfork libc_pthread_init \
    libc_multiple_threads fastlock
libpthread-sysdep_routines += pt-fork fastlock clock_gettime \
    sys_lwp_mutex_timedlock sys_lwp_mutex_trylock sys_lwp_mutex_unlock \
    sys_lwp_mutex_register sys_lwp_cond_wait sys_lwp_cond_signal \
    sys_lwp_cond_broadcast sys_lwp_sema_post sys_lwp_sema_trywait \
    sys_lwp_sema_timedwait sys_lwp_create sys_lwp_wait sys_lwp_exit \
    sys_lwp_kill sys_lwp_suspend sys_lwp_continue
libpthread-routines += sys_lwp_self \
    thr_create thr_join thr_exit thr_self \
    mutex_init cond_init cond_reltimedwait rwlock_init
endif

ifeq ($(subdir),posix)
CFLAGS-fork.c = -D_IO_MTSAFE_IO
sysdep_routines += sys_lwp_self sys_forkx
endif

# Needed in both the signal and nptl subdir.
CFLAGS-sigaction.c = -DWRAPPER_INCLUDE='<nptl/sigaction.c>'
