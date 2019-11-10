/*
 * compilation.cpp
 *
 *  Created on: 06 Nov 2019
 *      Author: akadar
 *
 *  Simple example to demonstrate when the definition of a template class
 *  be separated from its declaration.
 *
 *  References:
 *  [1] https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
 */

#include "headX.h"

int compilation()
{
	X<int> objx;

	X<float> obj;

    return 0;
}
