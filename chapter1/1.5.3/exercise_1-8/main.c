/*
Exercise 1-8. Write a program to count blanks, tabs, and newlines.
*/

#include <stdio.h>

int main()
{
    int c, count;

    count = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            count++;
        }
    }
    printf("count = %d\n", count);
}

/*
$ gcc chapter1/1.5.3/exercise_1-8/main.c -o chapter1/1.5.3/exercise_1-8/result.out

$ chapter1/1.5.3/exercise_1-8/result.out
hello   Neo // 1 \t, 1 \n
follow the white rabbit // 3 \s, 1\n
knock  knock // 2 \s, 1\n
count = 9
*/