#include <stdio.h>
#include <stdlib.h>
// #include <week9.h>

#ifndef __avl_tree__
typedef struct node {
    int data;
    int height;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t avl_t;
#endif

void print_tree_2(avl_t *t, int depth, char pre){
  int i;

  if (t != NULL) {
    for (i=0; i<depth; i++)
      printf("    ");
    printf("%c%d %d\n", pre, t->data, t->height);
    print_tree_2(t->left, depth+1, 'L');
    print_tree_2(t->right, depth+1, 'R');
  }
}

void print_tree(avl_t *t){
  print_tree_2(t, 0, 'r');
}

node_t *create_node(int data) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->data = data;
    new_node->height = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

avl_t *find_parent_node(avl_t *t, int data) {
    if (t == NULL)
        return NULL;
    
    if (data < t->data)
        if (t->left == NULL)
            return t;
        else
            return find_parent_node(t->left, data);
    else
        if (t->right == NULL)
            return t;
        else
            return find_parent_node(t->right, data);
}

int max_height(int h1, int h2) {
    if (h1 > h2)
        return h1;
    return h2;
}

int get_height(avl_t *t) {
    if (t == NULL)
        return -1;
    return t->height;
}

void update_height(avl_t **t) {
    int left_height, right_height;
    
    left_height = get_height((*t)->left);
    right_height = get_height((*t)->right);
    
    (*t)->height = max_height(left_height, right_height) + 1;
}


int decision_rotation(avl_t **t, int calling) {
    int left_hegiht = get_height((*t)->left);
    int right_height = get_height((*t)->right);

    int rotatation_case = 0;
    if (calling == 1) {
        const int left_case = 1;
        const int right_case = 3;

        if (left_hegiht > right_height) 
            rotatation_case = rotatation_case + left_case + decision_rotation(&((*t)->left), 2);
        else
            rotatation_case = rotatation_case + right_case + decision_rotation(&((*t)->right), 2);

    } else if (calling == 2) {
        const int left_case = 0;
        const int right_case = 1;

        if (left_hegiht > right_height)
            return left_case;
        else
            return right_case;
    }
    return rotatation_case;
}

void right_rotation(avl_t **t) {
    avl_t *origin_left_avl = (*t)->left;
    avl_t *origin_right_avl = (*t)->right;
    avl_t *left_right_avl = (*t)->left->right;

    avl_t *new_right_avl = create_node((*t)->data);
    free(*t);

    *t = origin_left_avl;
    (*t)->right = new_right_avl;
    new_right_avl->left = left_right_avl;
    new_right_avl->right = origin_right_avl;
}

void left_rotation(avl_t **t) {
    avl_t *origin_left_avl = (*t)->left;
    avl_t *origin_right_avl = (*t)->right;
    avl_t *right_left_avl = (*t)->right->left;
    
    avl_t *new_left_avl = create_node((*t)->data);
    free(*t);

    *t = origin_right_avl;
    (*t)->left = new_left_avl;
    new_left_avl->left = origin_left_avl;
    new_left_avl->right = right_left_avl;
}

void perform_rotation(avl_t **t, int rotation_case) {
    switch (rotation_case) {
        case 1: right_rotation(t);
                break;
        case 2: left_rotation(&((*t)->left));
                right_rotation(t);
                break;
        case 3: right_rotation(&((*t)->right));
                left_rotation(t);
                break;
        case 4: left_rotation(t);
                break;
        default: break;


    }

}

void full_backtrack_update_height(avl_t **t) {
    if (*t != NULL) {
        if ((*t)->left != NULL)
            full_backtrack_update_height(&((*t)->left));
        if ((*t)->right != NULL)    
            full_backtrack_update_height(&((*t)->right));
        update_height(t);
    }
}

void balancing(avl_t **t) {
    int balance_factor = abs(get_height((*t)->left) - get_height((*t)->right));
    if (balance_factor > 1) {
        perform_rotation(t, decision_rotation(t, 1));
        // full_backtrack_update_height(t);      
        if ((*t)->left != NULL)
            update_height(&((*t)->left));
        if ((*t)->right != NULL)
            update_height(&((*t)->right)); 
        update_height(t);
    }
}


avl_t *attrach_node(avl_t *t, node_t *new_node) {
    if (t == NULL)
        t = new_node;
    else {
        avl_t *sub_avl = NULL;
        if (new_node->data < t->data) {
            sub_avl = attrach_node(t->left, new_node);
            t->left = sub_avl;
        }
        else {
            sub_avl = attrach_node(t->right, new_node);
            t->right = sub_avl;
        }
        update_height(&t);
        balancing(&t);
    }
    return t;
} 

avl_t *insert(avl_t *t, int data) {
    node_t *new_node = create_node(data);
    t = attrach_node(t, new_node);
    return t;
}

node_t *find_minimum_node(avl_t *t) {
    if (t->left == NULL)
        return t;
    return find_minimum_node(t->left);

}

avl_t *find_target_parent(avl_t *t, int data) {
    if (t->data == data)
        return t;
    
    if (data < t->data)
        if (data == t->left->data)
            return t;
        else
            return find_target_parent(t->left, data);
    else
        if (data == t->right->data)
            return t;
        else
            return find_target_parent(t->right, data); 
}

int find_direction(avl_t *t, int data) {
    if (t->left != NULL)
        if (t->left->data == data)
            return 1;
    if (t->right != NULL)
        if (t->right->data == data)
            return 2;
    return 0;
}

avl_t *find_target_with_parent(avl_t *t, int direction) {
    if (direction == 1)
        return t->left;
    if (direction == 2)
        return t->right;
    return t;
}

void backtrack_update_height(avl_t **t, int data) {
    if (*t != NULL) {
        if (data < (*t)->data) {
            backtrack_update_height(&((*t)->left), data);
            update_height(t);
        } else {
            backtrack_update_height(&((*t)->right), data);
            update_height(t);
        }
    }
}

void backtrack_balancing(avl_t **t, int data) {
    if (*t != NULL) {
        if (data < (*t)->data) {
            backtrack_balancing(&((*t)->left), data);
            balancing(t);
        } else {
            backtrack_balancing(&((*t)->right), data);
            balancing(t);
        }
    }
}

avl_t *perform_deletion(avl_t *t, int data) {
    avl_t *target_parent = find_target_parent(t, data);
    int direction = find_direction(target_parent, data);
    avl_t *target = find_target_with_parent(target_parent, direction);
    avl_t *substitude = NULL;
    if (target->left != NULL && target->right != NULL) {
        substitude = create_node(find_minimum_node(target->right)->data);
        t = perform_deletion(t, substitude->data);
        substitude->left = target->left;
        substitude->right = target->right;
    } else if (target->left != NULL) {
        substitude = target->left;
    } else if (target->right != NULL) {
        substitude = target->right;
    } else {
        substitude = NULL;
    } 
    free(target);
    
    switch (direction) {
        case 0: t = substitude;
                break;
        case 1: target_parent->left = substitude;
                break;
        case 2: target_parent->right = substitude;
                break;
    }
    backtrack_update_height(&t, data);
    backtrack_balancing(&t, data);
    return t;
}



avl_t *delete(avl_t *t, int data) {
    t = perform_deletion(t, data);  
    return t;
}

int main(void) {
    avl_t *t = NULL;
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
                print_tree(t);
                break;
        }
    }
    return 0;
}

