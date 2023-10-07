#include <iostream>
#include <type_traits>
namespace std {
template <bool B, typename T = void> struct enable_if {};
template <class T> struct enable_if<true, T> { using type = T; };

template <bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;
} // namespace std

/// SFINAE (Substitution Failure Is Not An Error)
template <bool IsFeedBackOut, typename T,
          std::enable_if_t<IsFeedBackOut> * = nullptr>
auto FeedBackOut_(T &&) {}

template <bool IsFeedBackOut, typename T,
          std::enable_if_t<!IsFeedBackOut> * = nullptr>
auto FeedBackOut_(T &&) {}