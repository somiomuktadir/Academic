/**
 * @file void_pointers.c
 * @brief Demonstrates generic programming using void pointers.
 *
 * This program demonstrates:
 * 1. void* as a generic pointer type
 * 2. Memory copying using memcpy (simulated byte-by-byte copy)
 * 3. Generic swap function
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Generic swap function.
 *
 * Swaps the content of two memory locations of size 'size'.
 *
 * @param a Pointer to first element
 * @param b Pointer to second element
 * @param size Size of the elements in bytes
 */
void generic_swap(void *a, void *b, size_t size) {
    // Allocate temporary memory
    void *temp = malloc(size);
    if (temp == NULL) return;

    // Perform swap using memcpy
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);

    free(temp);
}

int main() {
    // Swap Integers
    int i1 = 10, i2 = 20;
    printf("Before swap (int): %d, %d\n", i1, i2);
    generic_swap(&i1, &i2, sizeof(int));
    printf("After swap (int):  %d, %d\n", i1, i2);

    // Swap Doubles
    double d1 = 1.5, d2 = 3.14;
    printf("\nBefore swap (double): %.2f, %.2f\n", d1, d2);
    generic_swap(&d1, &d2, sizeof(double));
    printf("After swap (double):  %.2f, %.2f\n", d1, d2);

    // Swap Characters
    char c1 = 'A', c2 = 'Z';
    printf("\nBefore swap (char): %c, %c\n", c1, c2);
    generic_swap(&c1, &c2, sizeof(char));
    printf("After swap (char):  %c, %c\n", c1, c2);

    return 0;
}
