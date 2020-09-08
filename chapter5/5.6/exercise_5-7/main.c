/*
Exercise 5-7. Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to maintain storage. How much faster is the program?
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "extern.h"
#include "../../../helper_functions.h"

char *lineptr[MAXLINES]; /* array of pointers to the starting char of line */

int readlines(char *lineptr[], char linestorage[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort1(char *lineptr[], int left, int right);

/* sort input lines */
int main() {
    int nlines; /* number of input lines read */
    char linestorage[MAXLINES * MAXLEN]; /* array to store input lines */

    if ((nlines = readlines(lineptr, linestorage, MAXLINES)) >= 0) {
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
$ gcc chapter5/5.6/exercise_5-7/main.c chapter5/5.6/exercise_5-7/io.c chapter5/5.6/exercise_5-7/sort.c helper_functions.c -o chapter5/5.6/exercise_5-7/result.out

$ chapter5/5.6/exercise_5-7/result.out
c
b
a
nlines = 3
a
b
c
$ chapter5/5.6/exercise_5-7/result.out
hello Neo
knock knock
follow the white rabbit
nlines = 3
follow the white rabbit
hello Neo
knock knock
*/