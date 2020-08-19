/*
Exercise 1.15. Exercise 1-16. Revise the main routine of the longest-line program so it will correctly print the length of arbitrary long input lines, and as much as possible of the text.
*/

#include <stdio.h>
#define MAXLINE 10

int getline1(char line[], int lim);
void copy(char to[], char from[]);

int main()
{
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = getline1(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0) {
        printf("Length of the longest line is: %d\n", max);
        printf("The longest line is: %s\n", longest);
    }
    return 0;
}

/*
$ gcc chapter1/1.9/exercise_1-16/main.c -o chapter1/1.9/exercise_1-16/result.out

$ chapter1/1.9/exercise_1-16/result.out
knock knock
hello Neo
follow the white rabbit
Length of the longest line is: 23
The longest line is: follow th
*/

int getline1(char s[], int lim) {
    int c, i, j;
    
    j = 0; // j is the counter for reading the line into s
    for (i = 0; (c=getchar())!=EOF && c!='\n'; i++) { // i is the counter for the length of the line
        // s[i] = c;
        if (j < lim-1) {
            s[j] = c;
            j++; // only increment j when s is still being filled
        }
    }
    if (c == '\n') {
        if (i < lim-1) {
            s[j] = c;
            j++; // count the trailing \n into line length
        }
    }
    s[j] = '\0'; // use null to mark the end of string
    return i;
}

void copy(char to[], char from[]) {
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0') {
        i++;
    }
}