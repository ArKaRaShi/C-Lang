#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXTSIZE 21

typedef struct item {
    char *text;
    struct item *next;
} item_t;

typedef struct hash {
    item_t **table;
    int size;
    int hash_key;
} hash_t;

item_t *create_item(char *str) {
    item_t *new_item = (item_t *) malloc(sizeof(item_t));
    new_item->text = (char *) malloc(sizeof(char) * TEXTSIZE);
    new_item->next = NULL;
    strcpy(new_item->text, str);
    return new_item;
}

unsigned int pre_hash(char *str, int hash_key) {
    unsigned int hash_value = 0;
    int text_length = strlen(str);
    for (int i = 0; i < text_length; i++)
        hash_value = hash_key * hash_value + str[i];
    return hash_value;
}

unsigned int hash_map(unsigned int hash_value, int size) {
    return hash_value % size;
}

hash_t *init_hashtable(int size, int hash_key) {
    hash_t *hash_table = (hash_t *) malloc(sizeof(hash_t));
    hash_table->table = (item_t **) malloc(sizeof(item_t *) * size);
    hash_table->size = size;
    hash_table->hash_key = hash_key;
    for (int itr = 0; itr < size; itr++)
        *(hash_table->table + itr) = NULL;
    return hash_table;
}

void insert(hash_t *hashtable, char *str) {
    unsigned int hash_value = pre_hash(str, hashtable->hash_key);
    unsigned int index = hash_map(hash_value, hashtable->size);

    item_t *temp_head = *(hashtable->table + index);
    *(hashtable->table + index) = create_item(str);
    (*(hashtable->table + index))->next = temp_head; 
}

int search(hash_t *hashtable, char *str) {
    unsigned int hash_value = pre_hash(str, hashtable->hash_key);
    unsigned int index = hash_map(hash_value, hashtable->size);
    
    item_t *itr = (*(hashtable->table + index));
    while (itr != NULL) {
        if (!strcmp(itr->text, str))
            return index;
        itr = itr->next;
    }
    return -1;
}

int main(void) {
    hash_t *hashtable = NULL;
    char *text = NULL;
    int m, n, i, hash_key;
    int command;
    scanf("%d %d %d", &m, &n, &hash_key);
    hashtable = init_hashtable(m, hash_key);
    text = (char *)malloc(sizeof(char)
    *TEXTSIZE);
    for (i=0; i<n; i++) {
        scanf("%d %s", &command, text);
        switch (command) {
            case 1:
                insert(hashtable, text);
                break;
            case 2:
                printf("%d\n",
                search(hashtable, text));
                break;
        }
    }
    return 0;
}