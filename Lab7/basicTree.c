#include <stdio.h>
#include <stdlib.h>

// You can define your own (one or more)
// structures here. However, we eventually
// need the data type "tree_t".
// For example:
typedef struct node {
    int value;
    struct node *sibling;
    struct node *child;
} node_t;
typedef node_t tree_t;

node_t *createNode(int value) {
    node_t *newNode = (node_t *) malloc(sizeof(node_t));
    newNode->value = value;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

node_t *findNode(tree_t *t, int value) {
    node_t *currNode = t;
    node_t *tmpNode = NULL;
    
    if (currNode == NULL)
        return NULL;

    if (currNode->value == value)
        return currNode;
    
    tmpNode = findNode(currNode->child, value);
    if (tmpNode == NULL)
        tmpNode = findNode(currNode->sibling, value);

    return tmpNode;
}

node_t *findParentNode(tree_t *t, int value) {
    node_t *currNode = t;
    node_t *tmpNode = NULL;

    if (currNode->child != NULL) {
        if (currNode->child->value == value)
            return currNode;
    } else if (currNode->sibling != NULL) {
        if (currNode->sibling->value == value)
            return currNode;
    } else
        return NULL;

    tmpNode = findParentNode(currNode->child, value);
    if (tmpNode == NULL)
        tmpNode = findParentNode(currNode->sibling, value);

    return tmpNode;
}
// option = 1 for node, 2 for parent
void destroy(tree_t *t) {
    if (t != NULL) {
        destroy(t->child);
        destroy(t->sibling);
        free(t);
    }
}

tree_t *attach(tree_t *t, int parentValue, int childValue) {
    node_t *newNode = createNode(childValue);
    node_t *parentNode = NULL;

    if (t == NULL)
        t = newNode;
    
    else {
        parentNode = findNode(t, parentValue);
        // printf("get value = %d\n", parentNode->value);
        if (parentNode->child == NULL)
            parentNode->child = newNode;
        else {
            parentNode = parentNode->child;
            while (parentNode->sibling != NULL)
                parentNode = parentNode->sibling;
            parentNode->sibling = newNode;
        }
    }
     
    return t;
}

tree_t *detach(tree_t *t, int value) {
    node_t *parentNode = findParentNode(t, value);
    tree_t *subTree = NULL;

    if (parentNode->child != NULL) {
        if (parentNode->child->value == value) {
            subTree = parentNode->child;
            parentNode->child = parentNode->child->sibling;
        }
    }

    if (parentNode->sibling != NULL) {
        if (parentNode->sibling->value == value) {
            subTree = parentNode->sibling;
            parentNode->sibling = parentNode->sibling->sibling;
        }
    }

    subTree->sibling = NULL;
    destroy(subTree);
    return t;
}


void print_tree(tree_t *t) {
    // node_t *currNode = t;
    if (t != NULL) {
        printf("-> Node: %d go child\n", t->value);
        print_tree(t->child);
        printf("-> Node %d go sibling\n", t->value);
        print_tree(t->sibling);
    }
    else
        printf(" Nothing\n");
}

int main(void) {
    tree_t *t = NULL;
    int n, i, command;
    int parent, child, node, start, end;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch(command) {
            case 1:
                scanf("%d %d", &parent, &child);
                t = attach(t, parent, child);
                break;
            case 2:
                scanf("%d", &node);
                t = detach(t, node);
                break;
            // case 3:
            //     scanf("%d", &node);
            //     printf("%d\n", search(t, node));
            //     break;
            // case 4:
            //     scanf("%d", &node);
            //     printf("%d\n", degree(t, node));
            //     break;
            // case 5:
            //     scanf("%d", &node);
            //     printf("%d\n", is_root(t, node));
            //     break;
            // case 6:
            //     scanf("%d", &node);
            //     printf("%d\n", is_leaf(t, node));
            //     break;
            // case 7:
            //     scanf("%d", &node);
            //     siblings(t, node);
            //     break;
            // case 8:
            //     scanf("%d", &node);
            //     printf("%d\n", depth(t, node));
            //     break;
            // case 9:
            //     scanf("%d %d", &start, &end);
            //     print_path(t, start, end);
            //     break;
            // case 10:
            //     scanf("%d %d", &start, &end);
            //     printf("%d\n",
            //     path_length(t, start, end));
            //     break;
            // case 11:
            //     scanf("%d", &node);
            //     ancestor(t, node);
            //     break;
            // case 12:
            //     scanf("%d", &node);
            //     descendant(t, node);
            //     break;
            // case 13:
            //     bfs(t);
            //     break;
            // case 14:
            //     dfs(t);
            //     break;
            case 15:
                print_tree(t);
                break;
        }
    }
    return 0;
}

/*
11
1 -1 1
1 1 2
1 1 3
1 2 4
1 2 5
1 5 6
1 6 7
2 7
15 
2 2
15
*/