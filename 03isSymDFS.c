#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 100

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct {
    int* data;
    int size;
    int capacity;
} DynamicArray;

void initArray(DynamicArray* arr) {
    arr->capacity = INITIAL_CAPACITY;
    arr->size = 0;
    arr->data = (int*)malloc(arr->capacity * sizeof(int));
}

void pushArray(DynamicArray* arr, int value) {
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->data = (int*)realloc(arr->data, arr->capacity * sizeof(int));
    }
    arr->data[arr->size++] = value;
}

void freeArray(DynamicArray* arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = arr->capacity = 0;
}

void depthSearch(Node* root, DynamicArray* arr) {
    if (root == NULL) {
        pushArray(arr, -1);
        return;
    }
    pushArray(arr, root->val);
    depthSearch(root->left, arr);
    depthSearch(root->right, arr);
}

bool isSymmetricDFS(Node* root) {
    if (root == NULL) {
        return true;
    }

    DynamicArray data;
    initArray(&data);
    depthSearch(root, &data);

    int j = data.size - 1;
    for (int i = 0; i < data.size / 2; i++) {
        if (data.data[i] != data.data[j]) {
            freeArray(&data);
            return false;
        }
        j--;
    }

    freeArray(&data);
    return true;
}

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
    if (root == NULL) 
        return;
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

    Node* root = buildTree(mas, 0, N);
    printf("Symmetrical: %s\n", isSymmetricDFS(root) ? "YES" : "NO");

    freeTree(root);
    return 0;
}
