#ifndef GYPSUM_BST_H
#define GYPSUM_BST_H

#include <stdbool.h>
#include <stddef.h>

typedef const struct bst_t {
  void* elem;
  const struct bst_t *left;
  const struct bst_t *right;
} bst_t;

bst_t* bst_empty();
bst_t* bst_create(void *, bst_t*, bst_t*);

typedef int(*cmp_t)(const void *, const void *);
bool bst_member(void *element, bst_t *bst, cmp_t compare);
bst_t* bst_insert(void *element, bst_t *bst, cmp_t compare);


#endif //GYPSUM_BST_H
