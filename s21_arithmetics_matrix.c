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

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = OK;
  if (A->columns != B->columns || A->rows != B->rows ||
      is_correct(A) == FAILURE || is_correct(B) == FAILURE) {
    ret = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    ret = CALCULATION_ERROR;
  } else {
    for (int r = 0; r < A->rows; r++) {
      for (int c = 0; c < A->columns; c++) {
        result->matrix[r][c] = A->matrix[r][c] + B->matrix[r][c];
      }
    }
  }
  return ret;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = OK;
  if (A->columns != B->columns || A->rows != B->rows ||
      is_correct(A) == FAILURE || is_correct(B) == FAILURE) {
    ret = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    ret = CALCULATION_ERROR;
  } else {
    for (int r = 0; r < A->rows; r++) {
      for (int c = 0; c < A->columns; c++) {
        result->matrix[r][c] = A->matrix[r][c] - B->matrix[r][c];
      }
    }
  }
  return ret;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (is_correct(A) == FAILURE) {
    return INCORRECT_MATRIX;
  }
  if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    return CALCULATION_ERROR;
  }
  for (int r = 0; r < A->rows; r++) {
    for (int c = 0; c < A->columns; c++) {
      result->matrix[r][c] = A->matrix[r][c] * number;
    }
  }
  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (s21_create_matrix(A->rows, B->columns, result) != OK) {
    return CALCULATION_ERROR;
  }
  if (A->columns != B->rows || is_correct(A) == FAILURE ||
      is_correct(B) == FAILURE) {
    return INCORRECT_MATRIX;
  }

  for (int row1 = 0; row1 < A->rows; row1++) {
    for (int col2 = 0; col2 < B->columns; col2++) {
      result->matrix[row1][col2] = 0;
      for (int col1 = 0; col1 < A->columns; col1++) {
        result->matrix[row1][col2] +=
            A->matrix[row1][col1] * B->matrix[col1][col2];
      }
    }
  }
  return OK;
}
