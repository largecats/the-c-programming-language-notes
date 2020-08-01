/*
Exercise 4-13. Write a recursive version of the function reverse(s), which reverses the string s in place.
*/

#include <stdio.h>
#include "../helper_functions.h"
#include <string.h>

void reverse(char s[]);
void reverse_helper(char s[], int start, int end);

int main() {
    char s[] = "hello Neo";

    reverse(s);
    print_string(s);
}

void reverse(char s[]) {
    reverse_helper(s, 0, strlen(s)-1);
}

void reverse_helper(char s[], int start, int end) {
    if (start >= end) {
        ;
    }
    else {
        swap(s, start, end);
        reverse_helper(s, start+1, end-1);
    }
}