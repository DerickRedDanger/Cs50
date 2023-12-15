// Implements a dictionary's functionality

#include <cs50.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

void recursionfree(node *node) // created to make unload easier
{
    // Handle base case
    if (node->next == NULL)
    {
        free(node);
    }
    // Free nodes recursively
    else
    {
        recursionfree(node->next);
        // Free node
        free(node);
    }
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int position = hash(word);
    //node *temp = malloc(sizeof(node)); // mallocing for a temp variable to find the word
    if (table[position]->next == NULL)
    {
        return false;
    }
    node *temp;
    temp = table[position]->next;

    while (temp->next != NULL)
    {
        if (strcasecmp(word, temp->word) == 0)
        {
            return true;
        }
        temp = temp->next;
    }
    if (strcasecmp(word, temp->word) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int x;
    x = toupper(word[0]) - 'A';
    if (isalpha(word[1]))
    {
        x = x + ((toupper(word[1]) - 'A') * 26);
    }

    return x;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    for (int x = 0; x < N; x++) // mallocing space for the table
    {
        table[x] = malloc(sizeof(node));
        table[x]->next = NULL;
    }
    if (table[0] == NULL) // in case tabble 0 is null
    {
        return false;
    }
    if (table[N - 1] == NULL) // in case tabble N-1 is NUll
    {
        for (int x = 0; x < N; x++)
        {
            free(table[x]);
        }
        return false;
    }

    FILE *file = fopen(dictionary, "r"); // opening the dictionary
    if (file == NULL)
    {
        printf("Could not open %s.\n", "file");
        unload();
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF) // reading and copying it to word
    {
        node *temp = NULL;
        node *new = malloc(sizeof(node)); // mallocing space for new values
        new->next = NULL;
        if (new == NULL)
        {
            unload();
        }
        unsigned int position = hash(word); // finding the position where to place the new word
        if (table[position]->next == NULL) // if the first next is empty, place the new word there
        {
            table[position]->next = new;
            strcpy(new->word, word);
        }
        else // if not, keep checking next after next till finding an empty space
        {
            strcpy(new->word, word);
            new->next = table[position]->next;
            table[position]->next = new;
        }
    }
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    node *temp = NULL;
    int n = 0;
    for (int x = 0; x < N; x++)
    {
        temp = table[x]->next;
        while (temp != NULL)
        {
            n++;
            temp = temp->next;
        }
    }
    return n;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    int n = 0;
    for (int x = 0; x < N; x++)
    {
        recursionfree(table[x]);
    }
    return true;
}
