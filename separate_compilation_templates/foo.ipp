#include "foo.hpp"

/// constructor
template <typename T> arithmetic<T>::arithmetic(T a, T b) : m_a(a), m_b(b) {}

/// add function
template <typename T> T arithmetic<T>::add() { return m_a + m_b; }

/// sub function
template <typename T> T arithmetic<T>::sub() { return m_a - m_b; }

/// mul function
template <typename T> T arithmetic<T>::mul() { return m_a * m_b; }

/// div function
template <typename T> T arithmetic<T>::div() { return m_a / m_b; }

/// square function with return type
template <typename S> S square(S s) { return s * s; }

/// square function with void return type
template <class U> void increment(U &u) { u++; }