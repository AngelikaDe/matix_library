#include "matrix.h"

S21Matrix::S21Matrix() : rows_(2), cols_(2) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  in(rows < 0 || cols < 0) {
    throw std::error("rows and cols suppose to be more that 0");
  }
  matrix_ = new double*[rows];
  if (matrix_ == nullptr) {
    throw std::error("Coulnt allocate memo")
  }
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols];
    if (matrix_[i] == nullptr) {
      throw std::error("Coulnt allocate memo");
    }
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix::S21Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

int main() {
  std::cout << "hello";
  return 0;
}