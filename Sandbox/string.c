#include <stdio.h>
int main(void) {
    char seq[30] = {"hello world!"};

    char *text = seq; // 0번째 글자의 주소값
    char (*text2)[30] = &seq; // 문자열 자체의 주소값
    
    printf("seq %p \n", seq);
    printf("*seq %c \n", *seq);
    printf("seq %s \n", seq);
    printf("text %s \n", text);

    printf("text2[2] %c \n", (*text2)[2]);

    return 0;
}