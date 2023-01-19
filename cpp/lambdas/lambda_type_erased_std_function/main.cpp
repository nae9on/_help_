/*
 * main.cpp
 *
 *  Created on: 17 Feb 2022
 *      Author: akadar
 *
 *  Simple example to demonstrate the usage of generic lambdas.
 *
 *  Reference:
 *  Section 11.4.5 The Type of a Lambda from "The C++ Programming Language 4th Edition"
 *  The exact type of a lambda expression is not defined. No two lambda expressions can have the same type!!
 *  The type of a lambda is roughly a local class type with a ctor and a const member function operator()()
 *  Altough their exact type is not defined, lambda's can be used to initialize variables declared auto or
 *  std::function<R<AL>> where R is the lambda's return type and AL is its argument list of types.
 */

#include "transform.h"

#include <iostream>

using namespace algebra;

int main()
{
    auto multiplyby2 = [](point a) { return point(2*a.x, 2*a.y); };
    auto divideby2 = [](point a) { return point(a.x/2, a.y/2); };

    point p(2, 4);
    transform t(multiplyby2, divideby2);
    std::cout << p << "\n";
    std::cout << t.GetDistortedPoint(p) << "\n";
    std::cout << t.GetUnDistortedPoint(p) << "\n";
    return 0;
}
