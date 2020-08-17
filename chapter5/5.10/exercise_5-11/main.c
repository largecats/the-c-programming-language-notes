/*
Exercise 5-11. Modify the program entab and detab (written as exercises in Chapter 1) to accept a list of tab stops as
arguments. Use the default tab settings if there are no arguments.
*/

/*
https://linux.die.net/man/1/tabs
The input is a list of integers representing tab stops. E.g., the default tab setting of every 8 columns starting at position 0
would have the list representation [0, 8, 16, 24, 32, 40]
*/

#include <stdio.h>
#include "../../../helper_functions.h"
#include "extern.h"

void detab(int argc, char *argv[], char line[]);
void entab(int argc, char *argv[], char line[]);

int main(int argc, char *argv[]) {
    char line[MAXLINE]; /* read original input into line */

    getline_pointer_version(line, MAXLINE);

    detab(argc, argv, line);
    entab(argc, argv, line);

    putchar('\n');
}

/*
$ gcc chapter5/5.10/exercise_5-11/main.c chapter5/5.10/exercise_5-11/detab.c chapter5/5.10/exercise_5-11/entab.c helper_functions.c -o chapter5/5.10/exercise_5-11/result.out

$ chapter5/5.10/exercise_5-11/result.out 8 16 32
follow the    white      rabbit
follow\sthe\s\s\s\swhite\s\s\s\s\s\srabbit
follow\sthe\s\s\s\swhite\t\srabbit

$ chapter5/5.10/exercise_5-11/result.out 5 10
white      rabbit
white\s\s\s\s\s\srabbit
white\t\srabbit\n

$ chapter5/5.10/exercise_5-11/result.out 8 16
white      rabbit
white\s\s\s\s\s\srabbit
white\t\s\s\srabbit\n

$ chapter5/5.10/exercise_5-11/result.out 2 4 6 8 10
white   rabbit
white\s\s\srabbit
white\t\trabbit\n

$ chapter5/5.10/exercise_5-11/result.out 3 6 9 12 
hello   Neo follow the    white      rabbit
hello\s\s\sNeo\sfollow\sthe\s\s\s\swhite\s\s\s\s\s\srabbit
hello\t\tNeo\tfollow\sthe\s\s\s\swhite\t\s\s\s\srabbit\n
*/