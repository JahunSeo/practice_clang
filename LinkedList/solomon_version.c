// #include <stdio.h>
// #include <stdlib.h>
// #include "prac.h"

// int main() {
//     linkedList *L = (linkedList *)malloc(sizeof(linkedList));
//     L->cur = NULL;
//     L->head = NULL;
//     L->tail = NULL;


//     creatNode(L, 1);
//     creatNode(L, 2);
//     creatNode(L, 3);
//     deleteNode(L);
//     creatNode(L, 4);
//     creatNode(L, 5);
//     showList(L);


//     return 0;
// }

// void showList(linkedList *L)
// {
//     node *p = L->head;
//     putchar('[');
//     while (p != NULL)
//     {
//         printf("%d, ", p->data);
//         p = p->next;
//     }
//     putchar(']');
//     putchar('\n');

// }

// void creatNode(linkedList *L, int tdata)
// {
//     node *newNode = (node *)malloc(sizeof(node));
//     newNode->data = tdata;
//     newNode->next = NULL;

//     if(L->head == NULL && L->tail == NULL)
//     {
//         L->head = L->tail = newNode;
//     }
//     else
//     {
//         L->tail->next = newNode;
//         L->tail = newNode;
//     }
// }

// void deleteNode(linkedList *L)
// {
//     node *p = L->head;
//     while (p->next->next != NULL)
//     {
//         p = p->next;
//     }

//     p->next = p->next->next;
//     L->tail = p;

// }