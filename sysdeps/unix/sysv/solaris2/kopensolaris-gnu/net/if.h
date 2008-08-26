/* net/if.h -- declarations for inquiring about network interfaces
   Copyright (C) 1997,98,99,2000,2001, 2008 Free Software Foundation, Inc.
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

#ifndef _NET_IF_H
#define _NET_IF_H	1

#include <features.h>

#ifdef __USE_MISC
# include <sys/types.h>
# include <sys/socket.h>
#endif


/* Length of interface name.  */
#define IF_NAMESIZE	16
#define LIF_NAMESIZE	32

struct if_nameindex
  {
    unsigned int if_index;	/* 1, 2, ... */
    char *if_name;		/* null terminated name: "eth0", ... */
  };


#ifdef __USE_MISC
/* Standard interface flags. */
enum
  {
    IFF_UP = 0x1,		/* Interface is up.  */
# define IFF_UP	IFF_UP
    IFF_BROADCAST = 0x2,	/* Broadcast address valid.  */
# define IFF_BROADCAST	IFF_BROADCAST
    IFF_DEBUG = 0x4,		/* Turn on debugging.  */
# define IFF_DEBUG	IFF_DEBUG
    IFF_LOOPBACK = 0x8,		/* Is a loopback net.  */
# define IFF_LOOPBACK	IFF_LOOPBACK
    IFF_POINTOPOINT = 0x10,	/* Interface is point-to-point link.  */
# define IFF_POINTOPOINT IFF_POINTOPOINT
    IFF_NOTRAILERS = 0x20,	/* Avoid use of trailers.  */
# define IFF_NOTRAILERS	IFF_NOTRAILERS
    IFF_RUNNING = 0x40,		/* Resources allocated.  */
# define IFF_RUNNING	IFF_RUNNING
    IFF_NOARP = 0x80,		/* No address resolution protocol.  */
# define IFF_NOARP	IFF_NOARP
    IFF_PROMISC = 0x100,	/* Receive all packets.  */
# define IFF_PROMISC	IFF_PROMISC

    /* Not supported */
    IFF_ALLMULTI = 0x200,	/* Receive all multicast packets.  */
# define IFF_ALLMULTI	IFF_ALLMULTI

    IFF_INTELLIGENT = 0x400,		/* Protocol code on board.  */
# define IFF_INTELLIGENT	IFF_INTELLIGENT

    IFF_MULTICAST = 0x800,	/* Supports multicast.  */
# define IFF_MULTICAST	IFF_MULTICAST

    IFF_MULTI_BCAST = 0x1000,		/* Multicast using broadcast address.  */
# define IFF_MULTI_BCAST	IFF_MULTI_BCAST
    IFF_UNNUMBERED = 0x2000,	/* Non-unique address.  */
# define IFF_DHCPRUNNING	IFF_DHCPRUNNING
    IFF_DHCPRUNNING = 0x4000,	/* DHCP controls this interface.  */
# define IFF_DHCPRUNNING	IFF_DHCPRUNNING
    IFF_PRIVATE = 0x8000,	/* Do not advertise.  */
# define IFF_PRIVATE	IFF_PRIVATE

    IFF_NOXMIT = 0x10000,	/* Do not transmit packets.  */
# define IFF_NOXMIT	IFF_NOXMIT
    IFF_NOLOCAL = 0x20000,	/* No address - just on-link subnet.  */
# define IFF_NOLOCAL	IFF_NOLOCAL
    IFF_DEPRECATED = 0x40000,	/* Interface address deprecated.  */
# define IFF_DEPRECATED	IFF_DEPRECATED
    IFF_ADDRCONF = 0x80000,	/* Address from stateless addrconf.  */
# define IFF_ADDRCONF	IFF_ADDRCONF

    IFF_ROUTER = 0x100000,	/* Router on this interface.  */
# define IFF_ROUTER	IFF_ROUTER
    IFF_NONUD = 0x200000,	/* No NUD on this interface.  */
# define IFF_NONUD	IFF_NONUD
	IFF_ANYCAST = 0x400000,	/* Anycast address.  */
# define IFF_ANYCAST	IFF_ANYCAST
	IFF_NORTEXCH = 0x800000,	/* Do not exchange routing info.  */
# define IFF_NORTEXCH	IFF_NORTEXCH

    IFF_IPV4 = 0x1000000,	/* IPv4 interface.  */
# define IFF_IPV4	IFF_IPV4
    IFF_IPV6 = 0x2000000,	/* IPv6 interface.  */
# define IFF_IPV6	IFF_IPV6
	/* IFF_MIPRUNNING = 0x4000000, */
    IFF_NOFAILOVER = 0x8000000,	/* Don't failover on NIC failure.  */
# define IFF_NOFAILOVER	IFF_NOFAILOVER

	IFF_FAILED = 0x10000000,	/* NIC has failed.  */
# define IFF_FAILED	IFF_FAILED
    IFF_STANDBY = 0x2000000,	/* Standby NIC to be used on failures.  */
# define IFF_STANDBY	IFF_STANDBY
    IFF_INACTIVE = 0x4000000,	/* NIC active or not.  */
# define IFF_INACTIVE	IFF_INACTIVE
    IFF_OFFLINE = 0x80000000,	/* NIC has been offlined.  */
# define IFF_OFFLINE	IFF_OFFLINE
  };

/* The ifaddr structure contains information about one address of an
   interface.  They are maintained by the different address families,
   are allocated and attached when an address is set, and are linked
   together so all addresses for an interface can be located.  */

struct ifaddr
  {
    struct sockaddr ifa_addr;	/* Address of interface.  */
    union
      {
	struct sockaddr	ifu_broadaddr;
	struct sockaddr	ifu_dstaddr;
      } ifa_ifu;
    struct iface *ifa_ifp;	/* Back-pointer to interface.  */
    struct ifaddr *ifa_next;	/* Next address for interface.  */
  };

# define ifa_broadaddr	ifa_ifu.ifu_broadaddr	/* broadcast address	*/
# define ifa_dstaddr	ifa_ifu.ifu_dstaddr	/* other end of link	*/

/* Device mapping structure. I'd just gone off and designed a
   beautiful scheme using only loadable modules with arguments for
   driver options and along come the PCMCIA people 8)

   Ah well. The get() side of this is good for WDSETUP, and it'll be
   handy for debugging things. The set side is fine for now and being
   very small might be worth keeping for clean configuration.  */

struct ifmap
  {
    unsigned long int mem_start;
    unsigned long int mem_end;
    unsigned short int base_addr;
    unsigned char irq;
    unsigned char dma;
    unsigned char port;
    /* 3 bytes spare */
  };

/* Interface request structure used for socket ioctl's.  All interface
   ioctl's must have parameter definitions which begin with ifr_name.
   The remainder may be interface specific. Note that OpenSolaris marks
   this as deprecated (in favour of struct lifreq).  */

struct ifreq
  {
# define IFHWADDRLEN	6
# define IFNAMSIZ	IF_NAMESIZE
	char ifr_name[IFNAMSIZ];	/* Interface name, e.g. "en0".  */
    union
      {
	struct sockaddr ifru_addr;
	struct sockaddr ifru_dstaddr;
    char ifru_oname[IFNAMSIZ];
	struct sockaddr ifru_broadaddr;
	int ifru_index;
    short ifru_flags;
    int ifru_metric;
	char ifru_data[1];
	char ifru_enaddr[6];
	int if_muxid[2];

    struct ifr_ppaflags
      {
        short ifrup_flags;
        short ifrup_filler;
        unsigned int ifrup_ppa;
      } ifru_ppaflags;

    struct ifr_dnld_reqs
      {
        uint32_t v_addr;
        uint32_t m_addr;
        uint32_t ex_addr;
        uint32_t size;
      } ifru_dnld_req;

    struct ifr_fddi_stats
      {
        uint32_t stat_size;
        uint32_t fddi_stats;
      } ifru_fddi_stat;

    struct ifr_netmapents
      {
        uint32_t map_ent_size;
        uint32_t entry_number;
        uint32_t fddi_map_ent;
      } ifru_netmapent;

    struct ifr_fddi_gen_struct
      {
        uint32_t ifru_fddi_gioctl;
        uint32_t ifru_fddi_gaddr;
      } ifru_fddi_gstruct;

    } ifr_ifru;
  };
# define ifr_addr	ifr_ifru.ifru_addr	/* address		*/
# define ifr_dstaddr	ifr_ifru.ifru_dstaddr	/* other end of p-p lnk	*/
# define ifr_oaddr	ifr_ifru.ifru_oname	/* other if name */
# define ifr_broadaddr	ifr_ifru.ifru_broadaddr	/* broadcast address	*/
# define ifr_flags	ifr_ifru.ifru_flags	/* flags		*/
# define ifr_metric	ifr_ifru.ifru_ivalue	/* metric		*/
# define ifr_data	ifr_ifru.ifru_data	/* for use by interface	*/
# define ifr_enaddr	ifr_ifru.ifru_enaddr	/* ethernet address */
# define ifr_index	ifr_ifru.ifru_index	/* interface index */
# define ifr_ppa	ifr_ifru.ifru_ppaflags.ifrup_ppa
# define ifr_dnld_req	ifr_ifru.ifru_dnld_req
# define ifr_fddi_stat	ifr_ifru.ifru_fddi_stat
# define ifr_fddi_netmap	ifr_ifru.ifru_netmapent
# define ifr_fddi_gstruct	ifr_ifru.ifru_fddi_gstruct
# define ifr_ip_muxid	ifr_ifru.if_muxid[0]
# define ifr_arp_muxid	ifr_ifru.if_muxid[1]

#define ifr_netmask	ifr_addr
#define ifr_ifindex	ifr_index
# define _IOT_ifreq	_IOT(_IOTS(char),IFNAMSIZ,_IOTS(char),16,0,0)
# define _IOT_ifreq_short _IOT(_IOTS(char),IFNAMSIZ,_IOTS(short),1,0,0)
# define _IOT_ifreq_int	_IOT(_IOTS(char),IFNAMSIZ,_IOTS(int),1,0,0)

#if 0
# define ifr_hwaddr	ifr_ifru.ifru_hwaddr	/* MAC address 		*/
# define ifr_mtu	ifr_ifru.ifru_mtu	/* mtu			*/
# define ifr_map	ifr_ifru.ifru_map	/* device map		*/
# define ifr_slave	ifr_ifru.ifru_slave	/* slave device		*/
# define ifr_bandwidth	ifr_ifru.ifru_ivalue	/* link bandwidth	*/
# define ifr_qlen	ifr_ifru.ifru_ivalue	/* queue length		*/
# define ifr_newname	ifr_ifru.ifru_newname	/* New name		*/
#endif


/* Structure used in SIOCGIFCONF request.  Used to retrieve interface
   configuration for machine (useful for programs which must know all
   networks accessible).  Note that OpenSolaris marks this as
   deprecated (in favour of struct lifconf).  */

struct ifconf
  {
    int	ifc_len;			/* Size of buffer.  */
    union
      {
	__caddr_t ifcu_buf;
	struct ifreq *ifcu_req;
      } ifc_ifcu;
  };
# define ifc_buf	ifc_ifcu.ifcu_buf	/* Buffer address.  */
# define ifc_req	ifc_ifcu.ifcu_req	/* Array of structures.  */
# define _IOT_ifconf _IOT(_IOTS(struct ifconf),1,0,0,0,0) /* not right */

/* Structure used in SIOCLIF*ND requests. */
typedef struct lif_nd_req
  {
#define ND_MAX_HDW_LEN  64
    struct sockaddr_storage lnr_addr;
    uint8_t lnr_state_create;
    uint8_t lnr_state_same_lla;
    uint8_t lnr_state_diff_lla;
    int lnr_hdw_len;
    int lnr_flags;
    int lnr_pad0;
    char lnr_hdw_addr[ND_MAX_HDW_LEN];
  } lif_nd_req_t;

#define ND_UNCHANGED	0
#define ND_INCOMPLETE	1
#define ND_REACHABLE	2
#define ND_STALE	3
#define ND_DELAY	4
#define ND_PROBE	5
#define ND_UNREACHABLE	6
#define ND_INITIAL	7
#define ND_STATE_VALID_MIN	0
#define ND_STATE_VALID_MAX	7

#define NDF_ISROUTER_ON		0x1
#define NDF_ISROUTER_OFF	0x2
#define NDF_ANYCAST_ON	0x4
#define NDF_ANYCAST_OFF		0x8
#define NDF_PROXY_ON	0x10
#define NDF_PROXY_OFF	0x20

/* Structure used for the SIOC[GS]LIFLNKINFO requests. */
typedef struct lif_ifinfo_req
  {
    uint8_t lir_maxhops;
    uint32_t lir_reachtime;
    uint32_t lir_reachretrans;
    uint32_t lir_maxmtu;
  } lif_ifinfo_req_t;

/* Recommended replacement structure for ifreq. */
struct lifreq
  {
# define LIFNAMSIZ	LIF_NAMESIZE
# define LIFGRNAMSIZ	LIF_NAMESIZE
    char lifr_name[LIFNAMSIZ];
    union
      {
        int lifru_addrlen;
        unsigned int lifru_ppa;
      } lifr_lifru1;
    unsigned int lifr_movetoindex;
    union
      {
        struct sockaddr_storage lifru_addr;
        struct sockaddr_storage lifru_dstaddr;
        struct sockaddr_storage lifru_broadaddr;
        struct sockaddr_storage lifru_token;
        struct sockaddr_storage lifru_subnet;
        int lifru_index;
        uint64_t lifru_flags;
        int lifru_metric;
        unsigned int lifru_mtu;
        char lifru_data[1];
        char lifru_enaddr[6];
        int lif_muxid[2];
        struct lif_nd_req lifru_nd_req;
        struct lif_ifinfo_req lifru_ifinfo_req;
        char lifru_groupname[LIFGRNAMSIZ];
        unsigned int lifru_delay;
        zoneid_t lifru_zoneid;
    } lifr_lifru;
};
#define lifr_addrlen	lifr_lifru1.lifru_addrlen
#define lifr_ppa	lifr_lifru1.lifru_ppa   /* driver's ppa */
#define lifr_addr	lifr_lifru.lifru_addr   /* address */
#define lifr_dstaddr	lifr_lifru.lifru_dstaddr /* other end of p-to-p link */
#define lifr_broadaddr	lifr_lifru.lifru_broadaddr /* broadcast address */
#define lifr_token	lifr_lifru.lifru_token  /* address token */
#define lifr_subnet	lifr_lifru.lifru_subnet /* subnet prefix */
#define lifr_index	lifr_lifru.lifru_index  /* interface index */
#define lifr_flags	lifr_lifru.lifru_flags  /* flags */
#define lifr_metric	lifr_lifru.lifru_metric /* metric */
#define lifr_mtu	lifr_lifru.lifru_mtu    /* mtu */
#define lifr_data	lifr_lifru.lifru_data   /* for use by interface */
#define lifr_enaddr	lifr_lifru.lifru_enaddr /* ethernet address */
#define lifr_index	lifr_lifru.lifru_index  /* interface index */
#define lifr_ip_muxid	lifr_lifru.lif_muxid[0]
#define lifr_arp_muxid	lifr_lifru.lif_muxid[1]
#define lifr_nd	lifr_lifru.lifru_nd_req
#define lifr_ifinfo	lifr_lifru.lifru_ifinfo_req
#define lifr_groupname	lifr_lifru.lifru_groupname
#define lifr_delay	lifr_lifru.lifru_delay
#define lifr_zoneid	lifr_lifru.lifru_zoneid

/* Structure used in SIOCT* requests. */
struct sioc_addrreq
  {
    struct sockaddr_storage sa_addr;
    int sa_res;
    int sa_pad;
  };

/* Structure used in SIOCGETLSGCNT requests. */
struct sioc_lsg_req
  {
    struct sockaddr_storage slr_src;
    struct sockaddr_storage slr_grp;
    unsigned int slr_pktcnt;
    unsigned int slr_bytecnt;
    unsigned int slr_wrong_if;
    unsigned int slr_pad;
  };

/* Structure used in SIOCGLIFNUM request. */
struct lifnum
  {
    sa_family_t lifn_family;
    int lifn_flags;
    int lifn_count;
  };

/* Structure used in SIOCGLIFCONF request. */
struct lifconf
  {
    sa_family_t lifc_family;
    int lifc_flags;
    int lifc_len;
    union
      {
        __caddr_t lifcu_buf;
        struct lifreq *lifcu_req;
      } lifc_lifcu;
  };
#define lifc_buf	lifc_lifcu.lifcu_buf
#define lifc_req	lifc_lifcu.lifcu_req

/* Structure used in SIOCGLIFSRCOF request. */
struct lifsrcof
  {
    unsigned int lifs_ifindex;
    size_t lifs_maxlen;
    size_t lifs_len;
    union
      {
        __caddr_t lifsu_buf;
        struct lifreq *lifsu_req;
      } lifs_lifsu;
 };
#define lifs_buf lifs_lifsu.lifsu_buf
#define lifs_req lifs_lifsu.lifsu_req

#define LIFC_NOXMIT				0x01
#define LIFC_EXTERNAL_SOURCE	0x02
#define LIFC_TEMPORARY			0x04
#define LIFC_ALLZONES			0x08

typedef struct if_data
  {
    unsigned char ifi_type;
    unsigned char ifi_addrlen;
    unsigned char ifi_hdrlen;
    unsigned int ifi_mtu;
    unsigned int ifi_metric;
    unsigned int ifi_baudrate;
    unsigned int ifi_ipackets;
    unsigned int ifi_ierrors;
    unsigned int ifi_opackets;
    unsigned int ifi_oerrors;
    unsigned int ifi_collisions;
    unsigned int ifi_ibytes;
    unsigned int ifi_obytes;
    unsigned int ifi_imcasts;
    unsigned int ifi_omcasts;
    unsigned int ifi_iqdrops;
    unsigned int ifi_noproto;
  } if_data_t;

typedef struct if_msghdr
  {
    unsigned short ifm_msglen;
    unsigned char ifm_version;
    unsigned char ifm_type;
    int ifm_addrs;
    int ifm_flags;
    unsigned short ifm_index;
    struct  if_data ifm_data;
  } if_msghdr_t;

typedef struct ifa_msghdr
  {
    unsigned short ifam_msglen;
    unsigned char ifam_version;
    unsigned char ifam_type;
    int ifam_addrs;
    int ifam_flags;
    unsigned short ifam_index;
    int ifam_metric;
  } ifa_msghdr_t;

enum ifta_proto
  {
    IFTAP_INVALID,
    IFTAP_IPV4,
    IFTAP_IPV6
  };

#define IFTUN_VERSION 1

/* Structure used in SIOCTUN[SG]PARAM requests. */
struct iftun_req
  {
#define IFTUN_SECINFOLEN 8
    char ifta_lifr_name[LIFNAMSIZ];
    struct sockaddr_storage ifta_saddr;
    struct sockaddr_storage ifta_daddr;
    unsigned int ifta_flags;
    enum ifta_proto ifta_upper;
    enum ifta_proto ifta_lower;
    unsigned int ifta_vers;
    uint32_t ifta_secinfo[IFTUN_SECINFOLEN];
    int16_t ifta_encap_lim;
    uint8_t ifta_hop_limit;
    uint8_t ifta_spare0;
    uint32_t ifta_spare1;
  };

#define IFTUN_SRC	0x01
#define IFTUN_DST	0x02
#define IFTUN_SECURITY	0x04
#define IFTUN_ENCAP		0x08
#define IFTUN_HOPLIMIT	0x10
#define IFTUN_COMPLEX_SECURITY	0x20

#endif	/* Misc.  */

__BEGIN_DECLS

/* Convert an interface name to an index, and vice versa.  */
extern unsigned int if_nametoindex (__const char *__ifname) __THROW;
extern char *if_indextoname (unsigned int __ifindex, char *__ifname) __THROW;

/* Return a list of all interfaces and their indices.  */
extern struct if_nameindex *if_nameindex (void) __THROW;

/* Free the data returned from if_nameindex.  */
extern void if_freenameindex (struct if_nameindex *__ptr) __THROW;

__END_DECLS

#endif /* net/if.h */
