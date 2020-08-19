/*
Exercise 1-9. Write a program to copy its input to its output, 
replacing each string of one or more blanks by a single blank.
*/

#include <stdio.h>

int main()
{
    int c, blankCount;

    blankCount = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            blankCount++;
        }
        else {
            blankCount = 0;
        }
        if (blankCount == 0 || blankCount == 1) {
            putchar(c);
        }
    }
}

/*
$ gcc chapter1/1.5.3/exercise_1-9/main.c -o chapter1/1.5.3/exercise_1-9/result.out

$ chapter1/1.5.3/exercise_1-9/result.out
hello   Neo
hello Neo
follow the  white   rabbit
follow the white rabbit
*/