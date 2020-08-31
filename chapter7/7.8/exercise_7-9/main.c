/*
Exercise 7-9. Functions like isupper can be implemented to save space or to save time. Explore both possibilities.
*/
#include <stdio.h>
#include "../../../helper_functions.h"

int isupper1(char c);

int main() {
    char c = 'a';
    print_variable(isupper1(c));
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