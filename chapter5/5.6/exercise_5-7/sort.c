#include <stdio.h>
#include "../../../helper_functions.h"
#include "extern.h"

void swap_pointer_version(char *v[], int i, int j);

/* qsort: sort v[left, right] into non-decreasing order */
void qsort1(char *v[], int left, int right) {
    int i, last;
    
    if (left >= right) {
        return;
        // ; /* not enough - need to terminate */
    }
    swap_pointer_version(v, left, (left + right)/2); /* pick middle element to be pivot and move it to the start of v[left, right] */
    last = left; /* initialize pivot position to left */
    for (i = left+1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0) {
            swap_pointer_version(v, ++last, i);
        }
    }
    swap_pointer_version(v, left, last); /* last is the final position of pivot */
    qsort1(v, left, last-1); /* recursively sort the left and right halves */
    qsort1(v, last+1, right);
}