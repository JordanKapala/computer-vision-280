#include <iostream>
#include <fstream>
#include "Image.hpp"
#include "processing.hpp"
using namespace std;

int main(int argc, char **argv) 
{
  // check that valid number of arguments were given
  if (argc < 4 || argc > 5) 
  {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
          << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  // open ppm file and check that it was opened properly
  ifstream input_file;
  input_file.open(argv[1]);

  if (!input_file.is_open())
  {
    cout << "Error opening file: " << argv[1] << endl;
    return 1;
  }

  // initialize image object with ppm file
  Image *img = new Image;
  Image_init(img, input_file);

  // get new width and height 
  int new_width, new_height;

  if (argc == 4) 
  { 
    new_width = atoi(argv[3]); 
    new_height = Image_height(img);
  }
  else
  {
    new_width = atoi(argv[3]); 
    new_height = atoi(argv[4]);
  }

  // check that valid width and height were given
  if (   new_width <= 0 || new_width > Image_width(img) 
      || new_height <= 0 || new_height > Image_height(img) )
  {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
          << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  // apply the seam carving algorithm to the img
  seam_carve(img, new_width, new_height);

  // write the new image file
  ofstream output_file(argv[2]);
  Image_print(img, output_file);

  delete img;
}