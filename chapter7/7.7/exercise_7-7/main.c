/*
Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its input from a set of named files or, if no files are
named as arguments, from the standard input. Should the file name be printed when a matching line is found?
*/

#include <stdio.h>
#include <string.h>
#include "../../../helper_functions.h"

#define MAXFILES 10 // maximum number of files to read

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[]) {
    char line[MAXLINE], *files[MAXFILES], *pattern;
    long lineNum = 0, fileNum = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((argc > 0) && (c = *++(argv[0]))) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                case 'p':
                    argc--;
                    pattern = *(++argv);
                    argv++;
                    argc--;
                    break;
                case 'f':
                    while (--argc > 0 && (*++argv)[0] != '-') { // get file names from argument
                        files[fileNum++] = *argv;
                    }
                    break;
                default:
                    printf("find: illegal options %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
    }
    if (fileNum == 0) { // no file name specified as argument
        // while (getline1(line, MAXLINE) > 0) {
        while (fgets(line, MAXLINE, stdin) != NULL) {
            lineNum++;
            if ((strstr(line, pattern) != NULL) != except) {
                if (number) {
                    printf("%ld:", lineNum);
                }
                printf("%s\n", line);
                found++;
            }
        }
    }
    else {
        char *result;
        int i = 0;
        while (i < fileNum) {
            FILE *fp = fopen(files[i], "r");
            lineNum = 0;
            while ((result = fgets(line, MAXLINE, fp)) != NULL) {
                lineNum++;
                if ((strstr(line, pattern) != NULL) != except) {
                    printf("Found in file %s: \n", files[i]);
                    if (number) {
                        printf("%ld:", lineNum);
                    }
                    printf("%s\n", line);
                    found++;
                }
            }
            i++;
        }
    }
    return found;
}

/*
$ gcc chapter7/7.7/exercise_7-7/main.c helper_functions.c -o chapter7/7.7/exercise_7-7/result.out

$ chapter7/7.7/exercise_7-7/result.out -p "do you read me" -n -f chapter7/7.7/exercise_7-7/hello.txt chapter7/7.7/exercise_7-7/hello1.txt
Found in file chapter7/7.7/exercise_7-7/hello.txt:
3:do you read me
*/
