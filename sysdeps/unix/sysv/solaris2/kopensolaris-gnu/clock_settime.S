#include <sysdep.h>
PSEUDO (clock_settime, clock_settime, 2)
  ret
PSEUDO_END(clock_settime)
librt_hidden_def (clock_settime)
