/* 
Exercise 4-7. Write a routine ungets(s) that will push back an entire string onto the input. Should ungets know about buf and bufp, or should it just use ungetch?
*/

#include <stdio.h>
#include<string.h>

#define BUFSIZE 100
#define MAXLINE 100

char buf[BUFSIZE];
int bufp = 0; /* next free position in buf */

int getch(void);
void ungetch(int c);
void ungets(char s[]);
int getline(char s[], int lim);

main() {
    int c;
    char s[MAXLINE];

    getline(s, MAXLINE); /* read line into string s */
    ungets(s); /* put string into buffer */
    while ((c=getch()) != EOF) { /* read character from buffer one by one */
        putchar(c);
    }
}

int getch(void) { /* get character from buffer */
    return (bufp > 0)? buf[--bufp]: getchar();
}

void ungetch(int c) { /* push character into buffer */
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    }
    else {
        buf[bufp++] = c;
    }
}

void ungets(char s[]) { /* push string into buffer */
    int l = strlen(s)-1;

    while (l >= 0) {
        ungetch(s[l--]);
    }
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