#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

//tests the image print fucntion when image is one pixel
TEST(test_print_min_size_img) {
  Image *img = new Image; // create an Image in dynamic memory

  const int min_width = 1;
  const int min_height = 1;
  const Pixel color = {5, 55, 255};

  Image_init(img, min_width, min_height);
  Image_fill(img, color);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n1 1\n255\n";
  correct << "5 55 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

//tests the image print fucntion when image is fill with max intensity pixels
TEST(test_print_max_intensity_img) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel max_intensity_pixel = {255, 255, 255};

  Image_init(img, 2, 4);
  Image_fill(img, max_intensity_pixel);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 4\n255\n";
  correct << "255 255 255 255 255 255 \n";
  correct << "255 255 255 255 255 255 \n";
  correct << "255 255 255 255 255 255 \n";
  correct << "255 255 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

//tests the image print fucntion when image is fill with min intensity pixels
TEST(test_print_min_intensity_img) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel min_intensity_pixel = {0, 0, 0};

  Image_init(img, 3, 5);
  Image_fill(img, min_intensity_pixel);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n3 5\n255\n";
  correct << "0 0 0 0 0 0 0 0 0 \n";
  correct << "0 0 0 0 0 0 0 0 0 \n";
  correct << "0 0 0 0 0 0 0 0 0 \n";
  correct << "0 0 0 0 0 0 0 0 0 \n";
  correct << "0 0 0 0 0 0 0 0 0 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

//Sets the pixels in a 5 by 3 image to various colors
//and checks the output is correct
TEST(test_image_set_and_print) {
  Image *img = new Image;

  const Pixel black = {0, 0, 0};

  const Pixel yellow = {200, 200, 0};
  const Pixel purple = {148, 0, 150};
  const Pixel brown = {139,42, 35};
  const Pixel orange = {250,100, 1};


  Image_init(img, 5,3);
  Image_fill(img, black);

  for (int r = 0; r < Image_height(img); r++) {
    Image_set_pixel(img, r, 2, brown);
  }

  for (int c = 0; c < Image_width(img); c++) {
    Image_set_pixel(img, 1, c, orange);
  }

  Image_set_pixel(img, 2, 3, purple);
  Image_set_pixel(img, 0, 2, yellow);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  ostringstream correct;
  correct << "P3\n5 3\n255\n";
  correct << "0 0 0 0 0 0 200 200 0 0 0 0 0 0 0 \n";
  correct << "250 100 1 250 100 1 250 100 1 250 100 1 250 100 1 \n";
  correct << "0 0 0 0 0 0 139 42 35 148 0 150 0 0 0 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img;
}

//Sets the pixels in a 3 by 50 image to various colors
//and checks to see if the changed pixels are correct
TEST(test_image_basic) {
  Pixel redish = {255, 30, 30};
  Pixel greenish = {12, 255, 13};
  Image *img = new Image;
  const Image *const_img = img;
  Image_init(img, 3, 50);

  ASSERT_EQUAL(Image_width(img), 3);
  ASSERT_EQUAL(Image_height(const_img), 50);

  Image_fill(img, redish);

  for (int r = 0; r < Image_height(img); r++) {
    for (int c = 0; c < Image_width(const_img); c++) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, r, c), redish));
    }
  }

  Image_set_pixel(img, 0, 1, greenish);

  for (int r = 0; r < Image_height(img); r++) {
    for (int c = 0; c < Image_width(const_img); c+=2) {
      Image_set_pixel(img, r, c, Image_get_pixel(img,0,1));
    }
  }

  for (int r = 0; r < Image_height(img); r++) {
    for (int c = 0; c < Image_width(const_img); c++) {
      if (c%2==0 || (r==0 && c==1)) {
        ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, r, c), greenish));
      }
      else {
        ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, r, c), redish));
      }
    }
  }

  delete img;
}

//Tests the reading in a "clutter" stream and outputting a "clean" stream
TEST(test_from_clutter_stream_to_clean_stream) {
  Image *img = new Image;

  // cluttered input PPM.
  string input = "P3 2 2\t255 235 0 0\n0\n225 0 \n0 0 255 5 3 2 \n";
  std::istringstream ss_input(input);
  Image_init(img, ss_input);

  string output_correct = "P3\n2 2\n255\n235 0 0 0 225 0 \n0 0 255 5 3 2 \n";

  std::ostringstream ss_output;
  Image_print(img, ss_output);
  string actual = ss_output.str();
  ASSERT_EQUAL(actual, output_correct);

  delete img;
}

//Tests image width function for a ppm file
TEST(test_reading_ppm_width) {
  Image *img = new Image;

  // open ppm file
  ifstream inputFile;
  inputFile.open("dog.ppm");

  // test that file was opened
  assert(inputFile.is_open());

  // initialize image
  Image_init(img, inputFile);

  // test that widths are equal
  ASSERT_EQUAL(Image_width(img), 5);

  delete img; // delete the Image
}

//Tests image height function for a ppm file
TEST(test_reading_ppm_height) {
  Image *img = new Image;

  // open ppm file
  ifstream inputFile;
  inputFile.open("dog.ppm");

  // test that file was opened
  assert(inputFile.is_open());

  // initialize image
  Image_init(img, inputFile);

  // test that widths are equal
  ASSERT_EQUAL(Image_height(img), 5);

  delete img; // delete the Image
}

//Tests initializing an image when the image is min size
TEST(test_initializing_img_min_parameters){
  Image *img = new Image;
  int min_width = 1;
  int min_height = 1;

  Image_init(img, min_width, min_height);

  ASSERT_EQUAL(Image_width(img), 1);
  ASSERT_EQUAL(Image_height(img), 1);

  delete img; // delete the Image
}

//Tests initializing an image when the image is max size
TEST(test_initializing_img_max_parameters){
  Image *img = new Image;

  Image_init(img, MAX_MATRIX_WIDTH, MAX_MATRIX_HEIGHT);

  ASSERT_EQUAL(Image_width(img), 500);
  ASSERT_EQUAL(Image_height(img), 500);

  delete img; // delete the Image
}

//Tests reading in a ppm file when the image is min size
TEST(test_initializing_ppm_min_parameters){
  Image *img = new Image;

  string input = "P3\n1 1\n255\n255 0 0";
  std::istringstream ss_input(input);

  Image_init(img, ss_input);

  ASSERT_EQUAL(Image_width(img), 1);
  ASSERT_EQUAL(Image_height(img), 1);

  delete img; // delete the Image
}

//Tests the fill image function when the image is min size
TEST(test_fill_min_size_img) {
  Image *img = new Image;
  int min_width = 1;
  int min_height = 1;
  Pixel red = {255, 0, 0};

  Image_init(img, min_width, min_height);
  Image_fill(img, red);

  ASSERT_EQUAL(Image_width(img), 1);
  ASSERT_EQUAL(Image_height(img), 1);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), red));

  delete img; // delete the Image
}

//Testing Image width and height functions
TEST(test_image_width_and_height_basic) {
  Image *img = new Image;

  Image_init(img, 27, 163);

  int img_width = Image_width(img);
  int img_height = Image_height(img);

  ASSERT_EQUAL(img_width, 27);
  ASSERT_EQUAL(img_height, 163);


  delete img; // delete the Image
}

//Testing Image width and height functions at min values
TEST(test_image_width_and_height_min) {
  Image *img = new Image;

  Image_init(img, 101, 1);

  int img_width = Image_width(img);
  int img_height = Image_height(img);

  ASSERT_EQUAL(img_width, 101);
  ASSERT_EQUAL(img_height, 1);


  delete img; // delete the Image
}

//Testing Image width and height functions at max values
TEST(test_image_width_and_height_max) {
  Image *img = new Image;

  Image_init(img, MAX_MATRIX_HEIGHT, MAX_MATRIX_WIDTH);

  int img_width = Image_width(img);
  int img_height = Image_height(img);

  ASSERT_EQUAL(img_width, 500);
  ASSERT_EQUAL(img_height, 500);


  delete img; // delete the Image
}

//Testing const Image width and height functions
TEST(test_const_image_width_and_height_basic) {
  Image *img = new Image;
  const Image *const_img = img;

  Image_init(img, 5, 5);

  int const_img_width = Image_width(const_img);
  int const_img_height = Image_height(const_img);

  ASSERT_EQUAL(const_img_width, 5);
  ASSERT_EQUAL(const_img_height, 5);


  delete img; // delete the Image
}

//Testing const Image width and height functions at min values
TEST(test_const_image_width_and_height_min) {
  Image *img = new Image;
  const Image *const_img = img;

  Image_init(img, 1, 1);

  int const_img_width = Image_width(const_img);
  int const_img_height = Image_height(const_img);

  ASSERT_EQUAL(const_img_width, 1);
  ASSERT_EQUAL(const_img_height, 1);


  delete img; // delete the Image
}

//Testing const Image width and height functions at max values
TEST(test_const_image_width_and_height_max) {
  Image *img = new Image;
  const Image *const_img = img;

  Image_init(img, MAX_MATRIX_HEIGHT, MAX_MATRIX_WIDTH);

  int const_img_width = Image_width(const_img);
  int const_img_height = Image_height(const_img);

  ASSERT_EQUAL(const_img_width, 500);
  ASSERT_EQUAL(const_img_height, 500);


  delete img; // delete the Image
}

// Tests the get pixel function using a const image
TEST(test_get_pixel_const_img) {
  Image *img = new Image;
  const Image *const_img = img;

  Image_init(img, 120,499);

  const Pixel yellow = {200, 200, 0};
  const Pixel brown = {139,42, 35};
  const Pixel orange = {250,100, 1};

  for (int r = 0; r < Image_height(const_img); r++) {
    for (int c = 0; c < Image_width(const_img); c++) {
      if (r == 7) {
        Image_set_pixel(img, r, c, orange);
      }
      if (c == 100) {
        Image_set_pixel(img, r, c, yellow);
      }
      if (c%5 == 0) {
        Image_set_pixel(img, r, c, brown);
      }
    }
  }

  ASSERT_TRUE(Image_equal(const_img, img))
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(const_img, 498, 115), brown));

  delete img;
}


// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
