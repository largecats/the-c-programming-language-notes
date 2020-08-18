/*
Exercise 2-5. Write the function any(s1,s2), which returns the first location in a string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2. (The standard library function strpbrk does the same job but returns a pointer to the location.)
*/
#include <stdio.h>
#define MATCHED 1
#define UNMATCHED 0

int any(char s1[], char s2[]) {
    int i, j, matchState;

    matchState = UNMATCHED;
    for (i=0; s1[i] != '\0' && matchState == UNMATCHED; i++) {
        for (j=0; s2[j] != '\0' && matchState == UNMATCHED; j++) {
            if (s2[j] == s1[i]) {
                matchState = MATCHED;
            }
        }
    }
    if (matchState == MATCHED) {
        return i-1;
    }
    else {
        return -1;
    }
}

int main() {
    char s1[] = "hello Neo";
    char s2[] = "Neo";

    printf("%d\n", any(s1, s2));
}

/*
$ gcc chapter2/2.8/exercise_2-5/main.c -o chapter2/2.8/exercise_2-5/result.out

$ chapter2/2.8/exercise_2-5/result.out
1
*/