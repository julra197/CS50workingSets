/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>


#include "dictionary.h"

/**
 * Define the node of a trie data structure
 */
typedef struct node
{
    bool is_word;
    struct node *children[27];
}
node;

node *root;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{

    //read the dictionary
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    char word[LENGTH];
    while(fgets(word, LENGTH, dict) != NULL)
    {
        //TODO add each word to the trie

        //print each word for test purposes
        printf("%s", word);
    }

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return true;
}
