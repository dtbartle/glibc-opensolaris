#include <unistd.h>
const char *START_OF_STRINGS =
#if _POSIX_V6_ILP32_OFF32 == 1
"POSIX_V6_ILP32_OFF32"
#endif
#if _POSIX_V6_ILP32_OFFBIG == 1
"POSIX_V6_ILP32_OFFBIG"
#endif
#if _POSIX_V6_LP64_OFF64 == 1
"POSIX_V6_LP64_OFF64"
#endif
#if _POSIX_V6_LPBIG_OFFBIG == 1
"POSIX_V6_LPBIG_OFFBIG"
#endif
"";