#include <stdio.h>
#include <math.h>

int isPrime(int number) {
    if (number == 1) return 0;

    for (int i = 2; i <= sqrt(number); i++) {
        if (number % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", isPrime(n));
    return 0;
}

// O(sqrt(n))