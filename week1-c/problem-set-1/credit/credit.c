#include <cs50.h>
#include <stdio.h>
#include <math.h>

int digit_sum(int);
bool validate_number(long);
string get_type(void);
string get_name(long);
int first, second, length = 0;
int main(void)
{
    long n = get_long("Number: ");
    printf("%s\n", get_name(n));
}
// ------------------------------------------------------------------
int digit_sum(int n)
{
    if (n == 0)
    {
        return 0;
    }
    return (n % 10) + digit_sum(n / 10);
}
// ------------------------------------------------------------------
bool validate_number(long number)
{
    int sum_of_product = 0;
    int sum_of_non_product = 0;
    const long original = number;

    while (number > 0)
    {
        sum_of_product += digit_sum((number % 100 / 10 * 2));
        sum_of_non_product += number % 10;
        if (number / 10 != 0)
        {
            length += 2;
        }
        else
        {
            length += 1;
        }
        number /= 100;
    }

    first = (original / pow(10, length - 1));
    second = ((original / (long)pow(10, length - 2)) % 10);

    if (length < 13 || (length == 16 && (first != 4 && second > 5)) || (length == 15 && first == 3 && (second != 4 && second != 7)))
    {
        return false;
    }
    return ((sum_of_product + sum_of_non_product) % 10 == 0);
}
// ------------------------------------------------------------------
string get_type()
{
    if (length == 15)
    {
        return "AMEX";
    }
    // first variable to differenciate between visa and mastercard when there number have same length
    if (length == 16 && first != 4) // aka visa always start with 4
    {
        return "MASTERCARD";
    }
    return "VISA";
}
// ------------------------------------------------------------------
string get_name(long number)
{
    if (!validate_number(number))
    {
        return "INVALID";
    }
    return get_type();
}
// ------------------------------------------------------------------