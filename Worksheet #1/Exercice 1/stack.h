#ifndef STACK_H
#define STACK_H

#include <stddef.h>

#define define_stack(T)                                                        \
  typedef struct StackNode_##T {                                               \
    T data;                                                                    \
    struct StackNode_##T *next;                                                \
  } StackNode_##T;                                                             \
                                                                               \
  typedef StackNode_##T *Stack_##T;                                            \
                                                                               \
  bool stack_##T##_empty(Stack_##T s) { return !s; }                           \
                                                                               \
  void stack_##T##_push(Stack_##T *s, T value) {                               \
    Stack_##T node = (Stack_##T)malloc(sizeof(StackNode_##T));                 \
    if (!node)                                                                 \
      return;                                                                  \
                                                                               \
    node->data = value;                                                        \
    node->next = *s;                                                           \
    *s = node;                                                                 \
  }                                                                            \
                                                                               \
  T stack_##T##_top(Stack_##T s) {                                             \
    if (stack_##T##_empty(s)) {                                                \
      fprintf(stderr, "Error: attempt to access top of empty stack\n");        \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
                                                                               \
    return s->data;                                                            \
  }                                                                            \
                                                                               \
  T stack_##T##_pop(Stack_##T *s) {                                            \
    if (stack_##T##_empty(*s)) {                                               \
      fprintf(stderr, "Error: attempt to pop from empty stack\n");             \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
                                                                               \
    T val = (*s)->data;                                                        \
    Stack_##T t = *s;                                                          \
    *s = (*s)->next;                                                           \
    free(t);                                                                   \
                                                                               \
    return val;                                                                \
  }

#endif // STACK_H
