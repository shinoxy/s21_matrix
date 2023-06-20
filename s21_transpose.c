#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int ret = OK;
  if (s21_create_matrix(A->columns, A->rows, result) != OK) {
    ret = INCORRECT_MATRIX;
  }
  for (int r = 0; r < A->rows; r++) {
    for (int c = 0; c < A->columns; c++) {
      result->matrix[c][r] = A->matrix[r][c];
    }
  }

  return ret;
}
