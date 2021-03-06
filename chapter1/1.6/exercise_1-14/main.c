/*
Exercise 1-14. Write a program to print a histogram of the frequencies of 
different characters in its input.
*/

#include <stdio.h>

int main()
{
    int c, chars[128];

    for (int i = 0; i < 128; i++) {
        chars[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        chars[c]++;
    }
    printf("\n");
    for (int i = 0; i < 128; i++) {
        if (chars[i] > 0) {
            if (i == '\n') {
                printf("\\n");
            }
            else if (i == '\t') {
                printf("\\t");
            }
            else {
                printf("%c ", i);
            }
            for (int j = 0; j < chars[i]; j++) {
                printf("-");
            }
            printf("\n");
        }
    }
}

/*
$ gcc chapter1/1.6/exercise_1-14/main.c -o chapter1/1.6/exercise_1-14/result.out

$ chapter1/1.6/exercise_1-14/result.out
hello Neo
knock knock
follow the white rabbit

\n---
  -----
N -
a -
b --
c --
e ----
f -
h ---
i --
k ----
l ----
n --
o ------
r -
t ---
w --
*/