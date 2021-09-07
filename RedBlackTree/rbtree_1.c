#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"


/* 
 * 추가 함수 입출력값 정의
 */

// rbtree_rotate_left:
void rbtree_rotate_left(rbtree *t, node_t *x);

// rbtree_rotate_right:
void rbtree_rotate_right(rbtree *t, node_t *x);

// rbtree_insert_fixup:
void rbtree_insert_fixup(rbtree *t, node_t *z);

// 중위 트리 순회
void rbtree_inorder_walk(const node_t *x);

// 그래프 그리기
void rbtree_graph(const rbtree *t);

/* 
 * main 함수
 */
int main(void) {
    printf("Hello, RBTree!\n");

    // 트리 생성
    rbtree *t = new_rbtree();
    // 비어 있는 트리 확인
    printf("rbtree : ");
    rbtree_inorder_walk(t->root);
    printf("\n\n");
    // 트리에 10 추가
    rbtree_insert(t, 10);
    printf("rbtree : ");
    rbtree_inorder_walk(t->root);
    printf("\n\n");
    // 트리에 5, 15 추가
    rbtree_insert(t, 5);
    rbtree_insert(t, 15);
    printf("rbtree : ");
    rbtree_inorder_walk(t->root);
    printf("\n\n");
    // 트리에 35, 20 추가
    rbtree_insert(t, 35);
    rbtree_insert(t, 20);
    printf("rbtree : ");
    rbtree_inorder_walk(t->root);    
    printf("\n\n");

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

void rbtree_inorder_walk(const node_t *x) {
    if (x != NULL) {
        rbtree_inorder_walk(x->left);
        int parent_key;
        char color;
        if (x->parent != NULL) {
            parent_key = x->parent->key;
        } else {
            parent_key = 0;
        }
        if (x->color == RBTREE_RED) {
            color = 'R';
        } else {
            color = 'B';
        }
        printf(" %d>[%d](%c) ", parent_key, x->key, color);
        rbtree_inorder_walk(x->right);
    }
}

void rbtree_graph(const rbtree* t) {
    node_t frontier[10];

}

void rbtree_rotate_left(rbtree *t, node_t *x) {
    // 1. 'y' 설정: 기준이 되는 x의 오른쪽 자식
    node_t *y = x->right;
    // 2. 'y'의 왼쪽 서브 트리를 'x'의 오른쪽 서브 트리로 변경
    // - x 관점
    x->right = y->left;
    // - y의 왼쪽 자식 관점
    if (y->left != NULL) {
        y->left->parent = x;
    } 
    // 3. 'y'를 'x 부모'의 자식으로 변경
    // - y 관점
    y->parent = x->parent;
    // - x 부모 관점
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
    // 4. 'x'를 'y'의 자식으로 변경: x는 y의 왼쪽 자식
    // - x 관점
    x->parent = y;
    // - y 관점
    y->left = x;
}

void rbtree_rotate_right(rbtree *t, node_t *x) {
    // 1. 'y' 설정: 기준이 되는 x의 왼쪽 자식
    node_t *y = x->left;
    // 2. 'y'의 오른쪽 서브 트리를 'x'의 왼쪽 서브 트리로 변경
    // - x 관점
    x->left = y->right;
    // - y 의 오른쪽 자식 관점
    if (y->right != NULL) {
        y->right->parent = x;
    }
    // 3. 'y'를 'x 부모'의 자식으로 변경
    // - y 관점
    y->parent = x->parent;
    // - x 부모 관점
    //   - x 부모가 없는 경우 (즉, x가 루트인 경우)
    if (x->parent == NULL) {
        t->root = y;
    //   - x가 왼쪽 자식인 경우
    } else if (x == x->parent->left) {
        x->parent->left = y;
    //   - x가 오른쪽 자식인 경우
    } else {
        x->parent->right = y;
    }
    // 4. 'x'를 'y'의 자식으로 변경: x는 y의 오른쪽 자식
    // - x 관점
    x->parent = y;
    // - y 관점
    y->right = x;
}

void rbtree_insert_fixup(rbtree *t, node_t *z) {
    // [주의] 노드의 NULL 체크
    // - 경계노드 NIL을 도입하면 NIL의 컬러가 BLACK이기 때문에 아래 2개 상황에서 코드가 간결해짐
    // 1) while (z->parent != NULL && z->parent->color == RBTREE_RED) {
    //   - z->parent 가 NIL인 경우, 컬러가 BLACK이어서 두 번째 조건만으로도 처리 가능
    // 2) if (uncle != NULL && uncle->color == RBTREE_RED) {
    //   - uncle이 NIL인 경우, 컬러가 BLACK이어서 두 번째 조건만으로 처리 가능

    // 1. 트리 규칙을 위반한 영역 수정하기
    // - 'z'는 트리 규칙에 문제가 생길 수 있는 노드이며, 그 시작은 트리에 새로 추가된 노드
    // - 'z'-'z 부모'가 RED-RED 인지 확인하여 규칙을 유지할 수 있도록 트리의 구조 변경
    // - (주의! 경계노드 NIL을 별도로 활용하지 않으므로 부모 노드 NULL 여부 체크 필요)
    node_t *uncle;    
    while (z->parent != NULL && z->parent->color == RBTREE_RED) {
        // 'z 부모'가 왼쪽 자식인 경우
        if (z->parent == z->parent->parent->left) {
            // 'z 부모의 형제(=z 삼촌)' 설정: 할아버지의 오른쪽 자식
            uncle = z->parent->parent->right;
            // [CASE 1] 'z 삼촌'이 RED인 경우
            // - 부모~삼촌이 RED~RED 이므로, 할아버지는 반드시 BLACK
            // - 부모와 삼촌을 BLACK, 할아버지를 RED로 바꾸면, 일단 z와 부모 간의 문제는 해결
            // - 하지만 할아버지가 RED로 변하여 본인의 부모와 없던 문제가 생길 수 있으므로,
            // - z를 'z의 부모 부모(=할아버지)'로 업데이트
            // - (주의! 경계노드 NIL을 별도로 활용하지 않으므로 uncle 노드 NULL 여부 체크 필요)
            if (uncle != NULL && uncle->color == RBTREE_RED) {
                // 부모와 삼촌을 BLACK으로
                z->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                // 할아버지를 RED로
                z->parent->parent->color = RBTREE_RED;
                // 새로운 타겟 노드로 z 변경
                z = z->parent->parent;
            // [CASE 2,3] 'z 삼촌'이 BLACK인 경우
            // - 부모~삼촌이 RED~BLACK 이므로, 할아버지는 반드시 BLACK
            // - 이 때는 '할아버지' 위치를 BLACK으로 유지하면서 '삼촌' 위치를 RED로 만들어 문제 해결
            // - (한쪽으로 치우친 RED를 반대편으로 넘겨주는 셈)
            } else {
                // [CASE 2] 'z'가 오른쪽 자식인 경우
                // - 이 경우 할아버지-부모-z가 < 모양으로 꺾여 있음
                // - 할아버지-부모-z가 일직선에 있는 CASE 3 상태로 먼저 만듦
                if (z == z->parent->right) {
                    z = z->parent;
                    rbtree_rotate_left(t, z);
                }
                // [CASE 3] 'z'가 왼쪽 자식인 경우
                // - 할아버지-부모-z가 / 모양으로 일직선 위에 있음
                // - RED가 한 쪽으로 치우쳐 있으므로, 할아버지를 기준으로 반대편에 RED를 하나 넘겨주어 균형을 맞춤
                // - 이를 위해 할아버지를 RED, 부모를 BLACK으로 바꾼 뒤, 할아버지를 기준으로 오른쪽 회전함
                // - 그러면 부모 BLACK에 두 자식이 RED인 형태로 균형이 맞게 됨
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                rbtree_rotate_right(t, z->parent->parent);
                // CASE 2,3 혹은 CASE 3을 수행한 이후에는
                // z-부모가 RED-BLACK 이므로 루프 종료
            }
        // 'z 부모'가 오른쪽 자식인 경우
        } else {
            // 'z 삼촌' 설정: 할아버지의 왼쪽 자식
            uncle = z->parent->parent->left;
            // [CASE 1] 'z 삼촌'이 RED 인 경우
            if (uncle != NULL && uncle->color == RBTREE_RED) {
                z->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            // [CASE 2,3] 'z 삼촌'이 BLACK 인 경우
            } else {
                // [CASE 2] 'z'가 왼쪽 자식인 경우 
                // - 할아버지-부모-z가 > 모양으로 꺾여 있음
                if (z == z->parent->left) {
                    z = z->parent;
                    rbtree_rotate_right(t, z);
                }
                // [CASE 3] 'z'가 오른쪽 자식인 경우
                // - 할아버지-부모-z가 \ 모양으로 일직선 위에 있음
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                rbtree_rotate_left(t, z->parent->parent);
            }
        } 

    }
    // 2. 루트 노드 BLACK으로 설정하기
    t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
    printf("[rbtree_insert] %d\n", key);
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
    /* DEBUGGING */
    printf("before fixup : ");
    rbtree_inorder_walk(t->root);
    printf("\n");
    /* ** ** ** */

    rbtree_insert_fixup(t, new_n);

    /* DEBUGGING */
    printf("after fixup : ");
    rbtree_inorder_walk(t->root);
    printf("\n");
    /* ** ** ** */

    // 5. 새로운 노드의 주소 리턴하기
    return new_n;
}