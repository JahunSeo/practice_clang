#include <stdio.h>
int main(void) {
    int n;
    int a, b;
    int ans = 3;
    printf("%lu\n", sizeof(char));
    printf("%lu\n", sizeof(int));
    printf("%lu\n", sizeof(long));
    printf("%lu\n", sizeof(float));
    printf("\n");
    printf("%x %x %x\n", 32, 32 | 0, 32 | 1);
    printf("%x %x %x\n", ~7, 8 & ~7, 9 & ~7);

    printf("*(unsigned int *)(%p) = (%d)\n", &a, ans);


    return 0;
}