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
  void SumMatrix(
      const S21Matrix& other);  // Adds the second matrix to the current one
  bool EqMatrix(
      const S21Matrix& other);  // Checks matrices for equality with each other
  void SubMatrix(
      const S21Matrix& other);  // Subtracts another matrix from the current one
  void MulNumber(
      const double num);  // Multiplies the current matrix by a number
  void MulMatrix(const S21Matrix& other);  // Multiplies the current matrix by
                                           // the second matrix
  S21Matrix Transpose();  // Creates a new transposed matrix from the current
                          // one and returns it
  S21Matrix CalcComplements();
  double Determinant();  // Calculates and returns the determinant of the
                         // current matrix
  S21Matrix InverseMatrix();

 private:
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated
  double determ;
  double mult;
  double result;
};