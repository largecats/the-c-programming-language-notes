/*
Exercise 5-15. Add the option -f to fold upper and lower case together, so that case distinctions are not made during sorting; for example, a and A compare equal.
*/

#include <stdio.h>
#include <string.h>
#include "../../../helper_functions.h"
#include "extern.h"

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort1(void *lineptr[], int left, int right, int (*comp)(void *, void *), int r);
int numcmp(char *s1, char *s2);
int caseless_strcmp(char *s1, char *s2); /* case-insensitive strcmp */
void parse_arg(int argc, char *argv[], int *n, int *r, int *f);

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines; /* number of input lines read */
    int numeric = 0; /* if numeric sort */
    int n = 0, r = 0, f = 0;

    parse_arg(argc, argv, &n, &r, &f); /* read n, r from command line input */
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        switch (n) {
            case 0:
                switch (f) {
                    case 0:
                        qsort1((void **) lineptr, 0, nlines-1, (int (*)(void *, void *)) strcmp, r);
                        break;
                    case 1:
                        qsort1((void **) lineptr, 0, nlines-1, (int (*)(void *, void *)) caseless_strcmp, r);
                        break;
                    default:
                        break;
                };
                break;
            case 1:
                qsort1((void **) lineptr, 0, nlines-1, (int (*)(void *, void *)) numcmp, r);
                break;
            default:
                break;
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
$ gcc chapter5/5.11/exercise_5-15/main.c chapter5/5.11/exercise_5-15/arg_parser.c chapter5/5.11/exercise_5-15/io.c chapter5/5.11/exercise_5-15/sort.c helper_functions.c -o chapter5/5.11/exercise_5-15/result.out

$ chapter5/5.11/exercise_5-15/result.out
a
A
A
a
$ chapter5/5.11/exercise_5-15/result.out -f
a
A
a
A
$ chapter5/5.11/exercise_5-15/result.out -f
A
a
A
a
$ chapter5/5.11/exercise_5-15/result.out -r
A
a
a
A
$ chapter5/5.11/exercise_5-15/result.out -r -f
A
a
A
a
*/