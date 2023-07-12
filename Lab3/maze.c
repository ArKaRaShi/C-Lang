#include <stdio.h>

int dfsRecursive(int col, int row, char **table) {



    return 0;
}

void displayTable(char *table, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", *(table + i));
    }
}

int main() {
    // char something[1][10];
    // gets(something[0]);
    // printf("%s", something[0]);
    int n;
    scanf("%d", &n);
    char table[n][n+1];
    while (getchar() != '\n') {}
    for (int i = 0; i < n; i++) 
        gets(table[i]);
    displayTable(&table, n);
    return 0;
}