#include <stack.h>
#include <stdio.h>
#include <stdlib.h>

void display(Stack *s) {
  Stack temp = stack_init();

  while (!stack_empty(s)) {
    int value = stack_pop(int, *s);
    printf("%d\n", value);
    stack_push(int, temp, value);
  }

  while (!stack_empty(temp))
    stack_push(int, *s, stack_pop(int, temp));
}

int main(int argc, char *argv[]) {
  Stack s = stack_init();

  stack_push(int, s, 2);
  stack_push(int, s, 1);
  stack_push(int, s, 5);
  stack_push(int, s, 2);
  stack_push(int, s, 6);
  stack_push(int, s, 0);
  stack_push(int, s, 1);

  display(&s);

  printf("Popping top element: %d\n", stack_top(int, s));

  // display(s);
  // display(s);
  // display(s);
  // display(s);
  // display(s);
  // display(s);
  //
  return EXIT_SUCCESS;
}
