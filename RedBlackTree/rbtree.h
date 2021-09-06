#ifndef RBTREE_H_
#define RBTREE_H_

#include <stddef.h>

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

#endif // RBTREE_H_