#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool validateInputNo(int count);
bool validateNoAlpha(string arg);
string get_cipher(string plain, int key);
char encrypt(char letter, int key);

int main(int argc, string argv[])
{
    if (!validateInputNo(argc) || !validateNoAlpha(argv[1]))
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    int key = atoi(argv[1]);
    string plain = get_string("plaintext:  ");
    string cipher = get_cipher(plain, key);
    printf("ciphertext: %s\n", cipher);

}

bool validateInputNo(int count)
{
    if (count < 2 || count > 2)
    {
        return false;
    }
    return true;
}

bool validateNoAlpha(string arg)
{
    for (int i = 0, n = strlen(arg); i < n; i++)
    {
        if (isalpha(arg[i]))
        {
            return false;
        }
    }
    return true;
}

char encrypt(char letter, int key)
{
    // if it's anything that's not alphabetic like - or space or digits (do not encrypt)
    if (toupper(letter) < 'A' || toupper(letter) > 'Z')
    {
        return letter;
    }

    char start = (letter == toupper(letter) ? 'A' : 'a');
    int order = (letter - start + key) % 26;
    return (order + start);
}

string get_cipher(string plain, int key)
{
    string cipher = plain;
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        cipher[i] = encrypt(plain[i], key);
    }
    return cipher;
}