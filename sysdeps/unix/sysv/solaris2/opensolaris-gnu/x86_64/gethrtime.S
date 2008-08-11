#include <sysdep.h>
#include <sys/trap.h>

	  .text;
ENTRY (gethrtime)
    movl $T_GETHRTIME, %eax
    int $T_FASTTRAP
L(pseudo_end):
	ret			/* Return to caller.  */
PSEUDO_END (gethrtime)
