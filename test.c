#include <stdio.h>
#include <stdlib.h>

void sortMatrixAscending(int **matrix, int n, int m, int *LS) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (LS[j] > LS[j + 1]) {
        int *temp = matrix[j];
        matrix[j] = matrix[j + 1];
        matrix[j + 1] = temp;
      }
    }
  }
}

int **construct_matrix_from_input(int n, int m) {
  int **matrix = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    matrix[i] = (int *)malloc(m * sizeof(int));
    for (int j = 0; j < m; j++) {
      printf("Enter element [%d][%d]: ", i, j);
      scanf("%d", &matrix[i][j]);
    }
  }
  return matrix;
}

int LastSeq(int *arr, int size) {
  int i = size - 1;

  while (i > 0 && arr[i] >= arr[i - 1])
    i--;

  return i;
}

int *VectSeq(int **matrix, int n, int m) {
  int *LS = (int *)malloc(n * sizeof(int));

  for (int i = 0; i < n; i++)
    LS[i] = LastSeq(matrix[i], m);

  return LS;
}

void display_vector(int *vec, int size) {
  printf("Vector: ");
  for (int i = 0; i < size; i++)
    printf("%d ", vec[i]);

  printf("\n");
}

void display_matrix(int **matrix, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      printf("%d ", matrix[i][j]);

    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  int n = 4, m = 5;

  int **matrix = construct_matrix_from_input(n, m);

  display_matrix(matrix, n, m);

  int *LS = VectSeq(matrix, n, m);

  display_vector(LS, n);

  sortMatrixAscending(matrix, n, m, LS);

  display_matrix(matrix, n, m);
}

typedef struct TreeNode {
  int val;
  struct TreeNode *left, *right;
} TreeNode;

typedef TreeNode *Tree;

void displayInorder(Tree root) {
  if (!root)
    return;

  displayInorder(root->left);
  printf("%d", root->val);
  displayInorder(root->right);
}
