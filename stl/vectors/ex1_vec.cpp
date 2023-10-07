#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
bool f(int x, int y)
{
    return x > y;
}

int main()
{
    std::vector<int> A = {1, 2, 3};
    std::vector<int> B = {3, 5, 7, 2};

    std::cout << "element of vector A[0] = " << A[0] << std::endl;

    //to sort vector
    std::sort(A.begin(), A.end());

    //binary search
    bool present = std::binary_search(A.begin(), A.end(), 3);
    present = std::binary_search(A.begin(), A.end(), 100);

    A.push_back(100);
    A.push_back(100);
    A.push_back(100);
    A.push_back(100);
    A.push_back(123);

    //iterators
    vector<int>::iterator it = lower_bound(A.begin(), A.end(), 100);
    vector<int>::iterator it2 = upper_bound(A.begin(), A.end(), 100);

    //in new c++ above things can be done using auto
    auto itB = lower_bound(B.begin(), B.end(), 100);
    auto itB2 = upper_bound(B.begin(), B.end(), 100);

    cout << *it << " " << *it2 << endl;

    //iterator difference
    cout << it2 - it << endl; //4

    //to sort in descending order
    sort(A.begin(), A.end(), f);

    //print contents of above function
    vector<int>::iterator it3;
    for (it3 = A.begin(); it3 != A.end(); it3++)
    {
        cout << "ascending sorted vals = " << *it3 << endl;
    }

    //other way of printing vector
    for (int x : A)
    {
        x++; //wont change values. to change see next
        cout << "call by val = " << x << endl;
    }

    //if you want to update contents of A and print, then call be reference
    for (int &x : A)
    {
        x++; //wont change values. to change see next
        cout << "call by ref = " << x << endl;
    }

    for(auto it=B.begin(); it!=B.end()-2; ++it){
        std::cout << "B vals: " << *it << std::endl;
    }

    std::cout << "print first val of vector: " << *(B.begin()) << "\n";

    return 0;
}
