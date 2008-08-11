#include <sysdep.h>
PSEUDO (clock_gettime, clock_gettime, 2)
  ret
PSEUDO_END(clock_gettime)
librt_hidden_def (clock_gettime)
