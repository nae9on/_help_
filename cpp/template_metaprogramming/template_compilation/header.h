/*
 * header.h
 *
 *  Created on: 06 Nov 2019
 *      Author: ahkad
 */

#ifndef HEADER_H_
#define HEADER_H_

#include <ostream>

namespace algebra
{

// class template
template <typename T>
class point{
public:
        point() = default;
        point(T a, T b);
public:
        T x{};
        T y{};
};

// alias decleration
using pointf = point<float>;

// function template
template <typename T>
std::ostream& operator<<(std::ostream& os, point<T>);

}
#endif /* HEADER_H_ */
