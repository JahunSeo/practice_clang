#include <stdio.h>
int main(void) {
    float a;
    double b;
    char c;
    a = 123.456789123456789f;
    b = 3.141592;
    c = 'A';
    printf("a is float %5.10f\n", a);
    printf("a is float %.2f\n", 1.0);
    printf("b is float %f\n", b);

    printf("c is char %d\n", c);

    return 0;
}