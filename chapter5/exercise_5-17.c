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
void update_args(int *n, int *r, int *f, int *d, int *fieldStart, int *fieldEnd, int fields[2], int fieldArgs[4]);
int isnumber(char c);
void get_field(char *from, char *start, char *end);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort1(void *lineptr[], int left, int right, int (*comp)(void *, void *));
void bubble_sort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
void sort_lines(int left, int right);
int numcmp(char *s1, char *s2);
int custom_cmp(char *s1, char *s2); /* case-insensitive strcmp */
int custom_strcmp(char *s1, char *s2);
void get_substring(char *from, char *to, int start, int end);

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
chapter5/result.out -k 0,2 -n -k 3,5 -r
123abc
234bcd
123bcd

234bcd
123bcd
123abc

This is because qsort is not a stable sorting algorithm, the order of the first two lines sorted by the first field 
changed when sorting by the second field.

When using the stable bubble_sort, the output is correct:

chapter5/result.out -k 0,2 -n -k 3,5 -r
123abc
234bcd
123bcd

123bcd
234bcd
123abc
*/

void sort_lines(int left, int right) {
    switch (n) {
        case 0:
            switch (f) {
                case 0:
                    // qsort1((void **) lineptr, left, right, (int (*)(void *, void *)) strcmp);
                    bubble_sort((void **) lineptr, left, right, (int (*)(void *, void *)) custom_strcmp);
                    break;
                case 1:
                    // qsort1((void **) lineptr, left, right, (int (*)(void *, void *)) custom_cmp);
                    bubble_sort((void **) lineptr, left, right, (int (*)(void *, void *)) custom_cmp);
                    break;
                default:
                    break;
            };
            break;
        case 1:
            // qsort1((void **) lineptr, left, right, (int (*)(void *, void *)) numcmp);
            bubble_sort((void **) lineptr, left, right, (int (*)(void *, void *)) numcmp);
            break;
        default:
            break;
    }
}

void parse_args(int argc, char *argv[], int fields[MAXFIELDS][2], int fieldArgs[MAXFIELDS][4]) {
    /* parse arguments from command line */
    int i = 0;
    int fieldPtr = 0;
    for (int row=0; row<MAXFIELDS; row++) {
        for (int col=0; col<=2; col++) {
            fields[row][col] = -1;
        }
    }
    fields[0][0] = 0;
    fields[0][1] = MAXLEN;

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

void update_args(int *n, int *r, int *f, int *d, int *fieldStart, int *fieldEnd, int fields[2], int fieldArgs[4]) {
    *n = fieldArgs[0];
    *r = fieldArgs[1];
    *f = fieldArgs[2];
    *d = fieldArgs[3];
    *fieldStart = fields[0];
    *fieldEnd = fields[1];
    print_variable(*n);
    print_variable(*r);
    print_variable(*f);
    print_variable(*d);
    print_variable(*fieldStart);
    print_variable(*fieldEnd);
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

void bubble_sort(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, j;

    for (i=left; i<right; i++) {
        for (j=left; j<right-i; j++) {
            if (r? (*comp)(v[j], v[j+1]) < 0: (*comp)(v[j], v[j+1]) > 0) {
                swap_pointer_version(v, j, j+1);
            }
        }
    }
}

#include <stdlib.h>

void get_substring(char *from, char *to, int start, int end) {
    int i;
    for (i=start; i <= end; i++) {
        to[i-start] = from[i];
    }
    to[i] = '\0';
    print_string(to);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2) {
    double v1, v2;
    int fieldLen = fieldEnd - fieldStart;
    char field1[fieldLen], field2[fieldLen];
    get_substring(s1, field1, fieldStart, fieldEnd);
    get_substring(s2, field2, fieldStart, fieldEnd);

    v1 = atof(field1);
    v2 = atof(field2);
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

int custom_strcmp(char *s1, char *s2) {
    int fieldLen = fieldEnd - fieldStart;
    char field1[fieldLen], field2[fieldLen];
    get_substring(s1, field1, fieldStart, fieldEnd);
    get_substring(s2, field2, fieldStart, fieldEnd);
    return strcmp(field1, field2);
}

#include <ctype.h>

/* custom_cmp: compare s1 and s2 with customization */
int custom_cmp_helper(char *field1, char *field2) {
    while (*field1 != '\0') {
        char a, b;

        a = f? tolower(*field1): *field1;
        b = f? tolower(*field2): *field2;
        if (d) {
            if (a != ' ' || !isdigit(a) || !isalpha(a)) {
                field1++;
            }
            if (b != ' ' || !isdigit(b) || !isalpha(b)) {
                field2++;
            }
        }
        else {
            if (a == b) {
                field1++;
                field2++;
            }
            else {
                return a - b;
            }
        }
    }
    return 0;
}
int custom_cmp(char *s1, char *s2) {
    int fieldLen = fieldEnd - fieldStart;
    char field1[fieldLen], field2[fieldLen];
    get_substring(s1, field1, fieldStart, fieldEnd);
    get_substring(s2, field2, fieldStart, fieldEnd);
    return custom_cmp_helper(field1, field2);
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