#include <stdio.h>
#include <stdlib.h>

// You can define your own (one or more)
// structures here. However, we eventually
// need the data type "tree_t".
// For example:
typedef struct node {
    int value;
    int level;
    struct node *sibling;
    struct node *child;
} node_t;
typedef node_t tree_t;

node_t *createNode(int value, int level) {
    node_t *newNode = (node_t *) malloc(sizeof(node_t));
    newNode->value = value;
    newNode->level = level;
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

node_t *findConnectNode(tree_t *t, int value) {
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

    tmpNode = findConnectNode(currNode->child, value);
    if (tmpNode == NULL)
        tmpNode = findConnectNode(currNode->sibling, value);

    return tmpNode;
}

node_t *findParrentNode(tree_t *t, int value) {
    node_t *currNode = t;
    node_t *tmpNode = NULL;

    if (currNode == NULL)
        return NULL;

    tmpNode = currNode->child;
    while (tmpNode != NULL) {
        if (tmpNode->value == value) 
            return currNode;
        tmpNode = tmpNode->sibling;
    }

    tmpNode = findParrent(currNode->child, value);
    if (tmpNode == NULL) 
        tmpNode = findParrent(currNode->sibling, value);
    
    return tmpNode;
}

void destroy(tree_t *t) {
    if (t != NULL) {
        destroy(t->child);
        destroy(t->sibling);
        free(t);
    }
}

tree_t *attach(tree_t *t, int parentValue, int childValue) {
    node_t *parentNode = NULL;

    if (t == NULL)
        t = createNode(childValue, 0);

    else {
        parentNode = findNode(t, parentValue);
        if (parentNode->child == NULL)
            parentNode->child = createNode(childValue, parentNode->level + 1);
        else {
            parentNode = parentNode->child;
            while (parentNode->sibling != NULL)
                parentNode = parentNode->sibling;
            parentNode->sibling = createNode(childValue, parentNode->level);
        }
    }
     
    return t;
}

tree_t *detach(tree_t *t, int value) {
    node_t *connectNode = findConnectNode(t, value);
    tree_t *subTree = NULL;

    if (connectNode->child != NULL) {
        if (connectNode->child->value == value) {
            subTree = connectNode->child;
            connectNode->child = connectNode->child->sibling;
        }
    }

    if (connectNode->sibling != NULL) {
        if (connectNode->sibling->value == value) {
            subTree = connectNode->sibling;
            connectNode->sibling = connectNode->sibling->sibling;
        }
    }

    subTree->sibling = NULL;
    destroy(subTree);
    return t;
}

int search(tree_t *t, int value) {
    node_t *targetNode = findNode(t, value);
    if (targetNode != NULL)
        return 1;
    return 0;
}

int degree(tree_t *t, int value) {
    node_t *targetNode = findNode(t, value);
    node_t *children = targetNode->child;
    
    int countNode = 0;
    if (children != NULL) {
        countNode++;
        while (children->sibling != NULL) {
            countNode++;
            children = children->sibling;
        }
    }
    return countNode;
}

int is_root(tree_t *t, int value) {
    node_t *targetNode = findNode(t, value);
    if (targetNode->level == 0)
        return 1;
    return 0;
}

int is_leaf(tree_t *t, int value) {
    node_t *targetNode = findNode(t, value);
    if (targetNode->child == NULL)
        return 1;
    return 0;
}

void siblings(tree_t *t, int value) {
    node_t *parrentNode = findParrentNode(t, value);
    node_t *tmpNode = NULL;
    if (parrentNode != NULL) {
        tmpNode = parrentNode->child;
        while (tmpNode != NULL) {
            if (tmpNode->value != value)
                printf("%d ",tmpNode->value);
            tmpNode = tmpNode->sibling;
        }
    }
    printf("\n");
}

void print_tree(tree_t *t) {
    // node_t *currNode = t;
    if (t != NULL) {
        printf("-> Node: %d level %d go child\n", t->value, t->level);
        print_tree(t->child);
        printf("-> Node %d level %d go sibling\n", t->value, t->level);
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
            case 3:
                scanf("%d", &node);
                printf("%d\n", search(t, node));
                break;
            case 4:
                scanf("%d", &node);
                printf("%d\n", degree(t, node));
                break;
            case 5:
                scanf("%d", &node);
                printf("%d\n", is_root(t, node));
                break;
            case 6:
                scanf("%d", &node);
                printf("%d\n", is_leaf(t, node));
                break;
            case 7:
                scanf("%d", &node);
                siblings(t, node);
                break;
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

23
1 -1 1
1 1 2
1 1 3
1 2 4
1 2 5
1 3 6
1 3 7
1 4 8
1 5 9
1 5 10
1 6 11
1 6 12
1 6 13
1 13 14
*/