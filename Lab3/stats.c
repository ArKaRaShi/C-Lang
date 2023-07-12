#include <stdio.h>
#include <stdlib.h>

void findStats(int *arr, double *avg, int *max, int *min, int n) {
    *avg = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            *max = *(arr + i);
            *min = *(arr + i);
        }
        
        if (*(arr + i) > *max) 
            *max = *(arr + i);
        
        if (*(arr + i) < *min) 
            *min = *(arr + i);

        *avg += *(arr + i);
    }
    *avg = *avg / n;
}

int main() {
    int n, i, maxi, mini;
    double avg;
    int *nums;
    scanf("%d", &n);
    nums = (int *)malloc(sizeof (int) *n);
    for (i=0; i<n; i++)
        scanf("%d", nums+i);
    findStats(nums, &avg, &maxi, &mini, n);
    printf("%.2f %d %d", avg, maxi, mini);
    return 0;
}