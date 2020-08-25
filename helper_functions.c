#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "helper_functions.h"

void print_array(int arr[]) {
    int i;

    i = 0;
    printf("[");
    while (arr[i] != '\0') {
        printf("%d, ", arr[i++]);
    }
    printf("]\n");
}

void print_float_array(double arr[]) {
    int i;

    i = 0;
    printf("[");
    while (arr[i] != '\0') {
        printf("%.3f, ", arr[i++]);
    }
    printf("]\n");
}

void swap(char s[], int i, int j) {
    int temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void swap_pointer_version(char *v[], int i, int j) {
    char *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0; /* next free position in buf */

int getch(void) { /* get character from buffer */
    return (bufp > 0)? buf[--bufp]: getchar(); /* get from last occupied position in buf */
}

void ungetch(int c) { /* push character back to buffer */
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    }
    else {
        buf[bufp++] = c;
    }
}

char *alloc(int n) {
    /* return pointer to the start of n characters block of free space */
    if (allocp + n <= allocbuf + ALLOCSIZE) {
        allocp += n; /* increment pointer to next free position */
        return allocp - n; /* return pointer to the allocated block */
    }
    else { /* not enough room */
        return 0;
    }
}

void afree(char *p) {
    /* free storage space from the address p points to onwards */
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        allocp = p; /* re-assign pointer to next free position */
    }
}

int getline1(char s[], int lim) {
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}

int getline_pointer_version(char *s, int lim) {
    int c;
    char *original_s = s;

    while (lim > 0 && (c=getchar()) != EOF && c != '\n') {
        *s++ = c;
        lim--;
    }
    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';
    return s - original_s;
}

void print_char_with_visible_blanks(char c) {
    if (c == '\t') {
        printf("\\t");
    }
    else if (c == ' ') {
        printf("\\s");
    }
    else if (c == '\n') {
        printf("\\n\n");
    }
    else {
        putchar(c);
    }
}

int string_in_array(char val[], char *arr[], int len, int caseSensitive) {
    int i;
    // int len = sizeof(arr)/sizeof(char *); // doesn't work, always return 1
    for (i = 0; i < len; i++) {
        if (caseSensitive) {
            if (strcmp(val, arr[i]) == 0) {
                return 1;
            }
        }
        else {
            char s1[strlen(val)];
            char s2[strlen(arr[i])];
            to_lower(val, s1);
            to_lower(arr[i], s2);
            // char *s1 = to_lower(val); /* will raise segmentation fault */
            // char *s2 = to_lower(arr[i]);
            if (strcmp(s1, s2) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void to_lower(char s[], char t[]) {
    /* issues with pointers: https://stackoverflow.com/questions/2661766/how-do-i-lowercase-a-string-in-c  */
    int i;
    for (i=0; s[i]; i++) {
        t[i] = tolower(s[i]);
    }
    t[i] = '\0';
}

// char *to_lower(char s[]) {
//     char *t;
//     int i;
//     for (i=0; s[i]; i++) {
//         *t++ = tolower(s[i]);
//     }
//     for (; i>0; i--) { /* reverse the traversal to point to start of t */
//         t--;
//     }
//     return t;
// }

void copy(char s[], char t[]) {
    int i;
    for (i=0; s[i]; i++) {
        t[i] = s[i];
    }
    t[i] = '\0';
}

/* strdup: make a duplicate of s */
char *strdup1 (char *s) {
    char *p;

    p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
    if (p != NULL) { /* if there is space */
        strcpy(p, s);
    }
    return p;
}