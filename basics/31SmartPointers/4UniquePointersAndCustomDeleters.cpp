/*
 --------------------------------------
 Unique Pointers and Custom Deleters
 --------------------------------------
 - There are two ways to create a unique_ptr object
   * Call the move constructor with the return value from make_unique(), which
     calls new() internally
   * Call the constructor with a traditional pointer as argument. The object
     will adopt this pointer
- The constructor could be given any pointer, not just one which represents
allocated memory. This should be something that has been allocated with new. And
then the unique_ptr object will, if you like, adopt this pointer. It will be
responsible for managing its lifetime
- We could use unique_ptr as a generic class for managing resources. We just
pass a pointer to the resource in the unique_ptr constructor
- However, unique_ptr's destructor calls delete
  * This will be disastrous if the pointer was not returned by new

-----------------------
Custo deleters
-----------------------
- We can provide a "deleter"
- This is a callable object
- It will be invoked by the destructor instead of delete
- The managed pointer is passed to the deleter
- The deleter then releases the resource as appropriate
  * In this case, we want to call disconnect()
- We need to provide a customr deleter
- This will be passed a pointer to the connection

  //custom deleter to close network connection
  auto end_connection = [](connection *conn) {disconnect(*conn);};

- This will be called when the unique_ptr is destroyed
- The network connection will always be closed, even if an exception is thrown

-----------------------
unique_ptr with deleter
-----------------------
- The deleter is part of the unique_ptr's type
- We need to give the deleter's type as an optional template parameter
- However, end_connection is a lambda expression
- Its type is known by the compiler, but not by us

---------------------
Deleter Type
---------------------
- We can use decltype to get the type of the lambda
- decltype is similar to auto, but it takes an expression

  //the compiler will replace this with the type of end_connection
  decltype(end_connection)

- We add this to the template parameters
  unique_ptr<connection, decltype(end_connection)>

  - and pass the deleter to the constructor
    unique_ptr<connection, decltype(end_connection)> p(&conn, end_connection);
    //so we pass the pointer to the connection as the first argument and the
    //lambda expression as the second
 */

#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

namespace custom_delete {
// code from C networking API
struct destination { /*...*/
};
struct connection { /*...*/
};

// Function to open a connection
connection connect(destination dest) {
  std::cout << "Connecting\n";
  connection conn;
  return conn;
}

// function to close a connection
void disconnect(connection conn) { std::cout << "Disconnecting\n"; }

void get_data(const destination &dest) {
  connection conn = connect(dest);
  std::unique_ptr<connection> ptr(&conn); // unique_ptr takes owenership
  std::cout << "Getting data...\n";
  // problem comes when we return from this function. The destructor of
  // unique_ptr will be called, and that will call delete and we have a pointer
  // which is on the stack so that is probably going to crash
  //  delete conn???
}

auto end_connection = [](connection *conn) { disconnect(*conn); };

void get_data_with_unique_ptr(const destination &dest) {
  connection conn = connect(dest);
  std::unique_ptr<connection, decltype(end_connection)> p(&conn,
                                                          end_connection);
  // so unique_ptr to a connection object, whose deleter is the same type as
  // this and then we initialize the member and the deleter
  std::cout << "Getting data...\n";
}

void get_data_with_unique_ptr_and_throw(const destination &dest) {
  connection conn = connect(dest);
  std::unique_ptr<connection, decltype(end_connection)> p(&conn,
                                                          end_connection);
  // so unique_ptr to a connection object, whose deleter is the same type as
  // this and then we initialize the member and the deleter
  throw std::out_of_range("oops");
  std::cout << "Getting data...\n";
}
void example() {
  destination dest;
  // get_data(dest);
  get_data_with_unique_ptr(dest);

  try {
    get_data_with_unique_ptr_and_throw(dest);
  } catch (...) { // connetion is closed and then exception is caught
    std::cout << "caught!\n";
  }
}

} // namespace custom_delete

int main() { custom_delete::example(); }
