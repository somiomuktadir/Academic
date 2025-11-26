/**
 * @file memory_leak_demo.c
 * @brief Demonstrates a memory leak and how to fix it.
 *
 * This program is designed to be run with a memory checker like Valgrind.
 * It contains a function that intentionally leaks memory (commented out by default)
 * and a fixed version.
 *
 * To test with Valgrind:
 * gcc -g memory_leak_demo.c -o leak_demo
 * valgrind --leak-check=full ./leak_demo
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Function with a memory leak.
 *
 * Allocates memory but forgets to free it.
 */
void leaky_function() {
    printf("Running leaky function...\n");
    int *ptr = (int *)malloc(10 * sizeof(int));
    if (ptr == NULL) return;
    
    ptr[0] = 100;
    // OOPS: forgot free(ptr);
    printf("Leaky function finished. Memory at %p is lost.\n", (void*)ptr);
}

/**
 * @brief Function that correctly manages memory.
 */
void safe_function() {
    printf("Running safe function...\n");
    int *ptr = (int *)malloc(10 * sizeof(int));
    if (ptr == NULL) return;

    ptr[0] = 100;
    
    // Correctly free the memory
    free(ptr);
    printf("Safe function finished. Memory freed.\n");
}

int main() {
    printf("--- Memory Management Demo ---\n");

    // Uncomment the line below to see a leak in Valgrind
    // leaky_function();

    safe_function();

    return 0;
}
