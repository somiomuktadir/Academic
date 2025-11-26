/**
 * @file dynamic_array_resize.c
 * @brief Implements a dynamic array that resizes automatically.
 *
 * This program demonstrates:
 * 1. malloc, realloc, and free
 * 2. Dynamic memory management strategies (doubling capacity)
 * 3. Error handling for memory allocation
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} DynamicArray;

/**
 * @brief Initializes the dynamic array.
 */
void init_array(DynamicArray *arr, size_t initial_capacity) {
    arr->data = (int *)malloc(initial_capacity * sizeof(int));
    if (arr->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    arr->size = 0;
    arr->capacity = initial_capacity;
}

/**
 * @brief Appends an element to the array, resizing if necessary.
 */
void append_array(DynamicArray *arr, int value) {
    if (arr->size == arr->capacity) {
        // Double the capacity
        size_t new_capacity = arr->capacity * 2;
        printf("Resizing array from %zu to %zu\n", arr->capacity, new_capacity);
        
        int *new_data = (int *)realloc(arr->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            // Original data is still valid, but we can't add more.
            // In a real app, we might handle this more gracefully.
            exit(1);
        }
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    arr->data[arr->size++] = value;
}

/**
 * @brief Frees the dynamic array memory.
 */
void free_array(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

int main() {
    DynamicArray arr;
    init_array(&arr, 2); // Start with small capacity to trigger resize

    for (int i = 0; i < 10; i++) {
        append_array(&arr, i * 10);
        printf("Added %d. Size: %zu, Capacity: %zu\n", i * 10, arr.size, arr.capacity);
    }

    printf("\nFinal Array Contents:\n");
    for (size_t i = 0; i < arr.size; i++) {
        printf("%d ", arr.data[i]);
    }
    printf("\n");

    free_array(&arr);
    return 0;
}
