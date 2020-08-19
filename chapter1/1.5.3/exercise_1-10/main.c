/*
Exercise 1-10. Write a program to copy its input to its output, 
replacing each tab by \t, each backspace by \b, and each backslash by \\. 
This makes tabs and backspaces visible in an unambiguous way.
*/

#include <stdio.h>

int main()
{
    int c;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            printf("\\t");
        }
        else if (c == '\b') {
            printf("\\b");
        }
        else if (c == '\\') {
            printf("\\\\");
        }
        else {
            putchar(c);
        }
    }
}

/*
$ gcc chapter1/1.5.3/exercise_1-10/main.c -o chapter1/1.5.3/exercise_1-10/result.out

$ chapter1/1.5.3/exercise_1-10/result.out
hello   Neo
hello\tNeo
comment\n
comment\\n
*/