/*
Exercise 5-13. Write the program tail, which prints the last n lines of its input. By default, n is set to 10, let us say, but it can be changed by an optional argument so that
tail -n
prints the last n lines. The program should behave rationally no matter how unreasonable the input or the value of n. Write the program so it makes the best use of available storage; lines should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of fixed size.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helper_functions.h"

#define MAXLINES 5000 /* max # of lines to sort */

char *lineptr[MAXLINES]; /* array of pointers to the starting char of line */

void parse_arg(int argc, char *argv[], int *np);
int readlines(char *lineptr[], int nlines, int n);
void tail(char *lineptr[], int nlines, int n);

int main(int argc, char *argv[]) {
    int n, nlines;

    n = 10;
    parse_arg(argc, argv, &n);
    if ((nlines = readlines(lineptr, MAXLINES, n)) >= 0) {
        tail(lineptr, nlines, n);
        return 0;
    }
    else {
        printf("error: input too many lines\n");
        return -1;
    }
}

void parse_arg(int argc, char *argv[], int *np) {
    int i = 0;

    while (++i < argc) {
        switch (*argv[i]) {
            case '-': 
                *np = atoi(++(argv[i]));
                break;
            default:
                break;
        }
    }
}

void tail(char *lineptr[], int nlines, int n) {
    int i = n < nlines? n: nlines;
    while (i-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

#define MAXLEN 1000 /* max length of any input line */

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