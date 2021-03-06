#include <stdio.h>
#include <string.h>
#include "../../helper_functions.h"

#define MAXLINES 5000 /* max # of lines to sort */

char *lineptr[MAXLINES]; /* array of pointers to the starting char of line */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort1(char *lineptr[], int left, int right);

/* sort input lines */
int main() {
    int nlines; /* number of input lines read */

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        print_variable(nlines);
        qsort1(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    }
    else {
        printf("error: input too many lines\n");
        return -1;
    }
}

/*
$ gcc chapter5/5.11/sort_lines.c helper_functions.c -o chapter5/5.11/result.out

$ chapter5/5.11/result.out
hello Neo
knock knock
follow the white rabbit
nlines = 3
follow the white rabbit
knock knock
hello Neo
*/

#define MAXLEN 1000 /* max length of any input line */

/* readlines: read input lines and store in array of pointers*/
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN]; /* line pointer and line */

    nlines = 0; /* counter in lineptr, the array of line pointers */
    while ((len = getline1(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            /* if there are too many lines or no space */
            return -1;
        }
        else {
            line[len-1] = '\0'; /* delete \n character */
            strcpy(p, line); /* point line pointer to line */
            lineptr[nlines++] = p; /* put line pointer in array */
        }
    }
    return nlines; /* return the number of lines read */
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

/* qsort1: sort v[left, right] into non-decreasing order */
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
    swap_pointer_version(v, left, last); /* last is the final position of pivot */
    qsort1(v, left, last-1); /* recursively sort the left and right halves */
    qsort1(v, last+1, right);
    }
}