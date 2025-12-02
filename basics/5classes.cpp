//The public members provide the interface of the class "what it does"
//The private members provide the implementation of the class "how it does"

//Struct is same as class, except all members are public by default. Normally 
//you would use struct when you want to keep related data items together. 

//Member functions are implemented as global functions. 

//When a member function is called on an object, the object is passed by address
//in a hidden argument 
Test test; 
test.func(1, 2.0, "three"); //Is called as Test::func(&test, 1, 2.0, "three") 

//The pointer to the object is available as "this" in the function body 
//Dereferencing "this" gives access to members of the object (both data & member functions) 
//In the body of Test::func()
this->i=1; //or just i=1
//"this" is equat to &test 

#include <iostream>
#include <string>

/// default visibility is private in class but public in struct
class entity
{
    /// private. Only visible to this class entity (both members and methods)
private:
    int X, Y;

    /// This class and all subclasses (class heirarchy) can access these members and functions
protected:
    int m, n;
    void print(){};

    /// visible to all
public:
    int l, k;
};

class player : public entity
{
public:
    // print();
};

int main()
{

    return 0;
}
