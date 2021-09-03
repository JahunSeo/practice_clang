#include <stdio.h>
int update(int *pa) {
    printf("%p\n", pa);
    printf("%d\n", *pa);

    *pa += 10;
    return 0;
}

int main(void) {
    int a = 0;
    
    update(&a);
    printf("result %d\n", a);
    return 0;
}