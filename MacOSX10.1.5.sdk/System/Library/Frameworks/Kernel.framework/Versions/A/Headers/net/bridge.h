/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * Copyright (c) 1998 Luigi Rizzo
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
#ifndef _NET_BRIDGE_H_
#define _NET_BRIDGE_H_

extern int do_bridge;
/*
 * the hash table for bridge
 */
typedef struct hash_table {
    struct ifnet *name ;
    unsigned char etheraddr[6] ;
    unsigned short used ;
} bdg_hash_table ;

extern bdg_hash_table *bdg_table ;

#define BDG_MAX_PORTS 128
extern unsigned char bdg_addresses[6*BDG_MAX_PORTS];
extern int bdg_ports ;

/*
 * out of the 6 bytes, the last ones are more "variable". Since
 * we are on a little endian machine, we have to do some gimmick...
 */
#define HASH_SIZE 8192	/* must be a power of 2 */
#define HASH_FN(addr)   (	\
	ntohs( ((short *)addr)[1] ^ ((short *)addr)[2] ) & (HASH_SIZE -1))

#define	IFF_MUTE	IFF_LINK2	/* will need a separate flag... */

struct ifnet *bridge_in(struct mbuf *m);
/* bdg_forward frees the mbuf if necessary, returning null */
int bdg_forward (struct mbuf **m, struct ifnet *dst);

#ifdef __i386__
#define BDG_MATCH(a,b) ( \
    ((unsigned short *)(a))[2] == ((unsigned short *)(b))[2] && \
    *((unsigned int *)(a)) == *((unsigned int *)(b)) )
#define IS_ETHER_BROADCAST(a) ( \
	*((unsigned int *)(a)) == 0xffffffff && \
	((unsigned short *)(a))[2] == 0xffff )
#else
#warning... must complete these for the alpha etc.
#define BDG_MATCH(a,b) (!bcmp(a, b, ETHER_ADDR_LEN) )
#endif
/*
 * The following constants are not legal ifnet pointers, and are used
 * as return values from the classifier, bridge_dst_lookup()
 * The same values are used as index in the statistics arrays,
 * with BDG_FORWARD replacing specifically forwarded packets.
 */
#define BDG_BCAST	( (struct ifnet *)1 )
#define BDG_MCAST	( (struct ifnet *)2 )
#define BDG_LOCAL	( (struct ifnet *)3 )
#define BDG_DROP	( (struct ifnet *)4 )
#define BDG_UNKNOWN	( (struct ifnet *)5 )
#define BDG_IN		( (struct ifnet *)7 )
#define BDG_OUT		( (struct ifnet *)8 )
#define BDG_FORWARD	( (struct ifnet *)9 )

#define PF_BDG 3 /* XXX superhack */
/*
 * statistics, passed up with sysctl interface and ns -p bdg
 */

#define STAT_MAX (int)BDG_FORWARD
struct bdg_port_stat {
    char name[16];
    u_long collisions;
    u_long p_in[STAT_MAX+1];
} ;

struct bdg_stats {
    struct bdg_port_stat s[16];
} ;


#define BDG_STAT(ifp, type) bdg_stats.s[ifp->if_index].p_in[(int)type]++ 
 
#if KERNEL
/*
 * Find the right pkt destination:
 *	BDG_BCAST	is a broadcast
 *	BDG_MCAST	is a multicast
 *	BDG_LOCAL	is for a local address
 *	BDG_DROP	must be dropped
 *	other		ifp of the dest. interface (incl.self)
 */
static __inline
struct ifnet *
bridge_dst_lookup(struct mbuf *m)
{
    struct ether_header *eh = mtod(m, struct ether_header *);
    struct ifnet *dst ;
    int index ;
    u_char *eth_addr = bdg_addresses ;

    if (IS_ETHER_BROADCAST(eh->ether_dhost))
	return BDG_BCAST ;
    if (eh->ether_dhost[0] & 1)
	return BDG_MCAST ;
    /*
     * Lookup local addresses in case one matches.
     */
    for (index = bdg_ports, eth_addr = bdg_addresses ;
		 index ; index--, eth_addr += 6 )
	if (BDG_MATCH(eth_addr, eh->ether_dhost) )
	    return BDG_LOCAL ;
    /*
     * Look for a possible destination in table
     */
    index= HASH_FN( eh->ether_dhost );
    dst = bdg_table[index].name;
    if ( dst && BDG_MATCH( bdg_table[index].etheraddr, eh->ether_dhost) )
	return dst ;
    else
	return BDG_UNKNOWN ;
}

#endif /* KERNEL */

#endif /* ! _NET_BRIDGE_H_ */

