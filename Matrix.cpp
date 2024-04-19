#include <cassert>
#include "Matrix.hpp"

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) 
{
  // test requirements
  assert(0 < width && width <= MAX_MATRIX_WIDTH);
  assert(0 < height && height <= MAX_MATRIX_HEIGHT);

  // set width and height of matrix
  mat->width = width;
  mat->height = height;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) 
{
  // print width and height
  os << Matrix_width(mat) << " " << Matrix_height(mat) << "\n";

  // print matrix value
  for (int r = 0; r < Matrix_height(mat); r++) 
  {
    for (int c = 0; c < Matrix_width(mat); c++) 
    {
      os << *Matrix_at(mat, r, c) << " ";
    }

    // print newline between rows
    os << "\n";
  }
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) 
{
  return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) 
{
  return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) 
{
  // test requirements
  assert(Matrix_at(mat, 0, 0) <= ptr);
  assert(ptr <= Matrix_at(mat, Matrix_height(mat) - 1, Matrix_width(mat) - 1));
  
  return (ptr - Matrix_at(mat, 0, 0)) / Matrix_width(mat);
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) 
{
  // test requirements
  assert(Matrix_at(mat, 0, 0) <= ptr);
  assert(ptr <= Matrix_at(mat, Matrix_height(mat) - 1, Matrix_width(mat) - 1));
  
  return (ptr - Matrix_at(mat, 0, 0)) - (Matrix_row(mat, ptr) * Matrix_width(mat));
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) 
{
  // test requirements
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column && column < Matrix_width(mat));

  // return selected element
  return &mat->data[row * Matrix_width(mat) + column];
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) 
{
  // test requirements
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column && column < Matrix_width(mat));

  // return selected element
  return &mat->data[row * Matrix_width(mat) + column];
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) 
{
  // loop through matrix and inititalize each element with value
  for (int r = 0; r < Matrix_height(mat); r++) 
  {
    for (int c = 0; c < Matrix_width(mat); c++) 
    {
      *Matrix_at(mat, r, c) = value;
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) 
{
  // loop through matrix and fill border
  for (int r = 0; r < Matrix_height(mat); r++) 
  {
    for (int c = 0; c < Matrix_width(mat); c++) 
    {
      // fill first row
      if (r == 0) { *Matrix_at(mat, r, c) = value; }

      // fill first column
      if (c == 0) { *Matrix_at(mat, r, c) = value; }

      // fill last row
      if (r == Matrix_height(mat) - 1) { *Matrix_at(mat, r, c) = value; }

      // fill last column
      if (c == Matrix_width(mat) - 1) { *Matrix_at(mat, r, c) = value; }
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) 
{
  // initialize a max value for comparison
  int max = *Matrix_at(mat, 0, 0);

  for (int r = 0; r < Matrix_height(mat); r++) 
  {
    for (int c = 0; c < Matrix_width(mat); c++) 
    {
      // test if current element is greater than max
      if (*Matrix_at(mat, r, c) > max) 
      {
        max = *Matrix_at(mat, r, c);
      }
    }
  }

  return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row, 
                                      int column_start, int column_end) 
{
  // test requirements
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);
  
  // initialize min value for comparison & pointer to element
  int min = *Matrix_at(mat, row, column_end - 1);
  const int *ptr = Matrix_at(mat, row, column_end - 1);

  // loop through region backwards to find minimum value
  for (int c = column_end - 1; c >= column_start; c--) 
  {
    // test if element is less than min
    if (*Matrix_at(mat, row, c) <= min) 
    {
      min = *Matrix_at(mat, row, c);
      ptr = Matrix_at(mat, row, c);
    }
  }

  return Matrix_column(mat, ptr);
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row, int column_start, int column_end) 
{
  // test requirements
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  // initialize min value for comparison
  int min = *Matrix_at(mat, row, column_start);

  // loop through region to find minimum value
  for (int c = column_start; c < column_end; c++) 
  {
    // test if element is less than min
    if (*Matrix_at(mat, row, c) < min) 
    {
      min = *Matrix_at(mat, row, c);
    }
  }

  return min;
}