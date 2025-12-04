#ifndef TRIE_H
#define TRIE_H

#define ASCII_SIZE 256;

typedef struct TrieNode {
    struct TrieNode *children[ASCII_SIZE]; // Assuming extended ASCII
    int frequency;
} TrieNode;





#endif /*TRIE_H*/