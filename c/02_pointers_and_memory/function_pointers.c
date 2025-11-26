/**
 * @file function_pointers.c
 * @brief Demonstrates the use of function pointers for callbacks.
 *
 * This program demonstrates:
 * 1. Declaring function pointers
 * 2. Passing functions as arguments (callbacks)
 * 3. Implementing a generic bubble sort using a comparator
 */

#include <stdio.h>
#include <stdbool.h>

// Function pointer type for comparison
// Returns true if a should come before b, false otherwise
typedef bool (*compare_func)(int a, int b);

/**
 * @brief Ascending comparison.
 */
bool ascending(int a, int b) {
    return a > b; // Swap if a > b
}

/**
 * @brief Descending comparison.
 */
bool descending(int a, int b) {
    return a < b; // Swap if a < b
}

/**
 * @brief Generic Bubble Sort using a comparator function.
 *
 * @param arr Array to sort
 * @param n Size of array
 * @param comp Comparison function pointer
 */
void bubble_sort(int arr[], int n, compare_func comp) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Use the callback to decide whether to swap
            if (comp(arr[j], arr[j + 1])) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: \n");
    print_array(arr, n);

    // Sort Ascending
    bubble_sort(arr, n, ascending);
    printf("\nSorted Ascending: \n");
    print_array(arr, n);

    // Sort Descending
    bubble_sort(arr, n, descending);
    printf("\nSorted Descending: \n");
    print_array(arr, n);

    return 0;
}
