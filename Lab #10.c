//  main.c
//  Lab #10
//  Created by Axel Diaz Bringuez on 4/18/24.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TrieNode {
    struct TrieNode *alphabet[26];
    int count;
};

// Trie structure
struct Trie {
    struct TrieNode *root;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
    struct TrieNode *current = pTrie->root;
    int i;
    for (i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!current->alphabet[index]) {
            current->alphabet[index] = malloc(sizeof(struct TrieNode));
            for (int j = 0; j < 26; j++) {
                current->alphabet[index]->alphabet[j] = NULL;
            }
            current->alphabet[index]->count = 0;
        }
        current = current->alphabet[index];
    }
    current->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
    int i;
    struct TrieNode *current = pTrie->root;
    for (i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!current->alphabet[index]) {
            return 0;
        }
        current = current->alphabet[index];
    }
    return current->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
    struct TrieNode *current = pTrie->root;
    free(current);
    pTrie->root = NULL;
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie(void) {
    int i;
    struct Trie *pTrie = malloc(sizeof(struct Trie));
    pTrie->root = malloc(sizeof(struct TrieNode));
    for (i = 0; i < 26; i++) {
        pTrie->root->alphabet[i] = NULL;
    }
    return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("could not open file. ERROR readDictionary"); // bug testing
        return 1;
    }
    int number_of_words = 0;
    char word[100];
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[number_of_words] = malloc(strlen(word) + 1);
        strcpy(pInWords[number_of_words], word);
        number_of_words++;
    }
    fclose(file);
    return number_of_words;
}

int main(void)
{
    char *inWords[256];
    
    //read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i=0;i<numWords;++i)
    {
        printf("%s\n",inWords[i]);
    }
    
    struct Trie *pTrie = createTrie();
    for (int i=0;i<numWords;i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
