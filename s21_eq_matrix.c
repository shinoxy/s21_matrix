#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int ret = SUCCESS;
  if (A->rows != B->rows || A->columns != B->columns || A->rows == 0) {
    ret = FAILURE;
  } else {
    for (int r = 0; r < A->rows; r++) {
      for (int c = 0; c < A->columns; c++) {
        if (A->matrix[r][c] != B->matrix[r][c]) {
          ret = FAILURE;
          break;
        }
      }
    }
  }
  return ret;
}