#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../../helper_functions.h"
#include "extern.h"

void qsort1(void *lineptr[], int left, int right, int (*comp)(void *, void *));
void bubble_sort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *s1, char *s2);
int custom_cmp(char *s1, char *s2); /* case-insensitive strcmp */
int custom_strcmp(char *s1, char *s2);
void get_substring(char *from, char *to, int start, int end);

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
