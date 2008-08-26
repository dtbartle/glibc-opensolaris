#include <sysdep.h>
#include <sys/trap.h>

PSEUDO_FASTTRAP (gethrvtime, GETHRVTIME, 0)
  ret
PSEUDO_END (gethrvtime)
