#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int ret = OK;

  if (rows < 1 || columns < 1) {
    ret = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;

    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      ret = CALCULATION_ERROR;
    } else {
      for (int r = 0; r < rows; r++) {
        result->matrix[r] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[r] == NULL) ret = CALCULATION_ERROR;
      }
    }
  }

  return ret;
}

void s21_remove_matrix(matrix_t *A) {
  A->rows = 0;
  A->columns = 0;
  for (int r = 0; r < A->rows; r++) {
    free(A->matrix[r]);
  }
  free(A->matrix);
}