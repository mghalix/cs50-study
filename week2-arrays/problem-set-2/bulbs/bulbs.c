#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

const int BITS_IN_BYTE = 8;

int charBinary[BITS_IN_BYTE];
void print_bulb(int bit);
void binary(int decimal);
void run(string word);
void reset();

int main(void)
{
    run(get_string("Message: "));
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

void run(string word)
{
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        binary((int)word[i]);
        for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
            print_bulb(charBinary[j]);
        }
        reset();
        printf("\n");
    }
}
void reset()
{
    for (int i = 0; i < BITS_IN_BYTE; i++)
    {
        charBinary[i] = 0;
    }
}

void binary(int decimal)
{
    for (int i = 0; decimal > 0; i++)
    {
        charBinary[i] = decimal % 2;
        decimal /= 2;
    }
}