#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = OK;
  if (A->columns != B->columns || A->rows != B->rows) {
    ret = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    ret = CALCULATION_ERROR;
  } else {
    result->rows = A->rows;
    result->columns = A->columns;
    for (int r = 0; r < A->rows; r++) {
      for (int c = 0; c < A->columns; c++) {
        result->matrix[c][r] = A->matrix[c][r] + B->matrix[c][r];
      }
    }
  }
  return ret;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = OK;
  if (A->columns != B->columns || A->rows != B->rows) {
    ret = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    ret = CALCULATION_ERROR;
  } else {
    result->rows = A->rows;
    result->columns = A->columns;
    for (int r = 0; r < A->rows; r++) {
      for (int c = 0; c < A->columns; c++) {
        result->matrix[c][r] = A->matrix[c][r] - B->matrix[c][r];
      }
    }
  }
  return ret;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int ret = OK;
  if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    ret = CALCULATION_ERROR;
  } else {
    result->rows = A->rows;
    result->columns = A->columns;
    for (int r = 0; r < A->rows; r++) {
      for (int c = 0; c < A->columns; c++) {
        result->matrix[c][r] = A->matrix[c][r] * number;
      }
    }
  }
  return ret;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = OK;
  if (s21_create_matrix(A->rows, B->columns, result) != OK) {
    ret = CALCULATION_ERROR;
  } else if (A->columns != B->rows) {
    ret = INCORRECT_MATRIX;
  } else {
    result->rows = A->rows;
    result->columns = B->columns;

    for (int row1 = 0; row1 < A->rows; row1++) {
      for (int col2 = 0; col2 < B->columns; col2++) {
        result->matrix[row1][col2] = 0;
        for (int col1 = 0; col1 < A->columns; col1++) {
          result->matrix[row1][col2] +=
              A->matrix[row1][col1] * B->matrix[col1][col2];
        }
      }
    }
  }
  return ret;
}
