#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void init_random() { srand((unsigned int)time(NULL)); }

int generate_random(int min, int max) { return rand() % (max - min + 1) + min; }

char *generate_password(int length, bool use_uppercase, bool use_lowercase,
                        bool use_numbers, bool use_special) {
  char lowercases[] = "abcdefghijklmnopqrstuvwxyz";
  char uppercases[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char numbers[] = "0123456789";
  char special[] = "!@#$%^&*()-_=+[]{}|;:,.<>?";

  char charset[strlen(lowercases) + strlen(uppercases) + strlen(numbers) +
               strlen(special) + 1];

  if (use_lowercase)
    strcat(charset, lowercases);
  if (use_uppercase)
    strcat(charset, uppercases);
  if (use_numbers)
    strcat(charset, numbers);
  if (use_special)
    strcat(charset, special);

  if (strlen(charset) == 0) {
    fprintf(stderr, "Error: At least one character type must be selected.\n");
    exit(EXIT_FAILURE);
  }

  char *password;

  init_random();

  for (int i = 0; i < length; i++) {
    int index = generate_random(0, strlen(charset) - 1);
    password[i] = charset[index];
  }

  password[length] = '\0';

  return password;
}

int main(int argc, char *argv[]) {
  // if (argc < 2) {
  //   fprintf(stderr, "Usage: %s <password-length>\n", argv[0]);
  //   return EXIT_FAILURE;
  // }

  // int length = atoi(argv[1]);
  int length = 12; // Default length for demonstration

  if (length <= 0) {
    fprintf(stderr, "Password length must be a positive integer.\n");
    return EXIT_FAILURE;
  }

  char *password = generate_password(length, true, true, true, true);

  printf("Generated Password: %s\n", password);

  return EXIT_SUCCESS;
}
