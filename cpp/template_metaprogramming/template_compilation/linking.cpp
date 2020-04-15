/*
 * linking.cpp
 *
 *  Created on: 06 Nov 2019
 *      Author: akadar
 *
 *  Simple example to demonstrate the linking errors that can result when
 *  defining a template class separately from its declaration
 *
 *  References:
 *  [1] https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
 */

#include "headX.h"

int main_linking()
{
	X<int> objx;

	X<float> obj;

    return 0;
}
