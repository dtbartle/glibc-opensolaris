#include <errno.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <sysdep.h>


int
signalfd (int fd, const sigset_t *mask)
{
#ifdef __NR_signalfd
  return INLINE_SYSCALL (signalfd, 3, fd, mask, _NSIG / 8);
#else
  __set_errno (ENOSYS);
  return -1;
#endif
}
