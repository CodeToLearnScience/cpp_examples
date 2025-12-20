/*
 File Modes
 - C++ gives us a number of options for opening a file. These are called "modes"
    * these are basically same as in unix. So if you know file modes in Unix
      then you know all this!
    * We can pass the file mode as a optional second argument when opening the
      file
 - By default, files are opened in "text mode"
    * It means the characters are stored in the file as ASCII. So if we write
      42 to a file, it will be stored as the ASCII characters '4' and '2'
    * These are the binary numbers 110100 and 110010
 - By default, output files are opened in "truncate mode"
    * Any data that was previously in the file will be overwritten
    * New data will be written from the start of the file
---------------------
Appending to Files
---------------------
- To open an ofstream in append mode, we pass fstream::app as the second
  argument to open
    ofile.open("important.txt", fstream::app); //open file for writing in appen
    * app is member of ios so you can use ios::app or fstream::app
mode.
- So when we write to the file, its current data will be preserved
- Our data will be added after the data that was already there
    ofile << "some more data";
----------
Binary Mode
-----------
- In binary mode, the data stored in the file will be identical to the data
  in memory
  * e.g. the number 42 is stored as a single binary number with the value
    110010
  * In text mode, it would be stored as two binary numbers
    - 110100 //ASCII code for the character '4'
    - 110010 // ASCII code for character '2'
- Binary mode is complicated, low level and error prone. It can also cause
  portability problems
  * It should be avoided wherever possible
  * However, it is needed for working with file formats (e.g. media files)

-----------
Other Modes
-----------
- trunc: open the file in truncate mode
- in: open the file for input
- out:
  1. open the file in output mode
  2. Also, in truncate mode, even if trunc is not specified
- ate: similar to append, but output can be written anywhere in the file which
  you can't do with append. Its after end of file

----------------
Combining Modes
----------------
- We can combine different modes by putting a vertical bar | (bitmask) between
  them
    fstream file;
    file.open("important.txt", fstream::out | fstream::app);
    * open for writing in append mode
- If we combine in and out, we can read from and write to the same file
    file.open("both.txt", fstream::in | fstream::out);
    * open file for reading and writing
    * In this case, the file will not be truncated
    * Usually when you do this, you want to read from the file before you write
      to the data, so it doesn't make sense to overwrite the data before you
      can look at it
    * unless we specify
        file.open("both.txt", fstream::in | fstream::out | fstream::trunc);
----------------------
File Mode Restrictions
----------------------
- There are some restrictions on how you can use mode.
- out: we can use with fstream and ofstream only
- in: fstream and ifstream only
- trunc: only in output mode
- app: 1. cannot combine with trunch 2. The file will always be opened in output
mode
 */
#include <fstream>
#include <iostream>

using namespace std;

int main() {
  ofstream ofile;
  ofile.open("important.txt", fstream::app);
  if (!ofile) {
    cout << "Could not open file\n";
    return -1;
  }

  ofile << "some more data";
}
