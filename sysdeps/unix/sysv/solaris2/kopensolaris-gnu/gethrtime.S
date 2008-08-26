#include <sysdep.h>
#include <sys/trap.h>

PSEUDO_FASTTRAP (gethrtime, GETHRTIME, 0)
  ret
PSEUDO_END (gethrtime)
