#include <cassert>
#include "Image.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) 
{
	// test requirements
	assert(0 < width && width <= MAX_MATRIX_WIDTH);
	assert(0 < height && height <= MAX_MATRIX_HEIGHT);

	// set width and height of matrix
  img->width = width;
  img->height = height;

	// initialize matrices
	Matrix_init(&img->red_channel, width, height);
	Matrix_init(&img->green_channel, width, height);
	Matrix_init(&img->blue_channel, width, height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) 
{
  // declare variables for file and img initialization
  std::string buffer;
  int width, height;

  // get file information
  is >> buffer; // discard P3
  is >> width >> height;
  is >> buffer; // discard max intensity

  // initialize image
  Image_init(img, width, height);

  // read rgb values into matrices
  for (int r = 0; r < Image_height(img); r++)
  {
    for (int c = 0; c < Image_width(img); c++)
    {
      is >> *Matrix_at(&img->red_channel, r, c);
      is >> *Matrix_at(&img->green_channel, r, c);
      is >> *Matrix_at(&img->blue_channel, r, c);
    }
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) 
{
  // print width and height

  os << "P3\n" << Image_width(img) << " " << Image_height(img) << "\n255\n";

  // print matrix value
  for (int r = 0; r < Image_height(img); r++) 
  {
    for (int c = 0; c < Image_width(img); c++) 
    {
      os << *(Matrix_at(&img->red_channel, r, c)) << " ";
      os << *(Matrix_at(&img->green_channel, r, c)) << " ";
      os << *(Matrix_at(&img->blue_channel, r, c)) << " ";
    }

    // print newline between rows
    os << "\n";
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) 
{
	return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) 
{
	return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) 
{
  assert(0 <= row && row < Image_height(img));
  assert(0 <= column && column < Image_width(img));
  int red_value = *(Matrix_at(&img->red_channel, row, column));
  int green_value = *(Matrix_at(&img->green_channel, row, column));
  int blue_value = *(Matrix_at(&img->blue_channel, row, column));
  Pixel found_pixel = {red_value, green_value, blue_value};
  return found_pixel;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) 
{
  assert(0 <= row && row < Image_height(img));
  assert(0 <= column && column < Image_width(img));
  assert(0 <= color.r && color.r <= MAX_INTENSITY);
  assert(0 <= color.g && color.g <= MAX_INTENSITY);
  assert(0 <= color.b && color.b <= MAX_INTENSITY);

	*(Matrix_at(&img->red_channel, row, column)) = color.r;
	*(Matrix_at(&img->green_channel, row, column)) = color.g;
	*(Matrix_at(&img->blue_channel, row, column)) = color.b;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) 
{
  // fill each matrix with its respective values
  Matrix_fill(&img->red_channel, color.r);
  Matrix_fill(&img->green_channel, color.g);
  Matrix_fill(&img->blue_channel, color.b);
}
