/*
Exercise 5-16. Add the -d ("directory order") option, which makes comparisons only on letters, numbers and blanks. Make sure it works in conjunction with -f.
*/

#include <stdio.h>
#include <string.h>
#include "../helper_functions.h"

#define MAXLINES 5000
char *lineptr[MAXLINES];
int n = 0, r = 0, f = 0, d = 0;

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort1(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *s1, char *s2);
int custom_cmp(char *s1, char *s2); /* case-insensitive strcmp */
void parse_arg(int argc, char *argv[], int *n, int *r, int *f, int *d);

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
$ ./result.out -d
!$#!@#$!2345
!#$!@#$$1234
!#$!@#$$1234
!$#!@#$!2345
$ ./result.out -d
!@#2345
!$%!#^@#$%@1234
!$%!#^@#$%@1234
!@#2345
$ ./result.out -d
!@$#!@#$ABC
!#$%#@$%@^abc
!#$%#@$%@^abc
!@$#!@#$ABC
$ ./result.out -d -f
!$#@#%@#$%ABC
#$!#%#$%@#$%@#%abc
!$#@#%@#$%ABC
#$!#%#$%@#$%@#%abc
*/

void parse_arg(int argc, char *argv[], int *n, int *r, int *f, int *d) {
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
        if (strcmp(argv[i], "-d") == 0) {
            *d = 1;
        }
    }
}

void qsort1(void *v[], int left, int right, int (*comp)(void *, void *)) {
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
    qsort1(v, left, last-1, comp);
    qsort1(v, last+1, right, comp);
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

/* custom_cmp: compare s1 and s2 with customization */
int custom_cmp(char *s1, char *s2) {
    while (*s1 != '\0') {
        char a, b;

        a = f? tolower(*s1): *s1;
        b = f? tolower(*s2): *s2;
        if (d) {
            if (a != ' ' || !isdigit(a) || !isalpha(a)) {
                s1++;
            }
            if (b != ' ' || !isdigit(b) || !isalpha(b)) {
                s2++;
            }
        }
        else {
            if (a == b) {
                s1++;
                s2++;
            }
            else {
                return a - b;
            }
        }
    }
    return 0;
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
