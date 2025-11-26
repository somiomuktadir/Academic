/**
 * @file prime_generator.c
 * @brief Generates prime numbers using the Sieve of Eratosthenes algorithm.
 *
 * This program demonstrates:
 * 1. Array manipulation
 * 2. Algorithm implementation (Sieve of Eratosthenes)
 * 3. Input validation
 * 4. Efficient boolean flagging
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Prints all prime numbers up to a specified limit.
 *
 * @param limit The upper bound for finding prime numbers.
 */
void sieve_of_eratosthenes(int limit) {
    // We create an array of booleans.
    // is_prime[i] will be true if i is prime, false otherwise.
    // We use (limit + 1) to accommodate the number 'limit' itself.
    bool *is_prime = (bool *)malloc((limit + 1) * sizeof(bool));

    if (is_prime == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return;
    }

    // Initialize all entries as true. A value in array[i] will
    // finally be false if i is Not a prime, else true.
    for (int i = 0; i <= limit; i++) {
        is_prime[i] = true;
    }

    // 0 and 1 are not prime numbers
    is_prime[0] = false;
    is_prime[1] = false;

    // Iterate from 2 to sqrt(limit).
    // If p is prime, then all multiples of p are not prime.
    for (int p = 2; p * p <= limit; p++) {
        // If is_prime[p] is not changed, then it is a prime
        if (is_prime[p] == true) {
            // Update all multiples of p greater than or equal to the square of it
            // numbers which are multiple of p and are less than p^2 are already been marked.
            for (int i = p * p; i <= limit; i += p) {
                is_prime[i] = false;
            }
        }
    }

    // Print all prime numbers
    printf("Prime numbers up to %d are:\n", limit);
    int count = 0;
    for (int p = 2; p <= limit; p++) {
        if (is_prime[p]) {
            printf("%d ", p);
            count++;
            // Print a newline every 10 numbers for better formatting
            if (count % 10 == 0) {
                printf("\n");
            }
        }
    }
    printf("\n");

    // Free the allocated memory to prevent memory leaks
    free(is_prime);
}

int main() {
    int n;

    printf("Enter the upper limit to generate prime numbers: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return 1;
    }

    if (n < 2) {
        printf("There are no prime numbers less than 2.\n");
        return 0;
    }

    sieve_of_eratosthenes(n);

    return 0;
}
