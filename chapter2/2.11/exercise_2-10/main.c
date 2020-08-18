/*
Exercise 2-10. Rewrite the function lower, which converts upper case letters to lower case, with a conditional expression instead of if-else.
*/

#include <stdio.h>

int lower(int c) {
    return (c>='A' && c<='Z') ? c + 'a'-'A': c;
}

int main() {
    printf("%c\n", lower('A'));
    return 0;
}

/*
$ gcc chapter2/2.11/exercise_2-10/main.c -o chapter2/2.11/exercise_2-10/result.out

$ chapter2/2.11/exercise_2-10/result.out
a
*/