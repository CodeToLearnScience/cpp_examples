#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
bool f(int x, int y)
{
    return x > y;
}

int main()
{
    set<int> S;
    S.insert(1);
    S.insert(2);
    S.insert(-1);
    S.insert(-10);

    for (int x : S)
    {
        cout << x << endl;
    }

    auto it = S.find(-1);

    if (it == S.end())
    {
        cout << "not present" << endl;
    }
    else
    {
        cout << "present " << *it << endl;
    }

    auto it2 = S.lower_bound(-1);
    auto it3 = S.upper_bound(-1);

    cout << *it2 << " " << *it3 << endl;

    auto it4 = S.upper_bound(2);
    if (it4 == S.end())
    {
        cout << "can't find something like that" << endl;
    }

    S.erase(-1);

    return 0;
}