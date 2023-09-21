#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t bst_t;

node_t *create_node(int data) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

bst_t *find_insert_parent_node(bst_t *t, int data) {
    if (t == NULL)
        return NULL;

    if (data < t->data)
        if (t->left == NULL)
            return t;
        else
            return find_insert_parent_node(t->left, data);

    else
        if (t->right == NULL)
            return t;
        else
            return find_insert_parent_node(t->right, data);

}

bst_t *insert(bst_t *t, int data) {
    node_t *new_node = create_node(data);
    bst_t *sub_bst = find_insert_parent_node(t, data);
    if (sub_bst == NULL) 
        return new_node;
    
    if (data < sub_bst->data)
        sub_bst->left = new_node;
    else
        sub_bst->right = new_node;

    return t;
}

node_t *find_min_value_node(bst_t *t) {
    if (t->left == NULL)
        return t;
    return find_min_value_node(t->left);
}

node_t *find_max_value_node(bst_t *t) {
    if (t->right == NULL)
        return t;
    return find_max_value_node(t->right);
}

bst_t *find_target_parent_node(bst_t *t, int data) {
    if (t == NULL)
        return NULL;
    
    if (data == t->data)
        return NULL;

    if (t->left != NULL)
        if (data == t->left->data)
            return t;
    
    if (t->right != NULL)
        if (data == t->right->data)
            return t;
    
    if (data < t->data)
        return find_target_parent_node(t->left, data);
    else
        return find_target_parent_node(t->right, data);
}

bst_t *find_target_node(bst_t *t, int data) {
    if (t == NULL)
        return NULL;
    
    if (data == t->data)
        return t;
    
    if (data < t->data)
        return find_target_node(t->left, data);
    else
        return find_target_node(t->right, data);
    
}

/*
16
1 82
1 79
1 66
1 78
1 83
1 80
1 81
1 85
*/

bst_t *delete(bst_t *t, int data) {
    bst_t *target_sub_tree = find_target_node(t, data);
    bst_t *target_parent_sub_tree = find_target_parent_node(t, data);
    node_t *substitute_node = NULL;
    int direction;

    if (target_parent_sub_tree != NULL) {
        if (target_parent_sub_tree->left != NULL)
            if (target_sub_tree->data == target_parent_sub_tree->left->data) 
                direction = 1;
        if (target_parent_sub_tree->right != NULL)
            if (target_sub_tree->data == target_parent_sub_tree->right->data) 
                direction = 2;
    } else 
        direction = 0;
    
    if (target_sub_tree->left != NULL && target_sub_tree->right != NULL) {
        substitute_node = create_node(find_min_value_node(target_sub_tree->right)->data);
        t = delete(t, substitute_node->data);
        substitute_node->left = target_sub_tree->left;
        substitute_node->right = target_sub_tree->right;
    } else if (target_sub_tree->left != NULL) {
        substitute_node = target_sub_tree->left; 
    } else if (target_sub_tree->right != NULL) {
        substitute_node = target_sub_tree->right;
    } else {
        substitute_node = NULL;
    }
    free(target_sub_tree);

    if (direction == 1) 
        target_parent_sub_tree->left = substitute_node;
    else if (direction == 2)
        target_parent_sub_tree->right = substitute_node;
    else
        t = substitute_node;

    return t;
}

int find(bst_t *t, int data) {
    if (t == NULL)
        return 0;

    if (data == t->data)
        return 1;
    
    if (data < t->data)
        return find(t->left, data);
    else
        return find(t->right, data);
}

int find_min(bst_t *t) {
    return find_min_value_node(t)->data;
}

int find_max(bst_t *t) {
    return find_max_value_node(t)->data;
}

void print_tree(bst_t *t) {
    if (t != NULL) {
        printf("Node: %d", t->data);
        if (t->left != NULL || t->right != NULL)
            printf(" -> ");

        if (t->left != NULL && t->right != NULL)
            printf("Left: %d, Right %d\n", t->left->data, t->right->data);
        else if (t->left != NULL)
            printf("Left: %d\n", t->left->data);
        else if (t->right != NULL)
            printf("Right: %d\n", t->right->data);


        print_tree(t->left);
        print_tree(t->right);
    }
}

int main(void) {
    bst_t *t = NULL;
    int n, i;
    int command, data;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d", &data);
                t = insert(t, data);
                break;
            case 2:
                scanf("%d", &data);
                t = delete(t, data);
                break;
            case 3:
                scanf("%d", &data);
                printf("%d\n", find(t, data));
                break;
            case 4:
                printf("%d\n", find_min(t));
                break;
            case 5:
                printf("%d\n", find_max(t));
                break;
            case 6:
                print_tree(t);
                break;
        }
    }
    return 0;
}