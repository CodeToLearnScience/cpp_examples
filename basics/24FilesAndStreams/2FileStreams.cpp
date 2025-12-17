/* 
------------
File Streams
------------

------------
Stream Types 
------------
- iostream 
  * ostream (cout) 
  * istream (cin) 
  * cout and cin are objects of the ostream and istream classes 
-G fstream 
  * ofstream (file stream for writing) 
    - class for writing to files 
  * ifstream (file stream for reading) 
    - class for reading from files 
- Unlike consoles, where there is only one console per computer, there can be 
  many files so when we use file stream, we need to say which file we are going 
  to use it with 

------------------------------
How to Open a File for Reading 
------------------------------
- The easiest way to open a file is to pass its name to the ifstream constructor 
- This will create a stream object which will open the file for input 
  ifstream ifile{"text.txt"};
- This kind of represents a "communication channel" which is used to receive 
  data from the file 
- Constructor performs an open operation, which coulf fail; if the file doesnt 
  exist or we are not allowed to read from it. So we need to check that we have 
  a valid file stream object before we can use it. 
  if(ifile) //true if the stream is ready for use, false if not 
    cout << "Successfully opened file for reading\n"; 
-------------------
fstream constructor 
-------------------
- In earlier version of C++, fstream's constructor could only take C-style 
  string for the file name 
- In C++11, it can now take a std::string 
  string str{"text.txt"}; 
  fstream ifile(str); //Not allowed in C++03 but OK in C++11  

-------------------- 
Reading from a File 
-------------------- 
- We can use ifile the way as cin 
  while(ifile >> text) //read a word from the file 
    cout << text << ", ";
- A word/value is defined as something that is separated by white space. 
- So this will read one word at a time and remove all whitespace (space, tab or 
  new line) from the input
  - This may not be what is required. Often you want to read spaces as well 
  - Also if the file has an internal structure, the code can be difficult to get 
    right 
  - Also the question of error handling. If the structure of the file does not 
    exactly match what you expect, perhaps the structure has changed or maybe 
    you made a mistake

------------------------------
How to Open a File for Writing  
------------------------------
- Create a stream object which will open the file 
  ofstream ofile{"text_out.txt"};  
- This represents a "communication channel" which is used to send data to the 
  file 
- We should check the stream state before using it 
  if(ofile)  
    cout << "Successfully opened file for writing\n"; 
- We can use ofile the same way as cout 
  vector<string> words ={"The", "sun", "rises", "in", "the", east"}; 
  for(auto word : words) 
    ofile << word << ", "; //send some data to the file 

------------------
fstream destructor 
------------------
- When fstream's destructor is called, the file is automatically closed. This 
  will happen just before the actual stream object is destroyed. If this is an 
  output stream, then this will make sure that any data that is hanging around 
  memory buffers will get written to the file. 
- If an fstream object goes out of scope after we have finished with it, we do 
  not need to explicitly call close() 
- However, it is good practice do to so 
*/ 


#include <iostream> 
#include <fstream> 
#include <string>
#include <vector> 

using namespace std; 

int main() {
string file{"text.txt"}; 
ifstream ifile(file);  // Declaration + initialization
if (ifile){
  string text{""}; 
  while ( ifile >> text){ //read a word from the file 
    cout << text << ", "; 
  } 
  cout << endl; 
  ifile.close(); //release the binding btw file and file 
}

cout <<"------------------------------------------------------------------\n";
ifile.open(file); //to open again we need to use ifile.open 
if (ifile){
  string text{""}; 
  while ( getline(ifile, text) >> text){ //read a word from the file 
    cout << text << endl; 
  } 
  ifile.close(); //release the binding btw file and file 
}

//write to file 
ofstream ofile{"text_out.txt"}; 
vector<string> words ={"The", "sun", "rises", "in", "the", "east"}; 

  if(ofile){
    for(auto word : words){
      ofile << word << ", ";
    }
    ofile.close(); 
  }
}

