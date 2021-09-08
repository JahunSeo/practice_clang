#include <stdio.h>
int main(void) {
    int n;
    int a, b;
    int ans = 0;
    scanf("%d\n", &n);
    printf("n: %d\n", n);
    for (int i=0; i < n; i++) {
        scanf("%d %d\n", &a, &b);
        ans = 1;
        for (int k=0; k < b; k++) {
            ans = (ans * a)%10;
            printf(" %d ", ans);
        }
        printf("%d\n", ans);
    }
    return 0;
}