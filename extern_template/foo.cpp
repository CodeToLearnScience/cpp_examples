#include "foo.h"

/// explicit instantiation
template int sum(int, int);
template double sum(double, double);
template int sum(int, double);
template double sum(double, int);
