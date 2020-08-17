#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../../helper_functions.h"
#include "extern.h"

void qsort1(void *v[], int left, int right, int (*comp)(void *, void *), int r) {
    int i, last;

    if (left >= right) {
        return;
    }
    swap_pointer_version(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if (r? (*comp)(v[i], v[left]) > 0: (*comp)(v[i], v[left])< 0) {
            swap_pointer_version(v, ++last, i);
        }
    }
    swap_pointer_version(v, left, last);
    qsort1(v, left, last-1, comp, r);
    qsort1(v, last+1, right, comp, r);
}

/* numcmp: compare s1 and s2 numerically */

int numcmp(char *s1, char *s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) {
        return -1;
    }
    else if (v1 > v2) {
        return 1;
    }
    else {
        return 0;
    }
}