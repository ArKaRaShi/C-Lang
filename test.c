#include <stdio.h>
#include <stddef.h>

struct data {
    int firstNumber;
    size_t secondNumber;
    char text[10];
};

int main() {
    struct data newData;
    printf("%p %zu bytes\n", &newData, sizeof(newData));
    printf("%p %zu bytes\n", &newData.firstNumber, sizeof(newData.firstNumber));
    printf("%zu bytes\n", sizeof(newData.secondNumber));
    printf("%zu bytes\n", sizeof(newData.text));
    printf("Offset of firstNumber: %zu\n", offsetof(struct data, firstNumber));
    printf("Offset of secondNumber: %zu\n", offsetof(struct data, secondNumber));
    printf("Offset of text: %zu\n", offsetof(struct data, text));
    return 0;
}
