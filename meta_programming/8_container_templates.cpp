#include <iostream>
#include <type_traits>

/// Various template declarations
template <int... Vals> struct IntContainer;
template <bool... Vals> struct BoolContainer;
template <typename... Types> struct TypeContainer;
template <template <typename> class... T> struct TemplateCount;
template <template <typename...> class... T> struct TemplateCount2;