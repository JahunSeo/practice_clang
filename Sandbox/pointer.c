#include <stdio.h>
int main(void) {
    int a = 3;
    int *pa = &a;

    printf("a is %d \n", a);
    printf("pa is %p \n", pa);
    printf("pa's target is %d \n", *pa);

    return 0;
}