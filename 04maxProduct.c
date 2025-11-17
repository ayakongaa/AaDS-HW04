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


void freeTree(Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void treeToArray(Node* root, int* array, int* index) {
    if (root == NULL) return;

    Node* queue[1000];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        Node* current = queue[front++];
        array[(*index)++] = current->val;

        if (current->left != NULL)
            queue[rear++] = current->left;
        if (current->right != NULL)
            queue[rear++] = current->right;
    }
}

int maxMinMultiplication(Node* root) {
    if (root == NULL) return -1;

    int array[1000];
    int length = 0;
    treeToArray(root, array, &length);

    if (length < 3) {
        return -1;
    }

    int min_index = 1;
    int max_index = 2;
    int i = 0;

    while (1) {
        int min_index_tmp = 2 * i + 1;
        if (min_index_tmp < length) {
            min_index = min_index_tmp;
            i = min_index_tmp;
            continue;
        }
        break;
    }

    i = 0;
    while (1) {
        int max_index_tmp = 2 * i + 2;
        if (max_index_tmp < length) {
            max_index = max_index_tmp;
            i = max_index_tmp;
            continue;
        }
        break;
    }


    int result = array[min_index] * array[max_index];
    return result;
}

int main() {
    int mas[] = { 8, 9, 11, 16, 3, 1 };
    int N = sizeof(mas) / sizeof(mas[0]);

    Node* root = buildTree(mas, 0, N);

    int result = maxMinMultiplication(root);
    printf("Max product: %d\n", result);

    freeTree(root);
    return 0;
}
