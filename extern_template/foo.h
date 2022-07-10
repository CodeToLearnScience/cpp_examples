#pragma once

template <typename T, typename U> T sum(T t, U u) { return t + u; }

/// sum will be explicitly instantiated somewhere
/// with the following template params
/// do not implicitly instantiate
extern template int sum(int, int);
extern template double sum(double, double);
extern template int sum(int, double);
extern template double sum(double, int);
