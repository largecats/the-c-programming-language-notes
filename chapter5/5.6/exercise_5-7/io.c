#include <stdio.h>
#include <string.h>
#include "../../../helper_functions.h"
#include "extern.h"

int getline_pointer_version(char *s, int lim);

/* readlines: read input lines and store in array of pointers*/
int readlines(char *lineptr[], char *linestorage, int maxlines) {
    int len, nlines;
    char *p = linestorage;
    char line[MAXLEN]; /* line pointer and line */

    nlines = 0; /* counter in lineptr, the array of line pointers */
    while ((len = getline_pointer_version(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || len > MAXLEN) {
            /* if there are too many lines or no space */
            return -1;
        }
        else {
            line[len-1] = '\0'; /* delete \n character */
            strcpy(p, line); /* point line pointer to line */
            lineptr[nlines++] = p; /* put line pointer in array */
            p += len;
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