// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void eliminateVowels(string str);

int main(int argc, string argv[])
{
    eliminateVowels(argv[1]);
}

void eliminateVowels(string str)
{
    //                      a ,  e ,  i ,  o
    const char subs[4] = { '6', '3', '1', '0'};
    for (int i = 0, n = strlen(str); i < n; i++) {
        switch (toupper(str[i])) {
        case 'A':
            printf("%c", subs[0]);
            break;
        case 'E':
            printf("%c", subs[1]);
            break;
        case 'I':
            printf("%c", subs[2]);
            break;
        case 'O':
            printf("%c", subs[3]);
            break;
        default:
            printf("%c", str[i]);
        }
    }
    printf("\n");
}