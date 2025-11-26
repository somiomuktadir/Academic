/**
 * @file quick_sort.c
 * @brief Implementation of Quick Sort algorithm.
 *
 * This program demonstrates:
 * 1. Divide and Conquer strategy
 * 2. Partitioning logic
 * 3. Recursive sorting
 */

#include <stdio.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/**
 * @brief Partitions the array around a pivot.
 * This implementation takes last element as pivot.
 */
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/**
 * @brief The main function that implements QuickSort.
 */
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void print_array(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: \n");
    print_array(arr, n);
    
    quick_sort(arr, 0, n - 1);
    
    printf("Sorted array: \n");
    print_array(arr, n);
    return 0;
}
