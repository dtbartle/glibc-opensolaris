/* Copyright (C) 1991-1999, 2000, 2004, 2008 Free Software Foundation, Inc.
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

/* Linux version.  */

#ifndef _NETINET_IN_H
# error "Never use <bits/in.h> directly; include <netinet/in.h> instead."
#endif

/* Really these belong in the enum in netinet/in.h.  */
#define IPPROTO_GGP	3
#define IPPROTO_HELLO	63
#define IPPROTO_ND	77
#define IPPROTO_EON	80

/* Options for use with `getsockopt' and `setsockopt' at the IP level.
   The first word in the comment at the right is the data type used;
   "bool" means a boolean value stored in an `int'.  */
#define        IP_OPTIONS      1       /* ip_opts; IP per-packet options.  */
#define        IP_HDRINCL      2       /* int; Header is included with data.  */
#define        IP_TOS          3       /* int; IP type of service and precedence.  */
#define        IP_TTL          4       /* int; IP time to live.  */
#define        IP_RECVOPTS     5       /* bool; Receive all IP options w/datagram.  */
#define        IP_RECVRETOPTS  6       /* bool; Receive IP options for response.  */
#define        IP_RECVDSTADDR  7       /* int; Receive IP dst addr w/datagram.  */
#define        IP_RETOPTS      8       /* ip_opts; Set/get IP per-packet options.  */
#define        IP_RECVIF       9       /* int; Receive the inbound interface index.  */
#define        IP_RECVSLLA     10      /* sockaddr_dl; Get source link layer address.  */
#define        IP_RECVTTL      11      /* u_char; Get TTL for inbound packet.  */
#define IP_MULTICAST_IF 16	/* in_addr; set/get IP multicast i/f */
#define IP_MULTICAST_TTL 17	/* u_char; set/get IP multicast ttl */
#define IP_MULTICAST_LOOP 18	/* i_char; set/get IP multicast loopback */
#define IP_ADD_MEMBERSHIP 19	/* ip_mreq; add an IP group membership */
#define IP_DROP_MEMBERSHIP 20	/* ip_mreq; drop an IP group membership */
#define IP_UNBLOCK_SOURCE 21	/* ip_mreq_source: unblock data from source */
#define IP_BLOCK_SOURCE 22	/* ip_mreq_source: block data from source */
#define IP_ADD_SOURCE_MEMBERSHIP 23 /* ip_mreq_source: join source group */
#define IP_DROP_SOURCE_MEMBERSHIP 24 /* ip_mreq_source: leave source group */
#define IP_NEXTHOP 25 /* send directly to next hop */
#define IP_PKTINFO 26 /* specify src address and/or index */
#define IP_RECVPKTINFO 26 /* recv dest/matched addr and index */
#define IP_SEC_OPT 34 /* used to set IPSEC options */

/* ipsec */
#define IPSEC_PREF_NEVER    0x01
#define IPSEC_PREF_REQUIRED 0x02
#define IPSEC_PREF_UNIQUE   0x04

typedef struct ipsec_req
  {
    unsigned int ipsr_ah_req; /* AH request */
    unsigned int ipsr_esp_req; /* ESP request */
    unsigned int ipsr_self_encap_req; /* Self-Encap request */
    unsigned int ipsr_auth_alg; /* Auth algs for AH */
    unsigned int ipsr_esp_alg; /* Encr algs for ESP */
    unsigned int ipsr_esp_auth_alg; /* Auth algs for ESP */
  }
ipsec_req_t;

#define MCAST_JOIN_GROUP 41	/* group_req: join any-source group */
#define MCAST_LEAVE_GROUP 42	/* group_req: leave any-source group */
#define MCAST_BLOCK_SOURCE 43	/* group_source_req: block from given group */
#define MCAST_UNBLOCK_SOURCE 44	/* group_source_req: unblock from given group*/
#define MCAST_JOIN_SOURCE_GROUP 45 /* group_source_req: join source-spec gr */
#define MCAST_LEAVE_SOURCE_GROUP 46 /* group_source_req: leave source-spec gr*/

#define MCAST_INCLUDE   1
#define MCAST_EXCLUDE   2

#define IP_BOUND_IF 65 /* bind socket to an ifindex */
#define IP_UNSPEC_SRC 66 /* use unspecified source address */
#define IP_BROADCAST_TTL 67 /* use specific TTL for broadcast */
#define IP_DONTFAILOVER_IF 68 /* no failover */
#define IP_DHCPINIT_IF 69 /* accept all unicast DHCP traffic */
#define IP_REUSEADDR 260
#define IP_DONTROUTE 261
#define IP_BROADCAST 262

#define IP_DEFAULT_MULTICAST_TTL        1
#define IP_DEFAULT_MULTICAST_LOOP       1
//#define IP_MAX_MEMBERSHIPS              20

/* Structure used for IP_PKTINFO.  */
struct in_pktinfo
  {
    unsigned int ipi_ifindex;			/* Interface index  */
    struct in_addr ipi_spec_dst;	/* Routing destination address  */
    struct in_addr ipi_addr;		/* Header destination address  */
  };

/* Options for use with `getsockopt' and `setsockopt' at the IPv6 level.
   The first word in the comment at the right is the data type used;
   "bool" means a boolean value stored in an `int'.  */
#define IPV6_UNICAST_HOPS	5
#define IPV6_MULTICAST_IF	6
#define IPV6_MULTICAST_HOPS	7
#define IPV6_MULTICAST_LOOP	8
#define IPV6_JOIN_GROUP		9
#define IPV6_LEAVE_GROUP	10
#define IPV6_ADD_MEMBERSHIP	IPV6_JOIN_GROUP
#define IPV6_DROP_MEMBERSHIP	IPV6_LEAVE_GROUP
#define IPV6_PKTINFO		11
#define IPV6_HOPLIMIT		12
#define IPV6_NEXTHOP		13
#define IPV6_HOPOPTS		14
#define IPV6_DSTOPTS		15
#define IPV6_RTHDR			16
#define IPV6_RTHDRDSTOPTS	17
#define IPV6_RECVPKTINFO	18
#define IPV6_RECVHOPLIMIT	19
#define IPV6_RECVHOPOPTS	20

#define IPV6_RECVRTHDR		22
#define IPV6_RECVRTHDRDSTOPTS	23
#define IPV6_CHECKSUM		24
#define IPV6_RECVTCLASS		25

#define IPV6_USE_MIN_MTU	32
#define IPV6_DONTFRAG		33
#define IPV6_SEC_OPT		34
#define IPV6_SRC_PREFERENCES	35
#define IPV6_RECVPATHMTU	36
#define IPV6_PATHMTU		37
#define IPV6_TCLASS			38
#define IPV6_V6ONLY			39
#define IPV6_RECVDSTOPTS	40

/* IPV6_SRC_PREFERENCES */
#define IPV6_PREFER_SRC_HOME	0x01
#define IPV6_PREFER_SRC_COA		0x02
#define IPV6_PREFER_SRC_PUBLIC	0x04
#define IPV6_PREFER_SRC_TMP		0x08
#define IPV6_PREFER_SRC_NONCGA	0x10
#define IPV6_PREFER_SRC_CGA		0x20
#define IPV6_PREFER_SRC_MIPMASK (IPV6_PREFER_SRC_HOME | IPV6_PREFER_SRC_COA)
#define IPV6_PREFER_SRC_MIPDEFAULT  IPV6_PREFER_SRC_HOME
#define IPV6_PREFER_SRC_TMPMASK (IPV6_PREFER_SRC_PUBLIC | IPV6_PREFER_SRC_TMP)
#define IPV6_PREFER_SRC_TMPDEFAULT  IPV6_PREFER_SRC_PUBLIC
#define IPV6_PREFER_SRC_CGAMASK (IPV6_PREFER_SRC_NONCGA | IPV6_PREFER_SRC_CGA)
#define IPV6_PREFER_SRC_CGADEFAULT  IPV6_PREFER_SRC_NONCGA
#define IPV6_PREFER_SRC_MASK (IPV6_PREFER_SRC_MIPMASK |\
	IPV6_PREFER_SRC_TMPMASK | IPV6_PREFER_SRC_CGAMASK)
#define IPV6_PREFER_SRC_DEFAULT (IPV6_PREFER_SRC_MIPDEFAULT |\
	IPV6_PREFER_SRC_TMPDEFAULT | IPV6_PREFER_SRC_CGADEFAULT)

#define IPV6_BOUND_IF		65
#define IPV6_UNSPEC_SRC		66
#define IPV6_BOUND_PIF		67
#define IPV6_DONTFAILOVER_IF	68

#define IPV6_RTHDR_TYPE_0   0

typedef __uint32_t	ipaddr_t;
typedef struct in6_addr in6_addr_t;
