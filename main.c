#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void func(int count, ...) {
  va_list args;
  va_start(args, count);

  for (int i = 0; i < count; i++) {
    int value = va_arg(args, int);
    printf("Argument %d: %d\n", i + 1, value);
  }

  va_end(args);
}

int main(int argc, char *argv[]) {
  func(4, 10, 20, 30, 40);
  return EXIT_SUCCESS;
