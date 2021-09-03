#include <stdio.h>
int main(void) {
    int a = 1;
    if (!(a=2)) {
        printf("if %d\n", a);        
    } else {
        printf("else %d\n", a);        
    }
    printf("%d\n", ++a);
    if ((a=8)) {
        printf("if %d\n", a);
    } else {
        printf("else %d\n", a);
    }
    printf("%d\n", a=9);
    return 0;
}