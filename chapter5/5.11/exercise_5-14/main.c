/*
Exercise 5-14. Modify the sort program to handle a -r flag, which indicates sorting in reverse (decreasing) order. Be sure that -r works with -n.
*/

#include <stdio.h>
#include <string.h>
#include "../../../helper_functions.h"
#include "extern.h"

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort1(void *lineptr[], int left, int right, int (*comp)(void *, void *), int r);
int numcmp(char *, char *);
void parse_arg(int argc, char *argv[], int *n, int *r);

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines; /* number of input lines read */
    int numeric = 0; /* if numeric sort */
    int n = 0, r = 0;

    parse_arg(argc, argv, &n, &r); /* read n, r from command line input */
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (n) {
            qsort1((void **) lineptr, 0, nlines-1, (int (*)(void *, void *)) numcmp, r);
        }
        else {
            qsort1((void **) lineptr, 0, nlines-1, (int (*)(void *, void *)) strcmp, r);
        }
        writelines(lineptr, nlines);
        return 0;
    }
    else {
        printf("input too big to sort\n");
        return 1;
    }
}

/*
$ gcc chapter5/5.11/exercise_5-14/main.c chapter5/5.11/exercise_5-14/arg_parser.c chapter5/5.11/exercise_5-14/io.c chapter5/5.11/exercise_5-14/sort.c helper_functions.c -o chapter5/5.11/exercise_5-14/result.out

$ chapter5/5.11/exercise_5-14/result.out -r
a
b
c
c
b
a
*/
