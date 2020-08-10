#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>

namespace algebra
{

// forward declering a template
template <typename T> class point;

template<typename T=float>
double slope(point<T> p);

}

#endif // UTILITY_H
