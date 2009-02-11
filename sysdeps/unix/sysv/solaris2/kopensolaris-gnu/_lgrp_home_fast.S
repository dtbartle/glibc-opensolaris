#include <sysdep.h>
#include <sys/trap.h>

PSEUDO_FASTTRAP (_lgrp_home_fast, GETLGRP, 0)
  ret
PSEUDO_END (_lgrp_home_fast)
