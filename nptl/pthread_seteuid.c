#include <pthreadP.h>
#ifndef NO_SETXID_SUPPORT
#define SINGLE_THREAD
#define seteuid pthread_seteuid_np
#include <seteuid.c>
#else /* NO_SETXID_SUPPORT */
stub_warning (pthread_seteuid_np)
#include <stub-tag.h>
#endif /* NO_SETXID_SUPPORT */
