#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_is_correct_matrix(A) || !s21_is_correct_matrix(B))
    return INCORRECT_MATRIX;

  if ((A->rows != B->rows || A->columns != B->columns)) return CALC_ERROR;

  if (s21_create_matrix(A->rows, A->columns, result)) return MALLOC_FAILED;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return OK;
}