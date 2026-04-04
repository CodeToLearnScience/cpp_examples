/*
-----------------------------------
Exceptions and Undefined Behavior
-----------------------------------
- Java and C# will throw an exception for many runtime errors which could cause
a crash or data corruption
 * Null pointer/null reference access
 * Divide by zero
 * etc
- In C++, these will not cause an exception to be thrown
- Instead, the program's behavior is Undefined
- In Jave and C# the program safety is regarded as very important. And in C++,
  efficiency is regarded as very important
- C++ has a design principle which says, "you should not have to pay for
  anything you do not eat."

-----------------------------
Catch-all Handlers
-----------------------------
- In Java and C#, all exception classes inherit from system Exception class
  * A handler can catch any type of exception by catching Exception

    catch (Exception e){
      //Handle the exception
    }

- In C++, any type can be used for an exception including built-in types
  * Although inheriting from std::exception is recommended
- To catch any type of exception, a special syntax is used
  catch(...){
   //Handle the exception
  }

--------------------------------
Checked and Unchecked Exception
--------------------------------
- Java has checked and unchecked ("runtime") exceptions
  * If a function can throw a checked exception, every caller of that function
    must handle that exception otherwise it won't compile
  * If a function can throw an unchecked exception, the caller is not required
    to handle the exception
- C++ and C# do not have checked exceptions
- All exceptions in C++ and C# work the same way, which is similar to
  unchecked exceptions in Java
  * The caller is not required to handle the exception

------------------------
Unhandled Exceptions
------------------------
- In Java, if an exception is not caught, the default behaviour is to print
a stack trace and terminate the thread
  * The programmer can write an UncaughtException handler to change its behavior
- In C# and C++, if an exception is not caught, the program is terminated by
default

--------------
Finally Block
--------------
- Jave and C# have a garbage collector, and this has implications for exception
If you have a class which has some OS resources such as an open file, for ex,
that object must release the resources. It must close the file before the
garbage collector disposes of the object. And it can happen that the garbage
collector destroys the object before it has released the resources. SO these
languages provides another block, called "finally" and in this "finally" block
you can put code which will release the resource. So that prevents the resoure
leak
- In Java and C#, a try/catch block can also have a "finally" block

   try{
     ...
   }
   catch(SomeException e){
     ...
   }
   finally{
     ...
   }
- The code in the "finally" block is always executed, even if no exception is
thrown
  * This is used to release resources to the OS
  * It avoids a resource leak in case the object is reclaimed by the garbage
    collector before the resource is released

-------------------------
Try with resources
-------------------------
- Newer versions of Java have try-with-resources

  try{FileReader fr = new FileReader(path)){
   ...
  }
  catch (SomeException e){
   ...
  }
- The close() method will be called for each resource declared in the try header
- C# has a "using" keyword, which is similar

-------------------
RAII
-------------------
- In C++, we use the RAII idiom
- Resources are wrapped inside a class
- The resource is released automatically when the destructor is called
  * When an exception is thrown
  * In the normal program flow, when the object is destroyed
- The code to release the resource is written once, in the class's destructor
*/
