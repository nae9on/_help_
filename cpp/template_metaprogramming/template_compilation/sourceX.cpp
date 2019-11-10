/*
 * sourceX.cpp
 *
 *  Created on: 06 Nov 2019
 *      Author: ahkad
 */

#include "headX.h"

template<typename T>
X<T>::X(){
	x = 0;
}

// When the below lines are included, compiler sees both the declaration and definition of the
// instantiated classes X<int> and X<float>. This prevents linking errors.

template class X<int>;

template class X<float>;

// These lines can also be included at the end of the header file.
// Note: including these lines can also be interpreted as "the programmer guarantees the working
// of template class instantiations for int and float types only"
