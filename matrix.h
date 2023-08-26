#include <iostream>

class S21Matrix {
 public:
  S21Matrix();   // Default constructor
  ~S21Matrix();  // Destructor
  S21Matrix(
      int rows,
      int cols);  // Parametrized constructor with number of rows and columns
  S21Matrix(const S21Matrix& other);  // Copy constructor
  S21Matrix(S21Matrix&& other);       // Move constructor
  void SumMatrix(const S21Matrix& other);
  bool EqMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated
};