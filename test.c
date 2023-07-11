#include <stdio.h>

struct data {
    int firstNumber;
    size_t secondNumber;
    char text[10];
};

int main() {
    struct data newData;
    printf("%llu bytes\n", sizeof (newData));
    printf("%llu bytes\n", sizeof (newData.firstNumber));
    printf("%llu bytes\n", sizeof (newData.secondNumber));
    printf("%llu bytes\n", sizeof (newData.text));
    return 0;
}