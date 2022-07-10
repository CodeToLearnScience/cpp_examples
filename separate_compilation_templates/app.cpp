#include "foo.hpp"

int main(int argc, char const *argv[]) {

  arithmetic<int> a(1, 2);

  std::cout << a.add() << "\t" << a.sub() << "\t" << a.mul() << "\t" << a.div()
            << std::endl;

  arithmetic<double> b(1.1, 2.2);

  std::cout << b.add() << "\t" << b.sub() << "\t" << b.mul() << "\t" << b.div()
            << std::endl;

  /// Use of templated function with return type
  std::cout << square((int)3) << "\t" << square(3.2f) << "\t"
            << square((double)3.5) << "\n";

  /// Use of templated void function
  int i = 3;
  float f = 3.2;
  double d = 5.5;
  increment(i);
  increment(f);
  increment(d);

  std::cout << i << "\t" << f << "\t" << d << "\n";

  return 0;
}
