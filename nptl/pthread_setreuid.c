#include <pthreadP.h>
#ifndef NO_SETXID_SUPPORT
#define SINGLE_THREAD
#define __setreuid pthread_setreuid_np
#include <setreuid.c>
#else /* NO_SETXID_SUPPORT */
stub_warning (pthread_setreuid_np)
#include <stub-tag.h>
#endif /* NO_SETXID_SUPPORT */
