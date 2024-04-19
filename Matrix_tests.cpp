#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Initializes a matrix with a width and a height
// and tests the width and height for correct values
TEST(test_init_basic) 
{
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 3;

  // initialize Matrix
  Matrix_init(mat, width, height);

  // test width and height of matrix
  ASSERT_EQUAL(Matrix_width(mat), width);
  ASSERT_EQUAL(Matrix_height(mat), height);

  delete mat;
}

// Initializes a matrix with a width and a height
// and tests the width and height for correct values
TEST(test_init_full_matrix) 
{
  Matrix *mat = new Matrix;

  const int width = MAX_MATRIX_WIDTH;
  const int height = MAX_MATRIX_HEIGHT;

  // initialize Matrix
  Matrix_init(mat, width, height);

  // test width and height of matrix
  ASSERT_EQUAL(Matrix_width(mat), width);
  ASSERT_EQUAL(Matrix_height(mat), height);

  delete mat;
}

// Tests the output of the print function with the
// correct output of the print function for 3x3 matrix
TEST(test_print_basic) 
{
  Matrix *mat = new Matrix;

  // intialize the matrix with a value
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 1);

  // create ostream objects for testing
  ostringstream expected;
  expected << "3 3\n"
           << "1 1 1 \n"
           << "1 1 1 \n"
           << "1 1 1 \n";
  ostringstream actual;
  Matrix_print(mat, actual);

  // compare outputs
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

// Tests the output of the print function with the
// correct output of the print function for 5x3 matrix
TEST(test_print_long_width) 
{
  Matrix *mat = new Matrix;

  // intialize the matrix with a value
  Matrix_init(mat, 5, 3);
  Matrix_fill(mat, 1);

  // create ostream objects for testing
  ostringstream expected;
  expected << "5 3\n"
           << "1 1 1 1 1 \n"
           << "1 1 1 1 1 \n"
           << "1 1 1 1 1 \n";
  ostringstream actual;
  Matrix_print(mat, actual);

  // compare outputs
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

// Tests the output of the print function with the
// correct output of the print function for 3x5 matrix
TEST(test_print_long_height) 
{
  Matrix *mat = new Matrix;

  // intialize the matrix with a value
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, 1);

  // create ostream objects for testing
  ostringstream expected;
  expected << "3 5\n"
           << "1 1 1 \n"
           << "1 1 1 \n"
           << "1 1 1 \n"
           << "1 1 1 \n"
           << "1 1 1 \n";
  ostringstream actual;
  Matrix_print(mat, actual);

  // compare outputs
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

// Tests the output of the print function with the
// correct output of the print function for 1x1 matrix
TEST(test_print_one_element) 
{
  Matrix *mat = new Matrix;

  // intialize the matrix with a value
  Matrix_init(mat, 1, 1);
  Matrix_fill(mat, 1);

  // create ostream objects for testing
  ostringstream expected;
  expected << "1 1\n"
           << "1 \n";
  ostringstream actual;
  Matrix_print(mat, actual);

  // compare outputs
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

// Initializes a matrix with a width
// and tests the width for correct values
TEST(test_width) 
{
  Matrix *mat = new Matrix;

  const int width = 3;

  // initialize Matrix
  Matrix_init(mat, width, 1);

  // test width of matrix
  ASSERT_EQUAL(Matrix_width(mat), width);

  delete mat;
}

// Initializes a matrix with a height
// and tests the height for correct values
TEST(test_height) 
{
  Matrix *mat = new Matrix;

  const int height = 3;

  // initialize Matrix
  Matrix_init(mat, 1, height);

  // test height of matrix
  ASSERT_EQUAL(Matrix_height(mat), height);

  delete mat;
}

// Tests that matrix_row returns the correct row
// when the matrix's width is longer than its height
TEST(test_row_long_width)
{
  Matrix *mat = new Matrix;

  // initialize matrix
  Matrix_init(mat, 5, 3);

  // create pointer to row 2, column 4 [1, 3]
  int *ptr = Matrix_at(mat, 1, 3);

  // test that correct row is returned
  ASSERT_EQUAL(Matrix_row(mat, ptr), 1);

  delete mat;
}

// Tests that matrix_row returns the correct row
// when the matrix's height is longer than its width
TEST(test_row_long_height)
{
  Matrix *mat = new Matrix;

  // initialize matrix
  Matrix_init(mat, 3, 5);

  // create pointer to row 4, column 3 [3, 2]
  int *ptr = Matrix_at(mat, 3, 2);

  // test that correct row is returned
  ASSERT_EQUAL(Matrix_row(mat, ptr), 3);

  delete mat;
}

// Tests that matrix_row returns the correct row
// when the ptr points to element in first row
TEST(test_row_first_row)
{
  Matrix *mat = new Matrix;

  // initialize matrix
  Matrix_init(mat, 5, 1);

  // create pointer to row 1, column 4 [0, 3]
  int *ptr = Matrix_at(mat, 0, 3);

  // test that correct row is returned
  ASSERT_EQUAL(Matrix_row(mat, ptr), 0);

  delete mat;
}

// Tests that matrix_row returns the correct row
// when the ptr points to element in last row
TEST(test_row_last_row)
{
  Matrix *mat = new Matrix;

  // initialize matrix
  Matrix_init(mat, 5, 5);

  // create pointer to row 5, column 3
  int *ptr = Matrix_at(mat, 4, 2);

  // test that correct row is returned
  ASSERT_EQUAL(Matrix_row(mat, ptr), 4);

  delete mat;
}

// Tests that matrix_row returns the correct row
// when the ptr points to element in first column
TEST(test_row_first_column)
{
  Matrix *mat = new Matrix;

  // initialize matrix
  Matrix_init(mat, 5, 5);

  // create pointer to row 3, column 1 [2, 0]
  int *ptr = Matrix_at(mat, 2, 0);

  // test that correct row is returned
  ASSERT_EQUAL(Matrix_row(mat, ptr), 2);

  delete mat;
}

// Tests that matrix_row returns the correct row
// when the ptr points to element in last column
TEST(test_row_last_column)
{
  Matrix *mat = new Matrix;

  // initialize matrix
  Matrix_init(mat, 5, 5);

  // create pointer to row 4, column 5 [3, 4]
  int *ptr = Matrix_at(mat, 3, 4);

  // test that correct row is returned
  ASSERT_EQUAL(Matrix_row(mat, ptr), 3);

  delete mat;
}

// Tests that matrix_column returns the correct column
// when the matrix's width is longer than its height
TEST(test_column_long_width)
{
  Matrix *mat = new Matrix;

  // initialize matrix
  Matrix_init(mat, 5, 3);

  // create pointer to row 2, column 4 [1, 3]
  int *ptr = Matrix_at(mat, 1, 3);

  // test that correct column is returned
  ASSERT_EQUAL(Matrix_column(mat, ptr), 3);

  delete mat;
}

// Tests that matrix_column returns the correct column
// when the matrix's height is longer than its width
TEST(test_column_long_height)
{
  Matrix *mat = new Matrix;

  // initialize matrix
  Matrix_init(mat, 3, 5);

  // create pointer to row 4, column 3 [3, 2]
  int *ptr = Matrix_at(mat, 3, 2);

  // test that correct column is returned
  ASSERT_EQUAL(Matrix_column(mat, ptr), 2);

  delete mat;
}

// Tests that matrix_column returns the correct column
// when the ptr points to element in first column
TEST(test_column_first_row)
{
  Matrix *mat = new Matrix;

  // initialize matrix
  Matrix_init(mat, 5, 1);

  // create pointer to row 1, column 4 [0, 3]
  int *ptr = Matrix_at(mat, 0, 3);

  // test that correct column is returned
  ASSERT_EQUAL(Matrix_column(mat, ptr), 3);

  delete mat;
}

// Tests that matrix_column returns the correct column
// when the ptr points to element in last column
TEST(test_column_last_row)
{
  Matrix *mat = new Matrix;

  // initialize matrix
  Matrix_init(mat, 5, 5);

  // create pointer to row 3, column 5
  int *ptr = Matrix_at(mat, 2, 4);

  // test that correct row is returned
  ASSERT_EQUAL(Matrix_column(mat, ptr), 4);

  delete mat;
}

// Tests that matrix_column returns the correct column
// when the ptr points to element in first column
TEST(test_column_first_column)
{
  Matrix *mat = new Matrix;

  // initialize matrix
  Matrix_init(mat, 5, 5);

  // create pointer to row 3, column 1 [2, 0]
  int *ptr = Matrix_at(mat, 2, 0);

  // test that correct row is returned
  ASSERT_EQUAL(Matrix_column(mat, ptr), 0);

  delete mat;
}

// Tests that matrix_column returns the correct column
// when the ptr points to element in last column
TEST(test_column_last_column)
{
  Matrix *mat = new Matrix;

  // initialize matrix
  Matrix_init(mat, 5, 5);

  // create pointer to row 4, column 5 [2, 4]
  int *ptr = Matrix_at(mat, 3, 4);

  // test that correct row is returned
  ASSERT_EQUAL(Matrix_column(mat, ptr), 4);

  delete mat;
}

// Tests matrix_at under normal conditions
TEST(test_matrix_at_basic)
{
  Matrix *mat = new Matrix;

  // initialize matrix and fill with values
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 1);

  // insert 1 at row 2 column 3
  *Matrix_at(mat, 1, 2) = 0;

  // create ostream objects for testing
  ostringstream expected;
  expected << "3 3\n"
           << "1 1 1 \n"
           << "1 1 0 \n"
           << "1 1 1 \n";
  ostringstream actual;
  Matrix_print(mat, actual);

  // test that matrices are equal
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

// Tests matrix_at at first element
TEST(test_matrix_at_first_element)
{
  Matrix *mat = new Matrix;

  // initialize matrix and fill with values
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 1);

  // insert 1 at row 1 column 1
  *Matrix_at(mat, 0, 0) = 0;

  // create ostream objects for testing
  ostringstream expected;
  expected << "3 3\n"
           << "0 1 1 \n"
           << "1 1 1 \n"
           << "1 1 1 \n";
  ostringstream actual;
  Matrix_print(mat, actual);

  // test that matrices are equal
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

// Tests matrix_at at last element
TEST(test_matrix_at_last_element)
{
  Matrix *mat = new Matrix;

  // initialize matrix and fill with values
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 1);

  // insert 1 at row 2 column 3
  *Matrix_at(mat, 2, 2) = 0;

  // create ostream objects for testing
  ostringstream expected;
  expected << "3 3\n"
           << "1 1 1 \n"
           << "1 1 1 \n"
           << "1 1 0 \n";
  ostringstream actual;
  Matrix_print(mat, actual);

  // test that matrices are equal
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

// Tests matrix_at at last element with full matrix
TEST(test_matrix_at_last_element_full_matrix)
{
  Matrix *mat = new Matrix;

  // initialize matrix and fill with values
  Matrix_init(mat, MAX_MATRIX_WIDTH, MAX_MATRIX_HEIGHT);
  Matrix_fill(mat, 1);

  // insert 0 at row 500 column 500
  *Matrix_at(mat, 499, 499) = 0;

  // create ostream objects for testing
  for (int r = 0; r < Matrix_height(mat); r++)
  {
    for (int c = 0; c < Matrix_width(mat); c++)
    {
      if (r == 499 && c == 499)
      { ASSERT_EQUAL(*Matrix_at(mat, r, c), 0); }
      else
      { ASSERT_EQUAL(*Matrix_at(mat, r, c), 1); }
    }
  }

  delete mat;
}

// Tests const matrix_at under normal conditions
TEST(test_const_matrix_at_basic)
{
  Matrix *mat = new Matrix;
  const Matrix *mat_ptr = mat;

  // initialize matrix and fill with values
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 1);

  // insert 1 at row 2 column 3
  *Matrix_at(mat, 1, 2) = 0;

  // test that const matrix_at returns correct value
  ASSERT_EQUAL(*Matrix_at(mat_ptr, 1, 2), 0);

  delete mat;
}

// Tests const matrix_at at first element
TEST(test_const_matrix_at_first_element)
{
  Matrix *mat = new Matrix;
  const Matrix *mat_ptr = mat;

  // initialize matrix and fill with values
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 1);

  // insert 1 at row 1 column 1
  *Matrix_at(mat, 0, 0) = 0;

  // test that const matrix_at returns correct value
  ASSERT_EQUAL(*Matrix_at(mat_ptr, 0, 0), 0);

  delete mat;
}

// Tests const matrix_at at last element
TEST(test_const_matrix_at_last_element)
{
  Matrix *mat = new Matrix;
  const Matrix *mat_ptr = mat;

  // initialize matrix and fill with values
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 1);

  // insert 1 at row 3 column 3
  *Matrix_at(mat, 2, 2) = 0;

  // test that const matrix_at returns correct value
  ASSERT_EQUAL(*Matrix_at(mat_ptr, 2, 2), 0);

  delete mat;
}

// Tests const matrix_at at last element with full matrix
TEST(test_const_matrix_at_last_element_full_matrix)
{
  Matrix *mat = new Matrix;
  const Matrix *mat_ptr = mat;

  // initialize matrix and fill with values
  Matrix_init(mat, MAX_MATRIX_WIDTH, MAX_MATRIX_HEIGHT);
  Matrix_fill(mat, 1);

  // insert 0 at row 500 column 500
  *Matrix_at(mat, 499, 499) = 0;

  // create ostream objects for testing
  for (int r = 0; r < Matrix_height(mat); r++)
  {
    for (int c = 0; c < Matrix_width(mat); c++)
    {
      if (r == 499 && c == 499)
      { ASSERT_EQUAL(*Matrix_at(mat_ptr, r, c), 0); }
      else
      { ASSERT_EQUAL(*Matrix_at(mat_ptr, r, c), 1); }
    }
  }

  delete mat;
}

// Fills a 3x3 matrix with a value and checks
// that matrix_at returns that value for each element.
TEST(test_fill_basic) 
{
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 3;
  const int value = 1;

  // initialize and fill matrix
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, value);

  // loop through matrix testing each value
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat;
}

// Fills a 1x1 Matrix with a value and checks
// that Matrix_at returns that value
TEST(test_fill_one_element)
{
  Matrix *mat = new Matrix;

  const int width = 1;
  const int height = 1;
  const int value = 1;

  // intialize and fill matrix
  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);

  // loop through matrix testing each value
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat;
}

// Fills a 500x500 Matrix with a value and checks
// that Matrix_at returns that value
TEST(test_fill_full_matrix)
{
  Matrix *mat = new Matrix;

  const int width = MAX_MATRIX_WIDTH;
  const int height = MAX_MATRIX_HEIGHT;
  const int value = 1;

  // intialize and fill matrix
  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);

  // loop through matrix testing each value
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat;
}

// Tests the output of the fill_border
// function with a 3x3 matrix
TEST(test_fill_border_basic) 
{
  Matrix *mat = new Matrix;

  // intialize the matrix with zeros
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 0);

  // fill border with ones
  Matrix_fill_border(mat, 1);

  // compare outputs
  // loop through matrix testing each value
  for(int r = 0; r < Matrix_height(mat); ++r){
    for(int c = 0; c < Matrix_width(mat); ++c){
      if (r == 0) { ASSERT_EQUAL(*Matrix_at(mat, r, c), 1); }
      else if (r == Matrix_height(mat) - 1) { ASSERT_EQUAL(*Matrix_at(mat, r, c), 1); }
      else if (c == 0) { ASSERT_EQUAL(*Matrix_at(mat, r, c), 1); }
      else if (c == Matrix_width(mat) - 1) { ASSERT_EQUAL(*Matrix_at(mat, r, c), 1); }
      else { ASSERT_EQUAL(*Matrix_at(mat, r, c), 0); }
    }
  }

  delete mat;
}

// Tests the output of the fill_border
// function with a full matrix
TEST(test_fill_border_full_matrix) 
{
  Matrix *mat = new Matrix;

  // intialize the matrix with zeros
  Matrix_init(mat, MAX_MATRIX_WIDTH, MAX_MATRIX_HEIGHT);
  Matrix_fill(mat, 0);

  // fill border with ones
  Matrix_fill_border(mat, 1);

  // compare outputs
  // loop through matrix testing each value
  for(int r = 0; r < Matrix_height(mat); ++r){
    for(int c = 0; c < Matrix_width(mat); ++c){
      if (r == 0) { ASSERT_EQUAL(*Matrix_at(mat, r, c), 1); }
      else if (r == Matrix_height(mat) - 1) { ASSERT_EQUAL(*Matrix_at(mat, r, c), 1); }
      else if (c == 0) { ASSERT_EQUAL(*Matrix_at(mat, r, c), 1); }
      else if (c == Matrix_width(mat) - 1) { ASSERT_EQUAL(*Matrix_at(mat, r, c), 1); }
      else { ASSERT_EQUAL(*Matrix_at(mat, r, c), 0); }
    }
  }

  delete mat;
}

// Fills the matrix with value and tests
// the correct maximum value is found
TEST(test_max_basic) 
{
  Matrix *mat = new Matrix;

  // initialize matrix
  Matrix_init(mat, 3, 3);

  // fill matrix with values
  int value = 1;

  for (int r = 0; r < Matrix_height(mat); r++) 
  {
    for (int c = 0; c < Matrix_width(mat); c++) 
    {
      *Matrix_at(mat, r, c) = value++;
    }
  }

  // test max
  ASSERT_EQUAL(Matrix_max(mat), 9);

  delete mat;
}

// Fills the matrix with value and tests
// the correct maximum value is found
TEST(test_max_one_element) 
{
  Matrix *mat = new Matrix;

  // initialize matrix and fill with values
  Matrix_init(mat, 1, 1);
  Matrix_fill(mat, 1);

  // test max
  ASSERT_EQUAL(Matrix_max(mat), 1);

  delete mat;
}

// Tests that matrix_column_of_min_value_in_row returns
// the correct column of the min value in the region
TEST(test_column_of_min_value_in_row_basic)
{
  Matrix *mat = new Matrix;

  // initialize the matrix with values
  Matrix_init(mat, 5, 5);
  Matrix_fill(mat, 1);

  // insert a min value in row 3 column 4
  *Matrix_at(mat, 2, 3) = 0;

  // test that the correct value is returned
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 0, 4), 3)

  delete mat;
}

// Tests that matrix_column_of_min_value_in_row returns
// the correct column of the min value in the region
// when two min values are in the same row
TEST(test_column_of_min_value_in_row_two_mins)
{
  Matrix *mat = new Matrix;

  // initialize the matrix with values
  Matrix_init(mat, 5, 5);
  Matrix_fill(mat, 1);

  // insert a min value in row 3 column 2 & column 4
  *Matrix_at(mat, 2, 1) = 0;
  *Matrix_at(mat, 2, 3) = 0;

  // test that the correct value is returned
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 0, 4), 1)

  delete mat;
}

// Tests that matrix_column_of_min_value_in_row returns
// the correct column of the min value in the region
// when all values in the row are equal
TEST(test_column_of_min_value_in_row_same_values)
{
  Matrix *mat = new Matrix;

  // initialize the matrix with values
  Matrix_init(mat, 5, 5);
  Matrix_fill(mat, 1);

  // test that the correct value is returned
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 0, 4), 0)

  delete mat;
}

// Tests that matrix_min_value_in_row returns
// the correct minimum value in the row
TEST(test_min_value_in_row_basic)
{
  Matrix *mat = new Matrix;

  // initialize the matrix with values
  Matrix_init(mat, 5, 5);
  Matrix_fill(mat, 1);

  // insert a min value in row 3 column 4
  *Matrix_at(mat, 2, 3) = 0;

  // test that the correct value is returned
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 0, 4), 0)

  delete mat;
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here