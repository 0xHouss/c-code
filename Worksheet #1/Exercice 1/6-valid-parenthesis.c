#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

define_stack(char);

bool valid_parenthesis(const char *str) {
  Stack_char s = NULL;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == '(') {
      stack_char_push(&s, '(');
    } else if (str[i] == ')') {
      if (stack_char_empty(s))
        return false;
      stack_char_pop(&s);
    }
  }

  if (stack_char_empty(s))
    return true;
  else {
    while (!stack_char_empty(s))
      stack_char_pop(&s);

    return false;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s \"arithmetic expression\"\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *input = argv[1];
  if (valid_parenthesis(input))
    printf("Valid parenthesis in \"%s\".\n", input);
  else
    printf("Invalid parenthesis in \"%s\".\n", input);

  return EXIT_SUCCESS;
}
