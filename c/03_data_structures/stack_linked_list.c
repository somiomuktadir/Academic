/**
 * @file stack_linked_list.c
 * @brief Implementation of a Stack using a Linked List.
 *
 * This program demonstrates:
 * 1. Stack LIFO (Last In First Out) property
 * 2. Dynamic memory allocation for stack nodes
 * 3. Push and Pop operations without size limit
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *top = NULL;

void push(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Stack Overflow\n");
        return;
    }
    new_node->data = value;
    new_node->next = top;
    top = new_node;
    printf("Pushed %d\n", value);
}

void pop() {
    if (top == NULL) {
        printf("Stack Underflow\n");
        return;
    }
    Node *temp = top;
    printf("Popped %d\n", temp->data);
    top = top->next;
    free(temp);
}

void display() {
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    Node *temp = top;
    printf("Stack elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    push(10);
    push(20);
    push(30);

    display();

    pop();
    pop();

    display();

    pop();
    pop(); // Underflow

    return 0;
}
