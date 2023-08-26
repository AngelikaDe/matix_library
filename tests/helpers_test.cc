#include "tests.h"

TEST(TestHelpers, SubtestEqTrue) {
  S21Matrix mat = S21Matrix(3, 3);
  S21Matrix mat2 = S21Matrix(3, 3);
  double tmp[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  mat.MatrixFill(tmp);
  mat2.MatrixFill(tmp);
  ASSERT_EQ(mat.EqMatrix(mat2), true);
}

TEST(TestHelpers, SubtestEqFalse) {
  S21Matrix mat = S21Matrix(3, 3);
  S21Matrix mat2 = S21Matrix(3, 3);
  double tmp[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  mat.MatrixFill(tmp);
  mat2.MatrixFill(tmp);
  mat2(0, 0) = 0;
  ASSERT_EQ(mat.EqMatrix(mat2), false);
}

TEST(TestHelpers, SubtestMatrixFill) {
  S21Matrix mat = S21Matrix(3, 3);
  double tmp[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  mat.MatrixFill(tmp);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      ASSERT_EQ(mat(i, j), tmp[i * mat.GetCols() + j]);
    }
  }
}

TEST(TestHelpers, SubtestCutMatrix) {
  S21Matrix mat = S21Matrix(3, 3);
  S21Matrix mat2 = S21Matrix(2, 2);
  double tmp[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  double tmp2[16] = {5, 6, 8, 9};
  mat.MatrixFill(tmp);
  mat2.MatrixFill(tmp2);
  ASSERT_EQ(mat.CutMatrix(0, 0).EqMatrix(mat2), true);
}

TEST(TestHelpers, SubtestCutMatrixError) {
  S21Matrix mat = S21Matrix(3, 3);
  S21Matrix mat2 = S21Matrix(2, 2);
  double tmp[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  double tmp2[16] = {5, 6, 8, 9};
  mat.MatrixFill(tmp);
  mat2.MatrixFill(tmp2);
  ASSERT_THROW(mat.CutMatrix(10, 1), std::out_of_range);
}
