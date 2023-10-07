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