#include "foo.hpp"
#include "foo.ipp"

/// explicit instantiation of templated class arithmetic
template class arithmetic<int>;
template class arithmetic<float>;
template class arithmetic<double>;

/// explicit instantiation of square function with return type
template int square(int);
template float square(float);
template double square(double);

/// explicit instantiation of templated void function
template void increment(int &);
template void increment(float &);
template void increment(double &);