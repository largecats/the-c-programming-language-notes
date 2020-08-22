#include <stdio.h>
#include <string.h>
#include "header.h"

/* binsearch: find word in tab[0]...tab[n-1] */
struct key *binsearch(char *word, struct key *tab, int n) {
    /* if found the struct key in the struct key array, "tab", return a pointer to the struct key and store its word field in variable word */
    int cond;
    struct key *low = &tab[0]; /* beginning of tab */
    struct key *high = &tab[n]; /* just past the end of tab */
    struct key *mid;
    
    while (low < high) {
        mid = low + (high-low) / 2; /* cannot add pointers, but subtraction is legal */
        if ((cond = strcmp(word, mid -> word)) < 0) {
            /* compare word with (*mid).word */
            high = mid;
        }
        else if (cond > 0) {
            low = mid + 1;
        }
        else {
            return mid;
        }
    }
    return NULL;
}
