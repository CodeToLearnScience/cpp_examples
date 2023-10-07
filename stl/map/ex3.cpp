#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;
bool f(int x, int y)
{
    return x > y;
}

int main()
{
  std::map<int, int> A;

    A[0] = 1;
    A[3] = -4;
    A[45] = 56;
    A[56] = 678;

    std::cout << " print map A: " << A.first<< "\n";
    map<char, int> cti;

    string s = "tatata";

    for (char c : s)
    {
        cti[c]++;
    }

    cout << cti['h'] << " " << cti['p'] << endl;

    //some example
    set<pair<int, int>> S; //pair is like {1, 1} , {3,4}, {3, h} etc

    S.insert({30, 40});
    S.insert({10, 20});
    S.insert({2, 3});
    S.insert({450, 987});

    int point = 11;

    auto it = S.upper_bound({point, INT64_MAX});

    if (it == S.begin())
    {
        cout << "the given point is not lying in any interval...\n";
    }
    it--;
    pair<int, int> current = *it;
    if (current.first <= point && point <= current.second)
    {
        cout << "yes its present" << current.first << " " << current.second << endl;
    }
    else
    {
        cout << "the current point doesn't lie in any interval..\n";
    }
    return 0;
}
