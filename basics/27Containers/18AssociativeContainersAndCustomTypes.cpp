/*
---------------------------------------
Associative Containers and Custom Types
---------------------------------------
- Custom types can be used with all the associative containers
  * map, set, multimap, and multiset
  * ordered or unordered versions
- We can use a custom type as either the value in an associative container or
the key, or both

--------------------
Custom Type as Value
--------------------
- We are going to create a container to represent a library of books
- We want to be able to search the container to find the books written by an
author (key-value)
- An author can write more thanone book (duplicate keys)
- The container will be a multimap
- The key will be a string
  * The author's name
- The value will be an object of a class
  * The details of the book

--------------------
Book Class
--------------------
//Class with book details
clas book{
private:
  string title;
  string publisher;

public:
  book(string title, string publisher) : title(title), publisher(publisher){}
};

multimap<string, book> library; //key is the author's name, value is a book
                                //object

--------------------
Sorting the Library
--------------------
- the multimap will sort the books in order of thier key
  * The author
- Books by the same author will be grouped together, but the titles will
probably not be in order
  * It would be useful to be able to sort the titles as well
- We need a compound key which includes both the author and the title
  * This key will sort by the author first, then the title
  * We will write a class to provide this compound key

----------------------
Custom Type as Key
----------------------
- The new class will contain the fields we want to sort on
  class book_idx{
  private:
    string author;
    string title;
  public:
  ...
  };
- We will use this class as they key in our multimap
 multimap<book_idx, book> library;

-------------------------------------------------
Custom Type and Container Organization
-------------------------------------------------
- Ordered associative containers use the < operator of thier keys to sort their
elements
  * The compiler will give an error if this not defined
  * We need to define a < operator for our class
  * To ensure our books are sorted correctly, the < operator needs to compare
    the author first, then the titles
- unordered associative containers use the hash value of thier keys to organize
thier elements
  * Need to specialize std::hash<T>
  * Need to define opeator == for our class

---------------------------------------------
Identity, equality and equivalence
---------------------------------------------
- Identity
  * The objects occupy the same memory, but are referred to differently
  * Corresponds to a single copy of a book
- Equality
  * The objects occupy different memory, but have the same values
  * Corresponds to two copies of the same book
- Equivalence
  * "Important" values are the same, but "unimportant" values may differ
  * Corresponds to e.g. hardback and paperback versions of same book
  * Will sort as if they were equal
  * So when we say two objects are equal in C++, this is what we are alluding to

-------------------
book_idx < opeator
-------------------
    bool operator < (const book_idx& other) const{
      //if the author is the same, order by title
      if(author==other.author){
        return title < other.title;
      }
      //otherwise, order by author
      return author < other.author;
    }
*/

#include <iostream>
#include <map>
#include <ostream>
#include <type_traits>
#include <utility>

using namespace std;

// Class with book details
class book {
private:
  string title;
  string publisher;

public:
  book(string title, string publisher) : title(title), publisher(publisher) {}
  friend ostream &operator<<(ostream &os, const book &bk) {
    os << "(" << bk.title << ", " << bk.publisher << ")";
    return os;
  }
};

class book_idx {
  std::string author;
  std::string title;

public:
  book_idx(const std::string &author, const std::string &title)
      : author(author), title(title) {}
  bool operator<(const book_idx &other) const {
    // If the author is the same, order by title
    if (author == other.author) {
      return title < other.title;
    }
    // otherwise, order by author
    return author < other.author;
  }

  friend ostream &operator<<(ostream &os, const book_idx &bkx) {
    os << "(" << bkx.author << ", " << bkx.title << ")";
    return os;
  }
};

class book1 {
private:
  string edition;
  string publisher;
  int date;

public:
  book1(string publisher, string edition, int date)
      : publisher(publisher), edition(edition), date(date) {}
  friend ostream &operator<<(ostream &os, const book1 &bk) {
    os << "(" << bk.publisher << ", " << bk.edition << ", " << bk.date << ")";
    return os;
  }
};

int main() {
  multimap<string, book> library;

  // Add some books to the library
  book prog_princs("Programming Principles and Practice", "Addison-Wesley");
  library.insert({"Stroustrup, Bjarne", prog_princs});

  book cpp_primer("C++ Primer", "Addison-Wesley");
  library.insert({"Lippman, Stanley B.", cpp_primer});

  book cpp_prog("The C++ Programming Language", "Addison-Wesley");
  library.insert({"Stroustrup, Bjarne", cpp_prog});

  book cpp_tour("A Tour of C++", "Addison-Wesley");
  library.insert({"Stroustrup, Bjarne", cpp_tour});

  // print out all the books
  for (const auto &b : library) {
    cout << b.first << ", " << b.second << "\n";
  }

  multimap<book_idx, book1> library1;

  // Add some books to the library
  book1 prog_princs1("Addison-Wesley", "2nd Edition", 2014);
  book_idx prog_princs_idx("Stroustrup, Bjarne",
                           "Programming Principles and Practice");
  library1.insert(make_pair(prog_princs_idx, prog_princs1));

  book1 cpp_primer1("Addison-Wesley", "5nd Edition", 2013);
  book_idx cpp_primer_idx("Lippman, Stanley B.", "C++ Primer");
  library1.insert(make_pair(cpp_primer_idx, cpp_primer1));

  book1 cpp_prog1("Addison-Wesley", "4nd Edition", 2013);
  book_idx cpp_prog_idx("Stroustrup, Bjarne", "The C++ Programming Language");
  library1.insert(make_pair(cpp_prog_idx, cpp_prog1));

  book1 cpp_tour1("Addison-Wesley", "1nd Edition", 2018);
  book_idx cpp_tour_idx{"Stroustrup, Bjarne", "A Tour of C++"};
  library1.insert(make_pair(cpp_tour_idx, cpp_tour1));

  for (const auto &b : library1) {
    cout << b.first << ", " << b.second << "\n";
  }
}
