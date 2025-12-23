#include "bitmap.h"
#include <fstream>

using namespace std;

bool bitmap::write() {
  bitmap_file_header file_header;
  bitmap_info_header info_header;

  // calculate the size of the bitmap
  file_header.file_size = sizeof(bitmap_file_header) +
                          sizeof(bitmap_info_header) +
                          width * height * sizeof(pixel);

  file_header.data_offset =
      sizeof(bitmap_file_header) + sizeof(bitmap_info_header);

  // set the image width and height
  info_header.width = width;
  info_header.height = height;

  // open the file where we will write the bitmap
  ofstream ofile(filename, fstream::out | fstream::binary);
  if (!ofile.is_open()) {
    return false;
  }

  // write the file header
  ofile.write(reinterpret_cast<char *>(&file_header),
              sizeof(bitmap_file_header));
  // write the info header
  ofile.write(reinterpret_cast<char *>(&info_header),
              sizeof(bitmap_info_header));

  // the first argument to write is an array containing the image data
  // the second argument is the size of the data
  ofile.write(reinterpret_cast<char *>(pixels.data()),
              pixels.size() * sizeof(pixel));

  if (!ofile) {
    return false;
  }
  ofile.close();
  return true;
}

void bitmap::set_pixel(int x, int y, pixel p) {
  int idx = y * width + x; // calculate pixel offset
  pixels[idx] = p;         // the vector index is the pixel offset
}

// set all the pixels in an entire row
void bitmap::set_row(int row, pixel p) {
  for (int i = 0; i < width; ++i) {
    set_pixel(i, row, p);
  }
}

void bitmap::set_all(pixel p) {
  for (int i = 0; i < height; ++i) {
    set_row(i, p);
  }
}
