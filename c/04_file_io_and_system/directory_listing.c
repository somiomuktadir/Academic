/**
 * @file directory_listing.c
 * @brief Lists files in the current directory.
 *
 * This program demonstrates:
 * 1. Using dirent.h for directory traversal
 * 2. opendir, readdir, and closedir functions
 * 3. Filtering entries (e.g., hiding hidden files)
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    struct dirent *de;  // Pointer for directory entry
    DIR *dr = opendir("."); // opendir() returns a pointer of DIR type.

    if (dr == NULL) {
        printf("Could not open current directory");
        return 0;
    }

    printf("Files in current directory:\n");
    printf("---------------------------\n");

    while ((de = readdir(dr)) != NULL) {
        // Skip hidden files (starting with .)
        if (de->d_name[0] != '.') {
            printf("%s\n", de->d_name);
        }
    }

    closedir(dr);
    return 0;
}
