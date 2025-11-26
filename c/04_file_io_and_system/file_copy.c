/**
 * @file file_copy.c
 * @brief Copies the contents of one file to another.
 *
 * This program demonstrates:
 * 1. File opening modes ("r", "w")
 * 2. Reading and writing characters (fgetc, fputc)
 * 3. Error handling for file operations
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *sourceFile, *destFile;
    char ch;

    // Check command line arguments
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    // Open source file
    sourceFile = fopen(argv[1], "r");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return 1;
    }

    // Open destination file
    destFile = fopen(argv[2], "w");
    if (destFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
        return 1;
    }

    // Copy contents
    printf("Copying from %s to %s...\n", argv[1], argv[2]);
    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(ch, destFile);
    }

    printf("File copied successfully.\n");

    // Close files
    fclose(sourceFile);
    fclose(destFile);

    return 0;
}
