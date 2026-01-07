#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
  int val;
  struct StackNode *next;
} StackNode;

typedef StackNode *Stack;

void push(Stack *p, int val) {
  Stack node = (Stack)malloc(sizeof(StackNode));

  node->val = val;
  node->next = *p;
  *p = node;
}

int pop(Stack *p) {
  if (*p == NULL)
    return -1;

  Stack head = *p;
  int val = head->val;
  *p = head->next;
  free(head);
  return val;
}

bool empty(Stack p) { return !p; }

Stack init_stack(int *size) {
  do {
    printf("How many integers do you wish to push: ");
    scanf("%d", size);

    if (size < 0 || *size > 200)
      printf("The size must be in [0, 200] !\n");
  } while (size < 0 || *size > 200);

  Stack p = NULL;

  for (int i = 0; i < *size; i++) {
    int val;

    do {
      printf("Enter the value at position %d: ", i + 1);
      scanf("%d", &val);

      if (val < 1)
        printf("The value must be strictly positive!\n");
    } while (val < 1);

    push(&p, val);
  }

  return p;
}

void stack_display(Stack p) {
  if (empty(p)) {
    printf("Stack is empty.\n");
    return;
  }

  Stack temp = NULL;

  while (!empty(p)) {
    int val = pop(&p);
    printf("---\n|%d|\n", val);
    push(&temp, val);
  }
  printf("---\n");

  while (!empty(temp))
    push(&p, pop(&temp));
}

void init_un(StackNode heads[], Stack tails[], int size) {
  for (int i = 0; i < size; i++) {
    Stack diviseurs = NULL;
    push(&diviseurs, 1);

    heads[i].next = diviseurs;
    tails[i] = diviseurs;
  }
}

void init_heads(Stack *p, StackNode heads[], int size) {
  Stack t = NULL;

  for (int i = 0; i < size; i++) {
    int val = pop(p);
    StackNode node = {val, 0};
    heads[i] = node;
    push(&t, val);
  }

  while (!empty(t))
    push(p, pop(&t));
}

Stack Creer_valeur_divisble(int val, int k) {
  if (val % k != 0)
    return NULL;

  Stack node = (Stack)malloc(sizeof(StackNode));

  node->val = k;
  node->next = NULL;

  return node;
}

void Construire_les_listes(StackNode heads[], Stack tails[], int size) {
  for (int i = 0; i < size; i++) {
    int val = heads[i].val;

    if (val == 1)
      continue;

    Stack diviseurs_head = Creer_valeur_divisble(val, val);
    Stack diviseurs_tail = diviseurs_head;

    for (int k = val - 1; k > 1; k--) {
      Stack node = Creer_valeur_divisble(val, k);

      if (!node)
        continue;

      node->next = diviseurs_head;
      diviseurs_head = node;
    }

    heads[i].next->next = diviseurs_head;
    tails[i] = diviseurs_tail;
  }
}

void Affiche(StackNode heads[], int size) {
  for (int i = 0; i < size; i++) {
    StackNode node = heads[i];

    printf("%d: ", node.val);

    Stack h = node.next;

    while (h) {
      printf("%d", h->val);

      if (h->next)
        printf(", ");

      h = h->next;
    }

    printf("\n");
  }
}

void Affiche_nb_premiers(StackNode heads[], int size) {
  for (int i = 0; i < size; i++) {
    StackNode node = heads[i];

    if (node.val == 1)
      continue;

    if (!node.next->next->next)
      printf("%d\n", node.val);
  }
}

int main(int argc, char *argv[]) {
  int size;
  Stack p = init_stack(&size);

  StackNode heads[200];
  Stack tails[200];

  init_heads(&p, heads, size);

  init_un(heads, tails, size);

  Construire_les_listes(heads, tails, size);

  Affiche(heads, size);
  Affiche_nb_premiers(heads, size);

  return EXIT_SUCCESS;
}
