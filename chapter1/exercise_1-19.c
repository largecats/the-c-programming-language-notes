/*
Exercise 1-19. Write a function reverse(s) that reverses the character string s. Use it to write a program that reverses its
input a line at a time.
*/

#include <stdio.h>
#define MAXLINE 100 // maximum line length to print

int getline(char line[], int lim);
void reverse(char line[]);

main()
{
    int len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > 0) {
            printf("%s\n", line);
            reverse(line);
            printf("%s\n", line);
        }
    }
    return 0;
}

int getline(char s[], int lim) {
    int c, i;

    i = 0;
    while (i<lim-1 && (c=getchar())!=EOF && c!='\n') {
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

/*
hello Neo
oeN olleh
follow the rabbit
tibbar eht wollof
*/
