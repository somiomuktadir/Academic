/**
 * @file doubly_linked_list.c
 * @brief Implementation of a Doubly Linked List (DLL).
 *
 * This program demonstrates:
 * 1. Structs with multiple pointers (prev, next)
 * 2. Dynamic memory allocation for nodes
 * 3. Insertion (front, end) and Deletion operations
 * 4. Forward and Backward traversal
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

/**
 * @brief Creates a new node.
 */
Node* create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

/**
 * @brief Inserts a node at the front of the list.
 */
void insert_front(Node **head, int data) {
    Node *new_node = create_node(data);
    
    if (*head == NULL) {
        *head = new_node;
        return;
    }

    new_node->next = *head;
    (*head)->prev = new_node;
    *head = new_node;
}

/**
 * @brief Inserts a node at the end of the list.
 */
void insert_end(Node **head, int data) {
    Node *new_node = create_node(data);

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new_node;
    new_node->prev = temp;
}

/**
 * @brief Displays the list in forward direction.
 */
void display_forward(Node *head) {
    printf("Forward: ");
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

/**
 * @brief Displays the list in backward direction.
 */
void display_backward(Node *head) {
    if (head == NULL) return;

    // Go to last node
    while (head->next != NULL) {
        head = head->next;
    }

    printf("Backward: ");
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->prev;
    }
    printf("NULL\n");
}

int main() {
    Node *head = NULL;

    insert_end(&head, 10);
    insert_end(&head, 20);
    insert_front(&head, 5);
    insert_end(&head, 30);
    insert_front(&head, 1);

    display_forward(head);
    display_backward(head);

    return 0;
}
