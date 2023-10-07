#include <iostream>
#include <vector>

int main()
{
    std::vector<float> v{0.0, 1.1, 2.2, 3.3, 4.4};

    const float *p1 = v.data();               // pointer to start
    const float *const p1end = p1 + v.size(); // pointer to end

    std::cout << "what: " << p1 << "\t" << p1end << "\n";

    return 0;
}
