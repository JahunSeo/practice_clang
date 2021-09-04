#include <stdio.h>
#include <stdlib.h>

// A linked list node
struct Node {
    int data;
    struct Node* next;
}; // 구조체 뒤에 ; 붙이기!

// This function prints contents of linked list starting from the given node.
void printList(struct Node* n) {
    // n은 그냥 특정 노드의 시작 주소값을 가리키는 포인터이지만,
    // n이 가리키는 것이 struct Node 라는 것을 알려주었기 때문에, 아래와 같은 절차가 가능함 
    while (n != NULL) {
        printf(" %d ", n->data);
        n = n->next;
    }
    printf("\n");
}


// program to create a simple linked list with 3 nodes
int main(void) {
    printf("hello linkedlist! 1!\n");

    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    // allocates 3 nodes in the heap
    // malloc: 메모리를 할당한다. (memory allocation)
    // - 인자로 전달된 크기 만큼의 메모리를 할당한 후, 그 메모리 블록의 시작 주소값을 가리키는 포인터 리턴
    // - 할당된 메모리는 초기화되지 읺있을 수 있음 (즉 기존에 있었던 내용이 남아 있을 수도 있음)
    // - 해당 포인터의 타입은 언제나 void* 이기 때문에, 사용자가 원하는 타입으로 캐스팅을 해줘야 함
    //   (당연하게도, malloc에 입력값으로 사이즈만 전달하므로 malloc이 리턴한 값은 자료형을 알고 있을 수 없음)
    // - 할당한 메모리는 반드시 free로 해제해주어야 함
    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));

    // 1번째 노드 설정
    head->data = 10; // (*head).data = 10;
    head->next = second; // second 노드의 시작 주소값, (*head).next 와 second 는 struct Node* 로 자료형이 동일함!
    // 2번째 노드 설정
    second->data = 20; // (*second).data = 20;
    second->next = third; // third 노드의 시작 주소값
    // 3번째 노드 설정
    third->data = 30; // (*third).data = 30;
    third->next = NULL;

    printList(head);

    return 0;
}