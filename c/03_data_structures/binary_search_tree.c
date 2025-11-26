/**
 * @file binary_search_tree.c
 * @brief Implementation of a Binary Search Tree (BST).
 *
 * This program demonstrates:
 * 1. Tree data structure
 * 2. Recursive insertion
 * 3. Inorder traversal (sorted output)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

/**
 * @brief Creates a new BST node.
 */
Node* new_node(int item) {
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

/**
 * @brief Inserts a new node with given key in BST.
 */
Node* insert(Node *node, int key) {
    // If the tree is empty, return a new node
    if (node == NULL) return new_node(key);

    // Otherwise, recur down the tree
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    // Return the (unchanged) node pointer
    return node;
}

/**
 * @brief Inorder traversal of BST.
 * Prints elements in sorted order.
 */
void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    /* Let us create following BST
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 */
    Node *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder traversal of the given tree: \n");
    inorder(root);
    printf("\n");

    return 0;
}
