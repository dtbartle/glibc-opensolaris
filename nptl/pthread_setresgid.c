#include <pthreadP.h>
#ifndef NO_SETXID_SUPPORT
#define SINGLE_THREAD
#define __setresgid pthread_setresgid_np
#include <setresgid.c>
#else /* NO_SETXID_SUPPORT */
stub_warning (pthread_setresgid_np)
#include <stub-tag.h>
#endif /* NO_SETXID_SUPPORT */
