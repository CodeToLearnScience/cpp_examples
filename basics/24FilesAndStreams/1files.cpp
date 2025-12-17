/*
---------------
Files in C++ 
---------------
- C++ has very minimalistic interpretation. A file is just a sequence of bytes 
  which has some file name to identify it. So we don't need to know whether the 
  data is stored on a disk or an SD card or some physical device. We don't know 
  how exactly it is stored, and we dont care what it is meant to represent.
------------------
Files and Streams
------------------
- The C++ library provides "fstream" objects fro interacting with files. 
  * Similar to iostream objects for console input/output 
- These fstream objects always access files sequentially, so that means one byte 
  after another. You can't jump forwards or go backwards, and they are always 
  in the same order. 
  * A sequence of bytes 
  * In order 
  * Of unknown length 
  * With no structure 
- fstream do not understand file formats 
---------------------- 
C++ fstream operations 
----------------------
- 4 main things we can do with fstream objects 
- Open 
  * Connects the fstream object to the file 
  * After Connecting file is available for use by the program 
- Read
  * Data is copied from the file into the program's memory 
- Write 
  * Data is copied from the program's memory to the file 
- Close 
  * Disconnects the fstream object from the file 
  * The file is no longer available for use by the program 

- For each of these operations, the fstream object will call a function in the 
  operating system API 
- The program will stop and wait while the operation is performed by the OS 
- When the OS has completed the task, the API call will return and the program 
  will then resume executing our instructions 

--------------------------
Opening and Closing a file 
-------------------------- 
- A file must be opened before we can use it 
- The file should be closed after use 
  * Ensures that any outstanding data is saved to the file 
  * Avoids the possibility of a "too many open files" error 
    - OS have a limit on the amount of files the program can have open at any 
      one time. If you try to open too many files, OS will stop you like how 
      you can't ask for allocating too much memory 
- When you compile a C++ program into binary, the compiler will add some extra 
  runtime code to the program. So this will set the program and then call main() 
  And when main() returns, this code will do any clearing up that is needed.And 
  one of the things it does it that it will go through all the files that the 
  program has opened and make sure they are closed. 
  * Its always good idea to close the file as soon as possible 
-------------------------
Reading and Writing Files 
-------------------------
- When you send or receive data with a file, it is not going to be actually 
  sent one byte at a time. The reason is that interacting with physical devices 
  is very time-consuming. So what happens is that the data is temporarily stored 
  in memory buffer. And when it reaches the optimal size, the data gets sent off 
  to the device. This makes large data transfers more efficient, but less timely
  However, there is a disadvantage to this, if your program waits too long 
  between transferring data, then the discrepancy, btw what the file says, and 
  what your program thinks the file says, will get bigger and bigger and that 
  can cause problems. 
*/
