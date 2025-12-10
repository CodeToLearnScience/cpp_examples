/// pointer is a integer that stores memory address

//memory allocated on heap will remain allocated until user deallocates or 
//the program gets terminated

//delete will call the destructor for the objects in the memory, then release 
//the allocated memory 
#include <iostream>
#include <cstring>
#define LOG(x) std::cout << x << std::endl;

int main()
{
    /// void means typeless
    void *ptr = 0;
    // void *ptr = NULL;
    // void *ptr = nullptr;

    int var = 8;

    ptr = &var;

    // int *ptr=&var;

    /// dereferencing pointer. Gives error. don't know types
    int *ptr1 = 0;
    int var1 = 19;

    /// dereferencing to assign value to pointer
    ptr1 = &var1;
    *ptr1 = 10;

    LOG(ptr1);
    std::cout
        << ptr << std::endl;

    /// all above we have allocated on stack
    /// to allocate on heap. It creates a pointer to the beginning of the data
    int *p1=new int; //points to memory allocated from heap. initialized to whatever value that's already there in that address  
    int *p2=new int{36}; //initialized memory (C++11) 
    int *p3=new int(36); //initialized memory (old C++) 
    
    //We can also allocate a block of memory and access it as if it were an array 
    int *pa = new int[10];
    for(int i=0; i<10; i++){
      pa[i]=i;
      std::cout << pa[i] <<"\n"; 
    }
    char *name = new char[8];
    memset(name, 0, 8);


    /// you should delete heap memory
    //This p1, p2 and p3 will be on stack although it may represent a memory 
    //that's allocated on the heap, but the actual variable itself will be on stack 
    //So once the memory has been released, the variable will continue to exist
    //until the end of the scope. So it is actually possible to access that
    //variable in the program, and if you do that, that's an undefined behavior
    //So the program will crash or behave very strangely. The reason is that p1 
    //p2, p3 is not pointing to memory and we say that these are dangling pointers 
    delete p1, p2, p3;
    //to delete block of memory, we neeed to use [] infront of delete 
    delete[] pa; //if we use delete pa, we will delete only first element so first element memory will be freed
    delete[] name;

    /// pointer to pointer
    char **buffer = &name;

    // std::cin.get();
}
