/*=============================================================================
// | Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
// |
// | Author: Diyor Suleymanov
// | Language: c
// |
// | To Compile:
// | gcc -o pa01 pa01.c
// |
// | To Execute:
// | or c -> ./pa01 kX.txt pX.txt
// |
// | Note: All input files are simple 8 bit ASCII input
// |
// | Class: CIS3360 - Security in Computing - Spring 2023
// | Instructor: McAlpin
// | Due Date: 3/6/2023
// |
+=============================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHARS 9991
#define MAX_MATRIX 9

// Function to print the key matrix
void printKey(int n, int key[MAX_MATRIX][MAX_MATRIX]) {
    int i, j;
    printf("Key matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%4d ", key[i][j]);
        }
        printf("\n");
    }
  printf("\n");
}

// Function to convert a character to an index
int char_to_index(char c) {
    if (islower(c)) {
        return c - 'a';
    }
    return -1; // invalid character
}
// a starts at 0 and z end at 25, 
// Function to convert an index to a character
char index_to_char(int i) {
    return i + 'a'; // Changed from i + 'A'
}

// Function to pad the plaintext 
void pad_plaintext(char *plaintext, int n) {
    int len, numPadding, i;
    len = strlen(plaintext);
    numPadding = n - (len % n);
    if (numPadding != n) {
        for (i = 0; i < numPadding; i++) {
            plaintext[len + i] = 'x';
        }
        plaintext[len + numPadding] = '\0';
    }
}


void encrypt(int n, int key[MAX_MATRIX][MAX_MATRIX], char *plaintext, char *ciphertext) {
    int blockSize = n;
    int numBlocks = strlen(plaintext) / blockSize;
    int block[blockSize];
    int result[blockSize];
    int arry;
    int ciphertextLen = strlen(plaintext);

    // Clean plaintext by removing all whitespace and special characters
    int cleanLen = 0;
    char cleanPlaintext[MAX_CHARS];
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            cleanPlaintext[cleanLen++] = tolower(plaintext[i]);
        }
    }
    cleanPlaintext[cleanLen] = '\0';

    // Pad the cleaned plaintext with 'x' characters if needed
    pad_plaintext(cleanPlaintext, n);

    // Print cleaned plaintext with newline after every 80 characters
    printf("Plaintext:\n");
    for (int i = 0; i < strlen(cleanPlaintext); i++) {
        printf("%c", cleanPlaintext[i]);
        if ((i+1) % 80 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");

    // Loop through each block of plaintext
    for (int i = 0; i < numBlocks; i++) {
        // Convert the block of plaintext to an array 
        for (int j = 0; j < blockSize; j++) {
            arry = char_to_index(cleanPlaintext[i*blockSize + j]);
            block[j] = arry;
        }
        // Multiply the block by the key matrix to get the encrypted result
        for (int j = 0; j < blockSize; j++) {
            int sum = 0;
            for (int k = 0; k < blockSize; k++) {
                sum += key[j][k] * block[k];
            }
            result[j] = sum % 26;
        }
        // Convert the array of indices back to a block of characters and append to ciphertext
        for (int j = 0; j < blockSize; j++) {
            ciphertext[i*blockSize + j] = index_to_char(result[j]);
        }
        // Add a newline character after each block
        ciphertext[i*blockSize + blockSize] = '\n'; 
    }
    // Add a null terminator to the end of the ciphertext
    ciphertext[ciphertextLen] = '\0'; 

    // Print ciphertext with newline after every 80 characters
    printf("Ciphertext:\n");
    for (int i = 0; i < strlen(cleanPlaintext); i++) {
        printf("%c", ciphertext[i]);
        if ((i+1) % 80 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}


int main(int argc, char* argv[]) {
    FILE *keyFile;
    int n, i, j, key[MAX_MATRIX][MAX_MATRIX];
    char plaintext[MAX_CHARS], ciphertext[MAX_CHARS];


    // Open key file
    keyFile = fopen(argv[1], "r");
    if (keyFile == NULL) {
        printf("Error opening key file\n");
        exit(1);
    }

    // Read key size from key file
    fscanf(keyFile, "%d", &n);

    // Read key matrix from key file
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(keyFile, "%d", &key[i][j]);
        }
    }

    // Close key file
    fclose(keyFile);

    // Open plaintext file
    FILE* plaintextFile = fopen(argv[2], "rb");
    if (plaintextFile == NULL) {
        printf("Error opening plaintext file\n");
        exit(1);
    }

    // Read plaintext from plaintext file
    size_t readCount = fread(plaintext, 1, MAX_CHARS, plaintextFile);
    plaintext[readCount] = '\0';

    // Close plaintext file
    fclose(plaintextFile);

    // Remove newline characters from plaintext
    for (i = 0; i < readCount; i++) {
        if (plaintext[i] == '\n') {
            plaintext[i] = ' ';
        }
    }

    // Pad plaintext
    pad_plaintext(plaintext, n);

    // Print key matrix
    printKey(n, key);

  
    // Encrypt plaintext and print ciphertext
    encrypt(n, key, plaintext, ciphertext);
    // printf("Ciphertext:\n%s\n", ciphertext);

    return 0;
}

/*=============================================================================
| I [Diyor] ([3836211]) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/

