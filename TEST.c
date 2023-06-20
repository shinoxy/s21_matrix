#include <check.h>

#include "s21_matrix.h"

START_TEST(test_s21_create_matrix) {
  matrix_t my_matrix;
  int ret = s21_create_matrix(2147483647, 2147483647, &my_matrix);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&my_matrix);

  ret = s21_create_matrix(10, 10, &my_matrix);
  ck_assert_int_eq(ret, 0);
  s21_remove_matrix(&my_matrix);

  ret = s21_create_matrix(1, 1, &my_matrix);
  ck_assert_int_eq(ret, 0);
  s21_remove_matrix(&my_matrix);

  ret = s21_create_matrix(-4, 4, &my_matrix);
  ck_assert_int_eq(ret, 1);

  ret = s21_create_matrix(10, 0, &my_matrix);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(test_s21_eq_matrix) {
  matrix_t matrix_1, matrix_2;
  s21_create_matrix(5, 5, &matrix_1);
  s21_create_matrix(3, 3, &matrix_2);
  int ret = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);
  ret = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  rows = 3, columns = 3;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = 1;
      matrix_2.matrix[i][j] = 2;
    }
  }
  ret = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  rows = 7, columns = 7;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = 5;
      matrix_2.matrix[i][j] = 5;
    }
  }
  ret = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  rows = 7, columns = 7;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = 5.1111111;
      matrix_2.matrix[i][j] = 5.1111112;
    }
  }
  ret = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(test_s21_sum_matrix) {
  int ret = 0, width = 0;
  matrix_t matrix_1, matrix_2, res, res_correct;

  width = 4;
  s21_create_matrix(width, width, &matrix_1);
  s21_create_matrix(width, width, &matrix_2);
  s21_create_matrix(width, width, &res);
  s21_create_matrix(width, width, &res_correct);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < width; j++) {
      matrix_1.matrix[i][j] = i + j;
      matrix_2.matrix[i][j] = i + j;
      res_correct.matrix[i][j] = matrix_1.matrix[i][j] + matrix_2.matrix[i][j];
    }
  }
  ret = s21_sum_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);

  width = 3;
  s21_create_matrix(width, width, &matrix_1);
  s21_create_matrix(width, width, &matrix_2);
  s21_create_matrix(width, width, &res);
  s21_create_matrix(width, width, &res_correct);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < width; j++) {
      matrix_1.matrix[i][j] = i + j * 2;
      matrix_2.matrix[i][j] = i * 2 + j;
      res_correct.matrix[i][j] = matrix_1.matrix[i][j] + matrix_2.matrix[i][j];
    }
  }
  ret = s21_sum_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);

  width = 7;
  s21_create_matrix(width, width, &matrix_1);
  s21_create_matrix(width, width, &matrix_2);
  s21_create_matrix(width, width, &res);
  s21_create_matrix(width, width, &res_correct);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < width; j++) {
      matrix_1.matrix[i][j] = i * 1.213124 + 6.1234 * j;
      matrix_2.matrix[i][j] = i * 4.412 + j * 1.215267;
      res_correct.matrix[i][j] = matrix_1.matrix[i][j] + matrix_2.matrix[i][j];
    }
  }
  ret = s21_sum_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);

  width = 5;
  s21_create_matrix(width, width, &matrix_1);
  s21_create_matrix(width, width, &matrix_2);
  s21_create_matrix(width, width, &res);
  s21_create_matrix(width, width, &res_correct);
  ret = s21_sum_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);

  width = 5;
  s21_create_matrix(width + 1, width, &matrix_1);
  s21_create_matrix(width, width + 1, &matrix_2);
  s21_create_matrix(width + 1, width + 1, &res);
  s21_create_matrix(width + 1, width + 1, &res_correct);
  ret = s21_sum_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, INCORRECT_MATRIX);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);

  width = 1;
  s21_create_matrix(width, width, &matrix_1);
  s21_create_matrix(width, width, &matrix_2);
  s21_create_matrix(width, width, &res);
  s21_create_matrix(width, width, &res_correct);
  ret = s21_sum_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);
}
END_TEST

START_TEST(test_s21_sub_matrix) {
  int ret = 0, width = 0;
  matrix_t matrix_1, matrix_2, res, res_correct;

  width = 4;
  s21_create_matrix(width, width, &matrix_1);
  s21_create_matrix(width, width, &matrix_2);
  s21_create_matrix(width, width, &res);
  s21_create_matrix(width, width, &res_correct);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < width; j++) {
      matrix_1.matrix[i][j] = i + j;
      matrix_2.matrix[i][j] = i + j;
      res_correct.matrix[i][j] = matrix_1.matrix[i][j] - matrix_2.matrix[i][j];
    }
  }
  ret = s21_sub_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);

  width = 3;
  s21_create_matrix(width, width, &matrix_1);
  s21_create_matrix(width, width, &matrix_2);
  s21_create_matrix(width, width, &res);
  s21_create_matrix(width, width, &res_correct);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < width; j++) {
      matrix_1.matrix[i][j] = i + j * 2;
      matrix_2.matrix[i][j] = i * 2 + j;
      res_correct.matrix[i][j] = matrix_1.matrix[i][j] - matrix_2.matrix[i][j];
    }
  }
  ret = s21_sub_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);

  width = 7;
  s21_create_matrix(width, width, &matrix_1);
  s21_create_matrix(width, width, &matrix_2);
  s21_create_matrix(width, width, &res);
  s21_create_matrix(width, width, &res_correct);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < width; j++) {
      matrix_1.matrix[i][j] = i * 1.213124 + 6.1234 * j;
      matrix_2.matrix[i][j] = i * 4.412 + j * 1.215267;
      res_correct.matrix[i][j] = matrix_1.matrix[i][j] - matrix_2.matrix[i][j];
    }
  }
  ret = s21_sub_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);

  width = 5;
  s21_create_matrix(width, width, &matrix_1);
  s21_create_matrix(width, width, &matrix_2);
  s21_create_matrix(width, width, &res);
  s21_create_matrix(width, width, &res_correct);
  ret = s21_sub_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);

  width = 5;
  s21_create_matrix(width + 1, width, &matrix_1);
  s21_create_matrix(width, width + 1, &matrix_2);
  s21_create_matrix(width + 1, width + 1, &res);
  s21_create_matrix(width + 1, width + 1, &res_correct);
  ret = s21_sub_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, INCORRECT_MATRIX);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);

  width = 1;
  s21_create_matrix(width, width, &matrix_1);
  s21_create_matrix(width, width, &matrix_2);
  s21_create_matrix(width, width, &res);
  s21_create_matrix(width, width, &res_correct);
  ret = s21_sub_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);
}
END_TEST

START_TEST(test_s21_mult_number) {
  matrix_t matrix_1, res_my, res_org;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &res_org);
  int ret = s21_mult_number(&matrix_1, 5, &res_my);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      res_org.matrix[i][j] = (i + j) * (-3);
    }
  }
  ret = s21_mult_number(&matrix_1, -3, &res_my);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
    }
  }
  ret = s21_mult_number(&matrix_1, 0, &res_my);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_mult_matrix) {
  matrix_t matrix_1, matrix_2, res, res_correct;

  int rows = 2, cols = 2;
  int mat_1_0[2][2] = {
      {1, 2},
      {3, 4},
  };
  int mat_2_0[2][2] = {
      {2, 7},
      {3, 4},
  };
  int res_correct_0[2][2] = {
      {8, 15},
      {18, 37},
  };
  s21_create_matrix(rows, cols, &matrix_1);
  s21_create_matrix(rows, cols, &matrix_2);
  s21_create_matrix(rows, cols, &res_correct);
  s21_create_matrix(rows, cols, &res);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix_1.matrix[i][j] = mat_1_0[i][j];
      matrix_2.matrix[i][j] = mat_2_0[i][j];
      res_correct.matrix[i][j] = res_correct_0[i][j];
    }
  }
  int ret = s21_mult_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);

  rows = 3, cols = 3;
  int mat_1_1[3][3] = {{4, 2, 0}, {2, 7, 7}, {2, 7, 2}};
  int mat_2_1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int res_correct_1[3][3] = {{12, 18, 24}, {79, 95, 111}, {44, 55, 66}};
  s21_create_matrix(rows, cols, &matrix_1);
  s21_create_matrix(rows, cols, &matrix_2);
  s21_create_matrix(rows, cols, &res_correct);
  s21_create_matrix(rows, cols, &res);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix_1.matrix[i][j] = mat_1_1[i][j];
      matrix_2.matrix[i][j] = mat_2_1[i][j];
      res_correct.matrix[i][j] = res_correct_1[i][j];
    }
  }
  ret = s21_mult_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);

  rows = 7, cols = 7;
  int mat_1_2[7][7] = {
      {1, 2, 3, 4, 5, 6, 7}, {8, 9, 10, 11, 12, 13, 14},
      {1, 2, 3, 4, 5, 6, 7}, {8, 9, 10, 11, 12, 13, 14},
      {1, 2, 3, 4, 5, 6, 7}, {8, 9, 10, 11, 12, 13, 14},
      {1, 2, 3, 4, 5, 6, 7},

  };
  int mat_2_2[7][7] = {
      {8, 9, 10, 11, 12, 13, 14}, {1, 2, 3, 4, 5, 6, 7},
      {8, 9, 10, 11, 12, 13, 14}, {1, 2, 3, 4, 5, 6, 7},
      {8, 9, 10, 11, 12, 13, 14}, {1, 2, 3, 4, 5, 6, 7},
      {8, 9, 10, 11, 12, 13, 14},
  };
  int res_correct_2[7][7] = {
      {140, 168, 196, 224, 252, 280, 308}, {385, 462, 539, 616, 693, 770, 847},
      {140, 168, 196, 224, 252, 280, 308}, {385, 462, 539, 616, 693, 770, 847},
      {140, 168, 196, 224, 252, 280, 308}, {385, 462, 539, 616, 693, 770, 847},
      {140, 168, 196, 224, 252, 280, 308},
  };
  s21_create_matrix(rows, cols, &matrix_1);
  s21_create_matrix(rows, cols, &matrix_2);
  s21_create_matrix(rows, cols, &res_correct);
  s21_create_matrix(rows, cols, &res);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix_1.matrix[i][j] = mat_1_2[i][j];
      matrix_2.matrix[i][j] = mat_2_2[i][j];
      res_correct.matrix[i][j] = res_correct_2[i][j];
    }
  }
  ret = s21_mult_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);

  int mat_1_3[3][2] = {{2, 7}, {3, 4}, {4, 2}};
  int mat_2_3[2][3] = {
      {1, 2, 3},
      {4, 5, 6},
  };
  int res_correct_3[3][3] = {{30, 39, 48}, {19, 26, 33}, {12, 18, 24}};
  s21_create_matrix(3, 2, &matrix_1);
  s21_create_matrix(2, 3, &matrix_2);
  s21_create_matrix(3, 3, &res_correct);
  s21_create_matrix(3, 3, &res);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      matrix_1.matrix[i][j] = mat_1_3[i][j];
      matrix_2.matrix[j][i] = mat_2_3[j][i];
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      res_correct.matrix[i][j] = res_correct_3[i][j];
    }
  }
  ret = s21_mult_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);

  s21_create_matrix(3, 2, &matrix_1);
  s21_create_matrix(3, 2, &matrix_2);
  s21_create_matrix(3, 3, &res);
  ret = s21_mult_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, INCORRECT_MATRIX);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);

  int mat_1_5[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int mat_2_5[3][2] = {{1, 2}, {3, 4}, {5, 6}};
  int res_correct_5[3][2] = {{22, 28}, {49, 64}, {76, 100}};

  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 2, &matrix_2);
  s21_create_matrix(3, 2, &res_correct);
  s21_create_matrix(3, 2, &res);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      matrix_2.matrix[i][j] = mat_2_5[i][j];
      res_correct.matrix[i][j] = res_correct_5[i][j];
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix_1.matrix[i][j] = mat_1_5[i][j];
    }
  }

  ret = s21_mult_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &res_correct);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&res_correct);

  int mat_1_6[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int mat_2_6[3][2] = {{1, 2}, {3, 4}, {5, 6}};
  int res_correct_6[3][2] = {{22, 28}, {49, 64}, {76, 100}};
  s21_create_matrix(3, 2, &matrix_1);
  s21_create_matrix(3, 3, &matrix_2);
  s21_create_matrix(3, 2, &res);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      matrix_1.matrix[i][j] = mat_2_6[i][j];
      res_correct.matrix[i][j] = res_correct_6[i][j];
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix_2.matrix[i][j] = mat_1_6[i][j];
    }
  }

  ret = s21_mult_matrix(&matrix_1, &matrix_2, &res);
  ck_assert_int_eq(ret, INCORRECT_MATRIX);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_s21_transpose) {
  matrix_t input, output, result;

  int input_1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  int result_1[3][2] = {{1, 4}, {2, 5}, {3, 6}};

  s21_create_matrix(2, 3, &input);
  s21_create_matrix(3, 2, &output);
  s21_create_matrix(3, 2, &result);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      input.matrix[i][j] = input_1[i][j];
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      result.matrix[i][j] = result_1[i][j];
    }
  }
  int ret = s21_transpose(&input, &output);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&output, &result);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&input);
  s21_remove_matrix(&output);
  s21_remove_matrix(&result);

  int input_2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int result_2[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};

  s21_create_matrix(3, 3, &input);
  s21_create_matrix(3, 3, &output);
  s21_create_matrix(3, 3, &result);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      input.matrix[i][j] = input_2[i][j];
      result.matrix[i][j] = result_2[i][j];
    }
  }
  ret = s21_transpose(&input, &output);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&output, &result);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&input);
  s21_remove_matrix(&output);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_determinant) {
  matrix_t matrix;

  int width = 3;
  double matrix0[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  s21_create_matrix(width, width, &matrix);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = matrix0[i][j];
    }
  }
  double res = 0;
  int ret = s21_determinant(&matrix, &res);
  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&matrix);

  width = 3;
  double matrix1[3][3] = {{4, 2, 0}, {5, 7, 5}, {2, 7, 7}};
  s21_create_matrix(width, width, &matrix);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = matrix1[i][j];
    }
  }
  res = 0;
  ret = s21_determinant(&matrix, &res);
  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(res, 6);
  s21_remove_matrix(&matrix);

  width = 3;
  double matrix2[4][4] = {
      {4, 2, 0, 0}, {5, 7, 5, 1}, {2, 7, 7, 2}, {1, 2, 3, 4}};
  s21_create_matrix(width, width, &matrix);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = matrix2[i][j];
    }
  }
  res = 0;
  ret = s21_determinant(&matrix, &res);
  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(res, 6);
  s21_remove_matrix(&matrix);

  double matrix3[2][3] = {{4, 2, 0}, {5, 7, 5}};
  s21_create_matrix(2, 3, &matrix);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      matrix.matrix[i][j] = matrix2[i][j];
    }
  }
  res = 0;
  ret = s21_determinant(&matrix, &res);
  ck_assert_int_eq(ret, INCORRECT_MATRIX);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_calc_complements) {
  matrix_t matrix, complements, res;

  int width = 3;
  double matrix0[3][3] = {{4, 2, 2}, {7, 0, 5}, {7, 8, 9}};
  double complements0[3][3] = {
      {-40, -28, 56},
      {-2, 22, -18},
      {10, -6, -14},
  };
  s21_create_matrix(width, width, &matrix);
  s21_create_matrix(width, width, &complements);
  s21_create_matrix(width, width, &res);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < width; j++) {
      matrix.matrix[i][j] = matrix0[i][j];
      complements.matrix[i][j] = complements0[i][j];
    }
  }
  int ret = s21_calc_complements(&matrix, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &complements);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&complements);
  s21_remove_matrix(&res);

  width = 5;
  double matrix1[5][5] = {{4, 2, 2, 7, 7},
                          {7, 0, 5, 3, 5},
                          {7, 8, 9, 2, 4},
                          {1, 2, 3, 4, 5},
                          {8, 9, 5, 3, 5}};
  double complements1[5][5] = {{-189, 21, -89, -1354, 1166},
                               {-195, 267, 25, 554, -526},
                               {27, -3, -513, -858, 990},
                               {540, -60, 44, 1240, -1544},
                               {-102, -234, 466, 788, -796}};
  s21_create_matrix(width, width, &matrix);
  s21_create_matrix(width, width, &complements);
  s21_create_matrix(width, width, &res);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < width; j++) {
      matrix.matrix[i][j] = matrix1[i][j];
      complements.matrix[i][j] = complements1[i][j];
    }
  }
  ret = s21_calc_complements(&matrix, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &complements);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&complements);
  s21_remove_matrix(&res);

  width = 2;
  double matrix2[2][2] = {
      {4, 2},
      {7, 0},
  };
  double complements2[2][2] = {
      {0, -7},
      {-2, 4},
  };
  s21_create_matrix(width, width, &matrix);
  s21_create_matrix(width, width, &complements);
  s21_create_matrix(width, width, &res);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < width; j++) {
      matrix.matrix[i][j] = matrix2[i][j];
      complements.matrix[i][j] = complements2[i][j];
    }
  }
  ret = s21_calc_complements(&matrix, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &complements);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix);

  double matrix3[2][3] = {
      {4, 2, 0},
      {7, 0, 0},
  };
  s21_create_matrix(2, 3, &matrix);
  s21_create_matrix(width, width, &res);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      matrix.matrix[i][j] = matrix3[i][j];
    }
  }
  ret = s21_calc_complements(&matrix, &res);
  ck_assert_int_eq(ret, INCORRECT_MATRIX);
  s21_remove_matrix(&matrix);

  double m[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double r[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &res);
  s21_create_matrix(3, 3, &complements);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix.matrix[i][j] = m[i][j];
      complements.matrix[i][j] = r[i][j];
    }
  }
  ret = s21_calc_complements(&matrix, &res);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&complements, &res);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res);
  s21_remove_matrix(&complements);
}
END_TEST

START_TEST(test_s21_inverse_matrix) {
  matrix_t matrix, inv_matrix, res;

  int width = 3;
  double mat1[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double inv1[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  s21_create_matrix(width, width, &matrix);
  s21_create_matrix(width, width, &inv_matrix);
  s21_create_matrix(width, width, &res);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < width; j++) {
      matrix.matrix[i][j] = mat1[i][j];
      inv_matrix.matrix[i][j] = inv1[i][j];
    }
  }
  int ret = s21_inverse_matrix(&matrix, &res);
  ck_assert_int_eq(ret, OK);
  ret = s21_eq_matrix(&res, &inv_matrix);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&inv_matrix);
  s21_remove_matrix(&res);
}
END_TEST

Suite *s21_matrix_suite() {
  Suite *s = suite_create("s21_matrix_test");

  TCase *tc_s21_create_matrix = tcase_create("test_s21_create_matrix");
  suite_add_tcase(s, tc_s21_create_matrix);
  tcase_add_test(tc_s21_create_matrix, test_s21_create_matrix);

  TCase *tc_s21_eq_matrix = tcase_create("test_s21_eq_matrix");
  suite_add_tcase(s, tc_s21_eq_matrix);
  tcase_add_test(tc_s21_eq_matrix, test_s21_eq_matrix);

  TCase *tc_s21_sum_matrix = tcase_create("test_s21_sum_matrix");
  suite_add_tcase(s, tc_s21_sum_matrix);
  tcase_add_test(tc_s21_sum_matrix, test_s21_sum_matrix);

  TCase *tc_s21_sub_matrix = tcase_create("test_s21_sub_matrix");
  suite_add_tcase(s, tc_s21_sub_matrix);
  tcase_add_test(tc_s21_sub_matrix, test_s21_sub_matrix);

  TCase *tc_s21_mult_number = tcase_create("test_s21_mult_number");
  suite_add_tcase(s, tc_s21_mult_number);
  tcase_add_test(tc_s21_mult_number, test_s21_mult_number);

  TCase *tc_s21_mult_matrix = tcase_create("test_s21_mult_matrix");
  suite_add_tcase(s, tc_s21_mult_matrix);
  tcase_add_test(tc_s21_mult_matrix, test_s21_mult_matrix);

  TCase *tc_s21_transpose = tcase_create("test_s21_transpose");
  suite_add_tcase(s, tc_s21_transpose);
  tcase_add_test(tc_s21_transpose, test_s21_transpose);

  TCase *tc_s21_determinant = tcase_create("test_s21_determinant");
  suite_add_tcase(s, tc_s21_determinant);
  tcase_add_test(tc_s21_determinant, test_s21_determinant);

  TCase *tc_s21_calc_complements = tcase_create("test_s21_calc_complements");
  suite_add_tcase(s, tc_s21_calc_complements);
  tcase_add_test(tc_s21_calc_complements, test_s21_calc_complements);

  TCase *tc_s21_inverse_matrix = tcase_create("test_s21_inverse_matrix");
  suite_add_tcase(s, tc_s21_inverse_matrix);
  tcase_add_test(tc_s21_inverse_matrix, test_s21_inverse_matrix);

  return s;
}

int main() {
  int no_failed = 0;
  Suite *s = s21_matrix_suite();
  SRunner *runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

// for (int i = 0; i < width; i++) {
// for (int j = 0; j < width; j++) {
// printf("%lF\t", inv_matrix.matrix[i][j]);
// }
// printf("\n");
// }
// printf("\n");
// for (int i = 0; i < width; i++) {
// for (int j = 0; j < width; j++) {
// printf("%lF\t", res.matrix[i][j]);
// }
// printf("\n");
// }