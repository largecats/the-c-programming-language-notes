#include <stdio.h>

typedef long Align; /* for alignment to long boundary */

union header { /* block header */
    struct {
        union header *ptr; /* next block if on free list */
        unsigned size; /* size of the block */
    } s;
    Align x; /* force alignment of blocks */
};

typedef union header Header;

static Header base; /* empty list to get started */
static Header *freep = NULL; /* start of free list */

void *malloc1(unsigned nbytes);
static Header *morecore(unsigned nu);
void free(void *ap);