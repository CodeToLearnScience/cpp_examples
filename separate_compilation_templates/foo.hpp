#pragma once

#include <iostream>

/// templated class
template <typename T> class arithmetic {
public:
  arithmetic(T a, T b);

  T add();
  T sub();
  T mul();
  T div();

private:
  T m_a, m_b;
};

/// templated function with return type
template <typename S> S square(S s);

/// templated function with void return type
/// NOTE: we can use either class or typename for template parameter
template <class U> void increment(U &u);
