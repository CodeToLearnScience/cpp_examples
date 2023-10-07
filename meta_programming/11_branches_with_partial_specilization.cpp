#include <iostream>

struct A;
struct B;

template <typename T> struct Fun_ { constexpr static std::size_t value = 0; };
template <> struct Fun_<A> { constexpr static std::size_t value = 1; };
template <> struct Fun_<B> { constexpr static std::size_t value = 2; };

constexpr std::size_t val = Fun_<B>::value;
///////////////////////////////////////////////////////////////////////////////
/// C++14
struct C;
struct D;

template <typename T> constexpr std::size_t Fun = 0;

template <> constexpr std::size_t Fun<C> = 1;
template <> constexpr std::size_t Fun<D> = 2;

constexpr std::size_t val2 = Fun<D>;
/////////////////////////////////////////////////////////////////////////////////
/// Also

template <typename TW> struct wrapper {
  template <typename T, typename Tdummy = void> struct Fun_ {
    constexpr static std::size_t value = 0;
  };
  template <typename Tdummy> struct Fun_<int, Tdummy> {
    constexpr static std::size_t value = 1;
  };
};

constexpr std::size_t val3 = wrapper<A>::Fun_<int>::value;