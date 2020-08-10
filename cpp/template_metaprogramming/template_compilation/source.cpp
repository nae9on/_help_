/*
 * source.cpp
 *
 *  Created on: 06 Nov 2019
 *      Author: ahkad
 */

#include "header.h"

namespace algebra
{

// class template definition
template<typename T>
point<T>::point(T a, T b)
{
    x = a;
    y = b;
}

// When the below lines are included, compiler sees both the declaration and definition of the
// instantiated classes point<int> and point<float>. This prevents linking errors.
// These lines can also be included at the end of the header file.
// Note: including these lines can also be interpreted as "the programmer guarantees the working
// of template class instantiations for int and float types only"

// class template instantiations
template class point<int>;
template class point<float>;

// function template definition
template <typename T>
std::ostream& operator<<(std::ostream& os, point<T> p)
{
    return os<<p.x<<" "<<p.y;
}

// function template instantiations
template std::ostream& operator<<(std::ostream& os, point<int> p);
template std::ostream& operator<<(std::ostream& os, point<float> p);
}
