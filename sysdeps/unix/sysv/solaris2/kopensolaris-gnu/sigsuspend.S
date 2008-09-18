#include <sysdep-cancel.h>
PSEUDO (__sigsuspend, sigsuspend, 1)
	ret
PSEUDO_END(__sigsuspend)
libc_hidden_def (__sigsuspend)
weak_alias (__sigsuspend, sigsuspend)
libc_hidden_weak (sigsuspend)
