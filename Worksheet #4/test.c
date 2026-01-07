#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *itos(int val) {
  char *str = (char *)malloc(12 * sizeof(char));
  sprintf(str, "%d", val);
  return str;
}

typedef struct TreeNode {
  char val;
  struct TreeNode *left, *right;
} TreeNode;

typedef TreeNode *Tree;

void traverse_tree(Tree root) {
  if (!root)
    return;

  printf("%d,\n", root->val);

  traverse_tree(root->right);
  traverse_tree(root->left);
}

void draw_nodes(Tree root, Agnode_t *parent, Agraph_t *g, int depth) {
  if (!root)
    return;

  char *label = (char *)malloc(12 * sizeof(char));
  sprintf(label, "%d.%d", depth, root->val);

  char value[2] = {root->val, '\0'};

  Agnode_t *node = agnode(g, label, 1);
  agsafeset(node, "label", value, "");

  if (parent)
    agedge(g, parent, node, 0, 1);

  draw_nodes(root->left, node, g, depth + 1);
  draw_nodes(root->right, node, g, depth + 1);
}

void draw_tree(Tree root) {
  GVC_t *gvc = gvContext();
  Agraph_t *g = agopen("G", Agdirected, 0);

  draw_nodes(root, NULL, g, 0);

  gvLayout(gvc, g, "dot");
  gvRenderFilename(gvc, g, "png", "tree.png");

  gvFreeLayout(gvc, g);
  agclose(g);
  gvFreeContext(gvc);
}

Tree create_node(char val) {
  Tree node = (TreeNode *)malloc(sizeof(TreeNode));
  node->val = val;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void insert(Tree *root, char val) {
  if (*root == NULL) {
    *root = create_node(val);
    return;
  }

  if (val <= (*root)->val) {
    insert(&((*root)->left), val);
  } else {
    insert(&((*root)->right), val);
  }
}

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

bool rechercheMot(Tree root, char *s) {
  if (!strlen(s))
    return true;

  if (!root)
    return false;

  if (root->val == s[0])
    return rechercheMot(root->left, s + 1);

  return rechercheMot(root->right, s);
}

int main() {
  Tree root = constructTree();

  addMot(&root, "triangle");

  draw_tree(root);

  return EXIT_SUCCESS;
}
