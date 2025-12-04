#ifndef TRIE_H
#define TRIE_H

#define ASCII_SIZE 256

typedef struct TrieNode {
    struct TrieNode *children[ASCII_SIZE]; // Assuming extended ASCII
    int frequency;
} TrieNode;

TrieNode* createNode();
void insert(TrieNode *root, const char *word);
char *getBestPrediction(TrieNode* root, const char *prefix);
void freeTrie(TrieNode* root);



#endif /*TRIE_H*/