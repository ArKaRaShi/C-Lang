#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;

void freeNodeUntilNUll(node_t *headNode) {
    node_t *nextNode = NULL;
    node_t *currNode = headNode;
    while (currNode != NULL) {
        nextNode = currNode->next;
        free(currNode);
        currNode = nextNode;
    }
}

void freeNodeStartToOrder(node_t *headNode, int repeat) {
    node_t *nextNode = NULL;
    node_t *currNode = headNode;
    for (int i = 0; i < repeat; i++) {
        nextNode = currNode->next;
        free(currNode);
        currNode = nextNode;
    }
}

node_t *findNodeByOrder(node_t *headNode, int order) {
    node_t *ptrNode = headNode;
    for (int i = 0; i < order; i++) {
        ptrNode = ptrNode->next;
    }
    return ptrNode;
}

node_t *findLastNode(node_t *headNode) {
    node_t *ptrNode = headNode;
    while (ptrNode->next != NULL) {
        ptrNode = ptrNode->next;
    }
    return ptrNode;
}

node_t *createNewNode(int value) {
    node_t *newNode = (node_t *) malloc(sizeof(node_t));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

node_t *append(node_t *headNode) {
    node_t *ptrNode;

    int inputData;
    scanf("%d", &inputData);
    node_t *tempNode = createNewNode(inputData);

    if (headNode == NULL) {
        headNode = tempNode;
    } else {
        ptrNode = findLastNode(headNode);
        ptrNode->next = tempNode;
    }
    return headNode;
}

node_t *reverse(node_t *headNode) {
    node_t *nextNode = NULL;
    node_t *currNode = headNode;
    node_t *prevNode = NULL;

    while (currNode != NULL) {
        nextNode = currNode->next;
        currNode->next = prevNode;
        prevNode = currNode;
        currNode = nextNode;
    }
    return prevNode;
}

node_t *cut(node_t *headNode) {
    int firstOrder, secondOrder;
    scanf("%d %d", &firstOrder, &secondOrder);

    node_t *newHead = findNodeByOrder(headNode, firstOrder);
    node_t *newTail = findNodeByOrder(headNode, secondOrder);

    freeNodeStartToOrder(headNode, firstOrder - 1);
    if (newTail->next != NULL)
        freeNodeUntilNUll(newTail->next);

    newTail->next = NULL;
    return newHead;
}

void get(node_t *headNode) {
    int order;
    scanf("%d", &order);
    node_t *ptrNode = findNodeByOrder(headNode, order);
    printf("%d\n", ptrNode->data);
}

void show(node_t *headNode) {
    node_t *ptrNode = headNode;
    while (ptrNode != NULL) {
        printf("%d ", ptrNode->data);
        ptrNode = ptrNode->next;
    }
    printf("\n");
}

int main(void) {
    node_t *startNode;
    int n,i;
    char command;
    startNode = NULL;
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf(" %c", &command);
        switch (command) {
            case 'A':
                startNode = append(startNode);
                break;
            case 'G':
                get(startNode);
                break;
            case 'S':
                show(startNode);
                break;
            case 'R':
                startNode = reverse(startNode);
                break;
            case 'C':
                startNode = cut(startNode);
                break;
            default:
                break;
        }
    }
    freeNodeUntilNUll(startNode);
    return 0;
}