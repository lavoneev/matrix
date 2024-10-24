#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  *result = 0;
  if (!checking_matrix(A) || !result) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALC_ERROR;
  int size_matrix = A->rows;
  if (size_matrix == 1) {
    *result = A->matrix[0][0];
  } else if (size_matrix == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  } else if (size_matrix > 2) {
    for (int i = 0; i < A->rows; i++) {
      matrix_t temp_matrix;
      s21_create_matrix(A->rows - 1, A->columns - 1, &temp_matrix);
      get_matrix(A, &temp_matrix, i, 0);
      double d = 0;
      s21_determinant(&temp_matrix, &d);
      *result = *result + (A->matrix[i][0] * d) * pow(-1, i + 2);
      s21_remove_matrix(&temp_matrix);
    }
  }
  return OK;
}
