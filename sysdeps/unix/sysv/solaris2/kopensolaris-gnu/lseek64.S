#define SYSCALL_64BIT_RETURN
#include <sysdep-cancel.h>
PSEUDO (__libc_lseek64, llseek, 3)
	ret
PSEUDO_END(__libc_lseek64)
libc_hidden_def (__libc_lseek64)
weak_alias (__libc_lseek64, __llseek)
libc_hidden_weak (__llseek)
weak_alias (__libc_lseek64, llseek)
libc_hidden_weak (llseek)
weak_alias (__libc_lseek64, __lseek64)
libc_hidden_weak (__lseek64)
weak_alias (__libc_lseek64, lseek64)
libc_hidden_weak (lseek64)
