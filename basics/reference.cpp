
/// pointer is a integer that stores memory address

#include <iostream>
#include <cstring>
#define LOG(x) std::cout << x << std::endl;

/** pass by value. The passed variable value will be copied to x
 * x will be incremented inside and not a value passed
 */
void increment(int x)
{
    x++;
}

/** pass by reference
 * Here value passed is by reference so the value passed will be incremented
 */
void increment_ref(int &x)
{
    x++;
}

/** pass by pointer
 * Here address of value passed will be dereferenced and incremented
 * so the original value will be incremented
 */
void increment_ptr(int *value)
{
    (*value)++;
}

int main()
{
    int a = 5;

    /// note that & is part of type, i.e., int&
    /// It is just reference. So here we just have a. ref is a
    /// When you declare a reference, you need to immediately assign it otherwise
    /// compiler will throw error
    int &ref = a;
    ref = 2;

    /// so we get 2 even if we assign ref=2
    LOG(a);

    /// here we still get 2 because it just copies value
    increment(a);
    LOG(a);

    /// if we were to increment a then
    increment_ref(a);
    LOG(a);

    /// or increment by pointer
    increment_ptr(&a);
    LOG(a);

    int *ptr = &a;

    LOG("********");
    LOG(*ptr);

    /// you can only create one reference so for ex
    /// Here b will be set a value of m, i.e., 9
    int m = 9;
    int &m_ref = m;
    int b = m_ref;

    /// or to assign different values
    int *ref1 = &m;
    *ref1 = 2;
    ref1 = &b;
    *ref1 = 1;
    LOG("******ptr****")
    LOG(m);
    LOG(b);
}