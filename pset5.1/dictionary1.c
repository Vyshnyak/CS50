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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

struct node *hashtable[HASHSIZE], *crawler;

unsigned int size_ht;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // an array to store the copy of the word with changed alpha chars case from upper to lower
    char word_1[LENGTH];
    
    // change alpha chars cases from upper to lower
    for (int i = 0, n = strlen(word); i < n + 1; i++)
    {
        if (isalpha(word[i]) && isupper(word[i]))
        {
            // change upper case chars to lower case and put in array
            word_1[i] = tolower(word[i]);
        }
        else if (i == n)
        {
            // terminate current word
            word_1[i] = '\0';
        }
        else
        {
            // put the non alpha chars without changing
            word_1[i] = word[i];
        }
    }
    
    // pointer to travers through an array
    crawler = hashtable[hash_function(word_1)];
    
    // search the word in dictionary
    while (crawler != NULL)
    {
        if (strcmp(crawler->word, word_1) == 0)
        {
            // the word has been found
            return true;
        }
        else
        {
            // go to the next word in dictionary
            crawler = crawler->next;
        }
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
    
    // assign each node in array to NULL
    for (int i = 0; i < HASHSIZE; i++)
    {
        hashtable[i] = NULL;
    }
    
    // asiign size of hastable to 0
    size_ht = 0;
    
    // load words from dictionaty file to hash table
    while (feof(dict) == 0)
    {
        // allocate memory for new node
        node* new_node = malloc(sizeof(node));
        
        if (new_node == NULL)
        {
            printf("Out of heap memory!");
            return 1;
        }
        
        // scan word from dictionary file to node
        fscanf(dict, "%s", new_node->word);
        
        if (!isalpha(new_node->word[0]))
        {
            continue;
        }
        
        // set the new node's next pointer to NULL
        new_node->next = NULL;
        
        // get hash value to be used as an index for hash table to store a new node
        int hashIndex = hash_function(new_node->word);
        
        // insert words in hash table
        if (hashtable[hashIndex] == NULL)
        {
            hashtable[hashIndex] = new_node;
            size_ht++;
        }
        else if (new_node->word[0] <= hashtable[hashIndex]->word[0])
        {
            new_node->next = hashtable[hashIndex];
            hashtable[hashIndex] = new_node;
            size_ht++;
        }
        else
        {
            // declare a pointer called crawler and assign it an adress of the head of array to traverse through the array
            crawler = hashtable[hashIndex];
            
            // declare a pointer and assign it an adress to previous word to compare it to next word 
            char* prvWord = crawler->word;
            
            while (crawler != NULL)
            {
                if (new_node->word[0] > crawler->word[0] && crawler->next == NULL)
                {
                    crawler->next = new_node;
                    size_ht++;
                    break;
                }
                else if (new_node->word[0] >= prvWord[0] && new_node->word[0] <= crawler->word[0])
                {
                    new_node->next = crawler->next;
                    crawler->next = new_node;
                    size_ht++;
                    break;
                }
                else
                {
                    // save the current word
                    prvWord = crawler->word;
                    
                    // go to the next word
                    crawler = crawler->next;
                }
            }
        }
    }
    
    // check whether dictionary was successfully loaded 
    if (feof(dict) != 0)
    {
        fclose(dict);
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
    return size_ht;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HASHSIZE; i++)
    {
        // pointer to traverse through an array
        crawler = hashtable[i];
        
        // free memory that was allocated for nodes
        while (crawler != NULL)
        {
            // variable that stores the node we're gonna free
            node* temp = crawler;
            
            // go to the next node
            crawler = crawler->next;
            
            // free memory
            free(temp);
        }
    }
    
    return true;
}

/**
 * Hashes the word, and returns an index that is less than size of an array 
 */
unsigned int hash_function(const char* word)
{
    unsigned int hash = 0;
    
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }
    
    return hash % HASHSIZE;
}

 
 