/*=============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit
| checksum on an ASCII input file
|
| Author: Diyor Suleymanov
| Language: c
|
| To Compile:
| gcc -o pa02 pa02.c
| //Caution - expecting input parameters
|
| To Execute: 
| or c -> ./pa02 inputFile.txt 8
| 
| where inputFile.txt is an ASCII input file
| and the number 8 could also be 16 or 32
| which are the valid checksum sizes, all
| other values are rejected with an error message
| and program termination
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Spring 2023
| Instructor: McAlpin
| Due Date: 4/23/2023
|
+=============================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int displayText(FILE *file, int checksum_size) {
    int c, char_count = 0;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
        char_count++;
        if (char_count % 80 == 0) {
            putchar('\n');
        }
    }

    if (checksum_size == 32) {
        int padding_needed = (4 - (char_count % 4)) % 4;
        for (int i = 0; i < padding_needed; i++) {
            putchar('X');
            char_count++;
        }
    }

    putchar('\n');
    return char_count;
}

uint32_t calculateChecksum(FILE *file, int checksum_size) {
    uint32_t checksum = 0;
    int c;
    int byte_count = 0;

    if (checksum_size == 32) {
        uint32_t temp = 0;
        while ((c = fgetc(file)) != EOF) {
            temp = (temp << 8) | (c & 0xFF);
            byte_count++;

            if (byte_count % 4 == 0) {
                checksum = (checksum + temp) & 0xFFFFFFFF;
                temp = 0;
            }
        }

        int padding_needed = (4 - (byte_count % 4)) % 4;
        for (int i = 0; i < padding_needed; i++) {
            temp = (temp << 8) | ('X' & 0xFF);
            byte_count++;

            if (byte_count % 4 == 0) {
                checksum = (checksum + temp) & 0xFFFFFFFF;
                temp = 0;
            }
        }
    } else {
        while ((c = fgetc(file)) != EOF) {
            if (checksum_size == 8) {
                checksum = (checksum + c) & 0xFF;
            } else if (checksum_size == 16) {
                if (byte_count % 2 == 0) {
                    checksum = (checksum + (c << 8)) & 0xFFFF;
                } else {
                    checksum = (checksum + c) & 0xFFFF;
                }
            }
            byte_count++;
        }
    }

    return checksum;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <checksum_size>\n", argv[0]);
        return 1;
    }

    int checksum_size = atoi(argv[2]);
    if (checksum_size != 8 && checksum_size != 16 && checksum_size != 32) {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

   int char_count = displayText(input_file, checksum_size);
    rewind(input_file);

    uint32_t checksum = calculateChecksum(input_file, checksum_size);
    fclose(input_file);

    printf("%d bit Checksum is %0*x for all %d chars\n", checksum_size,
           checksum_size / 4, checksum, char_count);

    return 0;
}

/*=============================================================================
| I [Diyor Suleymanov] ([di881771]) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+============================================================================*/
