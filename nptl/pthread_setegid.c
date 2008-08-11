#include <pthreadP.h>
#ifndef NO_SETXID_SUPPORT
#define SINGLE_THREAD
#define setegid pthread_setegid_np
#include <setegid.c>
#else /* NO_SETXID_SUPPORT */
stub_warning (pthread_setgid_np)
#include <stub-tag.h>
#endif /* NO_SETXID_SUPPORT */
