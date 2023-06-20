#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int ret = OK;

  if (rows < 1 || columns < 1) {
    ret = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;

    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      ret = CALCULATION_ERROR;
    } else {
      for (int r = 0; r < rows; r++) {
        result->matrix[r] = calloc(columns, sizeof(double));
        if (result->matrix[r] == NULL) ret = CALCULATION_ERROR;
      }
    }
  }

  return ret;
}

void s21_remove_matrix(matrix_t *A) {
    if (A->matrix) {
        for (int i = 0; i < A->rows; i++) {
            if (A->matrix[i]) {
                free(A->matrix[i]);
            }
        }
        free(A->matrix);
        A->matrix = NULL;
    }
    if (A->rows) A->rows = 0;
    if (A->columns) A->columns = 0;
}