#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

define_stack(int);

bool stack_int_merge(Stack_int s, int target) {
  Stack_int temp = NULL;

  while (!stack_int_empty(s) && stack_int_top(s) != target)
    stack_int_push(&temp, stack_int_pop(&s));

  bool found = !stack_int_empty(s);

  while (!stack_int_empty(temp))
    stack_int_push(&s, stack_int_pop(&temp));

  return found;
}

int main(int argc, char *argv[]) {
  Stack_int s = NULL;

  for (int i = 1; i < argc; i++) {
    int val = atoi(argv[i]);
    stack_int_push(&s, val);
  }

  int target;
  printf("Enter an integer to search for: ");
  scanf("%d", &target);

  if (stack_int_merge(s, target))
    printf("%d found in the stack.\n", target);
  else
    printf("%d not found in the stack.\n", target);

  return EXIT_SUCCESS;
}
