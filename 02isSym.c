#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 1000

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Queue {
    Node* data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

bool isEmpty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, Node* node) {
    if (q->rear < MAX_QUEUE_SIZE) {
        q->data[q->rear++] = node;
    }
}

Node* dequeue(Queue* q) {
    if (!isEmpty(q)) {
        return q->data[q->front++];
    }
    return NULL;
}

int queueSize(Queue* q) {
    return q->rear - q->front;
}

bool isSymmetricQueue(Node* root) {
    if (root == NULL) {
        return true;
    }

    Queue queue;
    initQueue(&queue);
    enqueue(&queue, root);

    while (!isEmpty(&queue)) {
        int levelSize = queueSize(&queue);
        Node** levelNodes = (Node**)malloc(levelSize * sizeof(Node*));

        for (int i = 0; i < levelSize; i++) {
            levelNodes[i] = dequeue(&queue);
        }

        for (int i = 0; i < levelSize / 2; i++) {
            Node* left = levelNodes[i];
            Node* right = levelNodes[levelSize - i - 1];

            if (left == NULL && right == NULL) {
                continue;
            }
            if (left == NULL || right == NULL) {
                free(levelNodes);
                return false;
            }
            if (left->val != right->val) {
                free(levelNodes);
                return false;
            }
        }

        for (int i = 0; i < levelSize; i++) {
            if (levelNodes[i] != NULL) {
                enqueue(&queue, levelNodes[i]->left);
                enqueue(&queue, levelNodes[i]->right);
            }
        }

        free(levelNodes);
    }

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

    Node* root1 = buildTree(mas, 0, N);
    printf("Pre-order: ");
    printTree(root1);
    printf("\n");
    printf("Simmetryc: %s\n\n", isSymmetricQueue(root1) ? "YES" : "NO");

    return 0;
}
