#include <stdio.h>
#include <stdlib.h>

/* 
 * 구조체 및 기본 함수 입출력값 정의
 */
typedef enum {RBTREE_RED, RBTREE_BLACK} color_t;

typedef int key_t;

typedef struct node_t {
    color_t color;
    key_t key;
    struct node_t *parent, *left, *right;
} node_t;

typedef struct {
    node_t *root;
} rbtree;

// new_rbtree: 새로운 RB트리 구조체를 생성하기
rbtree *new_rbtree(void);

// delete_rbtree:
void delete_rbtree(rbtree *t);

// rbtree_insert:
node_t *rbtree_insert(rbtree *t, const key_t key);

// rbtree_find:
node_t *rbtree_find(const rbtree *t, const key_t key);

// rbtree_min:
node_t *rbtree_min(const rbtree *t, const key_t key);

// rbtree_max:
node_t *rbtree_max(const rbtree *t, const key_t key);

// rbtree_erase:
int rbtree_erase(rbtree *t, const node_t *node);

// rbtree_to_array:
// - size_t는 부호 없는 정수형(unsigned int)으로 이미 정의되어 있음
int rbtree_to_array(const rbtree *t, key_t *p, const size_t size);


/* 
 * 추가 함수 입출력값 정의
 */

// rbtree_rotate_left:
void rbtree_rotate_left(rbtree *t, node_t *x);

// rbtree_rotate_right:
void rbtree_rotate_right(rbtree *t, node_t *x);

// rbtree_insert_fixup:
node_t *rbtree_insert_fixup(rbtree *t, node_t *z);



// 중위 트리 순회
int rbtree_inorder_walk(const rbtree *t);


/* 
 * main 함수
 */
int main(void) {
    printf("Hello, RBTree!");
    return 0;
}

/* 
 * rbtree 함수 구현하기 
 */
rbtree *new_rbtree(void) {
    rbtree *t = (rbtree *)malloc(sizeof(rbtree));
    return t;
}

void delete_rbtree(rbtree *t) {
    // TODO: 모든 노드의 메모리 반환하기

    // 트리의 메모리 반환하기
    free(t);
}

void rbtree_rotate_left(rbtree *t, node_t *x) {
    // 1. y 설정: 기준이 되는 x의 오른쪽 자식
    node_t *y = x->right;
    // 2. y의 왼쪽 서브 트리를 x의 오른쪽 서브 트리로 변경
    // - x 관점
    x->right = y->left;
    // - y의 왼쪽 자식 관점
    if (y->left != NULL) {
        y->left->parent = x;
    } 
    // 3. y를 x 부모 노드의 자식으로 변경
    // - y 관점
    y->parent = x->parent;
    // - x의 부모 노드 관점
    //   - x가 루트인 경우
    if (x->parent == NULL) {
        t->root = y;
    //   - x가 왼쪽 자식인 경우
    } else if (x == x->parent->left) {
        x->parent->left = y;
    //   - x가 오른쪽 자식인 경우
    } else {
        x->parent->right = y;
    }
    // 4. x를 y의 왼쪽 자식으로 설정
    // - y 관점
    y->left = x;
    // - x 관점
    x->parent = y;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
    // 1. 새로운 노드 생성하기
    node_t *new_n = (node_t *)malloc(sizeof(node_t));
    new_n->key = key;
    new_n->left = new_n->right = NULL;
    new_n->color = RBTREE_RED;
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
    // 4. RB트리 특성 유지시키기
    // rbtree_insert_fixup()

    // 5. 새로운 노드의 주소 리턴하기
    return new_n;
}