/// pointer is a integer that stores memory address

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
    char *name = new char[8];
    memset(name, 0, 8);

    /// you should delete heap memory
    delete[] name;

    /// pointer to pointer
    char **buffer = &name;

    // std::cin.get();
}