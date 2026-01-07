#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct St1 {
  int id, priority;
  char *username;
  struct St1 *next;
} St1;

typedef St1 *List;

List init_list() {
  List l = NULL;
  List tail = NULL;

  printf("Enter id, username, priority (-1 to end):\n");
  while (1) {
    int id, priority;
    char username[100];

    scanf("%d", &id);

    if (id == -1)
      break;

    scanf("%s %d", username, &priority);

    List new_node = (List)malloc(sizeof(St1));

    new_node->id = id;
    new_node->username = strdup(username);
    new_node->priority = priority;
    new_node->next = NULL;

    if (!l) {
      l = new_node;
      tail = new_node;
    } else {
      tail->next = new_node;
      tail = new_node;
    }
  }

  return l;
}

void display_list(List H) {
  List node = H;
  while (node) {
    printf("%d %s %d\n", node->id, node->username, node->priority);
    node = node->next;
  }
}

int delete(List *H, int priority, List *deleted_node) {
  *deleted_node = NULL;

  if (*H == NULL)
    return 0;

  if ((*H)->priority == priority) {
    List head = *H;
    *H = head->next;
    *deleted_node = head;
    return 1;
  }

  List prev = *H;
  List node = prev->next;

  while (node && node->priority != priority) {
    prev = node;
    node = node->next;
  }

  if (!node)
    return 0;

  prev->next = node->next;
  *deleted_node = node;
  return 1;
}

typedef struct St2 {
  int id;
  char *username;
  struct St2 *next;
} St2;

typedef St2 *Queue;

void enqueue(Queue *Q, int id, char *username) {
  Queue new_node = (Queue)malloc(sizeof(St2));
  new_node->id = id;
  new_node->username = strdup(username);
  new_node->next = NULL;

  if (*Q == NULL) {
    *Q = new_node;
  } else {
    Queue tail = *Q;

    while (tail->next)
      tail = tail->next;

    tail->next = new_node;
  }
}

Queue ConstQueue(List *H, int priority) {
  Queue Q = NULL;

  while (1) {
    List deleted_node;
    int res = delete(H, priority, &deleted_node);

    if (!res)
      break;

    enqueue(&Q, deleted_node->id, deleted_node->username);
    free(deleted_node->username);
  }

  return Q;
}

void display_queue(Queue Q) {
  Queue node = Q;
  while (node) {
    printf("%d %s\n", node->id, node->username);
    node = node->next;
  }
}

typedef struct St3 {
  int priority;
  Queue Q;
  struct St3 *next;
} St3;

typedef St3 *Stack;

void push(Stack *S, int priority, Queue Q) {
  Stack new_node = (Stack)malloc(sizeof(St3));
  new_node->priority = priority;
  new_node->Q = Q;
  new_node->next = *S;
  *S = new_node;
}

Queue pop(Stack *S, int *priority) {
  if (*S == NULL)
    return NULL;

  Stack top = *S;
  *priority = top->priority;
  Queue Q = top->Q;
  *S = top->next;
  free(top);
  return Q;
}

Stack ConstStack(List *H, int max_priority) {
  Stack S = NULL;

  for (int p = max_priority; p >= 0; p--) {
    Queue Q = ConstQueue(H, p);
    if (Q) {
      push(&S, p, Q);
    }
  }

  return S;
}

void display_stack(Stack S) {
  Stack node = S;
  while (node) {
    printf("Priority %d:\n", node->priority);
    display_queue(node->Q);
    node = node->next;
  }
}

int main(int argc, char *argv[]) {
  List H = init_list();

  printf("Initial list:\n");
  display_list(H);

  printf("Priority Stack:\n");
  Stack S = ConstStack(&H, 3);
  display_stack(S);
}
