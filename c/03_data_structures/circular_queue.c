/**
 * @file circular_queue.c
 * @brief Implementation of a Circular Queue using an array.
 *
 * This program demonstrates:
 * 1. Circular increment logic (i = (i + 1) % SIZE)
 * 2. Queue operations: Enqueue, Dequeue
 * 3. Handling full and empty states
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int items[SIZE];
int front = -1, rear = -1;

int is_full() {
    if ((front == 0 && rear == SIZE - 1) || (front == rear + 1))
        return 1;
    return 0;
}

int is_empty() {
    if (front == -1)
        return 1;
    return 0;
}

void enqueue(int element) {
    if (is_full()) {
        printf("Queue is full\n");
    } else {
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        items[rear] = element;
        printf("Inserted -> %d\n", element);
    }
}

int dequeue() {
    int element;
    if (is_empty()) {
        printf("Queue is empty\n");
        return -1;
    } else {
        element = items[front];
        if (front == rear) {
            // Reset queue when last element is removed
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
        printf("Deleted element -> %d\n", element);
        return element;
    }
}

void display() {
    int i;
    if (is_empty())
        printf("Empty Queue\n");
    else {
        printf("Front -> %d\n", front);
        printf("Items -> ");
        for (i = front; i != rear; i = (i + 1) % SIZE)
            printf("%d ", items[i]);
        printf("%d ", items[i]);
        printf("\nRear -> %d\n", rear);
    }
}

int main() {
    // Fails because front = -1
    dequeue();

    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);

    // Fails to enqueue because front == 0 && rear == SIZE - 1
    enqueue(6);

    display();
    dequeue();

    display();

    enqueue(7);
    display();

    // Fails to enqueue because front == rear + 1
    enqueue(8);

    return 0;
}
