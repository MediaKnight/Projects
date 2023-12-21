/* COP 3502C Programming Assignment 5
This program is written by: Diyor Suleymanov */
//#include "leak_detector_c.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//create Trie struct
typedef struct Trie {
    struct Trie* children[26];
    int frequency;
    int sum;
    int max;

} Trie;

//create 26 nodes, one for each letter of the alphabet
Trie* createNode() {
    Trie* node = (Trie*) malloc(sizeof(Trie));
    node->frequency = 0;
    node->sum = 0;
    node->max = 0;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}

//insert nodes in proper order
void insert(Trie* root, const char* word, int freq) {
    Trie* current = root;
    for (int i = 0; word[i]; i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            current->children[index] = createNode();
        }
        current = current->children[index];
        current->sum += freq;
    }
    current->frequency += freq;

    // Update max
    current = root;
    for (int i = 0; word[i]; i++) {
        int index = word[i] - 'a';
        current = current->children[index];
        current->max = 0;
        for (int j = 0; j < 26; j++) {
            if (current->children[j]) {
                current->max = current->children[j]->sum > current->max
                                             ? current->children[j]->sum
                                             : current->max;
            }
        }
    }
}

//search tree and print prefix
void query(Trie* root, const char* prefix) {
    Trie* current = root;
    for (int i = 0; prefix[i]; i++) {
        int index = prefix[i] - 'a';
        if (!current->children[index]) {
            printf("unknown word\n");
            return;
        }
        current = current->children[index];
    }

    int found = 0;
    for (int i = 0; i < 26; i++) {
        if (current->children[i] && current->children[i]->sum == current->max) {
            printf("%c", 'a' + i);
            found = 1;
        }
    }
    if (!found) {
        printf("unknown word");
    }
    printf("\n");
}

int main() {
  //atexit(report_mem_leak)
    int n, command, freq;
    char word[2000001];
    Trie* root = createNode();

    scanf("%d", &n);
    while (n--) {
        scanf("%d", &command);
        if (command == 1) {
            scanf("%s %d", word, &freq);
            insert(root, word, freq);
        } else {
            scanf("%s", word);
            query(root, word);
        }
    }

    return 0;
}
