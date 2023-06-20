#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>  // УБРАТЬ
#include <stdlib.h>

// ERROR CODES FOR EQ_MATRIX
#define SUCCESS 1
#define FAILURE 0

// ERROR CODES FOR OTHER FUNCTIONS
#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR \
  2  // Mismatched sizes; calculations cannot be performed, etc.

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_get_minor_matrix(matrix_t matrix, int row, int col,
                         matrix_t *minor_matrix);
int s21_determinant(matrix_t *A, double *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif  // SRC_S21_MATRIX_H_