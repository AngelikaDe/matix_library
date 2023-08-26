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
      if (matrix_[i][j] != other.matrix_[i][j]) {
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
  if (cols_ != other.rows_) {
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
  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result(rows_, cols_);
  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Different matrix dimentions");
  }
  S21Matrix tmp(*this);

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
    return S21Matrix();  // Return a 1x1 matrix with value 1
  }

  S21Matrix tmp(*this);            // Create a copy of the current matrix
  S21Matrix result(rows_, cols_);  // Create a matrix to store the complements

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minorMatrix(rows_ - 1,
                            cols_ - 1);  // Create a matrix for the minor
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
          minorMatrix.matrix_[minor_row][minor_col] = tmp.matrix_[row][col];
          minor_col++;
        }
        minor_row++;
      }

      double det =
          minorMatrix.Determinant();  // Calculate determinant of the minor
      double num = det * pow(-1, i + j);
      result.matrix_[i][j] = num;  // Store the complement value
    }
  }
  return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(rows_, cols_);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(rows_, cols_);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(rows_, cols_);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix, const double num) {
  S21Matrix result(rows_, cols_);
  result.MulNumber(num);
  return result;
}

S21Matrix S21Matrix::operator==(const S21Matrix& other) {
  return EqMatrix(other);
}

S21Matrix S21Matrix::operator=(const S21Matrix& other) {
  S21Matrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix, const double num) {
  MultNumber(number);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  MultNumber(other);
  return *this;
}