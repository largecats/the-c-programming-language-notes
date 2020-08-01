/*
Exercise 1-8. Write a program to count blanks, tabs, and newlines.
*/

#include <stdio.h>

main()
{
    int c, count;

    count = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            count++;
        }
    }
    printf("count = %d", count);
}