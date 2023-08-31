#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int value;
    int level;
    struct treeNode *sibling;
    struct treeNode *child;
} treeNode_t;

typedef struct stackNode {
    struct treeNode *dataNode;
    struct stackNode *next;
} stackNode_t;

typedef treeNode_t tree_t;
typedef stackNode_t stack_t;
// typedef node_t queue_t;

stackNode_t *createStackNode(treeNode_t *dataNode) {
    stackNode_t *newNode = (stackNode_t *) malloc(sizeof(stackNode_t));
    newNode->dataNode = dataNode;
    newNode->next = NULL;
    return newNode;
}

void push(stack_t **s, treeNode_t *tmpNode) {
    stackNode_t *newNode = createStackNode(tmpNode);
    newNode->next = *s;
    *s = newNode;
}

void pop(stack_t **s) {
    stackNode_t *tmpNode = *s;
    *s = (*s)->next;
    free(tmpNode);
}

int stackEmpty(stack_t *s) {
    if (s == NULL)
        return 1; 
    return 0;
}

int stackSize(stack_t *s) {
    int count = 0;
    while (s != NULL) {
        count++;
        s = s->next;
    }
    return count;
}

treeNode_t *top(stack_t *s) {
    return s->dataNode;
}

treeNode_t *createTreeNode(int value, int level) {
    treeNode_t *newNode = (treeNode_t *) malloc(sizeof(treeNode_t));
    newNode->value = value;
    newNode->level = level;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

treeNode_t *findNode(tree_t *t, int value) {
    treeNode_t *currNode = t;
    treeNode_t *tmpNode = NULL;

    if (currNode == NULL)
        return NULL;

    if (currNode->value == value)
        return currNode;
    
    tmpNode = findNode(currNode->child, value);
    if (tmpNode == NULL)
        tmpNode = findNode(currNode->sibling, value);

    return tmpNode;
}

treeNode_t *findConnectNode(tree_t *t, int value) {
    treeNode_t *currNode = t;
    treeNode_t *tmpNode = NULL;

    if (currNode->child != NULL || currNode->sibling != NULL) {
        if (currNode->child != NULL) {
            if (currNode->child->value == value) 
                return currNode;
        } 
        if (currNode->sibling != NULL) {
            if (currNode->sibling->value == value)
                return currNode;
        } 
    } else 
        return NULL;

    tmpNode = findConnectNode(currNode->child, value);
    if (tmpNode == NULL)
        tmpNode = findConnectNode(currNode->sibling, value);

    return tmpNode;
}

treeNode_t *findParrentNode(tree_t *t, int value) {
    treeNode_t *currNode = t;
    treeNode_t *tmpNode = NULL;

    if (currNode == NULL)
        return NULL;

    tmpNode = currNode->child;
    while (tmpNode != NULL) {
        if (tmpNode->value == value) 
            return currNode;
        tmpNode = tmpNode->sibling;
    }

    tmpNode = findParrentNode(currNode->child, value);
    if (tmpNode == NULL) 
        tmpNode = findParrentNode(currNode->sibling, value);
    
    return tmpNode;
}

void findPath(stack_t **s, treeNode_t *startNode, treeNode_t *endNode) {
    treeNode_t *parentOfEndNode = findParrentNode(startNode, endNode->value);

    push(s, endNode);
    if (parentOfEndNode == startNode) {
        push(s, startNode);
    } else {
        findPath(s, startNode, parentOfEndNode);
    }
}

int is_root(tree_t *t, int value) {
    treeNode_t *targetNode = findNode(t, value);
    if (targetNode->level == 0)
        return 1;
    return 0;
}

int is_leaf(tree_t *t, int value) {
    treeNode_t *targetNode = findNode(t, value);
    if (targetNode->child == NULL)
        return 1;
    return 0;
}

void destroy(tree_t *t) {
    if (t != NULL) {
        destroy(t->child);
        destroy(t->sibling);
        free(t);
    }
}

tree_t *attach(tree_t *t, int parentValue, int childValue) {
    treeNode_t *parentNode = NULL;

    if (t == NULL)
        t = createTreeNode(childValue, 0);

    else {
        parentNode = findNode(t, parentValue);
        if (parentNode->child == NULL)
            parentNode->child = createTreeNode(childValue, parentNode->level + 1);
        else {
            parentNode = parentNode->child;
            while (parentNode->sibling != NULL)
                parentNode = parentNode->sibling;
            parentNode->sibling = createTreeNode(childValue, parentNode->level);
        }
    }
     
    return t;
}

tree_t *detach(tree_t *t, int value) {

    if (is_root(t, value)) {
        destroy(t);
        t = NULL;
        return t;
    }


    treeNode_t *connectNode = findConnectNode(t, value);
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
    treeNode_t *targetNode = findNode(t, value);
    if (targetNode != NULL)
        return 1;
    return 0;
}

int degree(tree_t *t, int value) {
    treeNode_t *targetNode = findNode(t, value);
    treeNode_t *children = targetNode->child;
    
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


void siblings(tree_t *t, int value) {
    treeNode_t *parrentNode = findParrentNode(t, value);
    treeNode_t *tmpNode = NULL;
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

int depth(tree_t *t, int value) {
    treeNode_t *targetNode = findNode(t, value);
    return targetNode->level;
}



void print_path(tree_t *t, int startValue, int endValue) {
    treeNode_t *startNode = findNode(t, startValue);
    treeNode_t *endNode = findNode(t, endValue);

    stack_t *s = NULL;

    if (startValue == endValue)
        printf("%d", startValue);
    else {
        findPath(&s, startNode, endNode);
        while (!stackEmpty(s)) {
            printf("%d ", s->dataNode->value);
            pop(&s);
        }
    }
    printf("\n");
}

int path_length(tree_t *t, int startValue, int endValue) {
    treeNode_t *startNode = findNode(t, startValue);
    treeNode_t *endNode = findNode(t, endValue);

    int length = 0;
    stack_t *s = NULL;
    if (startValue == endValue)
        length = 1;
    else {
        findPath(&s, startNode, endNode);
        length = stackSize(s);
        while (!stackEmpty(s)) {
            pop(&s);
        }
    }
    return length;
}

void ancestor(tree_t *t, int value) {
    print_path(t, t->value, value);
}

void print_tree(tree_t *t) {
    // treeNode_t *currNode = t;
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
            case 8:
                scanf("%d", &node);
                printf("%d\n", depth(t, node));
                break;
            case 9:
                scanf("%d %d", &start, &end);
                print_path(t, start, end);
                break;
            case 10:
                scanf("%d %d", &start, &end);
                printf("%d\n",
                path_length(t, start, end));
                break;
            case 11:
                scanf("%d", &node);
                ancestor(t, node);
                break;
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
9 1 2
*/