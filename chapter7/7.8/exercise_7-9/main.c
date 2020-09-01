/*
Exercise 7-9. Functions like isupper can be implemented to save space or to save time. Explore both possibilities.

https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_7:Exercise_9
https://stackoverflow.com/questions/2169261/c-isupper-function
https://en.wikipedia.org/wiki/Space%E2%80%93time_tradeoff
*/
#include <stdio.h>
#include <string.h>
#include "../../../helper_functions.h"

int isupper1(char c);
int isupper2(char c);

int main() {
    char c = 'a';
    print_variable(isupper1(c));
    print_variable(isupper2(c));
    return 0;
}

/*
$ gcc chapter7/7.8/exercise_7-9/main.c helper_functions.c -o chapter7/7.8/exercise_7-9/result.out

$ chapter7/7.8/exercise_7-9/result.out
*/

/* isupper1: save space */
int isupper1(char c) {
    return (c >= 'A') && (c <= 'Z');
}

/* isupper2: save time? */
int isupper2(char c) {
    return (strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", c) != NULL);
}