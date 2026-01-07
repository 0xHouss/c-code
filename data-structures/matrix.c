#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix {
  int rows;
  int cols;
  double **data;
} Matrix;

Matrix *create_matrix(int rows, int cols) {
  Matrix *mat = (Matrix *)malloc(sizeof(Matrix));

  mat->rows = rows;
  mat->cols = cols;
  mat->data = (double **)malloc(rows * sizeof(double *));

  for (int i = 0; i < rows; i++)
    mat->data[i] = (double *)malloc(cols * sizeof(double));

  return mat;
}

void free_matrix(Matrix *mat) {
  for (int i = 0; i < mat->rows; i++)
    free(mat->data[i]);

  free(mat->data);
  free(mat);
}

void print_matrix(Matrix *mat) {
  for (int i = 0; i < mat->rows; i++) {
    for (int j = 0; j < mat->cols; j++)
      printf("%lf ", mat->data[i][j]);

    printf("\n");
  }
}

Matrix *add_matrices(Matrix *a, Matrix *b) {
  if (a->rows != b->rows || a->cols != b->cols) {
    fprintf(stderr, "Error: Matrices dimensions do not match for addition.\n");
    return NULL;
  }

  Matrix *result = create_matrix(a->rows, a->cols);

  for (int i = 0; i < a->rows; i++)
    for (int j = 0; j < a->cols; j++)
      result->data[i][j] = a->data[i][j] + b->data[i][j];

  return result;
}

Matrix *subtract_matrices(Matrix *a, Matrix *b) {
  if (a->rows != b->rows || a->cols != b->cols) {
    fprintf(stderr,
            "Error: Matrices dimensions do not match for subtraction.\n");
    return NULL;
  }

  Matrix *result = create_matrix(a->rows, a->cols);

  for (int i = 0; i < a->rows; i++)
    for (int j = 0; j < a->cols; j++)
      result->data[i][j] = a->data[i][j] - b->data[i][j];

  return result;
}

Matrix *scalar_multiply_matrix(Matrix *mat, double scalar) {
  Matrix *result = create_matrix(mat->rows, mat->cols);

  for (int i = 0; i < mat->rows; i++)
    for (int j = 0; j < mat->cols; j++)
      result->data[i][j] = mat->data[i][j] * scalar;

  return result;
}

Matrix *multiply_matrices(Matrix *a, Matrix *b) {
  if (a->cols != b->rows) {
    fprintf(stderr,
            "Error: Matrices dimensions do not match for multiplication.\n");
    return NULL;
  }

  Matrix *result = create_matrix(a->rows, b->cols);

  for (int i = 0; i < a->rows; i++) {
    for (int j = 0; j < b->cols; j++) {
      result->data[i][j] = 0;
      for (int k = 0; k < a->cols; k++)
        result->data[i][j] += a->data[i][k] * b->data[k][j];
    }
  }

  return result;
}

Matrix *transpose_matrix(Matrix *mat) {
  Matrix *result = create_matrix(mat->cols, mat->rows);

  for (int i = 0; i < mat->rows; i++)
    for (int j = 0; j < mat->cols; j++)
      result->data[j][i] = mat->data[i][j];

  return result;
}

bool is_square_matrix(Matrix *mat) { return mat->rows == mat->cols; }

bool is_symmetric_matrix(Matrix *mat) {
  if (!is_square_matrix(mat))
    return false;

  for (int i = 0; i < mat->rows; i++)
    for (int j = 0; j < mat->cols; j++)
      if (mat->data[i][j] != mat->data[j][i])
        return false;

  return true;
}

Matrix *identity_matrix(int size) {
  Matrix *mat = create_matrix(size, size);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      mat->data[i][j] = (i == j) ? 1 : 0;

  return mat;
}

bool is_identity_matrix(Matrix *mat) {
  if (!is_square_matrix(mat))
    return false;

  for (int i = 0; i < mat->rows; i++)
    for (int j = 0; j < mat->cols; j++) {
      if (i == j && mat->data[i][j] != 1)
        return false;
      else if (i != j && mat->data[i][j] != 0)
        return false;
    }

  return true;
}

bool are_matrices_equal(Matrix *a, Matrix *b) {
  if (a->rows != b->rows || a->cols != b->cols)
    return false;

  for (int i = 0; i < a->rows; i++)
    for (int j = 0; j < a->cols; j++)
      if (a->data[i][j] != b->data[i][j])
        return false;

  return true;
}
