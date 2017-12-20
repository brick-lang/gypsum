#ifndef GYPSUM_TREESET_H
#define GYPSUM_TREESET_H

#include <stdbool.h>
#include <stddef.h>

typedef const struct treeset_t {
  void* elem;
  const struct treeset_t *left;
  const struct treeset_t *right;
} treeset_t;

treeset_t* treeset_empty();
treeset_t* treeset_create(void *, treeset_t*, treeset_t*);

typedef int(*cmp_t)(const void *, const void *);
bool treeset_member(void *element, treeset_t *treeset, cmp_t compare);
treeset_t* treeset_insert(void *element, treeset_t *treeset, cmp_t compare);


#endif //GYPSUM_TREESET_H
