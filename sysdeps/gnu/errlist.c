/* This file is generated from errno.texi by errlist.awk.  */

#include <errno.h>

const char *_sys_errlist[] =
  {
    [0] = N_("Success"),
#ifdef EPERM
    [EPERM] = _N("Operation not permitted"),
#endif
#ifdef ENOENT
    [ENOENT] = _N("No such file or directory"),
#endif
#ifdef ESRCH
    [ESRCH] = _N("No such process"),
#endif
#ifdef EINTR
    [EINTR] = _N("Interrupted system call"),
#endif
#ifdef EIO
    [EIO] = _N("Input/output error"),
#endif
#ifdef ENXIO
    [ENXIO] = _N("Device not configured"),
#endif
#ifdef E2BIG
    [E2BIG] = _N("Argument list too long"),
#endif
#ifdef ENOEXEC
    [ENOEXEC] = _N("Exec format error"),
#endif
#ifdef EBADF
    [EBADF] = _N("Bad file descriptor"),
#endif
#ifdef ECHILD
    [ECHILD] = _N("No child processes"),
#endif
#ifdef EDEADLK
    [EDEADLK] = _N("Resource deadlock avoided"),
#endif
#ifdef ENOMEM
    [ENOMEM] = _N("Cannot allocate memory"),
#endif
#ifdef EACCES
    [EACCES] = _N("Permission denied"),
#endif
#ifdef EFAULT
    [EFAULT] = _N("Bad address"),
#endif
#ifdef ENOTBLK
    [ENOTBLK] = _N("Block device required"),
#endif
#ifdef EBUSY
    [EBUSY] = _N("Device or resource busy"),
#endif
#ifdef EEXIST
    [EEXIST] = _N("File exists"),
#endif
#ifdef EXDEV
    [EXDEV] = _N("Invalid cross-device link"),
#endif
#ifdef ENODEV
    [ENODEV] = _N("Operation not supported by device"),
#endif
#ifdef ENOTDIR
    [ENOTDIR] = _N("Not a directory"),
#endif
#ifdef EISDIR
    [EISDIR] = _N("Is a directory"),
#endif
#ifdef EINVAL
    [EINVAL] = _N("Invalid argument"),
#endif
#ifdef EMFILE
    [EMFILE] = _N("Too many open files"),
#endif
#ifdef ENFILE
    [ENFILE] = _N("Too many open files in system"),
#endif
#ifdef ENOTTY
    [ENOTTY] = _N("Inappropriate ioctl for device"),
#endif
#ifdef ETXTBSY
    [ETXTBSY] = _N("Text file busy"),
#endif
#ifdef EFBIG
    [EFBIG] = _N("File too large"),
#endif
#ifdef ENOSPC
    [ENOSPC] = _N("No space left on device"),
#endif
#ifdef ESPIPE
    [ESPIPE] = _N("Illegal seek"),
#endif
#ifdef EROFS
    [EROFS] = _N("Read-only file system"),
#endif
#ifdef EMLINK
    [EMLINK] = _N("Too many links"),
#endif
#ifdef EPIPE
    [EPIPE] = _N("Broken pipe"),
#endif
#ifdef EDOM
    [EDOM] = _N("Numerical argument out of domain"),
#endif
#ifdef ERANGE
    [ERANGE] = _N("Numerical result out of range"),
#endif
#ifdef EAGAIN
    [EAGAIN] = _N("Resource temporarily unavailable"),
#endif
#if defined (EWOULDBLOCK) && EWOULDBLOCK != EAGAIN
    [EWOULDBLOCK] = _N("Operation would block"),
#endif
#ifdef EINPROGRESS
    [EINPROGRESS] = _N("Operation now in progress"),
#endif
#ifdef EALREADY
    [EALREADY] = _N("Operation already in progress"),
#endif
#ifdef ENOTSOCK
    [ENOTSOCK] = _N("Socket operation on non-socket"),
#endif
#ifdef EMSGSIZE
    [EMSGSIZE] = _N("Message too long"),
#endif
#ifdef EPROTOTYPE
    [EPROTOTYPE] = _N("Protocol wrong type for socket"),
#endif
#ifdef ENOPROTOOPT
    [ENOPROTOOPT] = _N("Protocol not available"),
#endif
#ifdef EPROTONOSUPPORT
    [EPROTONOSUPPORT] = _N("Protocol not supported"),
#endif
#ifdef ESOCKTNOSUPPORT
    [ESOCKTNOSUPPORT] = _N("Socket type not supported"),
#endif
#ifdef EOPNOTSUPP
    [EOPNOTSUPP] = _N("Operation not supported"),
#endif
#ifdef EPFNOSUPPORT
    [EPFNOSUPPORT] = _N("Protocol family not supported"),
#endif
#ifdef EAFNOSUPPORT
    [EAFNOSUPPORT] = _N("Address family not supported by protocol"),
#endif
#ifdef EADDRINUSE
    [EADDRINUSE] = _N("Address already in use"),
#endif
#ifdef EADDRNOTAVAIL
    [EADDRNOTAVAIL] = _N("Cannot assign requested address"),
#endif
#ifdef ENETDOWN
    [ENETDOWN] = _N("Network is down"),
#endif
#ifdef ENETUNREACH
    [ENETUNREACH] = _N("Network is unreachable"),
#endif
#ifdef ENETRESET
    [ENETRESET] = _N("Network dropped connection on reset"),
#endif
#ifdef ECONNABORTED
    [ECONNABORTED] = _N("Software caused connection abort"),
#endif
#ifdef ECONNRESET
    [ECONNRESET] = _N("Connection reset by peer"),
#endif
#ifdef ENOBUFS
    [ENOBUFS] = _N("No buffer space available"),
#endif
#ifdef EISCONN
    [EISCONN] = _N("Transport endpoint is already connected"),
#endif
#ifdef ENOTCONN
    [ENOTCONN] = _N("Transport endpoint is not connected"),
#endif
#ifdef EDESTADDRREQ
    [EDESTADDRREQ] = _N("Destination address required"),
#endif
#ifdef ESHUTDOWN
    [ESHUTDOWN] = _N("Cannot send after transport endpoint shutdown"),
#endif
#ifdef ETOOMANYREFS
    [ETOOMANYREFS] = _N("Too many references: cannot splice"),
#endif
#ifdef ETIMEDOUT
    [ETIMEDOUT] = _N("Connection timed out"),
#endif
#ifdef ECONNREFUSED
    [ECONNREFUSED] = _N("Connection refused"),
#endif
#ifdef ELOOP
    [ELOOP] = _N("Too many levels of symbolic links"),
#endif
#ifdef ENAMETOOLONG
    [ENAMETOOLONG] = _N("File name too long"),
#endif
#ifdef EHOSTDOWN
    [EHOSTDOWN] = _N("Host is down"),
#endif
#ifdef EHOSTUNREACH
    [EHOSTUNREACH] = _N("No route to host"),
#endif
#ifdef ENOTEMPTY
    [ENOTEMPTY] = _N("Directory not empty"),
#endif
#ifdef EPROCLIM
    [EPROCLIM] = _N("Too many processes"),
#endif
#ifdef EUSERS
    [EUSERS] = _N("Too many users"),
#endif
#ifdef EDQUOT
    [EDQUOT] = _N("Disc quota exceeded"),
#endif
#ifdef ESTALE
    [ESTALE] = _N("Stale NFS file handle"),
#endif
#ifdef EREMOTE
    [EREMOTE] = _N("Object is remote"),
#endif
#ifdef EBADRPC
    [EBADRPC] = _N("RPC struct is bad"),
#endif
#ifdef ERPCMISMATCH
    [ERPCMISMATCH] = _N("RPC version wrong"),
#endif
#ifdef EPROGUNAVAIL
    [EPROGUNAVAIL] = _N("RPC program not available"),
#endif
#ifdef EPROGMISMATCH
    [EPROGMISMATCH] = _N("RPC program version wrong"),
#endif
#ifdef EPROCUNAVAIL
    [EPROCUNAVAIL] = _N("RPC bad procedure for program"),
#endif
#ifdef ENOLCK
    [ENOLCK] = _N("No locks available"),
#endif
#ifdef EFTYPE
    [EFTYPE] = _N("Inappropriate file type or format"),
#endif
#ifdef EAUTH
    [EAUTH] = _N("Authentication error"),
#endif
#ifdef ENEEDAUTH
    [ENEEDAUTH] = _N("Need authenticator"),
#endif
#ifdef ENOSYS
    [ENOSYS] = _N("Function not implemented"),
#endif
#ifdef EILSEQ
    [EILSEQ] = _N("Invalid or incomplete multibyte or wide character"),
#endif
#ifdef EBACKGROUND
    [EBACKGROUND] = _N("Inappropriate operation for background process"),
#endif
#ifdef EDIED
    [EDIED] = _N("Translator died"),
#endif
#ifdef ED
    [ED] = _N("?"),
#endif
#ifdef EGREGIOUS
    [EGREGIOUS] = _N("You really blew it this time"),
#endif
#ifdef EIEIO
    [EIEIO] = _N("Computer bought the farm"),
#endif
#ifdef EGRATUITOUS
    [EGRATUITOUS] = _N("Gratuitous error"),
#endif
#ifdef ERESTART
    [ERESTART] = _N("Interrupted system call should be restarted"),
#endif
#ifdef ENOMSG
    [ENOMSG] = _N("No message of desired type"),
#endif
#ifdef EIDRM
    [EIDRM] = _N("Identifier removed"),
#endif
#ifdef ECHRNG
    [ECHRNG] = _N("Channel number out of range"),
#endif
#ifdef EL2NSYNC
    [EL2NSYNC] = _N("Level 2 not synchronized"),
#endif
#ifdef EL3HLT
    [EL3HLT] = _N("Level 3 halted"),
#endif
#ifdef EL3RST
    [EL3RST] = _N("Level 3 reset"),
#endif
#ifdef ELNRNG
    [ELNRNG] = _N("Link number out of range"),
#endif
#ifdef EUNATCH
    [EUNATCH] = _N("Protocol driver not attached"),
#endif
#ifdef ENOCSI
    [ENOCSI] = _N("No CSI structure available"),
#endif
#ifdef EL2HLT
    [EL2HLT] = _N("Level 2 halted"),
#endif
#ifdef EBADE
    [EBADE] = _N("Invalid exchange"),
#endif
#ifdef EBADR
    [EBADR] = _N("Invalid request descriptor"),
#endif
#ifdef EXFULL
    [EXFULL] = _N("Exchange full"),
#endif
#ifdef ENOANO
    [ENOANO] = _N("No anode"),
#endif
#ifdef EBADRQC
    [EBADRQC] = _N("Invalid request code"),
#endif
#ifdef EBADSLT
    [EBADSLT] = _N("Invalid slot"),
#endif
#ifdef EDEADLOCK
    [EDEADLOCK] = _N("File locking deadlock error"),
#endif
#ifdef EBFONT
    [EBFONT] = _N("Bad font file format"),
#endif
#ifdef ENOSTR
    [ENOSTR] = _N("Device not a stream"),
#endif
#ifdef ENODATA
    [ENODATA] = _N("No data available"),
#endif
#ifdef ETIME
    [ETIME] = _N("Timer expired"),
#endif
#ifdef ENOSR
    [ENOSR] = _N("Out of streams resources"),
#endif
#ifdef ENONET
    [ENONET] = _N("Machine is not on the network"),
#endif
#ifdef ENOPKG
    [ENOPKG] = _N("Package not installed"),
#endif
#ifdef ENOLINK
    [ENOLINK] = _N("Link has been severed"),
#endif
#ifdef EADV
    [EADV] = _N("Advertise error"),
#endif
#ifdef ESRMNT
    [ESRMNT] = _N("Srmount error"),
#endif
#ifdef ECOMM
    [ECOMM] = _N("Communication error on send"),
#endif
#ifdef EPROTO
    [EPROTO] = _N("Protocol error"),
#endif
#ifdef EMULTIHOP
    [EMULTIHOP] = _N("Multihop attempted"),
#endif
#ifdef EDOTDOT
    [EDOTDOT] = _N("RFS specific error"),
#endif
#ifdef EBADMSG
    [EBADMSG] = _N("Not a data message"),
#endif
#ifdef EOVERFLOW
    [EOVERFLOW] = _N("Value too large for defined data type"),
#endif
#ifdef ENOTUNIQ
    [ENOTUNIQ] = _N("Name not unique on network"),
#endif
#ifdef EBADFD
    [EBADFD] = _N("File descriptor in bad state"),
#endif
#ifdef EREMCHG
    [EREMCHG] = _N("Remote address changed"),
#endif
#ifdef ELIBACC
    [ELIBACC] = _N("Can not access a needed shared library"),
#endif
#ifdef ELIBBAD
    [ELIBBAD] = _N("Accessing a corrupted shared library"),
#endif
#ifdef ELIBSCN
    [ELIBSCN] = _N(".lib section in a.out corrupted"),
#endif
#ifdef ELIBMAX
    [ELIBMAX] = _N("Attempting to link in too many shared libraries"),
#endif
#ifdef ELIBEXEC
    [ELIBEXEC] = _N("Cannot exec a shared library directly"),
#endif
#ifdef ESTRPIPE
    [ESTRPIPE] = _N("Streams pipe error"),
#endif
#ifdef EUCLEAN
    [EUCLEAN] = _N("Structure needs cleaning"),
#endif
#ifdef ENOTNAM
    [ENOTNAM] = _N("Not a XENIX named type file"),
#endif
#ifdef ENAVAIL
    [ENAVAIL] = _N("No XENIX semaphores available"),
#endif
#ifdef EISNAM
    [EISNAM] = _N("Is a named type file"),
#endif
#ifdef EREMOTEIO
    [EREMOTEIO] = _N("Remote I/O error"),
#endif
  };

const int _sys_nerr = sizeof _sys_errlist / sizeof _sys_errlist[0];
weak_alias (_sys_errlist, sys_errlist)
weak_alias (_sys_nerr, sys_nerr)
