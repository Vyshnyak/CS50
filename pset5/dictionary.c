/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

unsigned int size_tr, allocated, freed;
struct node* root;
bool loaded;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // create a pointer to traverse through the trie
    node* crawler = root;
    
    // checking for word in a trie char by char
    for (int i = 0, n = strlen(word) + 1; i < n; i++)
    {
        // get an num equivalent of a char and convert it to a range between 0 and 26  
        int index = word[i] == '\'' ? 26 : tolower(word[i]) - 97;
        
        // trie doesn't contain the word we search
        if (crawler == NULL)
        {
            break;
        }
        
        // trie contains the word we search
        else if (crawler->is_word == true && word[i] == '\0')
        {
            return true;
        }
        
        // go to the next node in array
        crawler = crawler->children[index];
    }
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open file
    FILE* dict = fopen(dictionary, "r");
    
    if (dict == NULL)
    {
        printf("Couldn't open %s.\n", dictionary);
        return false;
    }
    
    // allocate memory for the first node pointer called root
    root = calloc(1, sizeof(node));
    allocated++;
    
    if (root == NULL)
    {
        return false;
    }
    
    // create node pointer called crawler to traverse through nodes
    node* crawler = root;
    
    // load words from dictionaty file to trie
    for (char c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        // get index for the array corresponding to the char
        int index = c == '\'' ? 26 : c - 97;
        
        // we have not reached the end of the word yet    
        if (isalpha(c) || c == '\'')
        {
            if (crawler->children[index] == NULL)
            {
                // allocate memory for new node
                node* new_node = calloc(1, sizeof(node));
                allocated++;
                
                // assign pointer in array to a new node pointer
                crawler->children[index] = new_node;
            }
            
            // go to the next pointer in array    
            crawler = crawler->children[index];
        }
        
        // we heve reached the end of the word
        else
        {
            // set indicator of ending of the word to true
            crawler->is_word = true;
            
            // update counter of size of a trie
            size_tr++;
            
            // assign crawler pointer to the root node
            crawler = root;
        }
    }
    
    // we have succesfuly loaded the dictionary
    if (feof(dict) != 0)
    {
        fclose(dict);
        loaded = true;
        return true;
    }
    
    fclose(dict);
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return loaded == true ? size_tr : 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // unload dictionary
    unloadNode(root);

    return allocated == freed ? true : false;
}

/**
* Unloads node from memory.
*/
void unloadNode(node* ptr)
{
    // go to the deepest node in a trie
    for (int i = 0; i < SIZE; i++)
    {
        // go to the next node if next node isn't NULL
        if (ptr->children[i] != NULL)
        {
            // go to the next node
            unloadNode(ptr->children[i]);
        }
    }
    
    // unload current node
    free(ptr);
    freed++;
}
