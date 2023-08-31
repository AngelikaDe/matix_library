#include <cmath>
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
  int GetRows();
  int GetCols();
  void S21RemoveMatrix();
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
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num) const;
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int i, int j);

  void MatrixFill(const double* arr);
  void SetRows(int num);
  void SetCols(int num);

 private:
  int rows_,
      cols_;         // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated
  double mult;
  double result;
};