#include <stdio.h>
int add(int v) {
    printf("add! %d\n", v);
    return v + 3;
}

int main(void) {
    int a = 3;
    printf("%d\n", a);
    a = add(a);
    printf("%d\n", a);
    return 0;
}