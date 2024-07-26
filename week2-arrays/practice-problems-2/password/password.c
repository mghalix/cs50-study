// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool valid(string password);
bool isSymbol(char letter, string target);
bool constraint(bool a, bool b, bool c);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool hasLower = false;
    bool hasUpper = false;
    bool hasSymbol = false;
    string pattern = "!@#$";
    for (int i = 0, n = strlen(password); !constraint(hasLower, hasUpper, hasSymbol) && i < n; i++) {
        if (isSymbol(password[i], pattern)) {
            hasSymbol = true;
            continue;
        }
        if (!hasUpper && password[i] == toupper(password[i])) {
            hasUpper = true;
            continue;
        }
        hasLower = true;
    }
    return constraint(hasLower, hasUpper, hasSymbol);
}

bool constraint(bool a, bool b, bool c) {
    return (a && b && c);
}

bool isSymbol(char letter, string pattern) {
    for (int i = 0, n = strlen(pattern); i < n; i++) {
        if (letter == pattern[i])
            return true;
    }
    return false;
}