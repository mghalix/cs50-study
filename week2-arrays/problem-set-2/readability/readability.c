#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void sentence(string input);
bool isSentence(char c);
float L, S;

int main(void)
{
    string input = get_string("Text: ");
    sentence(input);
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = (int) round(index);
    if (grade < 0)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    if (grade >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    printf("Grade %i\n", grade);
}

bool isSentence(char c)
{
    return (c == '!' || c == '.' || c == '?');
}
void sentence(string input)
{
    int letters, sentences, words;
    letters = sentences = words = 0;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (isSentence(input[i]))
        {
            ++sentences;
            continue;
        }
        if (input[i] == ' ')
        {
            ++words;
            continue;
        }
        if (isalpha(input[i]))
        {
            ++letters;
        }
    }
    words += 1;
    L = (letters / (float)words * 100.0);
    S = (sentences / (float)words * 100.0);
}