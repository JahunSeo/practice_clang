#include <stdio.h>
#include <stdlib.h>

typedef int key_t;

typedef struct node_t {
    key_t key;
    struct node_t *left, *right, *parent;
} node_t;

typedef struct bstree {
    node_t *root;
} bstree;

// new_bstree: 새로운 이진 탐색 트리 구조체를 생성하기
bstree *new_bstree(void);
// delete_bstree: 트리 구조체가 차지했던 메모리를 반환하기
// - 트리의 모든 노드들을 순차적으로 제거한 뒤, 트리까지 제거해주어야겠군. 
void delete_bstree(bstree *);
// bstree_insert: 트리에 새로운 값(key)을 가진 노드 추가하기
// - 트리를 가리키는 포인터와 새로 추가하려는 key는 상수 인자로 전달
// - 재귀 버전, 순환식 버전 둘 다 구현해보기
node_t *bstree_insert(bstree *, const key_t);
// bstree_find: 트리에서 특정 값을 가진 노드 탐색하기
// - 트리 내에 해당 키를 가진 노드가 있는지 탐색하여 있으면 해당 node pointer 반환
// - 없으면 NULL 반환
// - 재귀 버전, 순환식 버전 둘 다 구현해보기
node_t *bstree_find(const bstree *, const key_t);
// bstree_min: 트리에서 최소값을 가진 노드 찾기
// - 트리가 비어 있으면 NULL 반환
node_t *bstree_min(const bstree *);
// bstree_max: 트리에서 최대값을 가진 노드 찾기
// - 트리가 비어 있으면 NULL 반환
node_t *bstree_max(const bstree *);
// bstree_erase: 트리에서 포인터로 지정된 노드를 삭제하고 해당 메모리를 반환하기
// - 지정된 노드가 트리에 속하지 않은 경우도 있을까?
// - 삭제하려면 노드에 parent를 멤버로 가지고 있어야 할까?
int bstree_erase(const bstree *, node_t *);
// bstree_to_array: 트리의 노드들을 key 순서대로 주어진 array로 변환하기
// - array의 크기는 n으로 주어지며 tree의 크기가 n보다 큰 경우에는 순서대로 n개까지만 변환
// - key 순서대로 라는 것이 뭐지?? 
// - 일단 중위 트리 순회
int bstree_to_array(const bstree *t, key_t *arr, const size_t n);

// C에서는 nested function을 지원하지 않는군
int walk(const node_t *n) {
    if (n != NULL) {
        walk(n->left);
        printf(" %d ", n->key);
        walk(n->right);
    }
    return 0;
}

int bstree_inorder_walk(const bstree *t) {
    printf("tree walk: ");
    walk(t->root);
    printf("\n");
    return 0;
}

int main(void) {
    printf("hello, BST!\n");
    bstree *t = new_bstree();
    printf("bstree %p\n", t);
    bstree_insert(t, 1);
    bstree_inorder_walk(t);
    bstree_insert(t, 2);
    bstree_inorder_walk(t);
    bstree_insert(t, 10);
    bstree_insert(t, 3);
    bstree_insert(t, 5);
    bstree_inorder_walk(t);

    return 0;
}


/* 함수 구현하기 */
bstree *new_bstree(void) {
    // bstree *p = (bstree *)calloc(1, sizeof(bstree));
    bstree *p = (bstree *)malloc(sizeof(bstree));
    return p;
}

void delete_bstree(bstree *t) {
    // TODO: 모든 노드의 메모리 반환하기

    // 트리의 메모리 반환하기
    free(t);
}

// bstree *t에서 const 를 해제함
node_t *bstree_insert(bstree *t, const key_t key) {
    // 1. 새로운 노드 생성하기
    node_t *new_n = (node_t *)malloc(sizeof(node_t));
    new_n->key = key;
    new_n->left = new_n->right = NULL; // new_n->parent는 아래에서 결정됨
    // 2. 트리에서 들어갈 장소 찾기
    node_t *parent_n = NULL; // 새로운 노드의 부모 노드 위치를 초기 설정
    node_t *child_n = t->root; // 새로운 노드의 위치를 초기 설정
    while (child_n != NULL) {
        parent_n = child_n;
        if (new_n->key < child_n->key) {
            child_n = child_n->left;
        } else {
            child_n = child_n->right;
        }
    }
    // 3. 트리에 새로운 노드 배치하기
    // 먼저 새로운 노드의 부모 노드 설정
    new_n->parent = parent_n;
    // 새로운 노드를 배치할 때,
    // 부모 노드가 비어 있는 경우, 즉 트리가 비어 있던 경우
    if (parent_n == NULL) {
        t->root = new_n;
    // 부모 노드의 key보다 작은 경우
    } else if (new_n->key < parent_n->key) {
        parent_n->left = new_n;
    // 부모 노드의 key보다 크거나 같은 경우
    } else {
        parent_n->right = new_n;
    }

    return t->root;
}

// // 중위 트리 순회 과정 출력하기
// // A function to do inorder traversal of BST
// void inorder_tree_walk(struct Node* root) {
//     if (root != NULL) {
//         inorder_tree_walk(root->left);
//         printf(" %d ", root->key);
//         inorder_tree_walk(root->right);
//     }
// }

// // 탐색하기: 재귀 버전
// // A function to search a given key in a given BST
// struct Node* search(struct Node* root, int key) {
//     // Base Cases: root is null or key is present at root
//     if (root == NULL || root->key == key) {
//         return root;
//     }
//     // key is greater than root's key
//     if (key > root->key) {
//         return search(root->right, key);
//     // key is smaller than root's key
//     } else {
//         return search(root->left, key);
//     }
// }

// // 탐색하기: 순환적 형태
// struct Node* iterative_search(struct Node* node, int key) {
//     while (node != NULL && node->key != key) {
//         if (key > node->key) {
//             node = node->right;
//         } else {
//             node = node->left;
//         }
//     }
//     return node;
// }

// // 새로운 노드 생성하기
// // A function to create a new BST node
// struct Node* make_node(int key) {
//     // 새로운 노드에 메모리 할당
//     struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
//     // 새로운 노드의 key 값 설정
//     temp->key = key;
//     // 새로운 노드의 left, right를 NULL로 초기화
//     temp->left = temp->right = NULL;
//     return temp;
// }

// // 트리에 새로운 노드 추가하기
// // A function to insert a new node with given key in BST
// void insert(struct Node* root, int key) {
//     struct Node* parent = NULL;
//     while ()
// }


