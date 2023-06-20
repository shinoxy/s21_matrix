#include "s21_matrix.h"

int s21_get_minor_matrix(matrix_t matrix, int row, int col,
                         matrix_t *minor_matrix) {
  int ret = OK;
  if (matrix.rows != matrix.columns || row > matrix.rows ||
      col > matrix.columns || matrix.rows == 0 || matrix.columns == 0) {
    ret = INCORRECT_MATRIX;
  } else {
    int minor_width = matrix.rows - 1;
    if (s21_create_matrix(minor_width, minor_width, minor_matrix) != OK) {
      ret = CALCULATION_ERROR;
    } else {
      int res_i = 0;
      for (int i = 0; i < matrix.rows; i++) {
        if (i != row) {
          int res_j = 0;
          for (int j = 0; j < matrix.columns; j++) {
            if (j != col) {
              minor_matrix->matrix[res_i][res_j] = matrix.matrix[i][j];
              res_j++;
            }
          }
          res_i++;
        }
      }
    }
  }
  return ret;
}

int s21_determinant(matrix_t *A, double *result) {
  int ret = OK;
  if (A->rows != A->columns || A->rows == 0) {
    ret = INCORRECT_MATRIX;
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result = (A->matrix[0][0] * A->matrix[1][1]) -
              (A->matrix[0][1] * A->matrix[1][0]);
  } else {
    int width = A->rows;
    *result = 0;
    for (int i = 0; i < width; i++) {
      matrix_t minor_matrix;
      s21_create_matrix(width - 1, width - 1, &minor_matrix);
      double minor = 0;
      s21_get_minor_matrix(*A, 0, i, &minor_matrix);
      s21_determinant(&minor_matrix, &minor);
      *result += (minor * pow(-1, i)) * A->matrix[0][i];
      s21_remove_matrix(&minor_matrix);
    }
  }
  return ret;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int ret = OK;
  if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    ret = CALCULATION_ERROR;
  } else if (A->rows != A->columns) {
    ret = INCORRECT_MATRIX;
  } else {
    int width = A->rows;
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < width; j++) {
        matrix_t minor_matrix;
        s21_get_minor_matrix(*A, i, j, &minor_matrix);
        double minor;
        ret = s21_determinant(&minor_matrix, &minor);
        result->matrix[i][j] = minor * pow(-1, i + j);
      }
    }
  }
  return ret;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int ret = OK;
  double determinant = 0;
  s21_determinant(A, &determinant);
  if (determinant == 0 ||
      (s21_create_matrix(A->rows, A->columns, result) != OK)) {
    ret = CALCULATION_ERROR;
  } else if (A->rows != A->columns) {
    ret = INCORRECT_MATRIX;
  } else {
    int width = A->rows;
    result->rows = width;
    result->columns = width;
    matrix_t complements;
    s21_calc_complements(A, &complements);

    double inv_determinant = 1.0 / determinant;
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < width; j++) {
        result->matrix[i][j] = complements.matrix[j][i] * inv_determinant;
      }
    }
  }

  return ret;
}