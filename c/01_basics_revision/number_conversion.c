/**
 * @file number_conversion.c
 * @brief Converts a decimal number to Binary, Octal, and Hexadecimal.
 *
 * This program demonstrates:
 * 1. Bitwise operations
 * 2. Modulo and division operations
 * 3. Recursive functions for printing
 * 4. Formatting output
 */

#include <stdio.h>

/**
 * @brief Prints the binary representation of a number.
 *
 * Uses recursion to print bits from most significant to least significant.
 *
 * @param n The decimal number.
 */
void print_binary(unsigned int n) {
    if (n > 1) {
        print_binary(n / 2);
    }
    printf("%d", n % 2);
}

/**
 * @brief Prints the octal representation of a number.
 *
 * @param n The decimal number.
 */
void print_octal(unsigned int n) {
    if (n > 7) {
        print_octal(n / 8);
    }
    printf("%d", n % 8);
}

/**
 * @brief Prints the hexadecimal representation of a number.
 *
 * @param n The decimal number.
 */
void print_hex(unsigned int n) {
    if (n > 15) {
        print_hex(n / 16);
    }
    int remainder = n % 16;
    if (remainder < 10) {
        printf("%d", remainder);
    } else {
        // Convert 10-15 to A-F
        printf("%c", 'A' + (remainder - 10));
    }
}

int main() {
    int num;

    printf("Enter a decimal number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    if (num < 0) {
        printf("This program handles positive integers for simplicity.\n");
        printf("Converting absolute value: %d\n", -num);
        num = -num;
    }

    printf("\nConversions for Decimal %d:\n", num);
    
    printf("Binary:      ");
    if (num == 0) printf("0"); else print_binary(num);
    printf("\n");

    printf("Octal:       ");
    if (num == 0) printf("0"); else print_octal(num);
    printf("\n");

    printf("Hexadecimal: ");
    if (num == 0) printf("0"); else print_hex(num);
    printf("\n");

    // Verification using standard format specifiers
    printf("\nVerification using printf:\n");
    printf("Octal (%%o):   %o\n", num);
    printf("Hex (%%X):     %X\n", num);

    return 0;
}
