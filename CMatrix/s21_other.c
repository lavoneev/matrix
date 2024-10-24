#include "s21_matrix.h"

void get_matrix(matrix_t *A, matrix_t *new, int skip_row, int skip_column) {
  int in = 0, jn = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i != skip_row) {
      for (int j = 0; j < A->columns; j++) {
        if (j != skip_column) {
          *(*((new->matrix) + in) + jn) = *(*((A->matrix) + i) + j);
          jn++;
        }
      }
      in++;
      jn = 0;
    }
  }
}

int checking_matrix(matrix_t *matrix) {
  return matrix && matrix->rows > 0 && matrix->columns > 0;
}

void algebraic_additions(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      *(*((A->matrix) + i) + j) = *(*((A->matrix) + i) + j) * pow(-1, (i + j));
    }
  }
}
