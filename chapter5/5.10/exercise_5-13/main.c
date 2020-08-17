/*
Exercise 5-13. Write the program tail, which prints the last n lines of its input. By default, n is set to 10, let us say, but it can be changed by an optional argument so that
tail -n
prints the last n lines. The program should behave rationally no matter how unreasonable the input or the value of n. Write the program so it makes the best use of available storage; lines should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of fixed size.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../helper_functions.h"
#include "extern.h"

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

/*
$ gcc chapter5/5.10/exercise_5-13/main.c chapter5/5.10/exercise_5-13/parse_args.c chapter5/5.10/exercise_5-13/io.c helper_functions.c -o chapter5/5.10/exercise_5-13/result.out

$ chapter5/5.10/exercise_5-13/result.out -5
1
2
3
4
5
6
7
3
4
5
6
7
*/