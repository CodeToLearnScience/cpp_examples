/*
---------------------------
Unbuffered Input and Output 
---------------------------
- There are some applications where stream buffering is not suitable 
  * e.g. a network application 
  * There is a network protocol, which is basically a set of rules for 
    communicating between computers. This will say that the "data" must be 
    transmitted in "packets" of a specified size. A packet is a block of memory 
    which has a fixed size or a given size. And almost certainly that is not 
    going to be the size that the stream chosen for the buffer 
  * Data may need to be transmitted at specific times 
- Therefore, we don't want to have stream buffers getting in the way and 
  delaying data and sending the wrong size of data.

- C++ supports lower level operations on streams 
  * These bypass the stream's buffer 
  * No formatting of data 
  * for example, if you have an output stream, it may add spaces or change 
    numbers to make them look nice. If you have an input stream and you're 
    using the right shift (>>) operator, it will remove all the white space. So 
    none of that will happen with these low-level operators 
- These low-level operations are mainly used when the programmer needs more 
  control over how the data is transmitted 
  * Networking applications 
  * communicating directly with hardware. If you have a network card or a sound 
    card or a hard drive, it probably requires that you communicate it with 
    memory with a fixed block. And you need to have control over the timing of 
    when data is send and received. 

--------------------------------------
Input and Output of a Single Character 
--------------------------------------
- The simplest memory block is a single Character, and there are member functions 
  for that. 
- Streams have a member function for reading or writing data, one Character at 
  a time 
  * get() fetches the next Character from an input stream 
  * put() sends its argument to an output stream 
- These both take a char argument 
  char c; 
  while (cin.get(c)) //Read a character until we get end of input 
    cout.put(c); //display character 
- get() will take a character by address, so it can be modified, and put() will 
  take it by value.
- get() will return true unless it reads the end of input character 

----------------------------------------
Input and Output of Blocks of Characters 
----------------------------------------
- For reading and writing more than one character at a time, there are the 
  read() and write() member functions 
- As we are not using a buffer managed by the stream, we have to provide our 
  own buffer. This will be an array of characters 
  * For write(), our buffer will contain all the data we want to send to the  
    output 
  * For read(), the buffer must be large enough to store all the data we expect 
    to receive 
   ------------------ 
   read() and write() 
   ------------------ 
   - Both these member functions take two arguments 
    * The address of the buffer 
    * The numbers of characters in the buffer 

      const int filesize{10}; //The size of memory buffer  
      char filebuf[filesize]; //The memory buffer 

      ifile.read(filebuf, filesize); //Fetch data from the file into the memory buffer 
      cout.write(filebuf, filesize); //Send the data from the memory buffer to output  
---------
gcount() 
---------
- Usually when we receive data, we will have some idea of how much data we are 
  going to get. Maybe network protocol will have some information which says 
  how much data it is going to send. Sometimes it doesn't. 
- So we need to know how much data an input stream has sent us  
  * We may need to allocate memory to process the data 
  * To detect partial or incomplete transfers
- So we need to know the number of characters that we have read. 
- The gcount() member function will return the number of characters that were 
  actually received. 

    std::streamsize nread = ifile.gcount; //How many bytes did we receive in 
      the last read operation 
- The type std::streamsize is a signed integral type used to represent the 
  number of characters transferred in an I/O operation or the size of an I/O 
  buffer. It is used as a signed counterpart of std::size_t, similar to the 
  POSIX type ssize_t.
  */ 



#include <iostream>
#include <string> 
#include <fstream> 

using namespace std; 

int main(){

  cout << "Enter some text: "<< endl; 
  char c; 
  //if we type "this is test", it doesn't actually read the data until we press 
  //the return key. So this is still line-oriented input. Obviously if we were 
  //reading from a file or network socket, then it wouldn't wait until the end 
  //ctrl-Z is the end of input character 
  while(cin.get(c)) 
    cout.put(c); 


  const int filesize{10}; //The size of memory buffer  
  char filebuf[filesize]; //The memory buffer 
  string filename{"input.txt"};

  ifstream ifile(filename); 
  if(!ifile){
    cout << "Couldn't not open " << filename << endl; 
    return -1; 
  }

  ifile.read(filebuf, filesize); //Fetch data from the file into the memory buffer 
  std::streamsize nread = ifile.gcount(); //how many bytes did we receive 
  //we could have used auto 
  //auto nread = ifile.gcount(); //how many bytes did we receive 
  ifile.close();  

  cout << "Read " << nread << " bytes from " << filename << endl;
  cout << "File data: "; 
  cout.write(filebuf, filesize); 
  cout << endl; 
}
