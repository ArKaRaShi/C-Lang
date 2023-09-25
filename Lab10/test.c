#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
};

int main(void) {
    struct node *node1 = NULL;

    int boolean = (!node1);
    printf("%d\n", boolean);
    boolean = node1;
    printf("%d\n", boolean);
    return 0;
}