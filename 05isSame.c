#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

bool isSameTree(Node* a, Node* b) {
    if (a == NULL && b == NULL) {
        return true;
    }
    if (a == NULL || b == NULL) {
        return false;
    }
    if (a->data != b->data) {
        return false;
    }
    return isSameTree(a->left, b->left) && isSameTree(a->right, b->right);
}

Node* buildTree(int* arr, int i, int size) {
    if (i >= size || arr[i] == -1)
        return NULL;

    Node* root = createNode(arr[i]);
    root->left = buildTree(arr, 2 * i + 1, size);
    root->right = buildTree(arr, 2 * i + 2, size);
    return root;
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {

    int arr1[] = { 1, 2, 3 };
    int arr2[] = { 1, 2, 4 };
    int size = sizeof(arr1) / sizeof(arr1[0]);

    Node* tree1 = buildTree(arr1, 0, size);
    Node* tree2 = buildTree(arr2, 0, size);

    printf("Equal?: %s\n\n", isSameTree(tree1, tree2) ? "YES" : "NO");


    freeTree(tree1);
    freeTree(tree2);

    return 0;
}
