#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

void freeTree(Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void findMinMax(Node* root, int* minVal, int* maxVal) {
    if (root == NULL) 
        return;
  
    if (root->val < *minVal)
        *minVal = root->val;
    if (root->val > *maxVal)
        *maxVal = root->val;

    findMinMax(root->left, minVal, maxVal);
    findMinMax(root->right, minVal, maxVal);
}

int maxMinMultiplication(Node* root) {
    if (root == NULL)
        return -1;

    int minVal = INT_MAX;
    int maxVal = INT_MIN;

    findMinMax(root, &minVal, &maxVal);

    if (minVal == INT_MAX && maxVal == INT_MIN) {
        return -1;
    return minVal * maxVal;
}

int main() {
    int mas[] = { 8, 9, 11, 16, 3, 1 };
    int N = sizeof(mas) / sizeof(mas[0]);

    Node* root = buildTree(mas, 0, N);

    int result = maxMinMultiplication(root);
    printf("Min Max Product: %d\n", result);

    freeTree(root);
    return 0;
}
