/* System-specific socket constants and types.  OpenSolaris version.
   Copyright (C) 1991, 1992, 1994-2001, 2004, 2006, 2007, 2008
   Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef __BITS_SOCKET_H
#define __BITS_SOCKET_H

#ifndef _SYS_SOCKET_H
# error "Never include <bits/socket.h> directly; use <sys/socket.h> instead."
#endif

#define	__need_size_t
#define __need_NULL
#include <stddef.h>

#include <limits.h>
#include <sys/types.h>

#define __SOCKADDR_IN6_EXTRA_FIELDS \
	__uint32_t __sin6_src_id;

/* Type for length arguments in socket calls.  */
#ifndef __socklen_t_defined
typedef __socklen_t socklen_t;
# define __socklen_t_defined
#endif

/* Types of sockets.  */
enum __socket_type
{
  SOCK_STREAM = 2,		/* Sequenced, reliable, connection-based
				   byte streams.  */
#define SOCK_STREAM SOCK_STREAM
  SOCK_DGRAM = 1,		/* Connectionless, unreliable datagrams
				   of fixed maximum length.  */
#define SOCK_DGRAM SOCK_DGRAM
  SOCK_RAW = 4,			/* Raw protocol interface.  */
#define SOCK_RAW SOCK_RAW
  SOCK_RDM = 5,			/* Reliably-delivered messages.  */
#define SOCK_RDM SOCK_RDM
  SOCK_SEQPACKET = 6		/* Sequenced, reliable, connection-based,
				   datagrams of fixed maximum length.  */
#define SOCK_SEQPACKET SOCK_SEQPACKET
};

/* Protocol families.  */
#define	PF_UNSPEC	0	/* Unspecified.  */
#define	PF_LOCAL	1	/* Local to host (pipes and file-domain).  */
#define	PF_UNIX		PF_LOCAL /* POSIX name for PF_LOCAL.  */
#define	PF_FILE		PF_LOCAL /* Another non-standard name for PF_LOCAL.  */
#define	PF_INET		2	/* IP protocol family.  */
#define	PF_IMPLINK	3	/* Arpanet imp addresses.  */
#define	PF_PUP		4	/* PUP protocols: e.g. BSP.  */
#define	PF_CHAOS	5	/* MIT CHAOS protocols.  */
#define	PF_NS		6	/* XEROX NS protocols.  */
#define	PF_NBS		7	/* NBS protocols.  */
#define	PF_ECMA		8	/* European Computer Manufacturers.  */
#define	PF_DATAKIT	9	/* Datakit protocols.  */
#define	PF_CCITT	10	/* CCITT protocols, X.25 etc.  */
#define	PF_SNA		11	/* Linux SNA Project */
#define	PF_DECnet	12	/* Reserved for DECnet project.  */
#define PF_DLI		13	/* Direct data link interface.  */
#define	PF_LAT		14	/* LAT.  */
#define	PF_HYLINK	15	/* NSC Hyperchannel.  */
#define	PF_APPLETALK	16	/* Appletalk DDP.  */
#define	PF_NIT		17	/*  Network Interface Tap.  */
#define	PF_802		18	/* IEEE 802.2, also ISO 8802.  */
#define	PF_OSI		19	/* Umbrella for all families used.  */
#define	PF_X25		20	/* Reserved for X.25 project.  */
#define	PF_OSINET	21	/* AFI = 47, IDI = 4.  */
#define	PF_GOSIP	22	/* U.S. Government OSI.  */
#define	PF_IPX		23	/* Novell Internet Protocol.  */
#define	PF_ROUTE	24	/* Internal Routing Protocol.  */
#define	PF_LINK		25	/* Link-layer interface.  */
#define	PF_INET6	26	/* IP version 6.  */
#define	PF_KEY		27	/* PF_KEY key management API.  */
#define	PF_NCA		28	/* NCA socket.  */
#define	PF_POLICY	29	/* Security Policy DB socket.  */
#define	PF_INET_OFFLOAD	30	/* Sun private; do not use.  */
#define	PF_MAX		30	/* For now..  */

/* Address families.  */
#define	AF_UNSPEC	PF_UNSPEC
#define	AF_UNIX		PF_UNIX
#define	AF_LOCAL	PF_LOCAL
#define	AF_INET		PF_INET
#define	AF_IMPLINK	PF_IMPLINK
#define	AF_PUP		PF_PUP
#define	AF_CHAOS	PF_CHAOS
#define	AF_NS		PF_NBS
#define	AF_NBS		PF_NBS
#define	AF_ECMA		PF_ECMA
#define	AF_DATAKIT	PF_DATAKIT
#define	AF_CCITT	PF_CCITT
#define	AF_SNA		PF_SNA
#define	AF_DECnet	PF_DECnet
#define	AF_DLI		PF_DLI
#define	AF_LAT		PF_LAT
#define	AF_HYLINK	PF_HYLINK
#define	AF_APPLETALK	PF_APPLETALK
#define	AF_NIT		PF_NIT
#define	AF_802		PF_802
#define	AF_X25		PF_X25
#define	AF_OSINET	PF_OSINET
#define	AF_GOSIP	PF_GOSIP
#define	AF_IPX		PF_IPX
#define	AF_ROUTE	PF_ROUTE
#define	AF_LINK		PF_LINK
#define	AF_INET6	PF_INET6
#define	AF_KEY		PF_X25
#define	AF_NCA		PF_X25
#define	AF_POLICY	PF_POLICY
#define	AF_INET_OFFLOAD	PF_INET_OFFLOAD
#define	AF_MAX		PF_MAX

/* Socket level values.  */
#define SOL_SOCKET		0xFFFF
#define SOL_IP			0 /* IPPROTO_IP */
#define SOL_ICMP        1 /* IPPROTO_ICMP */
#define SOL_TCP			6 /* IPPROTO_TCP */
#define SOL_UDP			17 /* IPPROTO_UDP */
#define SOL_IPV6		41 /* IPPROTO_IPV6 */
#define SOL_ICMPV6		58 /* IPPROTO_ICMPV6 */
#define SOL_SCTP		132 /* IPPROTO_SCTP */
#define SOL_RAW			255 /* IPPROTO_RAW */

/* Maximum queue length specifiable by listen.  */
#define SOMAXCONN	128

/* Get the definition of the macro to define the common sockaddr members.  */
#include <bits/sockaddr.h>

/* Structure describing a generic socket address.  */
struct sockaddr
  {
    __SOCKADDR_COMMON (sa_);	/* Common data: address family and length.  */
    char sa_data[14];		/* Address data.  */
  };


/* Structure large enough to hold any socket address (with the historical
   exception of AF_UNIX).  We reserve 128 bytes.  */
#define _SS_MAXSIZE		256
#define _SS_ALIGNSIZE	(sizeof (sockaddr_maxalign_t))
typedef double sockaddr_maxalign_t;
#define _SS_PAD1SIZE	(_SS_ALIGNSIZE - sizeof (sa_family_t))
#define _SS_PAD2SIZE	(_SS_MAXSIZE - (sizeof (sa_family_t) + \
	_SS_PAD1SIZE + _SS_ALIGNSIZE))

struct sockaddr_storage
  {
    __SOCKADDR_COMMON (ss_);	/* Address family, etc.  */
    char _ss_pad1[_SS_PAD1SIZE];
    sockaddr_maxalign_t __ss_align;	/* Force desired alignment.  */
    char _ss_pad2[_SS_PAD2SIZE];
  };


/* Bits in the FLAGS argument to `send', `recv', et al.  */
enum
  {
    MSG_OOB		= 0x01,	/* Process out-of-band data.  */
#define MSG_OOB		MSG_OOB
    MSG_PEEK		= 0x02,	/* Peek at incoming messages.  */
#define MSG_PEEK	MSG_PEEK
    MSG_DONTROUTE	= 0x04,	/* Don't use local routing.  */
#define MSG_DONTROUTE	MSG_DONTROUTE
#ifdef __USE_GNU
    /* DECnet uses a different name.  */
    MSG_TRYHARD		= MSG_DONTROUTE,
# define MSG_TRYHARD	MSG_DONTROUTE
#endif
    MSG_EOR		= 0x08, /* End of record.  */
#define	MSG_EOR		MSG_EOR
    MSG_CTRUNC		= 0x10,	/* Control data lost before delivery.  */
#define MSG_CTRUNC	MSG_CTRUNC
    MSG_TRUNC		= 0x20,
#define	MSG_TRUNC	MSG_TRUNC
    MSG_WAITALL		= 0x40, /* Wait for a full request.  */
#define	MSG_WAITALL	MSG_WAITALL
    MSG_DONTWAIT	= 0x80, /* Nonblocking IO.  */
#define	MSG_DONTWAIT	MSG_DONTWAIT
    MSG_NOTIFICATION	= 0x100, /* Notification, not data.  */
#define	MSG_NOTIFICATION	MSG_NOTIFICICATION
    MSG_XPG4_2		= 0x8000, /* Private: XPG4.2 flag.  */
#define	MSG_XPG4_2	MSG_XPG4_2

/* The following are not supported by the OpenSolaris kernel.  */
    MSG_NOSIGNAL	= 0x4000, /* Do not generate SIGPIPE.  */
#define	MSG_NOSIGNAL	MSG_NOSIGNAL
  };


/* Structure describing messages sent by
   `sendmsg' and received by `recvmsg'.  */
struct msghdr
  {
    void *msg_name;		/* Address to send to/receive from.  */
    socklen_t msg_namelen;	/* Length of address data.  */

    struct iovec *msg_iov;	/* Vector of data to send/receive into.  */
    size_t msg_iovlen;		/* Number of elements in the vector.  */

    void *msg_control;		/* Ancillary data (eg BSD filedesc passing). */
    socklen_t msg_controllen;	/* Ancillary data buffer length.  */

    int msg_flags;		/* Flags on received message.  */
  };

/* Structure used for storage of ancillary data object information.  */
struct cmsghdr
  {
    socklen_t cmsg_len;		/* Length of data in cmsg_data plus length
				   of cmsghdr structure.  */
    int cmsg_level;		/* Originating protocol.  */
    int cmsg_type;		/* Protocol specific type.  */
  };

/* Ancillary data object manipulation macros.  */
#if defined(__sparc__)
# define _CMSG_HDR_ALIGNMENT 8
#else
# define _CMSG_HDR_ALIGNMENT 4
#endif
#define CMSG_ALIGN(len)	(((uintptr_t)(len) + _CMSG_HDR_ALIGNMENT - 1) \
			& ~(_CMSG_HDR_ALIGNMENT - 1))
#define _CMSG_HDR_ALIGN(x)	CMSG_ALIGN(x)
#define CMSG_DATA(cmsg) ((unsigned char *) CMSG_ALIGN((struct cmsghdr *) (cmsg) + 1))
#define CMSG_NXTHDR(mhdr, cmsg) __cmsg_nxthdr (mhdr, cmsg)
#define CMSG_FIRSTHDR(mhdr) \
  ((size_t) (mhdr)->msg_controllen >= sizeof (struct cmsghdr)		      \
   ? (struct cmsghdr *) (mhdr)->msg_control : (struct cmsghdr *) NULL)
#define CMSG_SPACE(len) (CMSG_ALIGN (len) \
			 + CMSG_ALIGN (sizeof (struct cmsghdr)))
#define CMSG_LEN(len)   (CMSG_ALIGN (sizeof (struct cmsghdr)) + (len))

extern struct cmsghdr *__cmsg_nxthdr (struct msghdr *__mhdr,
				      struct cmsghdr *__cmsg) __THROW;
#ifdef __USE_EXTERN_INLINES
# ifndef _EXTERN_INLINE
#  define _EXTERN_INLINE __extern_inline
# endif
_EXTERN_INLINE struct cmsghdr *
__NTH (__cmsg_nxthdr (struct msghdr *__mhdr, struct cmsghdr *__cmsg))
{
  if ((size_t) __cmsg->cmsg_len < sizeof (struct cmsghdr))
    /* The kernel header does this so there may be a reason.  */
    return 0;

  __cmsg = (struct cmsghdr *) ((unsigned char *) __cmsg
			       + CMSG_ALIGN (__cmsg->cmsg_len));
  if ((unsigned char *) (__cmsg + 1) > ((unsigned char *) __mhdr->msg_control
					+ __mhdr->msg_controllen)
      || ((unsigned char *) __cmsg + CMSG_ALIGN (__cmsg->cmsg_len)
	  > ((unsigned char *) __mhdr->msg_control + __mhdr->msg_controllen)))
    /* No more entries.  */
    return 0;
  return __cmsg;
}
#endif	/* Use `extern inline'.  */

/* Socket options.  */
#define SO_DEBUG		0x0001 /* Turn on debugging info recording.  */
#define SO_ACCEPTCONN	0x0002 /* Socket has had listen().  */
#define SO_REUSEADDR	0x0004 /* Allow local address reuse.  */
#define SO_KEEPALIVE	0x0008 /* Keep connections alive.  */
#define SO_DONTROUTE	0x0010 /* Just use interface addresses.  */
#define SO_BROADCAST	0x0020 /* Permit sending of broadcast msgs.  */
#define SO_USELOOPBACK	0x0040 /* Bypass hardware when possible.  */
#define SO_LINGER		0x0080 /* Linger on close if data present.  */
#define SO_OOBINLINE	0x0100 /* Leave received OOB data in line.  */
#define SO_DGRAM_ERRIND	0x0200 /* Application wants delayed error.  */
#define SO_RECVUCRED	0x0400 /* Application wants ucred of sender.  */

/* Socket options not kept in so_options.  */
#define SO_SNDBUF		0x1001 /* Send buffer size.  */
#define SO_RCVBUF		0x1002 /* Receive buffer size.  */
#define SO_SNDLOWAT		0x1003 /* Send low-water mark.  */
#define SO_RCVLOWAT		0x1004 /* Receive low-water mark.  */
#define SO_SNDTIMEO		0x1005 /* Send timeout.  */
#define SO_RCVTIMEO		0x1006 /* Receive timeout.  */
#define SO_ERROR		0x1007 /* Get error status and clear.  */
#define SO_TYPE			0x1008 /* Get socket type.  */
#define SO_PROTOTYPE	0x1009 /* Get/set protocol type.  */
#define SO_ANON_MLP		0x100a /* Create MLP on anonymous bind.  */
#define SO_MAC_EXEMPT	0x100b /* Allow dominated unlabeled peers.  */
#define SO_DOMAIN		0x100c /* Get socket domain. */
/* SCM_RIGHTS = 0x1010 */
#define SO_SECATTR		0x1011 /* Socket's security attributes.  */
/* SCM_UCRED = 0x1012 */
#define SO_TIMESTAMP	0x1013 /* Sender's ucred.  */
#define SO_ALLZONES		0x1014 /* Bind in all zones.  */
#define SO_EXCLBIND		0x1015 /* Exclusive binding.  */

/* Socket level message types.  */
enum
  {
    SCM_RIGHTS = 0x1010,	/* Transfer file descriptors.  */
#define SCM_RIGHTS SCM_RIGHTS
    SCM_UCRED = 0x1012,
#define SCM_UCRED SCM_UCRED
    SCM_TIMESTAMP = SO_TIMESTAMP
#define SCM_TIMESTAMP SCM_TIMESTAMP
  };

/* Structure used to manipulate the SO_LINGER option.  */
struct linger
  {
    int l_onoff;		/* Nonzero to linger on close.  */
    int l_linger;		/* Time to linger.  */
  };

/* Socket versions.  */
#define SOV_STREAM		0 /* Not a socket - just a stream.  */
#define SOV_DEFAULT		1 /* Select based on so_default_version.  */
#define SOV_SOCKSTREAM	2 /* Socket plus streams operations.  */
#define SOV_SOCKBSD		3 /* Socket with no streams operations.  */
#define SOV_XPG4_2	    4 /* Xnet socket.  */

#endif	/* bits/socket.h */
