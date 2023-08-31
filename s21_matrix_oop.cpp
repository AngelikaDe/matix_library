#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(2), cols_(2) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

S21Matrix::~S21Matrix() { this->S21RemoveMatrix(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 0 || cols < 0) {
    throw std::runtime_error("rows and cols suppose to be more that 0");
  }
  matrix_ = new double*[rows];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols];
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
void S21Matrix::S21RemoveMatrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Different matrix dimentions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-07) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Different matrix dimentions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_ || rows_ != other.cols_) {
    throw std::invalid_argument("Different matrix dimentions");
  }
  S21Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);

  for (int i = 0; i < result.rows_; ++i) {
    for (int j = 0; j < result.cols_; ++j) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Different matrix dimentions");
  }
  S21Matrix tmp(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp.matrix_[i][j] = matrix_[i][j];
    }
  }
  mult = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = i + 1; j < rows_; j++) {
      mult = tmp.matrix_[j][i] / tmp.matrix_[i][i];
      for (int k = 0; k < rows_; k++) {
        tmp.matrix_[j][k] -= mult * tmp.matrix_[i][k];
      }
    }
  }
  result = 1.0;
  for (int i = 0; i < rows_; i++) {
    result *= tmp.matrix_[i][i];
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Different matrix dimensions");
  }

  if (rows_ == 1) {
    return S21Matrix(1, 1);
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minorMatrix(rows_ - 1, cols_ - 1);
      int minor_row = 0;

      for (int row = 0; row < rows_; row++) {
        if (row == i) {
          continue;
        }
        int minor_col = 0;
        for (int col = 0; col < cols_; col++) {
          if (col == j) {
            continue;
          }
          minorMatrix.matrix_[minor_row][minor_col] = matrix_[row][col];
          minor_col++;
        }
        minor_row++;
      }

      double det = minorMatrix.Determinant();

      double num = det * pow(-1, i + j);
      result.matrix_[i][j] = num;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix is not square");
  }

  double det = Determinant();
  if (fabs(det) < 1e-6) {
    throw std::invalid_argument("Matrix is singular; inverse does not exist");
  }

  S21Matrix complementMatrix = CalcComplements();
  S21Matrix transposeMatrix = complementMatrix.Transpose();

  for (int i = 0; i < transposeMatrix.rows_; i++) {
    for (int j = 0; j < transposeMatrix.cols_; j++) {
      transposeMatrix.matrix_[i][j] *= (1.0 / det);
    }
  }
  return transposeMatrix;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;

  S21Matrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Index is outside the matrix");
  }
  return matrix_[i][j];
}

void S21Matrix::MatrixFill(const double* arr) {
  int index = 0;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = arr[index++];
    }
  }
}

int S21Matrix::GetRows() { return rows_; }
int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetRows(int num) {
  if (num <= 0) throw std::invalid_argument("Array size can't be zero");
  S21Matrix result(num, cols_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      if (num > rows_ && i >= rows_) {
        result.matrix_[i][j] = 0;
      } else {
        result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      std::cout << result.matrix_[i][j] << std::endl;
    }
  }
  *this = std::move(result);
}

void S21Matrix::SetCols(int num) {
  if (num <= 0) throw std::invalid_argument("Array size can't be zero");
  S21Matrix result(rows_, num);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      if (num > cols_ && j >= cols_) {
        result.matrix_[i][j] = 0;
      } else {
        result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      std::cout << result.matrix_[i][j] << std::endl;
    }
  }
  *this = std::move(result);
}