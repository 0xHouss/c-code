#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

define_stack(int);

void stack_int_display(Stack_int s) {
  if (stack_int_empty(s)) {
    printf("Stack is empty.\n");
    return;
  }

  Stack_int temp = NULL;

  while (!stack_int_empty(s)) {
    int val = stack_int_pop(&s);
    printf("---\n|%d|\n", val);
    stack_int_push(&temp, val);
  }
  printf("---\n");

  while (!stack_int_empty(temp))
    stack_int_push(&s, stack_int_pop(&temp));
}

void stack_int_insert(Stack_int *s, int target) {
  Stack_int temp = NULL;

  while (!stack_int_empty(*s) && stack_int_top(*s) != target)
    stack_int_push(&temp, stack_int_pop(s));

  if (!stack_int_empty(*s))
    stack_int_pop(s);

  while (!stack_int_empty(temp))
    stack_int_push(s, stack_int_pop(&temp));
}

int main(int argc, char *argv[]) {
  Stack_int s = NULL;

  for (int i = 1; i < argc; i++) {
    int val = atoi(argv[i]);
    stack_int_push(&s, val);
  }

  int target;
  printf("Enter an integer to delete the first occurence of: ");
  scanf("%d", &target);

  stack_int_insert(&s, target);

  printf("Stack after deletion:\n");
  stack_int_display(s);

  return EXIT_SUCCESS;
}
