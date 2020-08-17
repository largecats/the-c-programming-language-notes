/*
Exercise 5-16. Add the -d ("directory order") option, which makes comparisons only on letters, numbers and blanks. Make sure it works in conjunction with -f.
*/

#include <stdio.h>
#include <string.h>
#include "../../../helper_functions.h"
#include "extern.h"

#define MAXLINES 5000
char *lineptr[MAXLINES];
int n = 0, r = 0, f = 0, d = 0;

void parse_arg(int argc, char *argv[], int *n, int *r, int *f, int *d);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort1(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *s1, char *s2);
int custom_cmp(char *s1, char *s2); /* case-insensitive strcmp */

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines; /* number of input lines read */
    int numeric = 0; /* if numeric sort */

    parse_arg(argc, argv, &n, &r, &f, &d); /* read n, r from command line input */
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        switch (n) {
            case 0:
                switch (f) {
                    case 0:
                        qsort1((void **) lineptr, 0, nlines-1, (int (*)(void *, void *)) strcmp);
                        break;
                    case 1:
                        qsort1((void **) lineptr, 0, nlines-1, (int (*)(void *, void *)) custom_cmp);
                        break;
                    default:
                        break;
                };
                break;
            case 1:
                qsort1((void **) lineptr, 0, nlines-1, (int (*)(void *, void *)) numcmp);
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
$ gcc chapter5/5.11/exercise_5-16/main.c chapter5/5.11/exercise_5-16/arg_parser.c chapter5/5.11/exercise_5-16/io.c chapter5/5.11/exercise_5-16/sort.c helper_functions.c -o chapter5/5.11/exercise_5-16/result.out

$ chapter5/5.11/exercise_5-16/result.out -d
!$#!@#$!2345
!#$!@#$$1234
!#$!@#$$1234
!$#!@#$!2345
$ chapter5/5.11/exercise_5-16/result.out -d
!@#2345
!$%!#^@#$%@1234
!$%!#^@#$%@1234
!@#2345
$ chapter5/5.11/exercise_5-16/result.out -d
!@$#!@#$ABC
!#$%#@$%@^abc
!#$%#@$%@^abc
!@$#!@#$ABC
$ chapter5/5.11/exercise_5-16/result.out -d -f
!$#@#%@#$%ABC
#$!#%#$%@#$%@#%abc
!$#@#%@#$%ABC
#$!#%#$%@#$%@#%abc
*/

