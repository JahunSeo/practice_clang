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
node_t *bstree_insert(bstree *t, const key_t key) {
    printf("[bstree_insert] %d\n", key);
    // 1. 새로운 노드 생성하기
    node_t *new_n = (node_t *)malloc(sizeof(node_t));
    new_n->key = key;
    new_n->left = new_n->right = NULL;
    // 2. 트리에서 들어갈 장소 찾기
    // - 새로운 노드와 그 부모 노드 초기회
    node_t *parent_n = NULL;
    node_t *child_n = t->root;
    // - 리프 노드에 도달할 때까지 이동 
    while (child_n != NULL) {
        // - 부모 노드 위치 업데이트
        parent_n = child_n;
        // - 새로운 노드 위치 업데이트
        if (new_n->key < child_n->key) {
            child_n = child_n->left;
        } else {
            child_n = child_n->right;
        }
    }
    // 3. 트리에 새로운 노드 배치하기
    // - 새로운 노드에 부모 노드 표시
    new_n->parent = parent_n;
    // - 부모 노드에 새로운 노드 표시
    //   - 부모 노드가 비어 있는 경우 (즉 새로운 노드가 루트인 경우) 
    if (parent_n == NULL) {
        t->root = new_n;
    //   - 부모 노드가 있고 새로운 노드가 왼쪽 자식인 경우
    } else if (new_n->key < parent_n->key) {
        parent_n->left = new_n;
    //   - 부모 노드가 있고 새로운 노드가 오른쪽 자식인 경우
    } else {
        parent_n->right = new_n;
    }
    // 4. 새로운 노드의 주소 리턴하기
    return new_n;
}

// 노드 v1을 v2로 대체하는 함수
void bstree_transplant(bstree* t, node_t* v1, node_t* v2) {
    // 'v1의 부모'와 'v2'를 연결
    // - v1 부모 관점
    //   - v1이 루트인 경우
    if (v1->parent == NULL) {
        t->root = v2;
    //   - v1이 왼쪽 자식인 경우
    } else if (v1 == v1->parent->left) {
        v1->parent->left = v2;
    //   - v1이 오른쪽 자식인 경우
    } else {
        v1->parent->right = v2;
    }    
    // - v2 관점
    if (v2 != NULL) {
        v2->parent = v1->parent;
    }
}

// 트리에서 노드 v의 직후 원소를 찾는 함수
node_t *bstree_successor(bstree *t, node_t *v) {
    
} 

// 트리에서 노드 z를 삭제하는 함수
// int bstree_erase(const bstree *t, node_t *z) {
//     if 
// }
