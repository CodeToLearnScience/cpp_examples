/*it rearranges a range so the element at position n is the same as if the range
 * were fully sorted; elements before it are <= it (not sorted), and elements
 * after are >= it.*/

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  // Example data
  std::vector<int> v = {9, 1, 8, 3, 7, 2, 6, 4, 5};

  // Choose n: we want the element that would be at index 4 in a sorted array
  std::size_t n = 4;

  // Print original
  std::cout << "Original: ";
  for (int x : v) {
    std::cout << x << ' ';
  }
  std::cout << '\n';

  // Use nth_element (default operator<). After this:
  // - v[n] is the element that would be at index n in a fully sorted version
  // - all elements before v.begin()+n are <= v[n] (unsorted)
  // - all elements after are >= v[n] (unsorted)
  std::nth_element(v.begin(), v.begin() + n, v.end());

  // Print after nth_element
  std::cout << "After nth_element (n=" << n << "): ";
  for (int x : v) {
    std::cout << x << ' ';
  }
  std::cout << '\n';

  // Show the selected nth value and verify by sorting a copy
  std::cout << "v[" << n << "] = " << v[n] << '\n';

  std::vector<int> sorted = v;
  std::sort(sorted.begin(), sorted.end());
  std::cout << "Fully sorted: ";
  for (int x : sorted) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
  std::cout << "Sorted[" << n << "] = " << sorted[n] << '\n';

  return 0;
}
