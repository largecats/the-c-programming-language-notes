/*
Exercise 5-9. Rewrite the routines day_of_year and month_day with pointers instead of indexing.
*/

#include <stdio.h>
#include "../../../helper_functions.h"

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main() {
    int m, d;
    print_variable(day_of_year(1988, 3, 1));
    month_day(1988, 60, &m, &d); /* p109: "Since the operator & produces the address of a variable, &a is a pointer to a" by definition. */
    print_variable(m);
    print_variable(d);
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
    int leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    char *months = daytab[leap];
    while (++months - daytab[leap] < month) {
        day += *months;
    }
    return day;
}

/* month day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    char *months = daytab[leap];
    while (yearday > *++months) {
        yearday -= *months;
    }
    *pmonth = months - daytab[leap];
    *pday = yearday;
}

/*
$ gcc chapter5/5.9/exercise_5-9/main.c helper_functions.c -o chapter5/5.9/exercise_5-9/result.out

$ chapter5/5.9/exercise_5-9/result.out
day_of_year(1988, 3, 1) = 61
m = 2
d = 29
*/