#include <stdio.h>
int main(void)
{
    int a = 0xaa;
    printf("a is %d\n", a);
    printf("a is %d\n", ~a);
    printf("a is %x\n", a);
    printf("a is %x\n", ~a);
    printf("a is %d\n", a);
    printf("a is %d\n", ~a);

}