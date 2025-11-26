/**
 * @file string_palindrome.c
 * @brief Checks if a string is a palindrome, ignoring case and non-alphanumeric characters.
 *
 * This program demonstrates:
 * 1. String handling (ctype.h, string.h)
 * 2. Two-pointer technique
 * 3. Character filtering and case conversion
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LEN 1024

/**
 * @brief Checks if a string is a palindrome.
 *
 * This function uses two pointers, one starting from the beginning (left)
 * and one from the end (right). It skips non-alphanumeric characters
 * and compares characters case-insensitively.
 *
 * @param str The input string to check.
 * @return true if palindrome, false otherwise.
 */
bool is_palindrome(const char *str) {
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        // Move left pointer forward until an alphanumeric char is found
        while (left < right && !isalnum(str[left])) {
            left++;
        }

        // Move right pointer backward until an alphanumeric char is found
        while (left < right && !isalnum(str[right])) {
            right--;
        }

        // Compare characters (case-insensitive)
        if (tolower(str[left]) != tolower(str[right])) {
            return false;
        }

        // Move pointers inward
        left++;
        right--;
    }

    return true;
}

int main() {
    char input[MAX_LEN];

    printf("Enter a string to check if it's a palindrome: ");
    
    // Read a line of text, including spaces
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove potential newline character at the end
        input[strcspn(input, "\n")] = 0;

        if (is_palindrome(input)) {
            printf("\"%s\" is a palindrome.\n", input);
        } else {
            printf("\"%s\" is NOT a palindrome.\n", input);
        }
    } else {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    return 0;
}
