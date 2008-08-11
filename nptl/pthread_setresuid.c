#include <pthreadP.h>
#ifndef NO_SETXID_SUPPORT
#define SINGLE_THREAD
#define __setresuid pthread_setresuid_np
#include <setresuid.c>
#else /* NO_SETXID_SUPPORT */
stub_warning (pthread_setresuid_np)
#include <stub-tag.h>
#endif /* NO_SETXID_SUPPORT */
