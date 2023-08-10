#include <stdio.h>
#include <stdlib.h>

typedef struct playerDetail {
    int order;
    int accumulation;
    int limit;
    struct playerDetail *next;
    struct playerDetail *prev;
} playerDetail_t;

playerDetail_t *createNode(int order, int limit) {
    playerDetail_t *newNode = (playerDetail_t *) malloc(sizeof(playerDetail_t));
    newNode->order = order;
    newNode->accumulation = 0;
    newNode->limit = limit;
    newNode->next = NULL;
    newNode->next = NULL;
    return newNode;
}

playerDetail_t *appendNode(playerDetail_t *tailNode, int limit, int order) {
    if (tailNode == NULL) {
        tailNode = createNode(order, limit);
    } else {
        playerDetail_t *newNode = createNode(order, limit);
        tailNode->next = newNode;
        tailNode->next->prev = tailNode;
        tailNode = newNode;
    }
    return tailNode;
}

playerDetail_t *removeNode(playerDetail_t *currNode) {
    playerDetail_t *nextNode = NULL;
    nextNode = currNode->next;

    if (currNode->next->next == currNode)
        currNode->next->next = NULL;
    else
        currNode->next->prev = currNode->prev;

    if (currNode->prev->prev == currNode)
        currNode->prev->prev = NULL;
    else
        currNode->prev->next = currNode->next;
    
    free(currNode);
    return nextNode;
}

int containK(int countNumber, int k) {
    int remainder;
    while (countNumber > 0) {
        remainder = countNumber % 10;
        countNumber = countNumber / 10;
        if (remainder == k)
            return 1;
    }
    return 0;
}

int main(void) {
    playerDetail_t *headNode = NULL;
    playerDetail_t *tailNode = NULL;
    playerDetail_t *ptrNode = NULL;

    int n, k;
    int inputLimit, totalPlayer, countNumber, winner;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d", &inputLimit);
        tailNode = appendNode(tailNode, inputLimit, i + 1);
        if (headNode == NULL)
            headNode = tailNode;
    }
    ptrNode = headNode;
    tailNode->next = headNode;
    headNode->prev = tailNode;
    totalPlayer = n;
    countNumber = 1;

    while (totalPlayer != 1) {

        if (countNumber % k == 0 || containK(countNumber, k)) 
            ptrNode->accumulation++;
        if (ptrNode->accumulation > ptrNode->limit) {
            ptrNode = removeNode(ptrNode);
            totalPlayer--;
        } else {
            ptrNode = ptrNode->next;
        }
        countNumber++;
    }
    winner = ptrNode->order;
    free(ptrNode);
    printf("%d", winner);
    return 0;
}