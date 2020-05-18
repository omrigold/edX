// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Number of buckets in hash table
const unsigned int N = 27;

// Represents a node in a hash table
typedef struct node
{
    bool inDict;
    struct node *next[N];
}
node;

struct node *createNode(void)
{
    struct node *newNode = NULL;
    newNode = malloc(sizeof(node));

    if (newNode)
    {
        newNode->inDict = false;

        for (int i = 0; i < N; i++)
        {
            newNode->next[i] = NULL;
        }
    }

    return newNode;
}

// Hash table
node *table;

// Loaded indicator
bool loaded = false;

// Word counter
unsigned int words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *trav = NULL;
    trav = table;
    int bucket;

    for (int i = 0, l = strlen(word); i < l; i++)
    {
        if (isalpha(word[i]))
        {
            bucket = tolower(word[i]) - 97;
        }
        else
        {
            bucket = 26;
        }

        if (trav->next[bucket] == NULL)
        {
            return false;
        }
        else
        {
            trav = trav->next[bucket];

            // if last letter, check if word exists and return true
            if (i == l - 1)
            {
                if (trav->inDict)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return false;
}

// Hashes word to a number
// adapted from djb2 by Dan Bernstein
// http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    do
    {
        c = *word++;
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    while (c);

    return (int) hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // attempt to open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Dictionary word to read next
    char word[LENGTH + 1];

    // create a temp node to traverse trie
    table = createNode();
    node *trav = NULL;
    int bucket;

    for (char *get = fgets(word, LENGTH + 1, dict); get != NULL; get = fgets(word, LENGTH + 1, dict))
    {
        trav = table;

        for (int c = 0; word[c] != '\n' && c < LENGTH + 1; c++)
        {
            // get bucket ID for character
            if (isalpha(word[c]))
            {
                bucket = word[c] - 97;
            }
            else
            {
                bucket = 26;
            }

            // check if next node level exists; if not, create it
            if (trav->next[bucket] == NULL)
            {
                trav->next[bucket] = createNode();
                trav = trav->next[bucket];
            }
            else
            {
                trav = trav->next[bucket];
            }
        }

        // write dictionary word to this node
        trav->inDict = true;

        words++;
    }

    fclose(dict);

    loaded = true;
    return loaded;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        return words;
    }
    else
    {
        return 0;
    }
}

// free node memory allocation recursively
bool deleteNode(node *thisNode)
{
    // check if children present
    for (int i = 0; i < N; i++)
    {
        if (thisNode->next[i] != NULL)
        {
            deleteNode(thisNode->next[i]);
        }
    }

    free(thisNode);

    return true;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (deleteNode(table))
    {
        return true;
    }
    return false;
}
