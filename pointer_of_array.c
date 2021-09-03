#include <stdio.h>
int main(void) {
    // 아이템 자료형 int인 크기 5의 배열 생성
    int arr[5] = {10, 20, 30, 40, 50};
    int i;
    printf("{ ");
    for (i =0; i < 5; i++) {
        printf("%d, ", arr[i]);
    }
    printf("} \n\n");

    // int *parr 은 배열의 0번째 아이템 주소값을 가리키는 포인터
    // - arr은 sizeof 혹은 &연산자 를 만나지 않는 한, 배열의 0번째 아이템 주소값으로 변환되기 때문
    // - 하지만 arr 과 parr 이 동일하지는 않음 (size를 확인하면 그 의미의 차이를 알 수 있음) 
    int *parr = arr;
    printf("int *parr = arr\n");
    printf("[ arr   ] %p\n", arr);
    printf("[ *arr  ] %d\n", *arr);
    // arr은 배열 자체를 의미하므로, 배열의 사이즈는 5 x 4바이트(integer 크기)
    printf("sizeof arr %lu\n", sizeof(arr)); 
    printf("[ parr  ] %p\n", parr);
    printf("[ *parr ] %d\n", *parr);
    // parr은 배열의 0번째 아이템을 가리키는 주소값이므로, 주소값 사이즈 8바이트(64비트)
    printf("sizeof parr %lu\n", sizeof(parr)); 
    // 아래 코드는 에러 발생!
    // printf("[ (*parr)[3] ] %d", (*parr)[3]); 
    printf("\n");
    
    // int (*parr)[5] 는 크기 5인 배열의 주소값을 가리키는 포인터
    // - arr 자체를 가리키려면 &연산자를 활용해 &arr 로 입력 
    // - 주의: int (*parr2)[5] = arr 이렇게 작성하면 에러 발생!
    // 아래 둘 다 가능: "parr2는 포인터인데, 그 주소값은 arr의 주소값인 &arr 야."
    // int (*parr2)[5] = &arr;
    int (*parr2)[5];
    parr2 = &arr;

    printf("int (*parr2)[5] = &arr\n");
    // parr2 는 배열 arr 자체를 가리키는 포인터이므로, parr2는 arr과 동일하게 배열의 0번째 아이템 주소값으로 변환됨
    printf("[ parr2  ] %p\n", parr2); 
    // parr2 는 배열 arr 자체를 가리키는 포인터이므로 *parr2는 그 값 arr을 의미하고, 
    // arr을 출력하면 배열의 0번째 아이템 주소값으로 변환됨
    printf("[ *parr2 ] %p\n", *parr2);
    // *parr2는 포인터의 값 arr이 되므로 아래와 같은 코드 실행 가능
    printf("[ (*parr2)[3] ] %d\n", (*parr2)[3]);
    printf("[ arr[3] ] %d\n", arr[3]);
    printf("\n");

    // int *parr3[5] 는 아이템 자료형이 포인터인 크기 5의 배열
    // - 즉 포인터들의 배열을 의미함
    // int *parr3[5];

    // 2차원 배열에서 테스트
    printf(" {{1,2,3}, {10,20,30}} \n");
    int arr2[2][3] = {{1,2,3}, {10,20,30}};

    // arr2 는 arr2의 0번째 아이템의 주소값으로 변환됨 (즉, 하위 배열 {1,2,3}의 주소값)
    // arr2의 0번째 아이템이 크기 3의 배열이므로, 그 주소값을 저장할 포인터는 (*p)[3]의 형태를 띄어야 함    
    // 아래 2개 모두 가능: "p는 크기 3의 배열을 가리킬 포인터인데, 그 주소값은 arr2의 0번째 아이템 주소값이야."
    // int (*p)[3] = arr2;
    int (*p)[3];
    p = arr2; // arr2의 0번째 아이템 주소값, 즉 {1,2,3}의 주소값

    // p[1][2] 는  *(*(p + 1) + 2)
    // - (p+1)   : p는 arr2의 0번째 아이템 주소값이므로, 주소값에 1을 더하면, arr2의 1번째 아이템의 주소값이 됨
    // - *(p+1)  : arr2의 1번째 아이템은 {10,20,30}이므로, 그 값 자체인 배열을 의미하게 됨
    // - (*(p+1)+2) : 이 맥락에서 *(p+1)은 {10,20,30}의 0번째 아이템, 10 의 주소값을 의미하게 되며, 
    //                주소값에 2를 더하면 {10,20,30}의 2번째 아이템 주소값이 됨
    // - *(*(p+1)+2) : 주소값인 (*(p+1)+2)의 실제 값, 30을 의미하게 됨
    //
    // 결과적으로 위 과정에 의해 p는 단지 배열 arr2의 0번째 아이템 주소값을 의미하지만,
    // p[1][2]가 arr2[1][2]과 동일한 의미를 가지게 됨
    printf("[ p, arr2 ] %p %p\n", p, arr2);
    printf("[ *p, *arr2 ] %p %p\n", *p, *arr2);     
    printf("[ **p, **arr2 ] %d %d\n", **p, **arr2);     
    printf("[ **(p+1), **(arr2+1) ] %d %d\n", **(p+1), **(arr2+1));     

    printf("[ p[1][2] ] %d\n", p[1][2]);
    printf("[ arr2[1][2] ] %d\n", arr2[1][2]);

    printf("\n");
    return 0;
}