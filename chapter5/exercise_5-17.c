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
#include "../helper_functions.h"

#define MAXLINES 5000
#define MAXLEN 1000 /* max length of any input line */
#define MAXFIELDS 10
char *lineptr[MAXLINES];
int fields[MAXFIELDS][2]; // 2D array to store the start and end of each field
int fieldArgs[MAXFIELDS][4]; // 2D array to store arguments for each field, in the order -n -r -f -d
int n = 0, r = 0, f = 0, d = 0; // numeric, reverse, fold, directory
int fieldStart = 0, fieldEnd = 0;

void parse_args(int argc, char *argv[], int fields[MAXFIELDS][2], int fieldArgs[MAXFIELDS][4]);
void update_args(int *n, int *r, int *f, int *d, int args[4]);
int isnumber(char c);
void get_field(char *from, char *start, char *end);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort1(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *s1, char *s2);
int custom_cmp(char *s1, char *s2); /* case-insensitive strcmp */

int main(int argc, char *argv[]) {
    int nlines; /* number of input lines read */
    parse_args(argc, argv, fields, fieldArgs);
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        int i = 0;
        print_variable(fields[i][0]);
        while (fields[i][0] != (-1)) {
            fieldStart = fields[i][0];
            fieldEnd = fields[i][1];
            print_variable(fieldStart);
            print_variable(fieldEnd);
            update_args(&n, &r, &f, &d, fieldArgs[i]);
            print_variable(n);
            print_variable(r);
            print_variable(f);
            print_variable(d);
            switch (n) {
                case 0:
                    switch (f) {
                        case 0:
                            qsort1((void **) lineptr, fieldStart, fieldEnd, (int (*)(void *, void *)) strcmp);
                            break;
                        case 1:
                            qsort1((void **) lineptr, fieldStart, fieldEnd, (int (*)(void *, void *)) custom_cmp);
                            break;
                        default:
                            break;
                    };
                    break;
                case 1:
                    qsort1((void **) lineptr, fieldStart, fieldEnd, (int (*)(void *, void *)) numcmp);
                    break;
                default:
                    break;
            }
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

void parse_args(int argc, char *argv[], int fields[MAXFIELDS][2], int fieldArgs[MAXFIELDS][4]) {
    /* parse arguments from command line */
    int i = 0;
    int fieldPtr = -1;
    for (int row=0; row<MAXFIELDS; row++) {
        for (int col=0; col<=2; col++) {
            fields[row][col] = -1;
        }
    }

    while (++i < argc) {
        if (strcmp(argv[i], "-k") == 0) {
            print_string(argv[i]);
            fieldPtr++;
        }
        else {
            print_string(argv[i]);
            if (isnumber(argv[i][0])) {
                char start[MAXLEN];
                char end[MAXLEN];
                get_field(argv[i], start, end);
                fields[fieldPtr][0] = atoi(start);
                fields[fieldPtr][1] = atoi(end);
            }
            else {
                if (strcmp(argv[i], "-n") == 0) {
                    fieldArgs[fieldPtr][0] = 1;
                }
                else if (strcmp(argv[i], "-r") == 0) {
                    fieldArgs[fieldPtr][1] = 1;
                }
                else if (strcmp(argv[i], "-f") == 0) {
                    fieldArgs[fieldPtr][2] = 1;
                }
                else if (strcmp(argv[i], "-d") == 0) {
                    fieldArgs[fieldPtr][3] = 1;
                }
                else {
                    printf("Error: unknown argument");
                }
            }
        }
        // print_variable(i);
        // print_variable(fieldPtr);
    }
}

void update_args(int *n, int *r, int *f, int *d, int args[4]) {
    *n = args[0];
    *r = args[1];
    *f = args[2];
    *d = args[3];
}

int isnumber(char c) {
    char numbers[] = "0123456789";
    return (strchr(numbers, c) != NULL);
}

void get_field(char *from, char *start, char *end) {
    int i = 0;
    int j = 0;
    while (from[i] != ',') {
        start[j++] = from[i++];
    }
    start[j] = '\0';
    i++;
    j = 0;
    while (from[i] != '\0') {
        end[j++] = from[i++];
    }
    end[j] = '\0';
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