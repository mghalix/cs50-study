#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_pyramid(int);
int main(void)
{
    int n = get_height();
    print_pyramid(n);
}

// ------------------------------------------------------------
int get_height(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}
// ------------------------------------------------------------
void print_pyramid(int h)
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < h - i - 1; j++)
        {
            printf(" ");
        }

        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        for (int j = 0; j < 2; j++)
        {
            printf(" ");
        }

        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
// ------------------------------------------------------------