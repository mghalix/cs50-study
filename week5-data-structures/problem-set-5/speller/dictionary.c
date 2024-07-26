// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * LENGTH + 26;
int words_no = 0;

// Hash table
node *table[N];

bool insert_node(const char *word)
{
    int hashed = hash(word);

    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        return false;
    }

    strcpy(new_node->word, word);
    new_node->next = table[hashed];
    table[hashed] = new_node;

    return true;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashed = hash(word);
    node *cursor = table[hashed];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

int asciiOf(const char *word)
{
    int sum = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        sum += (toupper(word[i]) - 'A');
    }

    return sum;
}
// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return (toupper(word[0]) - 'A') + asciiOf(word);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) == 1)
    {
        if (!insert_node(word))
        {
            fclose(file);
            return false;
        }

        ++words_no;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words_no;
}

void unloader(node *root)
{
    if (root == NULL)
    {
        return;
    }

    unloader(root->next);
    free(root);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        unloader(table[i]);
    }

    return true;
}
