#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
#include "../../../helper_functions.h"

int get_string_array_length(char *arr[]);
void to_lower1(char s[]);
char *to_lower2(char *s);
char *to_lower3(char s[]);

int main() {
    printf("Length of array of strings\n");
    char *arr[] = {"A", "B", "C"};
    int len1 = sizeof(arr)/sizeof(char *);
    print_variable(len1);
    int len2 = get_string_array_length(arr);
    print_variable(len2);
    putchar('\n');


    printf("Convert string to lowercase using array of char\n");
    char s1[] = "Hello";

    /* ok */
    // for (int i=0; s1[i]; i++) {
    //     s1[i] = tolower(s1[i]);
    // }
    // print_string(s1);

    /* ok */
    for (char *p=s1; *p; p++) {
        *p = tolower(*p);
    }
    print_string(s1);

    /* ok */
    // to_lower1(s1); /* can't apply functions that returns pointer because s1 is array */
    // print_string(s1);

    /* ok */
    // char *t1 = to_lower3(s1);
    // print_string(t1);

    putchar('\n');


    printf("Convert string to lowercase using pointer\n");
    char *s2 = "Hello";
    /* segmentation fault */
    // for (int i=0; s2[i]; i++) {
    //     s2[i] = tolower(s2[i]);
    // }
    // print_string(s2);

    /* segmentation fault */
    for (char *p=s2; *p; p++) {
        *p = tolower(*p);
    }
    print_string(s2);
    
    /* segmentation fault */
    // s2 = to_lower2(s2);
    // print_string(s2);

    /* ok */
    // char *t2 = to_lower3(s2);
    // print_string(t2);

}

/*
$ gcc chapter6/6.5/exercise_6-3/questions.c helper_functions.c -o chapter6/6.5/exercise_6-3/questions.out

$ chapter6/6.5/exercise_6-3/questions.out
Length of array of strings
len1 = 3
len2 = 1

Convert string to lowercase using array of char
s1 = hello

Convert string to lowercase using pointer
Segmentation fault (core dumped)
*/

/* 
Notes
https://stackoverflow.com/questions/2661766/how-do-i-lowercase-a-string-in-c
*/

int get_string_array_length(char *arr[]) {
    return sizeof(arr)/sizeof(char *);
}

void to_lower1(char s[]) {
    for (int i=0; s[i]; i++) {
        s[i] = tolower(s[i]);
    }
}

char *to_lower2(char *s) {
    for (char *p=s; *p; p++) {
        *p = tolower(*p);
    }
    return s;
}

char *to_lower3(char s[]) {
    char *t;
    int i;
    for (i=0; s[i]; i++) {
        *t++ = tolower(s[i]);
    }
    for (; i>0; i--) { /* reverse the traversal to point to start of t */
        t--;
    }
    return t;
}