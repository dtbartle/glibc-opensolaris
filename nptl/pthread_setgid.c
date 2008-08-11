#include <pthreadP.h>
#ifndef NO_SETXID_SUPPORT
#define SINGLE_THREAD
#define __setgid pthread_setgid_np
#include <setgid.c>
#else /* NO_SETXID_SUPPORT */
stub_warning (pthread_setgid_np)
#include <stub-tag.h>
#endif /* NO_SETXID_SUPPORT */
