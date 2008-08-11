#include <pthreadP.h>
#ifndef NO_SETXID_SUPPORT
#define SINGLE_THREAD
#define __setuid pthread_setuid_np
#include <setuid.c>
#else /* NO_SETXID_SUPPORT */
stub_warning (pthread_setuid_np)
#include <stub-tag.h>
#endif /* NO_SETXID_SUPPORT */
