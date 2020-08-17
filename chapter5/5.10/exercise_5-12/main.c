/*
Exercise 5-12. Extend entab and detab to accept the shorthand
entab -m +n
to mean tab stops every n columns, starting at column m. Choose convenient (for the user) default behavior.
*/

#include <stdio.h>
#include "../../../helper_functions.h"
#include "extern.h"

void parse_arg(int argc, char *argv[], int *mp, int *np);
void detab(int m, int n, char line[]);
void entab(int m, int n, char line[]);

int main(int argc, char *argv[]) {
    char line[MAXLINE]; /* read original input into line */
    int m, n;

    parse_arg(argc, argv, &m, &n);
    getline_pointer_version(line, MAXLINE);

    detab(m, n, line);
    entab(m, n, line);

    putchar('\n');
}

/*
$ gcc chapter5/5.10/exercise_5-12/main.c chapter5/5.10/exercise_5-12/detab.c chapter5/5.10/exercise_5-12/entab.c chapter5/5.10/exercise_5-12/parse_args.c helper_functions.c -o chapter5/5.10/exercise_5-12/result.out

$ chapter5/5.10/exercise_5-12/result.out -10 +8
hello   Neo follow  the    white        rabbit
hello\tNeo\sfollow\s\sthe\s\s\s\swhite\s\s\s\s\s\s\s\srabbit
hello\tNeo\sfollow\s\sthe\t\swhite\trabbit\n

$ chapter5/5.10/exercise_5-12/result.out -10 +8
hello   Neo follow  the    white        rabbit
hello\s\s\sNeo\sfollow\s\sthe\s\s\s\swhite\s\s\s\s\s\s\s\srabbit
hello\s\s\sNeo\sfollow\s\sthe\t\s\s\swhite\trabbit\n
*/