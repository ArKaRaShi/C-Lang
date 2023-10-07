#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 51

typedef struct pair {
    char *original_str;
    char *sorted_str;
} pair_t;

typedef struct list {
    pair_t *str_pair;
    int *pair_value;
} list_t;

list_t *create_list(int size) {
    list_t *new_list = (list_t *) malloc(sizeof(list_t));
    new_list->str_pair = (pair_t *) malloc(sizeof(pair_t) * size);
    new_list->pair_value = (int *) malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        (new_list->str_pair + i)->original_str = (char *) malloc(sizeof(char) * STRSIZE);
        (new_list->str_pair + i)->sorted_str = (char *) malloc(sizeof(char) * STRSIZE);
    }
    return new_list;
}

void sorted(char *in_str) {
    const int size = strlen(in_str);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (in_str[j] > in_str[j + 1]) {
                char temp_char = in_str[j];
                in_str[j] = in_str[j + 1];
                in_str[j + 1] = temp_char;
            }
        }
    }
}

int calculate_value(char *str) {
    int total_value = 0;
    const int size = strlen(str);
    for (int i = 0; i < size; i++)
        total_value += str[i];
    return total_value;
}

int main(void) {
    int n, question;
    scanf("%d %d", &n, &question);
    list_t *str_list = create_list(n);
    char *in_str = (char *) malloc(sizeof(char) * STRSIZE);

    while (getchar() != '\n') {}
    for (int i = 0; i < n; i++) {
        scanf("%s", in_str);
        strcpy((str_list->str_pair + i)->original_str, in_str);
        sorted(in_str);
        strcpy((str_list->str_pair + i)->sorted_str, in_str);
        *(str_list->pair_value + i) = calculate_value(in_str);
    }

    int temp_value;
    for (int i = 0; i < question; i++) {
        scanf("%s", in_str);
        temp_value = calculate_value(in_str);
        sorted(in_str);
        for (int j = 0; j < n; j++) {
            if (temp_value == *(str_list->pair_value + j)) 
                if (!strcmp(in_str, (str_list->str_pair + j)->sorted_str))
                    printf("%s ", (str_list->str_pair + j)->original_str);
        }
        printf("\n");
    }
    return 0;
}