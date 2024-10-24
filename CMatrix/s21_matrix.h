#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-7

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

typedef enum {
  OK = 0,
  INCORRECT_MATRIX = 1,
  CALC_ERROR = 2,
  MALLOC_FAILED = 3,
} s21_code;

int s21_inverse_matrix(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
double s21_minor(matrix_t *A, int rows, int columns);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_is_correct_matrix(matrix_t *A);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
void s21_remove_matrix(matrix_t *A);
int s21_create_matrix(int rows, int columns, matrix_t *result);

void s21_initialize_matrix(matrix_t *A, double start_value,
                           double iteration_step);

void get_matrix(matrix_t *A, matrix_t *new, int skip_row, int skip_column);
int checking_matrix(matrix_t *matrix);
void algebraic_additions(matrix_t *A);

#endif
