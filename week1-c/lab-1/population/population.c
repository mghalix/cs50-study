#include <stdio.h>
#include <cs50.h>

int get_start(void);
int get_end(int start);
int get_years(int start, int end);

int main(void)
{
    // starting lamas
    int start = get_start();
    // end lamas
    int end = get_end(start);
    // how long it's going to take for starting lamas number to reach end lamas population
    printf("Years: %i\n", get_years(start, end));
}
// ---------------------------------------------------------------
int get_start(void)
{
    int n;

    do
    {
        n = get_int("Start size: ");
    }
    while (n < 9);

    return n;
}
// ---------------------------------------------------------------
int get_end(int start)
{
    int n;

    do
    {
        n = get_int("End size: ");
    }
    while (n < start);

    return n;
}
// ---------------------------------------------------------------
int get_years(int start, int end)
{
    int years = 0;

    while (start < end)
    {
        start += (start / 3) - (start / 4);
        years++;
    }

    return years;
}
// ---------------------------------------------------------------
