/*
Exercise 2-2. Write a loop equivalent to the for loop above without using && or ||.
*/

#include <stdio.h>
#define MAXLINE 100 // maximum line length to print

int getline(char line[], int lim);

main() {
    int len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        printf("%s", line);
    }

}

int getline(char s[], int lim) {
    int c, i;

    i = 0;
    while ((i<lim-1) == ((c=getchar())!=EOF) == (c!='\n') == 1) {
        /* check if all expression evaluate to 1*/
        s[i] = c;
        i++;
    }
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}