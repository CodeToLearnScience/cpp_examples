/*
--------------------------------
C++ Streams and Output Buffering
--------------------------------
- C++ streams use "buffering" to minimize calls to the OS
- During a write operations, data is temporarily held in a memory buffer 
- The size of this buffer is chosen to match the maximum amount of data that 
  the OS will accept in a single call 
- When the buffer is full, that means we have the optimal amount of data. And 
  then the stream will remove the data from the buffer and send it off to the 
  OS. This is known as "flushing" the output buffer.  
-------------------------------
When are stream buffers flushed 
-------------------------------
- It depends on the type of stream 
- For ostream, like cout it depends on the terminal configuration. The usual 
  arrangement is to have what is called "line oriented" output. So every time 
  the terminal sees a new line, it iwll print all the data it has. If you only 
  give it part of the line, it will wait until it gets the new line character  
- Also, C++ requires that if the program is going to read from cin, it must 
  first flush cout. So that makes sure that the user can see all the output the 
  program has generated, before they are required to respond to it. 
- For output file streams, the buffer is only flushed when it is full. And for 
  input streams, there is surprisingly no way to actually flush them directly 
- If you want to remove data from a stream, you have to read it. And that's 
  good enough for most programs. We don't really care too much when the output
  appears on the screen or gets written to the disk, so long as it is there
  when we need it. 

----------
std::flush
----------
- But there are sometimes when we need to have control over it
- std::flush allows us to control when the stream's buffer is flushed. This is 
  not a function call. It is actually something called a manipulator. A stream
  manipulator
- All the data in the buffer is immediately sent to its destination. That is it 
  will cause the cout buffer to be flushed
  cout << i << flush; //i will appear immediately on the screen 
- So this means that the output on the screen, or the data in the file, always 
  matches exactly what the program thinks it has sent off. But this 
  singnificantly affects performance because we are doing lot more hardware 
  operations 
- Therefore, it should only be used if the data really needs to be up to date 
  * e.g. log file to find out why a program crashed 
  * if you let the stream decide when the buffer is flushed, it is possible that 
    the program could crash when there is still a lot of data in the buffer. So 
    the actual data in the file could be out of date. It could be several  
    operations before the one that causes the problem. 
*/

#include <iostream> 
#include <fstream> 


using namespace std;

int main (int argc, char *argv[]) {

  ofstream ofile{"log.txt"}; 

  if(!ofile){
    cout << "could not open file\n";
    return -1; 
  }

  for(int i=0; i<1'000'000; ++i){
    /*cout is presumably line buffered. So this should display the correct 
      value every time we send value i to cout.*/ 
    std::cout << i << "\n";
    /*However, the output file stream is not line buffered. So this is going to 
      bet he last value from when the buffer was flushed. And that may or may 
      not contain the right value for when the program stopped
      So the value on the file will be less than the value printed to screen
      */
    ofile << i << "\n";
    if(i==66666)
      terminate();
  }
  ofile.close();

  //demonstrate flush 
  ofstream ofile1("log1.txt"); 

  if(!ofile1){
    cout << "could not open file\n";
    return -1; 
  }
  
  //comment terminate() before running this 
  //Now we see that both cout and ofile1 have same data 
  for(int i=0; i<1'000'000; ++i){
    std::cout << i << "\n" << flush; 
    ofile1 << i << "\n" << flush; 
    //endl is equivalent to doing new line followed by flush
    //gives the same results as above
    //std::cout << i << endl; 
    //ofile1 << i << endl; 
    if(i==66666){
      terminate();
    }
  }
  ofile1.close();
  return 0;
}
