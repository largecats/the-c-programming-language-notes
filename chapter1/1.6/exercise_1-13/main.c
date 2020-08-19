/*
Exercise 1-13. Write a program to print a histogram of the lengths of words in its input. 
It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging.
*/

#include <stdio.h>

// horizontal
int main()
{
    int c;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            printf("\n");
        }
        else {
            printf("-");
        }
    }
    putchar('\n');
}

/*
$ gcc chapter1/1.6/exercise_1-13/main.c -o chapter1/1.6/exercise_1-13/result.out

$ chapter1/1.6/exercise_1-13/result.out
hello Neo knock knock follow the white rabbit
-----
---
-----
-----
------
---
-----
-------
*/