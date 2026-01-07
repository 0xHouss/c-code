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

Stack_int stack_int_merge(Stack_int *s1, Stack_int *s2) {
  Stack_int temp1 = NULL;
  Stack_int temp2 = NULL;
  Stack_int temp = NULL;
  Stack_int s = NULL;

  while (!stack_int_empty(*s1) && !stack_int_empty(*s2)) {
    if (stack_int_top(*s1) < stack_int_top(*s2)) {
      int val = stack_int_pop(s1);
      stack_int_push(&temp, val);
      stack_int_push(&temp1, val);
    } else {
      int val = stack_int_pop(s2);
      stack_int_push(&temp, val);
      stack_int_push(&temp2, val);
    }
  }

  while (!stack_int_empty(*s1)) {
    int val = stack_int_pop(s1);
    stack_int_push(&temp, val);
    stack_int_push(&temp1, val);
  }

  while (!stack_int_empty(*s2)) {
    int val = stack_int_pop(s2);
    stack_int_push(&temp, val);
    stack_int_push(&temp2, val);
  }

  // Restore original stacks
  while (!stack_int_empty(temp1))
    stack_int_push(s1, stack_int_pop(&temp1));

  while (!stack_int_empty(temp2))
    stack_int_push(s2, stack_int_pop(&temp2));

  // Reverse temp into s to get correct order
  while (!stack_int_empty(temp))
    stack_int_push(&s, stack_int_pop(&temp));

  return s;
}

void stack_int_fill(Stack_int *s) {
  while (true) {
    int val;
    printf("Enter an integer to insert (or q to stop): ");
    if (scanf("%d", &val) != 1) {
      // Input wasn’t a number
      scanf("%*s"); // discard invalid token
      break;
    }
    stack_int_push(s, val);
  }
}

// Insert target into an ascending ordered stack from top to bottom
int main(int argc, char *argv[]) {
  Stack_int s1 = NULL;
  Stack_int s2 = NULL;

  printf("Fill the first stack:\n");
  stack_int_fill(&s1);

  printf("Fill the second stack:\n");
  stack_int_fill(&s2);

  Stack_int s = stack_int_merge(&s1, &s2);

  printf("First stack:\n");
  stack_int_display(s1);

  printf("Second stack:\n");
  stack_int_display(s2);

  printf("Merged stack:\n");
  stack_int_display(s);

  return EXIT_SUCCESS;
}
