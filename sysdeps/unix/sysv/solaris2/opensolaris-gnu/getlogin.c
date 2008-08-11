/* solaris does not define NAME_MAX - define it here to make getlogin work */
#define NAME_MAX 255
#include <sysdeps/unix/getlogin.c>
