/*
Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations like a-z in the string s1 into the equivalent
complete list abc...xyz in s2. Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and
a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.
*/
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

bool isletter(char s) {
    return (s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z');
}

bool isdigit(char s) {
    return (s >= '0' && s <= '9');
}

void expand(char s1[], char s2[]) {
    int i, j;
    for (i=j=0; i < strlen(s1); i++) {
        if (s1[i] == '-') {
            if (i == 0 || i == strlen(s1) - 1) {
                s2[j++] = s1[i];
            }
            else if (s1[i+1] >= s1[i-1] && 
                        (isletter(s1[i+1]) && isletter(s1[i-1])) ||
                        (isdigit(s1[i+1]) && isdigit(s1[i-1]))
                    ) {
                char c = s1[i-1] + 1;
                while (c <= s1[i+1]) {
                    s2[j++] = c++;
                }
                i += 1;
            }
            else {
                s2[j++] = s1[i];
            }
        }
        else {
            s2[j++] = s1[i];
        }
    }
    s2[j] = '\0';
}

int get_input(char s[], int lim) {
    int i,c;

    for(i=0;i<lim-1 && (c=getchar())!=EOF;i++) {
        s[i]=c;
    }

    s[i]='\0';
}

int main() {
    char s1[MAXLINE], s2[MAXLINE];
    get_input(s1, MAXLINE);
    expand(s1, s2);
    printf("%s", s2);

    return 0;
}

/*
-hello a-b-c world a-z0-9 -a-z 3-7 P-Y
-hello abc world abcdefghijklmnopqrstuvwxyz0123456789 -abcdefghijklmnopqrstuvwxyz 34567 PQRSTUVWXY
*/
