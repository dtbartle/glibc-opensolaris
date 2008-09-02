#include <sysdep.h>
PSEUDO (__profil, profil, 2)
	ret
PSEUDO_END(__profil)
libc_hidden_def (__profil)
weak_alias (__profil, profil)
libc_hidden_weak (profil)
