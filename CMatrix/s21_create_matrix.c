#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0) return INCORRECT_MATRIX;
  result->matrix = calloc(rows, sizeof(double *));
  result->rows = rows;
  result->columns = columns;
  if (!result->matrix) return MALLOC_FAILED;
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = calloc(columns, sizeof(double));
    if (!result->matrix[i]) {
      for (int j = 0; j < i; j++) free(result->matrix[j]);
      free(result->matrix);
      return MALLOC_FAILED;
    }
  }
  return OK;
}
