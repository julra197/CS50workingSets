/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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

void initRoot()
{
    root = malloc(sizeof(struct node));
    root->is_word = false;
    for(int i = 0; i < 27; i++)
    {
        root->children[i] = NULL;
    }
}

node *getNode()
{
    node *new_node = malloc(sizeof(struct node));
    new_node->is_word = false;
    for(int i = 0; i < 27; i++)
    {
        new_node->children[i] = NULL;
    }
    return new_node;
}

void insertInTrie(char *word)
{
    node *newPointer = root;
    for(int i = 0, len = strlen(word); i<len; i++)
        {
            if(word[i] != 10)
            {
                int slot = word[i]-97;
                if(slot<0)
                {
                    slot += 32;
                }
                if(newPointer->children[slot] == NULL)
                {
                    newPointer->children[slot] = getNode();
                }
                newPointer = newPointer->children[slot];
            }
        }
    newPointer->is_word = true;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    bool retVal = false;
    node *currPointer = root;
    for(int i = 0, len = strlen(word); i<len; i++)
    {
        int slot = word[i]-97;
        if(slot<0)
        {
            slot += 32;
        }
        if(currPointer->children[slot] != NULL)
        {
            currPointer = currPointer->children[slot];
            if(i == len-1 && currPointer->is_word == true)
            {
                retVal = true;
            }
        }
        else
        {
            return retVal;
        }
    }
    return retVal;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    //init root node of trie
    initRoot();
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
        insertInTrie(word);
    }

    return true;
}

/**
 * Count the size of the trie
 * Uses recursion
 */
int counter = 0;

unsigned int count(node* pointer)
{
    if(pointer->is_word)
    {
        counter++;
    }
    for(int i = 0; i < 27; i++)
    {
        if(pointer->children[i] != NULL)
        {
            count(pointer->children[i]);
        }
    }
    return counter;
}
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    printf("size called");
    return count(root);
}

/**
 * Uses recursion to unload
 */
void unloadPointer(node* pointer)
{
    for(int i = 0; i < 27; i++)
    {
        if(pointer->children[i] != NULL)
        {
            unloadPointer(pointer->children[i]);
        }
    }
    free(pointer);
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    unloadPointer(root);
    return true;
}
