#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
  char val;
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

Tree constructTree() {
  int height;

  printf("Enter the height of the tree: ");
  scanf("%d", &height);

  if (height <= 0)
    return NULL;

  Queue q = NULL;
  for (int i = 0; i < (1 << height) - 1; i++) {
    char c;
    printf("Enter character for node %d in bfs order (use '.' for NULL): ",
           i + 1);
    scanf(" %c", &c);

    Tree newNode = NULL;
    if (c != '.') {
      newNode = (Tree)malloc(sizeof(TreeNode));
      newNode->val = c;
      newNode->left = newNode->right = NULL;
    }

    enqueue(&q, newNode);
  }

  Tree root = dequeue(&q);
  Queue nodesQueue = NULL;
  enqueue(&nodesQueue, root);

  while (!isQueueEmpty(nodesQueue)) {
    Tree current = dequeue(&nodesQueue);
    if (!current)
      continue;

    current->left = dequeue(&q);
    current->right = dequeue(&q);

    enqueue(&nodesQueue, current->left);
    enqueue(&nodesQueue, current->right);
  }

  return root;
}

void displayTree(Tree root) {
  Queue q = NULL;
  enqueue(&q, root);

  printf("[");
  while (!isQueueEmpty(q)) {
    Tree current = dequeue(&q);
    if (current) {
      printf("%c", current->val);

      if (!isQueueEmpty(q) || current->left || current->right)
        printf(",");

      enqueue(&q, current->left);
      enqueue(&q, current->right);
    } else {
      printf("null ");
    }
  }
  printf("]\n");
}

bool rechercheMot(Tree root, char *s) {
  if (strlen(s) == 0)
    return true;

  if (!root)
    return false;

  if (root->val == s[0])
    return rechercheMot(root->left, s + 1);

  return rechercheMot(root->right, s);
}

void addMot(Tree *root, char *s) {
  if (!strlen(s))
    return;

  if (*root == NULL) {
    *root = (Tree)malloc(sizeof(TreeNode));
    (*root)->val = *s;

    return addMot(&((*root)->left), s + 1);
  }

  if ((*root)->val == *s)
    return addMot(&((*root)->left), s + 1);

  addMot(&((*root)->right), s);
}

int main(int argc, char *argv[]) {
  Tree root = constructTree();

  addMot(&root, "con");

  printf("'con' is %s in the tree",
         rechercheMot(root, "con") ? "found" : "not found");

  printf("'test' is %s in the tree",
         rechercheMot(root, "test") ? "found" : "not found");

  return EXIT_SUCCESS;
}
