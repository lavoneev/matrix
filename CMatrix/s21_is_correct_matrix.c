#include "s21_matrix.h"

int s21_is_correct_matrix(matrix_t *A) {
  int code = 1;
  if (!A || !A->matrix) code = 0;
  for (int i = 0; i < A->rows; i++) {
    if (!A->matrix[i]) code = 0;
  }

  if (code && (A->rows <= 0 || A->columns <= 0)) code = 0;

  return code;
}
