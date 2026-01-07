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
  int val;
  struct TreeNode *left, *right;
} BinaryTreeNode;

void traverse_tree(BinaryTreeNode *root) {
  if (!root)
    return;

  printf("%d,\n", root->val);

  traverse_tree(root->right);
  traverse_tree(root->left);
}

void draw_nodes(BinaryTreeNode *root, Agnode_t *parent, Agraph_t *g,
                int depth) {
  if (!root)
    return;

  char *label = (char *)malloc(12 * sizeof(char));
  sprintf(label, "%d.%d", depth, root->val);

  Agnode_t *node = agnode(g, label, 1);
  agsafeset(node, "label", itos(root->val), "");

  if (parent)
    agedge(g, parent, node, 0, 1);

  draw_nodes(root->left, node, g, depth + 1);
  draw_nodes(root->right, node, g, depth + 1);
}

void draw_tree(BinaryTreeNode *root) {
  GVC_t *gvc = gvContext();
  Agraph_t *g = agopen("G", Agdirected, 0);

  draw_nodes(root, NULL, g, 0);

  gvLayout(gvc, g, "dot");
  gvRenderFilename(gvc, g, "png", "tree.png");

  gvFreeLayout(gvc, g);
  agclose(g);
  gvFreeContext(gvc);
}

BinaryTreeNode *create_node(int val) {
  BinaryTreeNode *node = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
  node->val = val;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void insert(BinaryTreeNode **root, int val) {
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

int generate_random(int min, int max) { return min + rand() % (max - min + 1); }

int main() {
  BinaryTreeNode *root = NULL;

  int VAL_MIN = 1;
  int VAL_MAX = 100;
  int N_NODES = 10;

  srand(time(NULL)); // Initialization, should only be called once.
  for (int i = 0; i < N_NODES; i++) {
    int r = generate_random(VAL_MIN, VAL_MAX);
    printf("Inserting %d\n", r);
    insert(&root, r);
  }

  draw_tree(root);

  return EXIT_SUCCESS;
}
