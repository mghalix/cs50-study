#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int len = strlen(input), num = 0;
    // TODO
    if (len - 1 < 0)
    {
        return 0;
    }
    num = (input[len - 1] - '0');
    input[len - 1] = '\0';
    return 10 * convert(input) + num;
}