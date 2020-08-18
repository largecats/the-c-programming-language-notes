/*
Exercise 5-17. Add a field-searching capability, so sorting may bee done on fields within lines, each field sorted according to
an independent set of options. (The index for this book was sorted with -df for the index category and -n for the page numbers.)
*/

/* index of the book starts from p263 */

/* GNU sort command: https://www.gnu.org/software/coreutils/manual/html_node/sort-invocation.html */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../helper_functions.h"
#include "extern.h"

char *lineptr[MAXLINES];
int fields[MAXFIELDS][2]; // 2D array to store the start and end of each field
int fieldArgs[MAXFIELDS][4]; // 2D array to store arguments for each field, in the order -n -r -f -d
int n = 0, r = 0, f = 0, d = 0; // numeric, reverse, fold, directory
int fieldStart = 0, fieldEnd = 0;

void parse_args(int argc, char *argv[], int fields[MAXFIELDS][2], int fieldArgs[MAXFIELDS][4]);
void update_args(int *n, int *r, int *f, int *d, int *fieldStart, int *fieldEnd, int fields[2], int fieldArgs[4]);
void sort_lines(int left, int right);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);


int main(int argc, char *argv[]) {
    int nlines; /* number of input lines read */
    parse_args(argc, argv, fields, fieldArgs);
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        int i = 0;
        print_variable(fields[i][0]);
        while (fields[i][0] != (-1)) {
            update_args(&n, &r, &f, &d, &fieldStart, &fieldEnd, fields[i], fieldArgs[i]);
            sort_lines(0, nlines-1);
            i++;
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
$ gcc chapter5/5.11/exercise_5-17/main.c chapter5/5.11/exercise_5-17/parse_args.c chapter5/5.11/exercise_5-17/io.c chapter5/5.11/exercise_5-17/sort.c helper_functions.c -o chapter5/5.11/exercise_5-17/result.out

chapter5/5.11/exercise_5-17/result.out -k 0,2 -n -k 3,5 -r
123abc
234bcd
123bcd

234bcd
123bcd
123abc

This is because qsort is not a stable sorting algorithm, the order of the first two lines sorted by the first field 
changed when sorting by the second field.

When using the stable bubble_sort, the output is correct:

chapter5/5.11/exercise_5-17/result.out -k 0,2 -n -k 3,5 -r
123abc
234bcd
123bcd

123bcd
234bcd
123abc
*/


