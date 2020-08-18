/*
Exercise 3-2. Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences like
\n and \t as it copies the string t to s. Use a switch. Write a function for the other direction as well, converting escape
sequences into the real characters.
*/

#include <stdio.h>

#define MAXLINE 1000

void reverse_escape(char s[], char t[]);
void escape(char s[], char t[]);
int get_input(char s[], int lim);

int main() {
    char t[MAXLINE], s[MAXLINE];
    get_input(t, MAXLINE);
    escape(s, t);
    printf("escape:\n");
    printf("%s\n", s);

    char t1[MAXLINE] = "hello\\tworld\\nhello";
    char s1[MAXLINE];
    reverse_escape(s1, t1);
    printf("reverse escape:\n");
    printf("%s\n", s1);

    return 0;
}

/*
$ gcc chapter3/3.4/exercise_3-2/main.c -o chapter3/3.4/exercise_3-2/result.out

$ chapter3/3.4/exercise_3-2/result.out
I remember black skies  The lightening all round me
I remember each flash   As time began to blur
escape:
I remember black skies\tThe lightening all round me\nI remember each flash\tAs time began to blur\n
reverse escape:
hello   world
hello
*/

void reverse_escape(char s[], char t[]) {
    int i, j;
    i = j = 0;
    while (t[i] != '\0') {
        switch (t[i]) {
            case '\\':
                switch (t[i+1]) {
                    case 't': 
                        s[j] = '\t';
                        break;
                    case 'n': 
                        s[j] = '\n';
                        break;
                    default:
                        ;
                        break;
                }
                i++;
                break;
            default: s[j] = t[i];
        }
        j++;
        i++;
    }
}

void escape(char s[], char t[]) {
    int i, j;
    i = j = 0;
    while (t[i] != '\0') {
        switch (t[i]) {
            case '\n': 
                s[j] = '\\';
                j++;
                s[j] = 'n';
                break;
            case '\t':
                s[j] = '\\';
                j++;
                s[j] = 't';
                break;
            default: 
                s[j] = t[i];
                break;
        }
        i++;
        j++;
    }
    s[j] = '\0';
}

int get_input(char s[], int lim) {
    int i,c;

    for(i=0;i<lim-1 && (c=getchar())!=EOF;i++) {
        s[i]=c;
    }

    s[i]='\0';
}