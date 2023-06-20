# s21_matrix.h
## Implementation of the matrix.h library.

### Matrix structure in C language:

```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```
## Matrix operations

All operations (except matrix comparison) return the resulting code:  
- 0 - OK
- 1 - Error, incorrect matrix
- 2 - Calculation error (mismatched matrix sizes; matrix for which calculations cannot be performed, etc.)

### Creating matrices (create_matrix)

```c
int s21_create_matrix(int rows, int columns, matrix_t *result);
```

### Cleaning of matrices (remove_matrix)

```c
void s21_remove_matrix(matrix_t *A);
```

### Matrix comparison (eq_matrix)

```c
#define SUCCESS 1  
#define FAILURE 0  

int s21_eq_matrix(matrix_t *A, matrix_t *B);
```

The comparison must be up to and including 7 decimal places.  

### Adding (sum_matrix) and subtracting matrices (sub_matrix)

```c
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

### Matrix multiplication by scalar (mult_number). Multiplication of two matrices (mult_matrix)

```c
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

### Matrix transpose (transpose)

```c
int s21_transpose(matrix_t *A, matrix_t *result);
```

The transpose of matrix A is in switching its rows with its columns with their numbers retained   

### Minor of matrix and matrix of algebraic complements (calc_complements)

```c
int s21_calc_complements(matrix_t *A, matrix_t *result);
```

### Matrix determinant

```c
int s21_determinant(matrix_t *A, double *result);
```
The determinant can only be calculated for a square matrix.  

### Inverse of the matrix (inverse_matrix)  

```c
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
```

A matrix A to the power of -1 is called the inverse of a square matrix A if the product of these matrices equals the identity matrix.  

## About project

- The library is developed in C language of C11 standard using gcc compiler
- POSIX.1-2017 standard is used
- The project follows the Google style
- The project made as a static library (with the s21_matrix.h header file)
- The library is developed according to the principles of structured programming
- Unit tests cover at least 80% of each function (checked using gcov)
- Makefile for building the library and tests (with targets all, clean, test, s21_matrix.a, gcov_report) is provided
- Verifiable accuracy of the fractional part is up to 6 decimal places


