/*----------------------------------
 * Algorithms and Iterators Workshop
 *----------------------------------
1) Fill a vector with 10 random integers between 0 and 1000
2) (For each exercise, display the result)
3) Find the maximum element in this vector
4) Find the index of this maximum element
5) Sum the elements of the vector
6) Count the number of odd numbers in the vector
7) Normalize the vector (divide all the elements by the largest.) Put
the normalized elements into a vector of doubles, without setting
the size of the output vector first
8) Make a sorted copy of the vector. Without using a functor or a
lambda (or equivalent), find the first element greater than 455 and
the number of elements > 455
9) Copy all the odd numbers to a vector of doubles, without setting
the size of the output vector first
10) Sort the vector in descending order
11)Randomly shuffle all but the first and the last element of the vector
12)Remove all the odd numbers from the vector
13)Write the remaining elements to a text file on a single line as a
comma separated list, without a trailing comma
14)Read the file "words.txt". Display each distinct word once. Ignore
punctuation and capitalization
Hint: look into std::istreambuf_iterator
15)Count the total number of words in the file
16)Count the number of lines in the file
17)Count the number of characters in the file
18)Read "words.txt" and "words2.txt". Display the words which are
common to both files
19)Calculate the factorial of 6 (6 x 5 x 4 x ... x 1)
*/

#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

template <class T, class S> void print(const T &obj) {
  ostream_iterator<S> oi(cout, ", ");
  copy(cbegin(obj), cend(obj), oi);
  cout << "\n";
}

template <typename T>
void print_comma_separated(ostream &os, const std::vector<T> &v) {
  if (!v.empty()) {
    std::copy(v.begin(), std::prev(v.end()),
              std::ostream_iterator<T>(os, ", "));
    os << v.back();
  }
  os << '\n';
}

static std::string normalize1(std::string s) {
  auto is_punct = [](unsigned char c) { return std::ispunct(c); };
  // remove leading punctuation
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [&](char ch) {
            return !is_punct((unsigned char)ch);
          }));
  // remove trailing punctuation
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [&](char ch) { return !is_punct((unsigned char)ch); })
              .base(),
          s.end());
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return s;
}

int main() {

  // 1. Fill vec with random values
  mt19937 mt;
  uniform_int_distribution<int> uid(0, 1000);
  vector<int> vec(10);
  // generate(begin(vec), end(vec), [&mt, &uid]() { return uid(mt); });
  generate(begin(vec), end(vec), [&]() { return uid(mt); });

  // 2. display result
  print<std::vector<int>, int>(vec);

  // 3. Max element in vector
  auto max_el = max_element(cbegin(vec), cend(vec));
  cout << "Max element of a vector: " << *max_el << "\n";

  // 4. index of max_el
  cout << "Max element of a vector is at inex: "
       << distance(cbegin(vec), max_el) << "\n";

  // 5. Sum the elements of vector
  auto sum_vec = accumulate(cbegin(vec), cend(vec), 0);
  cout << "The sum of elements of vec: " << sum_vec << "\n";

  // 6. Count the odd numbers in vec
  /*  vector<int> odd_elem_vec;
    copy_if(cbegin(vec), cend(vec), back_inserter(odd_elem_vec),
            [](int n) { return n % 2 == 1; });
    cout << "There are " << odd_elem_vec.size()
         << " odd elements in vec and those are: ";
    print<std::vector<int>, int>(odd_elem_vec);*/
  auto num_odd_elem_vec =
      count_if(cbegin(vec), cend(vec), [](int n) { return n % 2 == 1; });
  cout << "There are " << num_odd_elem_vec << "\n";

  // 7. Normalize the vector
  vector<double> normalized_vec;
  transform(cbegin(vec), cend(vec), back_inserter(normalized_vec),
            [max_el](int n) { return (n / static_cast<double>(*max_el)); });
  cout << "Normalized vector: ";
  print<std::vector<double>, double>(normalized_vec);

  // 8. Make a sorted copy
  vector<int> sorted_vec{vec};
  sort(begin(sorted_vec), end(sorted_vec));
  cout << "Sorted vector: ";
  print<std::vector<int>, int>(sorted_vec);
  auto gt_455 = find_if(begin(sorted_vec), end(sorted_vec),
                        [](int n) { return n > 455; });
  cout << "Number of elements greater than 455: "
       << distance(gt_455, end(sorted_vec)) << " \n";

  // 9. Copy all the odd numbers to vec of doubles
  vector<double> vec_odd_elems;
  copy_if(cbegin(vec), cend(vec), back_inserter(vec_odd_elems),
          [](int n) { return n % 2 == 1; });
  cout << "The odd elements copied to vec: ";
  print<std::vector<double>, double>(vec_odd_elems);

  // 10. Sort the vector in descending order
  sort(begin(vec), end(vec), [](int m, int n) { return m > n; });
  cout << "The sorted vec in descending order: ";
  print<std::vector<int>, int>(vec);

  // 11. shuffle vec except frst and last element
  shuffle(begin(vec) + 1, end(vec) - 1, mt);
  cout << "The shuffled vec: ";
  print<std::vector<int>, int>(vec);

  // 12. Remove all the odd numbers from the vector
  auto retval =
      remove_if(begin(vec), end(vec), [](int n) { return n % 2 == 1; });
  cout << "After removing odd numbers: ";
  print<std::vector<int>, int>(vec);

  // 13. write the remaining elements to file
  ofstream ofile("text.txt");
  if (ofile.is_open()) {
    copy(retval, prev(vec.end()), ostream_iterator<int>(ofile, ", "));
    ofile << vec.back();
    ofile << '\n';
  }
  ofile.close();

  // 14 and 15. Read words.txt and display each distinct words once
  int num_chars{0};
  {
    int total_num_words{0};
    ifstream ifile("words.txt");
    istreambuf_iterator<char> it(ifile);
    istreambuf_iterator<char> end;
    string word;
    while (it != end) {
      char c = *it++; // read next character
      num_chars++;
      if (isspace(static_cast<unsigned char>(c))) {
        if (!word.empty()) {
          cout << word << "\n"; // output collected word
          word.clear();
          total_num_words++;
        }
      } else if (isalpha(c)) {
        word.push_back(c); // accumulate non-space into word
      }
    }
    if (!word.empty()) // last word if file doesn't end with space
      std::cout << word << '\n';
    std::cout << "Total number of words in the file are: " << total_num_words
              << "\n";
  }
  // 16. Total number of lines in the file
  int total_num_lines{-1};
  ifstream ifile("words.txt");
  if (ifile.is_open()) {
    while (ifile) {
      string line;
      getline(ifile, line);
      total_num_lines++;
    }
  }
  ifile.close();
  std::cout << "Total number of lines in the file are: " << total_num_lines
            << "\n";
  std::cout << "Total number of characters in the file are: " << num_chars
            << "\n";
  // 18. Read words.txt and words2.txt
  // ifile.clear();
  // ifile.seekg(0, std::ios::beg); // seek to start

  ifstream ifile1("words.txt");
  ifstream ifile2("words2.txt");

  std::vector<std::string> words1{
      std::istream_iterator<std::string>(ifile1),
      std::istream_iterator<std::string>() // end iterator
  };
  std::vector<std::string> words2{
      std::istream_iterator<std::string>(ifile2),
      std::istream_iterator<std::string>() // end iterator
  };

  auto normalize = [](const std::string &s) {
    std::string ret;
    std::copy_if(s.cbegin(), s.cend(), std::back_inserter(ret),
                 [](unsigned char c) { return std::isalpha(c); });
    std::transform(ret.begin(), ret.end(), ret.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return ret;
  };

  std::transform(words1.begin(), words1.end(), words1.begin(), normalize);
  std::transform(words2.begin(), words2.end(), words2.begin(), normalize);

  // remove empty tokens that may result from normalization
  words1.erase(std::remove_if(words1.begin(), words1.end(),
                              [](const std::string &s) { return s.empty(); }),
               words1.end());
  words2.erase(std::remove_if(words2.begin(), words2.end(),
                              [](const std::string &s) { return s.empty(); }),
               words2.end());

  sort(words1.begin(), words1.end());
  sort(words2.begin(), words2.end());

  // compute intersection
  std::vector<std::string> common;
  std::set_intersection(words1.begin(), words1.end(), words2.begin(),
                        words2.end(), std::back_inserter(common));

  // print results
  std::copy(common.begin(), common.end(),
            std::ostream_iterator<std::string>(std::cout, "\n"));
  // 20. Calculate the factorial of 6
  vector<int> fact(6);
  iota(fact.begin(), fact.end(), 1);
  auto res = accumulate(fact.cbegin(), fact.cend(), 1, multiplies<int>());
  cout << "The factorial of 6 is: " << res << "\n";
}
