#include <stdio.h>




int main() {
    while (1) {
        char temp = getchar();
        printf("%c\n", temp);
        if (temp == '\n') break;
    }



    return 0;
}