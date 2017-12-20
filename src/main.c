#include <acid.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

extern atomic_uint_fast64_t acid_world_count;
extern atomic_uint_fast64_t acid_collect_count;

stack_t* stack_test(int arr[], int c) {
  stack_t* last _cleanup_acid_dissolve_ = stack_empty();
  stack_t* curr = NULL;
  acid_set(curr, last);
  for (int i = c; i > 0; i--) {
    stack_t* cell _cleanup_acid_dissolve_ = stack_cons(&arr[i], curr);
    acid_set(curr, cell);
  }
  return curr;
}

int main(int argc, char** argv) {
  acid_setup();
  int back[] = {3, 4, 5};
  stack_t* back_stack = stack_test(back, sizeof(back) / sizeof(int));

  int front[] = {0, 1, 2};
  stack_t* front_stack = stack_test(front, sizeof(front) / sizeof(int));

  stack_t* combo = stack_concat(front_stack, back_stack);

  acid_dissolve(back_stack);
  acid_dissolve(front_stack);
  acid_dissolve(combo);

  int lst[] = {0, 1, 2, 3, 4};
  int replacement = 7;
  stack_t* full_stack = stack_test(lst, sizeof(lst) / sizeof(int));
  stack_t* updated = stack_update(full_stack, 2, &replacement);

  (void)full_stack;
  acid_dissolve(full_stack);
  acid_dissolve(updated);

  acid_teardown();
  printf("Total number of objects created: %lu\n", acid_world_count);
  printf("Total number of objects collected: %lu\n", acid_collect_count);
  exit(0);
}
