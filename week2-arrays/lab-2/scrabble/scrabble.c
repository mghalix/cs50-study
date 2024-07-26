#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };

int compute_score(string word);
string winner(int score1, int score2);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    printf("%s\n", winner(score1, score2));
}

int compute_score(string word)
{
    int score = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (tolower(word[i]) < 'a' || tolower(word[i]) > 'z')
        {
            continue;
        }
        score += POINTS[tolower(word[i]) - 'a'];
    }
    return score;
}

string winner(int score1, int score2)
{
    if (score1 == score2)
    {
        return "Tie!";
    }
    return (score1 > score2 ? "Player 1 wins!" : "Player 2 wins!");
}