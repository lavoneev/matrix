#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    return false;
  }
  int flag = 1;
  for (int i = 0; i < this->rows_ && flag; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (this->matrix_[i][j] != other.matrix_[i][j]) {
        flag = 0;
        break;
      }
    }
  }
  return flag;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::invalid_argument("SumMatrix: Invalid size of matrix_");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::invalid_argument("SubMatrix: Invalid size of matrix_");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->rows_ != other.cols_) {
    throw std::invalid_argument("MulMatrix: Invalid matrix_ given");
  }
  S21Matrix result(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      double res = 0.0;
      for (int k = 0; k < this->cols_; k++) {
        res += this->matrix_[i][k] * other.matrix_[k][j];
      }
      result.matrix_[i][j] = res;
    }
  }
  this->~S21Matrix();
  *this = result;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(this->cols_, this->rows_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      result.matrix_[j][i] = this->matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::Minor(int i, int j) const {
  S21Matrix minor(this->rows_ - 1, this->cols_ - 1);
  for (int l = 0; l < i; ++l) {
    for (int k = 0; k < this->cols_; ++k) {
      if (k < j) {
        minor.matrix_[l][k] = this->matrix_[l][k];
      } else if (k > j) {
        minor.matrix_[l][k - 1] = this->matrix_[l][k];
      }
    }
  }
  for (int l = i + 1; l < this->rows_; ++l) {
    for (int k = 0; k < this->cols_; ++k) {
      if (k < j) {
        minor.matrix_[l - 1][k] = this->matrix_[l][k];
      } else if (k > j) {
        minor.matrix_[l - 1][k - 1] = this->matrix_[l][k];
      }
    }
  }
  return minor;
}

double S21Matrix::Determinant() const {
  if (this->cols_ != this->rows_) {
    throw std::invalid_argument("Determinant: Not square matrix");
  }
  if (this->rows_ == 1) {
    return this->matrix_[0][0];
  }
  if (this->rows_ == 2) {
    return this->matrix_[0][0] * this->matrix_[1][1] -
           this->matrix_[1][0] * this->matrix_[0][1];
  }
  double result = 0.0;
  for (int i = 0; i < this->rows_; i++) {
    S21Matrix minor = this->Minor(0, i);
    result += pow(-1, i) * this->matrix_[0][i] * minor.Determinant();
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (this->rows_ != this->cols_ || this->rows_ == 1) {
    throw std::invalid_argument("CalcComplements: Invalid matrix_");
  }
  S21Matrix result(this->rows_, this->cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      S21Matrix minor = this->Minor(i, j);
      result.matrix_[i][j] = pow(-1, i + j) * minor.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double res = this->Determinant();
  if (fabs(res) < EPS) {
    throw std::domain_error("InverseMatrix: Zero determinant");
  }
  S21Matrix result(this->rows_, this->cols_);
  if (this->rows_ == 1) {
    result.matrix_[0][0] = 1.0 / this->matrix_[0][0];
  } else {
    result = this->CalcComplements().Transpose();
    result.MulNumber(1.0 / res);
  }
  return result;
}