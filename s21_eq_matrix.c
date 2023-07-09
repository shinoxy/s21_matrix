#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if ((A->rows != B->rows || A->columns != B->columns || A->rows == 0) ||
      is_correct(A) == FAILURE || is_correct(B) == FAILURE) {
    return FAILURE;
  } else {
    for (int r = 0; r < A->rows; r++) {
      for (int c = 0; c < A->columns; c++) {
        if (fabs(A->matrix[r][c] - B->matrix[r][c]) > 1e-6) {
          return FAILURE;
        }
      }
    }
  }
  return SUCCESS;
}