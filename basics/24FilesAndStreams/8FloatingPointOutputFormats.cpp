#include <iomanip>
#include <ios>
#include <iostream>

using namespace std;

int main() {
  double pi{3.141'592'653'5};
  cout << pi << "\n";
  cout << scientific << pi << "\n";
  cout << scientific << uppercase << pi << "\n";

  double c{299'792'458};
  cout << c << "\n";
  cout << fixed << c << "\n";

  double e{1.602e-19};
  cout << fixed << e << "\n";

  int precision{3}, default_precision{6};
  cout << "pi to " << precision << "significant figures is ";
  cout << setprecision(precision) << pi << "\n";
  cout << "pi to " << default_precision << " significant figures is ";
  cout << setprecision(default_precision) << pi << "\n";

  // all manipulators are sticky. So that remains. So we should always restore
}
