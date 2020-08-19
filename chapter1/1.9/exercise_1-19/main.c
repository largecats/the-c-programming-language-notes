/*
Exercise 1-19. Write a function reverse(s) that reverses the character string s. Use it to write a program that reverses its
input a line at a time.
*/

#include <stdio.h>
#include "../../../helper_functions.h"

#define MAXLINE 100 // maximum line length to print

void reverse(char line[]);

int main()
{
    int len;
    char line[MAXLINE];

    while ((len = getline1(line, MAXLINE)) > 0) {
        if (len > 0) {
            reverse(line);
            printf("%s\n", line);
        }
    }
    return 0;
}

/*
$ gcc chapter1/1.9/exercise_1-19/main.c helper_functions.c -o chapter1/1.9/exercise_1-19/result.out

$ chapter1/1.9/exercise_1-19/result.out
hello Neo
oeN olleh

follow the white rabbit
tibbar etihw eht wollof
*/


void reverse(char s[]) {
    int len;

    for (len=0; s[len] != '\n' && s[len] != '\0'; len++) {
        ;
    }
    len--; // ignore \n at the end
    for (int i=0; i<len-i; i++) {
        char temp = s[len-i];
        s[len-i] = s[i];
        s[i] = temp;
    }
    s[len+1] = '\n';
    s[len+2] = '\0';
}