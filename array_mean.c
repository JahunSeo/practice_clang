#include <stdio.h>
int main(void) {
    int n;
    scanf("%d", &n);

    int arr[n];
    int i;
    int max_value = 0;
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }

    double sum = 0;
    for (i = 0; i < n; i++) {
        sum += (arr[i] / (double)max_value) * 100;
    }
    printf("%f\n", sum / n);

    // printf("%d\n", arr[0]);
    // printf("%d\n", max_value);
    // printf("%f\n", sum);
    
    return 0;
}