#include <stdio.h>
#include "../header.h"

#define MAX_N_BYTES 10000

/* malloc: general-purpose storage allocator */
void *malloc1(unsigned nbytes) {
    if (nbytes <= 0 || nbytes > MAX_N_BYTES) {
        fprintf(stderr,"malloc1: exceeded maximum number of bytes %u\n", MAX_N_BYTES);
        return NULL;
    }
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;

    nunits = (nbytes + sizeof(Header)-1) / sizeof(Header) + 1; /* round up the requested size (nbytes) to the proper number of header-sized units */
    if ((prevp = freep) == NULL) { /* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) { /* search through the list of free blocks */
        if (p->s.size >= nunits) { /* big enough */
            if (p->s.size == nunits) { /* exactly */
                prevp->s.ptr = p->s.ptr;
            }
            else { /* allocate tail end */
                p->s.size -= nunits; /* allocate from tail end by subtracting nunits from the free block found */
                p += p->s.size; /* advance pointer to free block by nunits so that it points to the start of the allocated block */
                p->s.size = nunits; /* set size of allocated block to nunits */
            }
            freep = prevp;
            return (void *)(p+1); /* return pointer to the free space that is 1 unit behind the header */
        }
        if (p == freep) { /* wrapped around free list; freep is the head of the free list */
            if ((p = morecore(nunits)) == NULL) {
                return NULL; /* none left */
            }
        }
    }
}

#define NALLOC 1024 /* minimum #units to requset */

/* morecore: ask system for more memory */
static Header *morecore(unsigned nu) {
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC) {
        nu = NALLOC;
    }
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1) { /* no space at all */
        return NULL;
    }
    up = (Header *) cp; /* create header for the storage returned by sbrk() */
    up->s.size = nu;
    free((void *)(up+1));
    return freep;
}

/* free: put block ap in free list */
void free(void *ap) {
    Header *bp, *p;

    bp = (Header *)ap - 1; /* point to block header */

    if (bp->s.size <= 0) {
        fprintf(stderr, "free: invalid size %u", bp->s.size);
    }

    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        /* find space between two existing blocks; if, while doing so, the search wraps around the list of free blocks and the newly requested block is located at the end/start of the list, no further action is needed*/
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
            break; /* freed block at end of start of arena */
        }
    }
    /* bp is now between p and p->s.ptr */
    if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else {
        bp->s.ptr = p->s.ptr;
    }
    if (p + p->s.size == bp) { /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else {
        p->s.ptr = bp;
    }
    freep = p;
}