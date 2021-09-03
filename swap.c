#include <stdio.h>

int swap(int *pm, int *pn) {
    printf("swap pointers: %p %p\n", pm, pn);
    printf("swap values: %d %d\n", *pm, *pn);

    int temp = *pm;
    *pm = *pn;
    *pn = temp;

    return 0;
}

int main(void) {
    int a=3, b=5;
    printf("before: %d %d\n", a, b);
    swap(&a, &b);
    printf("after : %d %d\n", a, b);
    printf("pointer : %p %p\n", &a, &b);
    return 0;
}