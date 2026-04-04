/*----------------
Exception Safety
------------------
- Exception Safety means that code behaves correctly when Exceptions are thrown
- All our programs should be exception safe!
- There are three main ways to write exception-safe code
- Basic exception guarantee
  * If an exception it thrown during an operation, no resources are leaked
  * Files opened during the operation will be closed
- Strong exception guarantee
  * If an exception is thrown, the program reverts to its previous state
  * As if the operation had not happened
- No-throw guarantee
  * The code does not thrown any exceptions

--------------------------------
Basic Exception Guarantee
--------------------------------
- The basic exception guarantee provides the minimum level of exception safety
  * An operation will either succeed or throw an exception
  * If the operation thrown an exception, no resources will be leaked
- All the operations and functions in the C++ standard library provide this
basic guarantee

-------------------------------------
Strong Exception Guarantee
-------------------------------------
- An operation will either succeed have no effect
- If it throws an exception, the program will be left in the same state as it
was before the operation
  * The operation has transactional semantics
  * Similar to commit and rollback in databases
- All iterators or references which were obtained before will remain valid, even
if the operation fails
- All operations on STL containers provide the strong exception guarantee
  * Except for a couple of special cases of insert operations

----------------------------------------
Providing the Basic Exception Guarantee
----------------------------------------
- For code to provide the basic guarantee, any resources acquired during the
operation must be released when an exception is thrown
- We can manually release the resource
  * Call delete on memory allocated by new
- Or we use objects which automatically release the resources when destroyed
  * std::string and std::vector's destructors release the memory
  * fstream's destructor closes the file
*/
