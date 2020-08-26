#include <stdio.h>
#include "header.h"
#include "../../../helper_functions.h"

/* print_nlist: print all (name, defn) entries in hashtab */
void print_nlist(struct nlist *hashtab[]) {
    for (int i=0; i < HASHSIZE; i++) {
        for (struct nlist *np = hashtab[i]; np != NULL; np = np->next) {
            printf("name = %s, defn = %s\n", np->name, np->defn);
        }
    }
    putchar('\n');
}