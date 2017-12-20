#include "bst.h"
#include <acid.h>

typedef int (*cmp_t)(const void *, const void *);

bst_t *bst_empty() {
  return bst_create(NULL,NULL,NULL);
}

bst_t *bst_create(void* elem, bst_t* left, bst_t* right) {
  struct bst_t *node = acid_malloc(sizeof(bst_t));
  acid_set_field(node, elem, elem);
  acid_set_field(node, left, left);
  acid_set_field(node, right, right);
  return node;
}

bool bst_is_empty(bst_t *bst) { return bst->elem == NULL; }

bool bst_member(void *e, bst_t *bst, cmp_t compare) {
  if (bst->elem == NULL) {
    return false;
  } else {
    if (compare(e, bst->elem) < 0) {
      return bst_member(e, bst->left, compare);
    } else if (compare(e, bst->elem) > 0) {
      return bst_member(e, bst->right, compare);
    } else {
      return true;
    }
  }
}

bst_t *bst_insert(void *element, bst_t *bst, cmp_t compare) {
  // base case
  if (bst_is_empty(bst)) {
    bst_t *empty_l = bst_empty();
    bst_t *empty_r = bst_empty();
    bst_t *new_node = bst_create(element, empty_l, empty_r);
    acid_dissolve(empty_r);
    acid_dissolve(empty_l);
    return new_node;
  }

  if (compare(element, bst->elem) < 0) {
    bst_t *new_node = bst_insert(element, bst->left, compare);
    bst_t *clone =  bst_create(bst->elem, new_node, bst->right);
    acid_dissolve(new_node);
    return clone;
  } else if (compare(element, bst->elem) > 0) {
    bst_t *new_node = bst_insert(element, bst->right, compare);
    bst_t *clone = bst_create(bst->elem, bst->left, new_node);
    acid_dissolve(new_node);
    return clone;
  } else {
    acid_retain(bst); // increment the strong in prep for decrementing
    return bst;
  }
}
