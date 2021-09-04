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


// deleteNode:
// Given a reference (pointer to pointer) to the head of a list and a key,
// deletes the first occurrence of key in linked list.
void deleteNode(struct Node** head_ref, int target) {
    // temp: 삭제할 노드를 가리키는 포인터로, head 노드로 초기 설정
    struct Node* temp = *head_ref;
    // prev: 삭제할 노드의 이전 노드
    struct Node* prev;

    // head가 타겟인 경우
    if (temp != NULL && temp->data == target) {
        // head의 다음 노드를 head로 설정
        *head_ref = temp->next;
        // head 노드를 free
        free(temp);
        return;
    }

    // 삭제할 노드 탐색
    // - 이 때, 삭제할 노드의 이전 노드를 함께 유지함 (이전 노도의 next 값을 변경해주어야 하기 때문)
    while (temp != NULL && temp->data != target) {
        prev = temp; // 업데이트 순서 중요!! prev를 temp로 한 칸 이동
        temp = temp->next; // temp도 temp의 next로 한 칸 이동
    }
    // 만약 삭제할 노드가 없는 경우
    if (temp == NULL) {
        return;
    }
    // 삭제할 노드를 찾은 경우
    // 이전 노드의 next를 삭제할 노드의 next로 변경 (unlink the node from linked list)
    prev->next = temp->next;
    // 삭제할 노드에 할당되어 있던 메모리를 free
    free(temp);
    return;
}

// push: 
// Given a reference (pointer to pointer) to the head of a list and an int,
// inserts a new node on the front of the list.
//   본래 head 는 특정 노드의 시작 주소값을 가리키는 포인터 였음
//   그러므로 그 포인터를 변경하려고 하니, 포인터의 포인터를 입력값으로 전달하는 것
void push(struct Node** head_ref, int new_data) {
    // 1. 새로운 노드 할당
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    // 2. 새로운 노드에 데이터 입력
    new_node->data = new_data;
    // 3. 기존에 head였던 노드의 시작 주소값을 새로운 노드의 next에 입력
    new_node->next = (*head_ref);
    // 4. 새로운 노드를 head로 설정
    // - 포인터의 포인터를 *로 변환하면 바로 struct Node*인 head
    // - 그 곳에 새로운 노드의 시작 주소값인 new_node을 설정
    (*head_ref) = new_node; 
    return;
}

// insertAfter:
// Given a node prev_node, insert a new node after the given prev_node.
void insertAfter(struct Node* prev_node, int new_data) {
    // 1. 이전 노드가 NULL 인지 확인
    if (prev_node == NULL) {
        printf("the given previous node cannot be NULL");
        return;
    }
    // 2. 새로운 노드 할당
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    // 3. 새로운 노드에 데이터 입력
    new_node->data = new_data;
    // 4. 새로운 노드의 next에 이전 노드의 next를 복사
    new_node->next = prev_node->next;
    // 5. 이전 노드의 next에 새로운 노드 설정
    prev_node->next = new_node;
    return;
}

// append:
// Given a reference (pointer to pointer) to the head of a list and int,
// appends a new node at the end.
void append(struct Node** head_ref, int new_data) {
    // 1. 새로운 노드 할당
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    // 2. 새로운 노드에 데이터 입력
    new_node->data = new_data;
    // 3. 새로운 노드는 마지막 노드가 될 것이므로, next를 Null로 설정
    new_node->next = NULL;
    // 4. LinkedList가 비어 있는 경우, head로 설정
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    // 5. LinkedList에 노드가 있던 경우, 마지막 노드까지 이동
    // - head로 초기 설정
    struct Node* last = *head_ref; // (*head_ref)는 head
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
    return;
} 

// program to create a simple linked list with 3 nodes
int main(void) {
    printf("hello linkedlist! 2!\n");

    // 비어 있는 리스트로 시작
    struct Node* head = NULL;
    
    // 맨 끝에 새로운 데이터 6 추가: 6 > NULL
    append(&head, 6);
    // 맨 앞에 새로운 데이터 7 추가: 7 > 6 > NULL
    push(&head, 7);
    // 맨 앞에 새로운 데이터 1 추가: 1 > 7 > 6 > NULL
    push(&head, 1);
    // 맨 끝에 새로운 데이터 4 추가: 1 > 7 > 6 > 4 > NULL
    append(&head, 4);
    // head->next 뒤에 새로운 데이터 8 추가: 1 > 7 > 8 > 6 > 4 > NULL
    insertAfter(head->next, 8);

    printf("Created Linked List: \n");
    printList(head);
    deleteNode(&head, 1);
    printf("Linked List after Deletion of 1: \n");
    printList(head);
    deleteNode(&head, 6);
    printf("Linked List after Deletion of 6: \n");
    printList(head);

    return 0;
}