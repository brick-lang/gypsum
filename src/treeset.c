#include "treeset.h"
#include <acid.h>

treeset_t *treeset_empty() {
  return treeset_create(NULL,NULL,NULL);
}

treeset_t *treeset_create(void* elem, treeset_t* left, treeset_t* right) {
  struct treeset_t *node = acid_malloc(sizeof(treeset_t));
  acid_set_field(node, elem, elem);
  acid_set_field(node, left, left);
  acid_set_field(node, right, right);
  return node;
}

bool treeset_is_empty(treeset_t *treeset) { return treeset->elem == NULL; }

bool treeset_member(void *e, treeset_t *treeset, cmp_t compare) {
  if (treeset->elem == NULL) {
    return false;
  } else {
    if (compare(e, treeset->elem) < 0) {
      return treeset_member(e, treeset->left, compare);
    } else if (compare(e, treeset->elem) > 0) {
      return treeset_member(e, treeset->right, compare);
    } else {
      return true;
    }
  }
}

treeset_t *treeset_insert(void *element, treeset_t *treeset, cmp_t compare) {
  // base case
  if (treeset_is_empty(treeset)) {
    treeset_t *empty_l = treeset_empty();
    treeset_t *empty_r = treeset_empty();
    treeset_t *new_node = treeset_create(element, empty_l, empty_r);
    acid_dissolve(empty_r);
    acid_dissolve(empty_l);
    return new_node;
  }

  if (compare(element, treeset->elem) < 0) {
    treeset_t *new_node = treeset_insert(element, treeset->left, compare);
    treeset_t *clone =  treeset_create(treeset->elem, new_node, treeset->right);
    acid_dissolve(new_node);
    return clone;
  } else if (compare(element, treeset->elem) > 0) {
    treeset_t *new_node = treeset_insert(element, treeset->right, compare);
    treeset_t *clone = treeset_create(treeset->elem, treeset->left, new_node);
    acid_dissolve(new_node);
    return clone;
  } else {
    acid_retain(treeset); // increment the strong in prep for decrementing
    return treeset;
  }
}
