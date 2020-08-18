#include <stdio.h>
#include "../../../helper_functions.h"
#include "extern.h"

/* readlines: read input lines and store in array of pointers*/
int readlines(char *lineptr[], int maxlines, int n) {
    int len, nlines;
    char *p, line[MAXLEN]; /* line pointer and line */

    nlines = 0; /* counter in lineptr, the array of line pointers */
    while ((len = getline_pointer_version(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            /* if there are too many lines or no space */
            return -1;
        }
        else {
            line[len-1] = '\0'; /* delete \n character */
            strcpy(p, line); /* point line pointer to line */
            if (nlines >= n) { /* if there are >= n input lines */
                for (int i = 0; i < n-1; i++) {
                    /* discard the first line since it won't be among the last n lines,
                    and shift all subsequent lines forward */
                    lineptr[i] = lineptr[i+1];
                }
                lineptr[n-1] = p; /* record new line at the position just emptied*/
                nlines++;
            }
            else { /* if not, just record new line */
                lineptr[nlines++] = p;
            }   
        }
    }
    return nlines; /* return the number of lines read */
}


void tail(char *lineptr[], int nlines, int n) {
    int i = n < nlines? n: nlines;
    while (i-- > 0) {
        printf("%s\n", *lineptr++);
    }
}