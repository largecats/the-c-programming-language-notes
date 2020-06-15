/*
Exercise 1-9. Write a program to copy its input to its output, 
replacing each string of one or more blanks by a single blank.
*/

#include <stdio.h>

main()
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