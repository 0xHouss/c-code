#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int fib(int n) {
  double phi = (1 + sqrt(5)) / 2;
  double psi = (1 - sqrt(5)) / 2;
  return (pow(phi, n) - pow(psi, n)) / sqrt(5);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return EXIT_FAILURE;
  }

  int n = atoi(argv[1]);
  int result = fib(n);
  printf("%d\n", result);

  return EXIT_SUCCESS;
}
