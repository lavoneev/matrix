#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  s21_code code = OK;

  if (A == NULL || A->matrix == NULL || B == NULL || A->matrix == NULL ||
      result == NULL)
    return 1;

  if (A->rows != B->columns || A->columns != B->rows) return 2;

  code = s21_create_matrix(A->rows, B->columns, result);

  for (int i = 0; i < A->rows && !code; i++) {
    for (int j = 0; j < B->columns; j++) {
      double n = 0;
      for (int x = 0; x < A->columns; x++) {
        n += A->matrix[i][x] * B->matrix[x][j];
      }
      if (isinf(fabs(n)) || isnan(fabs(n))) code = CALC_ERROR;
      if (!code) result->matrix[i][j] = n;
    }
  }
  return code;
}
