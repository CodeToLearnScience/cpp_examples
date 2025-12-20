/* Stream member functions and state
------
open()
------
- We have been using it
- We bind a file when we pass its name to the stream constructor
    ofstream ofile{"hello.txt"}; //create an output stream
    * so when stream is constructed, it will also open the file and bind it to
      the file hello.txt, using default mode.
- We can also bind it later by calling open()
    ofstre ofile; //create an output stream which is not bound to any file
     ...             //do something else
    ofile.open("hello.txt");//bind the stream to the file hello.txt using
default mode
- In both cases, when ofstream binds the file
  * The file mode will be applied
  * If the output file doesn't already exist, it will be created
  * By default opens in tructation mode
--------
is_open()
---------
- we can use the is_open() member function to check if the file is open
    if(ofile.is_open()){
        ...//ok to use
    }
----------------------------
Stream State Member Functions
----------------------------
- C++ streams have a state, and the state will depend on the result of the last
  operation. Usually we will be interested in this for input stream. So the
  state of input stream will depend on the result of the last time that it read
  data from a keyboard or a file. If the operation succeeded, then the stream
  is in good state and good() will return true
- C++ streams have member functions to check the state of the stream
- good(): returns true if the input was read successfully
- fail(): returns true if there was a recoverable error, e.g. data in wrong
  format.
- bad(): And if something really serious happens like a disk failure, then
  will be true and the stream will be in a bad state.
- clear(): Restores the stream's state to valid
  * It does not actually change the bufefr though
- eof(): returns true after the end of the file has been reached
    while(!ifile.eof()) //Is this correct?
        ifile >> x;
 */

#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

int main() {
  int x{0};
  cout << "Please enter a number: ";
  cin >> x;
  if (cin.good()) { // successfully read int
    cout << "You entered the number " << x << "\n";
  } else if (cin.fail()) { // Not an int. Probably user entered non-int
    cout << "Please try again and enter a number\n";
  } else if (cin.bad()) {
    cout << "something has gone seriously wrong\n";
  }

  // eof example
  ifstream ifile;
  ifile.open("input1.txt");
  int y{0};
  /* with the following code 9 will be printed twice as there is extra blank
   * line after 9. Since !ifile.open() is true at last line as it its not eof
   * but it will print 9 because that's what there in stream from previous
   * read*/
  /* while (!ifile.eof()) {
     ifile >> y;
     cout << y;
   }*/

  /*So the right way to do this is
   * This right shift willa actually return the state of the file. So while the
   * state of the file [stream] is good, then it is going to print out the
   * value that it has just read. If the file stream is bad or has reached the
   * end of file, this will be false. So this doesn't print anything at all. So
   * we don't get the extra iteration which prints out the data that we don't
   * want unlike previous example. Since y is declared as int, if there is some
   * other type in between ints, it will stop as soon as it reads non-int as
   * the stream state returns false as the state is bad*/
  while (ifile >> y) {
    cout << y << ",";
  }

  /*So we need to think about how we are going to deal with invalid input. The
   * obvious approach is to have Boolean which will tell us whether the input is
   * true or not. Then we can have loop which checks that, and this loop will
   * keep repeating until the user enters some valid input */
  int z{0};
  cout << "Please enter number: ";
  cin >> z;

  bool success{false};
  while (!success) {
    if (cin.good()) {
      cout << "You have entered the number " << z << "\n";
      success = true;
    } else if (cin.fail()) {
      cout << "Please try again and enter a number\n";
      cin.clear(); // otherwise it will go to infinite loop stream state will be
                   // false
      // cin.ignore(20, '\n');
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin >> z;
    }
  }
  /* in above code when cin >> z is executed, the stream will go to the first
    character in ints input buffer, and it will start trying to convert the
    characters in that buffer to an int. And it will only stop when it
    encounters some white space
   * If the first character is somethign that can't be converted into an int,
    it will stop immediately and it will leave that character in the buffer
   * Then next time through, it'll go to the first character in the input,
     which is still the same one that made it fail before, and that will make
     it [fail] again. So the problem is that it keeps reading the same user
     input over and over again. It doen't discard the user input and go onto
     the next one
    * The solution is to force cin to flush its buffer, to get rid of all the
      stale [characters] from the last user input and then it can start
      processing the new lot of user input.
      -------
      ignore
      --------
      - Unfortunately, input streams do not support flush
      - Howver there is a member function called ignore() which will remove
        characters from the buffer. We can tell how many characters to remove
        There is problem there. If user types in 5 characters and then presses
        the return key, then this "ignore" is going to ignore the next 20
        characters. So the five characters that the user types are going to be
        ignored, and then the 15 characters after that are going to be ignored
        Which is not what we want so we can provide second argument, which is a
        new line character. THis means if you get a new line character before
        20 characters, then stop there. So this will either remove the next 20
        characters or everything up to the next new line. Whichever comes first
        And characters removed from the buffer are thrown away and you can't
        access them again
      - But we may not know how many character user will enter. So 20 characters
        maynot be enough. Maybe 1000? or 10000? we don't know so its better to
        ignore/discard whatever there in the buffer and start with empty buffer.
        And C++ does actually provide an expression for finding that. It is
        rather an ugly one. So it is in numeric limits. This requires the limits
        header.
    */
}
