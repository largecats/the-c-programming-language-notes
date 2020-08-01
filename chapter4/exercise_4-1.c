/*
Exercise 4-1. Write the function strindex(s,t) which returns the position of the rightmost occurrence of t in s, or -1 if there is none.
*/

#include <stdio.h>
#include <string.h>

int strindex(char s[], char t[]);

int main() {
    char s[] = "knock knock";
    char t[] = "ck";
    printf("%d", strindex(s, t));

    return 0;
}

int strindex(char s[], char t[]) {
    int i, j, k;
    for (i = strlen(s)-1; i>=0; i--) {
        for (j=i, k=strlen(t)-1; k>=0 && t[k] == s[j]; j--, k--) {
            ;
        }
        if (k==-1) {
            return i-strlen(t)+1;
        }
    }
    return -1;
}

/*
9
*/