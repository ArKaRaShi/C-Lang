#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXTSIZE 21

typedef char* item_t;
typedef struct hash {
    item_t *table;
    int size;
    int hash_key;
} hash_t;

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
    hash_table->table = (item_t *) malloc(sizeof(item_t) * size);
    hash_table->size = size;
    hash_table->hash_key = hash_key;
    for (int itr = 0; itr < size; itr++) {
        *(hash_table->table + itr) = (char *) malloc(sizeof(char) * TEXTSIZE);
        strcpy(*(hash_table->table + itr), "");
    }
    return hash_table;
}

void insert(hash_t *hashtable, char *str) {
    unsigned int hash_value = pre_hash(str, hashtable->hash_key);
    unsigned int index = hash_map(hash_value, hashtable->size);
    unsigned int init_index = index;

    int i = 0;
    while (strlen(*(hashtable->table + index))) {
        index = (init_index + (i + i*i) / 2) % hashtable->size;
        i++;
    }
    strcpy(*(hashtable->table + index), str);
}

int search(hash_t *hashtable, char *str) {
    unsigned int hash_value = pre_hash(str, hashtable->hash_key);
    unsigned int index = hash_map(hash_value, hashtable->size);
    unsigned int init_index = index;

    int i = 1;
    do {
        if (strcmp(str, *(hashtable->table + index)) == 0)
            return index;
        index = (init_index + (i + i*i) / 2) % hashtable->size;
        i++;
    } while (index != init_index);
    return -1;
}

int main(void) {
    hash_t *hashtable = NULL;
    char *text = NULL;
    int m, n, i, hash_key;
    int command;
    scanf("%d %d %d", &m, &n, &hash_key);
    hashtable = init_hashtable(m, hash_key);
    text = (char *)malloc(sizeof(char)*TEXTSIZE);
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