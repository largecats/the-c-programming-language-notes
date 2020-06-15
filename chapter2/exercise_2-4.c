/*
Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes each character in s1 that matches any character in the string s2.
*/
#include <stdio.h>
#define MATCHED 1
#define UNMATCHED 0

void squeeze(char s1[], char s2[]) {
    int i, j, k;
    int matchState;

    k = 0;
    for (i=0; s1[i] != '\0'; i++) {
        matchState = UNMATCHED;
        for (j=0; s2[j] != '\0' && matchState == UNMATCHED;j++) {
            if (s1[i] == s2[j]) {
                matchState = MATCHED;
            }
        }
        if (matchState == UNMATCHED) {
            s1[k++] = s1[i];
        }
    }
    s1[k] = '\0';
}

main() {
    char s1[] = "hello Neo";
    char s2[] = "aeiou";

    squeeze(s1, s2);

    printf("%s\n", s1);
    printf("%s", s2);
}