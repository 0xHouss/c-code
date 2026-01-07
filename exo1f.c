#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
  int data;
  struct StackNode *next;
} StackNode;

typedef StackNode *Stack;

#define stack_init() NULL

bool stack_empty(Stack s) { return !s; }

void stack_push(Stack *s, int value) {
  Stack node = (Stack)malloc(sizeof(StackNode));
  if (!node)
    return;

  node->data = value;
  node->next = *s;
  *s = node;
}

int stack_top(Stack s) {
  if (stack_empty(s)) {
    fprintf(stderr, "Error: attempt to access top of empty stack\n");
    exit(EXIT_FAILURE);
  }

  return s->data;
}

int stack_pop(Stack *s) {
  if (stack_empty(*s)) {
    fprintf(stderr, "Error: attempt to pop from empty stack\n");
    exit(EXIT_FAILURE);
  }

  int val = (*s)->data;
  Stack t = *s;
  *s = (*s)->next;
  free(t);

  return val;
}

void display(Stack *s) {
  Stack temp = stack_init();

  while (!stack_empty(*s)) {
    int value = stack_pop(s);
    printf("%d\n", value);
    stack_push(&temp, value);
  }

  while (!stack_empty(temp))
    stack_push(s, stack_pop(&temp));
}

int main(int argc, char *argv[]) {
  Stack s = stack_init();

  stack_push(&s, 1);
  stack_push(&s, 2);
  stack_push(&s, 3);
  stack_push(&s, 4);
  stack_push(&s, 5);
  stack_push(&s, 6);
  stack_push(&s, 7);
  stack_push(&s, 8);

  display(&s);

  return EXIT_SUCCESS;
}
