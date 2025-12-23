// we can't use cout and cin as they do conversion
// Always use read and write

#include <cstdint> //as we are using c-std int int32_t
#include <fstream>
#include <iostream>

using namespace std;

#pragma pack(push, 1)
struct point {
  char c;
  int32_t x;
  int32_t y;
};
#pragma pack(pop)

int main() {

  point p{'a', 1, 2};
  ofstream ofile("file.bin", fstream::binary);
  if (ofile.is_open()) {
    ofile.write(reinterpret_cast<char *>(&p), sizeof(point));
    ofile.close();
  }
  // to view binary file as hexadecimal => hexdump -C file.bin
  //  output written to file without #pragma pack(push,1) and #pragma
  //  pack(pop,1)
  //
  //  00000000  61 00 00 00 01 00 00 00  02 00 00 00 |a...........|
  //  0000000c  => C is 12 in hexadecimal, that's the total number of bytes
  //  written 61 for a and then 3bytes of padding as data is written with word
  //  size (4bytes) Then 01 00 00 00 which is equal to 1 and then next 2 both
  //  with 4 bytes

  // with pragrams. No padding for char so total of 9bytes 1byte char and 2 ints
  // of 4 bytes
  //
  // 00000000  61 01 00 00 00 02 00 00  00 |a........| 00000009 =>
  // total of 9 bytes written

  ifstream ifile("file.bin", fstream::binary);
  point p2;

  if (ifile.is_open()) {
    ifile.read(reinterpret_cast<char *>(&p2), sizeof(point));
    ifile.close();
    cout << "Read " << ifile.gcount() << " bytes\n";
    cout << "Read x = " << p2.x << ", y = " << p2.y << "\n";
  }
}
