#include <stdio.h>

#define HASHSIZE 101

struct nlist {
    /* struct for table entry */
    struct nlist *next; /* next entry in the chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

extern struct nlist *hashtab[];
void print_nlist(struct nlist *hashtab[]);