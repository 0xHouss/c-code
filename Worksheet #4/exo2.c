#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
  double val;
  struct TreeNode *left, *right;
} TreeNode;

typedef TreeNode *Tree;

typedef struct QueueNode {
  Tree val;
  struct QueueNode *next;
} QueueNode;

typedef QueueNode *Queue;

void enqueue(Queue *q, Tree val) {
  Queue node = (Queue)malloc(sizeof(QueueNode));

  node->val = val;
  node->next = NULL;

  if (*q == NULL) {
    *q = node;
    return;
  }

  Queue tail = *q;

  while (tail->next)
    tail = tail->next;

  tail->next = node;
}

Tree dequeue(Queue *q) {
  if (*q == NULL)
    return NULL;

  Queue head = *q;
  Tree val = head->val;
  *q = head->next;
  free(head);
  return val;
}

bool isQueueEmpty(Queue q) { return !q; }

double sum(Tree root) {
  if (!root)
    return 0;

  return root->val + sum(root->left) + sum(root->right);
}

double sum_iter(Tree root) {
  Queue q = NULL;
  enqueue(&q, root);

  double sum = 0;

  while (!isQueueEmpty(q)) {
    Tree node = dequeue(&q);

    if (!node)
      continue;

    sum += node->val;

    enqueue(&q, node->left);
    enqueue(&q, node->right);
  }

  return sum;
}

int occurences(Tree root, double val) {
  if (!root)
    return 0;

  int occ = root->val == val ? 1 : 0;

  return occ + occurences(root->left, val) + occurences(root->right, val);
}

double occurences_iter(Tree root, double val) {
  Queue q = NULL;
  enqueue(&q, root);

  double occurences = 0;

  while (!isQueueEmpty(q)) {
    Tree node = dequeue(&q);

    if (!node)
      continue;

    if (node->val == val)
      occurences++;

    enqueue(&q, node->left);
    enqueue(&q, node->right);
  }

  return occurences;
}

int max(int a, int b) { return a > b ? a : b; }

int height(Tree root) {
  if (!root)
    return 0;

  return 1 + max(height(root->left), height(root->right));
}
