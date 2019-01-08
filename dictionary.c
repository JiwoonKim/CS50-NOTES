/**
 * Implements a dictionary's functionality
 * Created functions check, load, size, and unload to spell-check words in a text file based on a collection of words (dictionary).
   load function: loads dictionary in memory by constructing a trie and counts the number of words (size).
   check function: checks word-by-word in the text file based on the dictionary by traversing through the trie implemented in load.
   size function: returns the total number of words.
   unload function: frees the dynamically allocated memory used to implement the trie for the dictionary.
   
 * these functions are used to speller.c file created by CS50 for Pset5. 
   Use by ex) ./speller texts/austinpowers.txt
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// define node type for load
typedef struct node
{
    bool is_word;
    struct node *children[27];
} node;

// prototype definition returning index number
int ret_index(int letter);
void free_node(node *nodePointer);

// set starting pointer root as global variable
node *root;

/* set integer pointer for counting number of words (counted in load but returned in size function) */
unsigned int *dic_size;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // set a node pointer to root to traverse trie
    node *traverse = root;
    // iterate through letters of the word
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // put value of letter
        int letter = word[i];
        // convert all the letters of the word into lowercase
        if (isupper(letter))
        {
            letter = tolower(letter);
        }
        // return index of the letter (' = 0 and a ~ z = 1 ~ 27)
        int index = ret_index(letter);
        // if there is no path
        if (traverse -> children[index] == NULL)
        {
            return false;
        }
        // follow the path by taking one step down the trie
        else
        {
            traverse = traverse -> children[index];
        }
    }
    // check if word is at the end of the path
    if (traverse -> is_word == true)
    {
        return true;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Cannot open dictionary file!\n");
        return false;
    }
    /* create head root for trie
     and also, initialize root's members with null value (prevent errors) */
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        printf("Unable to malloc root!\n");
        return false;
    }
    for (int i = 0; i < 27; i++)
    {
        root -> children[i] = NULL;
    }
    root -> is_word = false;
    // initialize count for size of words in dictionary
    dic_size = malloc(sizeof(unsigned int));
    if (dic_size == NULL)
    {
        printf("Unable to malloc dic_size!\n");
        return false;
    }
    *dic_size = 0;
    // create node pointer traverse to move around trie
    node *traverse = root;
    // create string buffer
    char *word;
    word = malloc(sizeof(char) * 46);
    if (word == NULL)
    {
        printf("Unable to malloc word!\n)");
        return false;
    }

    // iterate through dictionary by word (scan string into word buffer)
    while (fscanf(fp, "%s", word) != EOF)
    {
        // iterate through the word by character and input into trie (each new letter goes down the trie)
        for (int i = 0, n = strlen(word); i < n; i++)
        {
            // convert the char to index
            int c = ret_index(word[i]);
            // if there is no path, create a new node
            if (traverse -> children[c] == NULL)
            {
                node *new_node = malloc(sizeof(node));
                for (int j = 0; j < 27; j++)
                {
                    new_node -> children[j] = NULL;
                }
                new_node -> is_word = false;
                traverse -> children[c] = new_node;
            }
            // go down path
            traverse = traverse -> children[c];
        }
        // signal is_word at the end of the trie
        traverse -> is_word = true;
        // count size of dictionary (to use in size function)
        *dic_size = *dic_size + 1;
        // update traverse to start from root
        traverse = root;
    }
    // free memory for word
    free(word);
    // eliminate traverse pointer
    traverse = NULL;
    // signal function is completed; else return false (free file pointer while doing so)
    if (fseek(fp, 0, SEEK_CUR) == fseek(fp, 0, SEEK_END))
    {
        fclose(fp);
        return true;
    }
    fclose(fp);
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // store size of dictionary in sizeDic for return value
    unsigned int sizeDic = *dic_size;
    return sizeDic;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // free dic_size
    free(dic_size);
    // free node by using free_node function (recursion)
    free_node(root);
    root = NULL;
    // signal successful or not
    if (root == NULL)
    {
        return true;
    }
    return false;
}

// function used to unload (recursion)
void free_node(node *nodePointer)
{
    // iterate through children pointers in a single node
    for (int i = 0; i < 27; i++)
    {
        // if there is path, go down (recursion)
        if (nodePointer -> children[i] != NULL)
        {
            free_node(nodePointer -> children[i]);
        }
    }
    free(nodePointer);
}

// change value of letter into index value for use in trie
int ret_index(int letter)
{
    // check whether valid input was given
    if (!isalpha(letter) && letter != '\'')
    {
        printf("invalid letter given to re_index!\n");
    }
    // index used inside children[#]: ' = 0, a ~ z = 1 ~ 26
    int index;
    if (isalpha(letter))
    {
        index = letter - 96;
    }
    else
    {
        index = letter - 39;
    }
    return index;
}
