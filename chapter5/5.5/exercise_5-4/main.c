/*
Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s, and zero otherwise.
*/

#include <stdio.h>
#include <string.h>
#include "../../../helper_functions.h"

int strend(char *s, char *t);

int main() {
    char s[] = "hello Neo";
    char t1[] = "Neo";
    printf("%d\n", strend(s, t1));
    char t2[] = "hello";
    printf("%d\n", strend(s, t2));
}

/*
$ gcc chapter5/5.5/exercise_5-4/main.c helper_functions.c -o chapter5/5.5/exercise_5-4/result.out

$ chapter5/5.5/exercise_5-4/result.out
1
0
*/

int strend(char *s, char *t) {
    while (*s != '\0') { /* find end of s */
        s++;
    }
    s -= strlen(t);
    while (*s++ == *t++) {
        if (*t == '\0') { /* t is fully matched */
            return 1;
        }
    }
    return 0;
}