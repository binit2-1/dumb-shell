#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

TrieNode *createNode(void)
{
    TrieNode *newNode = (TrieNode *)malloc(sizeof(TrieNode));
    if (!newNode)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    newNode->frequency = 0;
    for (int i = 0; i < ASCII_SIZE; i++)
    {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void insert(TrieNode *root, const char *word)
{
    if (!root || !word)
    {
        return;
    }
    TrieNode *current = root;
    while (*word)
    {
        int index = (unsigned char)(*word);
        if (current->children[index] == NULL)
        {
            current->children[index] = createNode();
            if (!current->children[index])
            {
                return; // Memory allocation failed
            }
        }
        current = current->children[index];
        word++;
    }
    current->frequency++;
}

//Helper for counting max frequency
void countMaxFrequency(TrieNode* node, char* buffer, char* best_word, int* max_freq){
    if(!node){
        return;
    }
    if(node->frequency > 0){
        if(node->frequency > *max_freq){
            *max_freq = node->frequency;
            strcpy(best_word, buffer);
        }
    }

    for(int i = 0; i<ASCII_SIZE; i++){
        if(node->children[i] != NULL){
            int len = strlen(buffer);
            buffer[len] = (char)i;
            buffer[len + 1] = '\0';
            countMaxFrequency(node->children[i], buffer, best_word, max_freq);
            buffer[len] = '\0';
        }
    }
}

char *getBestPrediction(TrieNode* root, const char *prefix){
    if (!root || !prefix){
        return NULL;
    }
    TrieNode* current = root;
    const char *prefix_start = prefix;
    
    // Navigate to the prefix node
    while(*prefix){
        int index = (unsigned char)(*prefix);
        if(current->children[index] == NULL){
            return NULL; // Prefix not found
        }
        current = current->children[index];
        prefix++;
    }

    char buffer[1024];
    static char best_word[1024];
    int max_freq = -1;

    // Initialize buffer WITH the prefix
    strncpy(buffer, prefix_start, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    best_word[0] = '\0';

    countMaxFrequency(current, buffer, best_word, &max_freq);

    if(max_freq > 0){
        return best_word;
    }
    return NULL;
}

void freeTrie(TrieNode* root) {
    if (!root) {
        return;
    }
    
    // Recursively free all children
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (root->children[i] != NULL) {
            freeTrie(root->children[i]);
        }
    }
    
    // Free the current node
    free(root);
}
