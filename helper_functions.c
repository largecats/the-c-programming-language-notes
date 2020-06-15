#include <stdio.h>
#include <string.h>
#include "helper_functions.h"
/* test */

void print_string(char s[]) {
    printf("%s\n", s);
}

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
        printf("%.2f, ", arr[i++]);
    }
    printf("]\n");
}

void swap(char s[], int i, int j) {
    int temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void swap_pointer(char *v[], int i, int j) {
    char *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// #define BUFSIZE 100

// char buf[BUFSIZE];
// int bufp = 0; /* next free position in buf */

// int getch(void) { /* get character from buffer */
//     return (bufp > 0)? buf[--bufp]: getchar(); /* get from last occupied position in buf */
// }

// void ungetch(int c) { /* push character back to buffer */
//     if (bufp >= BUFSIZE) {
//         printf("ungetch: too many characters\n");
//     }
//     else {
//         buf[bufp++] = c;
//     }
// }

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

// int getline(char s[], int lim) {
//     int c, i;

//     i = 0;
//     while (i<lim-1 && (c=getchar())!=EOF && c!='\n') {
//         s[i] = c;
//         i++;
//     }
//     if (c == '\n') {
//         s[i] = c;
//         i++;
//     }
//     s[i] = '\0';
//     return i;
// }

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