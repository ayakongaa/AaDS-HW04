#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* buildTree(int* arr, int i, int size) {
    if (i >= size || arr[i] == -1)
        return NULL;

    Node* root = createNode(arr[i]);
    root->left = buildTree(arr, 2 * i + 1, size);
    root->right = buildTree(arr, 2 * i + 2, size);
    return root;
}

void printTree(Node* root) {
    if (root == NULL) return;
    printf("%d ", root->val);
    printTree(root->left);
    printTree(root->right);
}

void freeTree(Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int mas[] = { 8, 9, 11, 16, 3, 1 };
    int N = sizeof(mas) / sizeof(mas[0]);

    printf("Size of array: %d\n", N);
    printf("Array elems: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", mas[i]);
    }
    printf("\n");

    Node* root = buildTree(mas, 0, N);

    printf("pre-order: ");
    printTree(root);
    printf("\n");

    freeTree(root);
    return 0;
}
