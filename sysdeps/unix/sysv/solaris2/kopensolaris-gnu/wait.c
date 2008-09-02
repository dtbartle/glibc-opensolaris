#include <sysdep-cancel.h>
#include <sysdeps/posix/wait.c>
LIBC_CANCEL_HANDLED (); /* waitpid handles cancellation */
