/*
Exercise 5-15. Add the option -f to fold upper and lower case together, so that case distinctions are not made during sorting; for example, a and A compare equal.
*/

#include <stdio.h>
#include <string.h>
#include "../helper_functions.h"

#define MAXLINES 5000
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
$ ./result.out
a
A
A
a
$ ./result.out -f
a
A
a
A
$ ./result.out -r
A
a
a
A
$ ./result.out -r -f
A
a
A
a
*/

void parse_arg(int argc, char *argv[], int *n, int *r, int *f) {
    int i = 0;

    while (++i < argc) {
        if (strcmp(argv[i], "-n") == 0) {
            *n = 1;
        }
        if (strcmp(argv[i], "-r") == 0) {
            *r = 1;
        }
        if (strcmp(argv[i], "-f") == 0) {
            *f = 1;
        }
    }
}

void qsort1(void *v[], int left, int right, int (*comp)(void *, void *), int r) {
    int i, last;

    if (left >= right) {
        return;
    }
    swap_pointer_version(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if (r? (*comp)(v[i], v[left]) > 0: (*comp)(v[i], v[left])< 0) {
            swap_pointer_version(v, ++last, i);
        }
    }
    swap_pointer_version(v, left, last);
    qsort1(v, left, last-1, comp, r);
    qsort1(v, last+1, right, comp, r);
}

#include <stdlib.h>

/* numcmp: compare s1 and s2 numerically */

int numcmp(char *s1, char *s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) {
        return -1;
    }
    else if (v1 > v2) {
        return 1;
    }
    else {
        return 0;
    }
}

#include <ctype.h>

/* caseless_strcmp: compare s1 and s2 in case-insensitive manner */
int caseless_strcmp(char *s1, char *s2) {
    for (; tolower(*s1) == tolower(*s2); s1++, s2++) {
        if (*s1 == '\0') {
            return 0;
        }
    }
    return *s1 - *s2;
}

#define MAXLEN 1000 /* max length of any input line */

/* readlines: read input lines and store in array of pointers*/
int readlines(char *lineptr[], int maxlines) {
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
