/*
Exercise 1-18. Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines.
*/

#include <stdio.h>
#define MAXLINE 100 // maximum line length to print

int getline(char line[], int lim);
int remove_trailing_blanks(char line[]);
void print_with_visible_blanks(char line[]); // so that it's clear that the trailing blanks are removed

main()
{
    int len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        printf("original line: \n");
        print_with_visible_blanks(line);
        if (remove_trailing_blanks(line) > 0) {
            printf("cleaned up line: \n");
            print_with_visible_blanks(line);
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

int remove_trailing_blanks(char s[]) {
    int i;
    for (i=0; s[i] != '\n'; i++) {// get length of s
        ;
    }
    i--; // ignore the \n at the end
    for (i=i; i>=0 && (s[i] == '\t' || s[i] == ' '); i--) {// remove trailing blanks
        ;
    }
    i++;
    s[i] = '\n';
    i++;
    s[i] = '\0'; // mark the end of character array
    return i;
}

void print_with_visible_blanks(char line[]) {
    for (int i=0; line[i] != '\n'; i++) {
        if (line[i] == '\t') {
            printf("\\t");
        }
        else if (line[i] == ' ') {
            printf("\\s");
        }
        else if (line[i] == '\n') {
            printf("\\n");
        }
        else {
            putchar(line[i]);
        }
    }
    putchar('\n');
}

/*
hello Neo
original line:   
hello\sNeo       
cleaned up line: 
hello\sNeo       
knock knock   
original line:    
knock\sknock\s\s\s
cleaned up line:  
knock\sknock      
follow the white rabbit
original line: 
follow\sthe\swhite\srabbit\t\t
cleaned up line:
follow\sthe\swhite\srabbit
*/