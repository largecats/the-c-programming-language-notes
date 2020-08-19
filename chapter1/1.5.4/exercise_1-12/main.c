/*
Exercise 1-12. Write a program that prints its input one word per line.
*/

#include <stdio.h>

int main()
{
    int c;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            printf("\n");
        }
        else {
            putchar(c);
        }
    }
}

/*
$ gcc chapter1/1.5.4/exercise_1-12/main.c -o chapter1/1.5.4/exercise_1-12/result.out

$ chapter1/1.5.4/exercise_1-12/result.out
hello Neo knock knock follow the white rabbit
hello
Neo
knock
knock
follow
the
white
rabbit
*/