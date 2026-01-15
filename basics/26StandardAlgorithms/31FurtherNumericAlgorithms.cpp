/*
------------------------
Other Numeric Algorithms
------------------------
- There are some other algorithms in <numeric> which are useful in numerical
computing
  * partial_sum
  * adjacent_difference
  * inner_product
- C++17 also provides a number of special functions in <cmath>
  * Bessel functions, Legendre polynomials etc.

--------------
partial_sum()
--------------
- partial_sum() writes the "running total" of the elements into another
container
- Given a source container {a,b,c}
- The target container will have elements {a, a+b, a+b+c}
  vector<int> vec1{1,2,3,4,5}

  //vec2 will have the elements {1,3,6,10,15}
  partial_sum(begin(vec1), cend(vec1), back_insert(vec2));

- Can be used to performa numerical integration
- By default, the + operator of the element is used

---------------------
adjacent_difference()
---------------------
- adjacent_difference() writes the difference between successive elements into
another container
- Given a source container {a,b,c,...}
- The target container will have elements {a,b-a,c-b}
  vector<int> vec1{1,3,6,10,15}


  //vec2 will have the elements {1,2,3,4,5}
  //adjacent_difference(begin(vec1), cend(vec1), back_insert(vec2));

- Can be used to perform numerical differentiation
  * The inverse of partial_sum sum
- By default, the - operator of the element is used

-----------------------
inner_product()
-----------------------
- inner_product() multiplies the corresponding elements of two containers
together and calculates their sum
- Given source containers {a1,a2,a3,...} and {b1,b2,b3,...}
- The result will be a1*b1+a2*b2+a3*b3+,...
- Equivalent to "scalar product"
- As with accumulate(), we have to provide an initial value for the sum
  auto result = inner_product(cbegin(vec1), cend(vec1), cbegin(vec2),
                cend(vec2), 0);
- By default, the + operator and * operator of the element are used
- Also, this can be implemented in two steps using transform() and accumulate()
- A transform step which multiplies elements from each range together and stores
the results in another range

  transform(cbegin(vec1), cend(vec1), cbegin(vec2), back_inserter(vec3),
            multiplies<int>());
- An accumulate step which adds up the result in that range
  auto result = accumulate(cbegin(vec3), cend(vec3), 0, std::plus<int>());

----------------------------------
Overloading inner_product()
----------------------------------
- inner_product() can be overloaded by providing different binary functions
instead of the default + and * operators
- We can replace * operator by a "transform" operation
  * This takes two arguments of the element type, and returns a value of some
    return type
- We can replace the + operator by an "accumulate operation
  * This takes two arguments of the return type, and returns a value of the
    result type
  * This collects the result of all the transform operations and calculates the
    final result

------------------------------------
Overloading inner_product() example
------------------------------------
- The result of a scientific experiment are stored in a vector
- We have another vector which contains the theoretically predicted values
- We want to find the biggest error (the maximum difference between and expected
result and the corresponding actual result)
- We can do this using an overload version of inner_product()
  * THe transform operation will find the difference between corresponding
    elements
  * The reduce operation will find go through these difference and find the
    largest single difference
  * The result will be the maximum error in the data
- Replace the * operator by a function that finds the difference between
corresponding elements
- Replace the + operator by a function that finds the largest difference
//Find the biggest difference between corresponding elements
//in two vectors of double (taken from Marco Arena blog)

 inner_product(begin(expected), end(expected), begin(actual),
               0.0, //intial max error
               [](auto a, auto b){return max(a,b);} //reduce operation
               [](auit l, auto r){return fabs(r-l);} //transform operation
         );

 --------------------------------------------------------
 std::inner_product() and parallel processing
 --------------------------------------------------------
 - Transform + accumulate is a common pattern in parallel programming
   * Break a large calculation into smaller parts which can be performed
     independently of each other
   * Perform each sub-calculation on its own processor core
   * Combine the results of the sub-calculation to give the final result
- However, std::accumulate() is not suitable for parallel processing
- C++17 has std::transform_reduce()
   * Same as inner_product(),but uses reduce() instead of accumulate()
   * std::reduce() is compatible with parallel processing
*/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

using namespace std;

void print(const vector<int> &vec) {
  for (auto v : vec) {
    cout << v << " ";
  }
  cout << "\n";
}

int main() {
  vector<int> vec1{1, 2, 3, 4, 5};
  vector<int> vec2;

  cout << "+++++++++demonstration of partial_sum()++++++++++++++++++\n";
  cout << "Source vector: ";
  print(vec1);

  partial_sum(cbegin(vec1), cend(vec1), back_inserter(vec2));
  cout << "Target vector: ";
  print(vec2);
  //---------------------------------------------------------------------------
  // adjacent_difference
  cout << "+++++++++demonstration of adjacent_difference++++++++++++++++++\n";
  cout << "It's the inverse of partial_sum()\n";
  cout << "Source vector: ";
  print(vec2);
  vector<int> vec3;
  adjacent_difference(cbegin(vec2), cend(vec2), back_inserter(vec3));
  cout << "Target vector: ";
  print(vec3);

  //---------------------------------------------------------------------------
  // inner_product
  cout << "+++++++++demonstration of inner_product++++++++++++++++++\n";
  cout << "Source vectors are: ";
  print(vec2);
  print(vec3);

  auto result = inner_product(cbegin(vec2), cend(vec2), cbegin(vec3), 0);
  cout << "The inner product of two source vectors is: " << result << "\n";
  //---------------------------------------------------------------------------
  // inner_product implemented using transform() and accumulate()
  cout << "+++++++++demonstration of inner_product using transform() and "
          "accumulate()++++++++++++++++++\n";
  cout << "Source vectors are: ";
  print(vec2);
  print(vec3);

  vector<int> vec4;

  transform(cbegin(vec2), cend(vec2), cbegin(vec3), back_inserter(vec4),
            multiplies<int>());
  cout << "Tranformed vector: ";
  print(vec4);

  auto result1 = accumulate(cbegin(vec4), cend(vec4), 0, std::plus<int>());
  cout << "Now the sum accumulated from Tranformed vector: " << result1 << "\n";

  //---------------------------------------------------------------------------
  // inner_product overload
  cout << "+++++++++demonstration of inner_product "
          "Overloading++++++++++++++++++\n";
  cout << "We will demonstrate this by finding max difference between expected "
          "and actual values from experimental data+++++++++++\n";

  vector<double> expected{0.1, 0.2, 0.3, 0.4, 0.5};
  vector<double> actual{0.09, 0.22, 0.27, 0.41, 0.52};

  // second lambda function returns the absolute difference between values
  // first lambda function finds the maximum difference
  auto max_diff = inner_product(
      begin(expected), end(expected), begin(actual), 0.0,
      [](auto a, auto b) { return max(a, b); },    // reduce operation
      [](auto l, auto r) { return fabs(r - l); }); // transform operation

  cout << "Max difference is: " << max_diff << "\n";
}
