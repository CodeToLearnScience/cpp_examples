//some member functions are "special" in a sense that they are there to manage 
//objects. Their names are realated to class's name 

//compiler will automatically insert calls to these member functions when 
//needed and sometimes they generate these for us 

//In traditional C++, these special member functions are: 1) Constructor, 
//(2) Copy Constructor, (3) Assignment operator and (4) Destructor 


//-----------------------------------------------------------------------------
/*
Constructor: 
- Has same name as class
- Initializes the newly created object with its arguments 
- Performs any initial configuration required 
*/

Test(int i, string& str) : i(i) str(str){
  //Operations and things you want to do after object is created 
  //Allocate memory, connect to database, etc
}

//-----------------------------------------------------------------------------
/*
Copy Constructor 
- similar to Constructor but uses other object for initialization 
- Always takes one argument 
Note: other is alwasy passed by reference and not by value (and it's not to do 
with efficiency) because if you have a copy constructor, which takes arguments 
by value, that will need to make a copy of the object and to do that, it will 
call the copy constructor. And then that call to the copy constructor will 
itself need to make a copy and so on..and you will get an infinite recursion of 
calls to the copy constructor. So you have to do it by reference. And normally 
you would do that by reference to const, because you really don't want to 
change something to the object you are copying. That would be bad. 
*/

//Reference to another object of the same class 
Test(const Test& other) : i(other.i), str(other.str){ //initialize object 
  //configure object if needed 
}

//-----------------------------------------------------------------------------
/*
Assignment operator 
- also takes an existing object, but it is called on an object that already 
exists and it will assign the object so the values in the target object are the 
same as the values of the members in the source object 
- always takes one argument which is usually reference to const 
- and the function returns a reference to the assigned object. It should be non 
const reference, for consistency with built-in-types 
- The reason why it returns the reference is that you can chain together 
assignment statements in C and C++ (you can say a=b=c and its legal). And 
returning the assigned-to object is required for it to work
-Some say assignment operator should return a const reference, but that's not 
the best thing to do as built-in-types always return non-const reference, and 
you should do that here as well. Generally, whenever you write your own 
operators, they should work the same way as built-in-types, othewise it gets 
confusing 
*/

Test& operator = (const Test& other){
  i = other.i; 
  str = other.str;
  return this* //return this object by reference (*this will dereference and so 
  //it will give actual object and then the compiler will return a reference to 
  //that which we from function signature Test& other=. Doing this way is safe 
  //as well because "this" will always be valid object for as long as the 
  //object exists 
}


//-----------------------------------------------------------------------------
/*
Destructor 
- Called just before the object is destroyed, before the members of the object 
are released in memory 
- We can use this to perform any tidying up which you want to do before the 
object disappears like releasing memory that you allocated, or if you have a 
database connection open, you can close it and so on... 
*/
//Prepare object to be released 
~Test(){
  //Release allocated memory, close the connection to the database, etc. 
}
