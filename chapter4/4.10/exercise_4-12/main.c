/*
Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa; that is, convert an integer into a string by calling a recursive routine.
*/

#include <stdio.h>
#include "../../../helper_functions.h"

void itoa(int n, char s[]);

int main() {
    char s[100] = {'\0'};

    itoa(123045, s);
    print_string(s);
}

/*
$ gcc chapter4/4.10/exercise_4-12/main.c helper_functions.c -o chapter4/4.10/exercise_4-12/result.out

$ chapter4/4.10/exercise_4-12/result.out
s = 123045
*/

void itoa(int n, char s[]) {
    static int i = 0;
    
    if (n < 0) {
        n = -n;
        s[i] = '-';
    }

    if (n / 10) {
        itoa(n/10, s);
    }
    s[i++] = (n % 10 + '0');
}