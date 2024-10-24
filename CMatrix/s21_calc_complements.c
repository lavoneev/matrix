#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!checking_matrix(A)) {
    return INCORRECT_MATRIX;
  }
  if (A->rows != A->columns) {
    return CALC_ERROR;
  }
  if (s21_create_matrix(A->columns, A->rows, result) != OK) {
    return MALLOC_FAILED;
  }
  if (A->rows == 1) {
    result->matrix[0][0] = A->matrix[0][0];
  } else {
    matrix_t temp_matrix;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        s21_create_matrix(A->rows - 1, A->columns - 1, &temp_matrix);
        get_matrix(A, &temp_matrix, i, j);
        double det = 0;
        s21_determinant(&temp_matrix, &det);
        result->matrix[i][j] = det;
        s21_remove_matrix(&temp_matrix);
      }
    }
    algebraic_additions(result);
  }
  return OK;
}
