#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  this->rows_ = 0;
  this->cols_ = 0;

  this->matrix_ = nullptr;
}

S21Matrix::S21Matrix(const int rows, const int cols)
    : rows_{rows}, cols_{cols} {
  if (rows < 1 || cols < 1) {
    this->rows_ = 0, this->cols_ = 0;
    this->matrix_ = nullptr;
    throw std::out_of_range("Invalid rows or cols value");
  }

  this->matrix_ = new double*[this->rows_];
  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->cols_];
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = 0.0;
    }
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = new double*[rows_];
  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->cols_];
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (this->matrix_) {
    for (int i = 0; i < this->rows_; ++i) {
      delete[] this->matrix_[i];
    }
    delete[] this->matrix_;
    this->matrix_ = nullptr;
    this->rows_ = this->cols_ = 0;
  }
}

int S21Matrix::GetCols() const { return this->cols_; }

int S21Matrix::GetRows() const { return this->rows_; }

S21Matrix& S21Matrix::SetRows(int i) {
  if (i < 1) {
    throw std::out_of_range("SetRows: new rows value out of range");
  }
  int min = i > this->rows_ ? this->rows_ : i;
  S21Matrix res(i, this->cols_);
  for (int k = 0; k < min; ++k) {
    for (int j = 0; j < this->cols_; ++j) {
      res(k, j) = this->matrix_[k][j];
    }
  }
  this->~S21Matrix();
  *this = res;
  return *this;
}

S21Matrix& S21Matrix::SetCols(int j) {
  if (j < 1) {
    throw std::out_of_range("SetCols: new cols value out of range");
  }
  int min = j > this->cols_ ? this->cols_ : j;
  S21Matrix res(this->rows_, j);
  for (int i = 0; i < this->rows_; ++i) {
    for (int k = 0; k < min; ++k) {
      res(i, k) = this->matrix_[i][k];
    }
  }
  this->~S21Matrix();
  *this = res;
  return *this;
}