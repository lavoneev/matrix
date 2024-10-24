#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!checking_matrix(A)) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALC_ERROR;
  double det = 0;
  int code = s21_determinant(A, &det);
  if (fabs(det) < 1e-6 || code) return CALC_ERROR;
  if (A->columns == 1) {
    s21_create_matrix(1, 1, result);
    result->matrix[0][0] = 1 / A->matrix[0][0];
  } else {
    matrix_t temp_matrix;
    matrix_t temp_matrix_2;
    s21_transpose(A, &temp_matrix);
    s21_calc_complements(&temp_matrix, &temp_matrix_2);
    det = 1 / det;
    s21_mult_number(&temp_matrix_2, det, result);
    s21_remove_matrix(&temp_matrix);
    s21_remove_matrix(&temp_matrix_2);
  }
  return OK;
}
