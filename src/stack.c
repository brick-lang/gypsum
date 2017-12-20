#include "stack.h"
#include <acid.h>
#include <assert.h>
#include <stdlib.h>

stack_t *stack_empty() { return stack_cons(NULL, NULL); }

bool stack_is_empty(stack_t *const stack) { return stack->val == NULL; }

stack_t *stack_cons(void *const elem, stack_t *const stack) {
  stack_t *cell = acid_malloc(sizeof(stack_t));
  acid_set_field(cell, val, elem);
  acid_set_field(cell, next, stack);
  return cell;
}

void *stack_head(stack_t *const stack) {
  assert(stack->val != NULL);
  return stack->val;
}

stack_t *stack_tail(stack_t *const stack) {
  assert(stack->val != NULL);
  return stack->next;
}

stack_t *stack_concat(stack_t *const stack1, stack_t *const stack2) {
  if (stack_is_empty(stack1)) {
    acid_retain(stack2); // increment the strong count in preparation for decrementing it
    return stack2;
  } else {
    void *const x = stack_head(stack1);
    stack_t* const xs = stack_tail(stack1);
    stack_t *const zs = stack_concat(xs, stack2);
    stack_t *const xzs = stack_cons(x, zs);  // x :: (xs ++ ys)
    acid_dissolve(zs);
    return xzs;
  }
}

stack_t *stack_update(stack_t *const stack, size_t idx, void *const y) {
  assert(!stack_is_empty(stack));
  stack_t *const xs = stack_tail(stack);
  if (idx == 0) { // base case
    return stack_cons(y, xs);
  } else {
    void * const x = stack_head(stack);
    stack_t *const new_tail = stack_update(xs, idx - 1, y);
    stack_t *const new_stack = stack_cons(x, new_tail); // x :: update (xs, idx-1, y)
    acid_dissolve(new_tail);
    return new_stack;
  }
}
