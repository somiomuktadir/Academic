/**
 * @file hash_table_simple.c
 * @brief Simple Hash Table implementation using linear probing.
 *
 * This program demonstrates:
 * 1. Hash function implementation
 * 2. Collision resolution using Linear Probing
 * 3. Basic key-value storage (integer keys and values)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20

typedef struct {
    int key;
    int data;
} DataItem;

DataItem* hash_array[SIZE];
DataItem* dummy_item;
DataItem* item;

/**
 * @brief Hash function: key % SIZE
 */
int hash_code(int key) {
    return key % SIZE;
}

/**
 * @brief Search for a key in the hash table.
 */
DataItem* search(int key) {
    int hash_index = hash_code(key);

    // Move in array until an empty
    while (hash_array[hash_index] != NULL) {
        if (hash_array[hash_index]->key == key)
            return hash_array[hash_index];

        // Go to next cell
        ++hash_index;

        // Wrap around the table
        hash_index %= SIZE;
    }
    return NULL;
}

/**
 * @brief Insert a key-value pair.
 */
void insert(int key, int data) {
    DataItem *item = (DataItem*)malloc(sizeof(DataItem));
    item->data = data;
    item->key = key;

    int hash_index = hash_code(key);

    // Move in array until an empty or deleted cell
    while (hash_array[hash_index] != NULL && hash_array[hash_index]->key != -1) {
        ++hash_index;
        hash_index %= SIZE;
    }

    hash_array[hash_index] = item;
}

/**
 * @brief Delete a key from the hash table.
 */
DataItem* delete(DataItem* item) {
    int key = item->key;
    int hash_index = hash_code(key);

    while (hash_array[hash_index] != NULL) {
        if (hash_array[hash_index]->key == key) {
            DataItem* temp = hash_array[hash_index];
            // Assign a dummy item at deleted position
            hash_array[hash_index] = dummy_item;
            return temp;
        }
        ++hash_index;
        hash_index %= SIZE;
    }
    return NULL;
}

void display() {
    for (int i = 0; i < SIZE; i++) {
        if (hash_array[i] != NULL && hash_array[i]->key != -1)
            printf(" (%d,%d)", hash_array[i]->key, hash_array[i]->data);
        else
            printf(" ~~ ");
    }
    printf("\n");
}

int main() {
    dummy_item = (DataItem*)malloc(sizeof(DataItem));
    dummy_item->data = -1;
    dummy_item->key = -1;

    insert(1, 20);
    insert(2, 70);
    insert(42, 80);
    insert(4, 25);
    insert(12, 44);
    insert(14, 32);
    insert(17, 11);
    insert(13, 78);
    insert(37, 97);

    printf("Hash Table Contents:\n");
    display();

    item = search(37);
    if (item != NULL) {
        printf("Element found: %d\n", item->data);
    } else {
        printf("Element not found\n");
    }

    delete(item);
    item = search(37);
    if (item != NULL) {
        printf("Element found: %d\n", item->data);
    } else {
        printf("Element not found\n");
    }

    return 0;
}
