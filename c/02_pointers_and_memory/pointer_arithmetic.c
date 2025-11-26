/**
 * @file pointer_arithmetic.c
 * @brief Demonstrates pointer addition, subtraction, and comparison.
 *
 * This program demonstrates:
 * 1. Relationship between arrays and pointers
 * 2. Traversing arrays using pointers
 * 3. Pointer subtraction to find distance
 */

#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *ptr = arr; // Points to the first element

    printf("Array elements using pointer arithmetic:\n");
    for (int i = 0; i < n; i++) {
        // *(ptr + i) is equivalent to arr[i]
        printf("Address: %p, Value: %d\n", (void*)(ptr + i), *(ptr + i));
    }

    printf("\nPointer Traversal:\n");
    int *end_ptr = &arr[n - 1]; // Points to the last element
    
    // Traverse from end to start
    printf("Reverse order:\n");
    while (end_ptr >= ptr) {
        printf("%d ", *end_ptr);
        end_ptr--; // Move pointer back by one integer size
    }
    printf("\n");

    // Pointer subtraction
    int *p1 = &arr[1];
    int *p2 = &arr[4];
    long diff = p2 - p1; // Difference in terms of 'number of elements', not bytes
    
    printf("\nPointer Subtraction:\n");
    printf("p1 points to %d, p2 points to %d\n", *p1, *p2);
    printf("Distance between p2 and p1: %ld elements\n", diff);

    return 0;
}
