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
    using T = float;
    auto multiplyby2 = [](point<T> a) { return point<T>(2*a.x, 2*a.y); };
    auto divideby2 = [](point<T> a) { return point<T>(a.x/2, a.y/2); };

    point<T> p(2, 4);
    transform<T> t0, t1(multiplyby2, divideby2);
    std::cout << p << "\n";
    std::cout << t0.GetDistortedPoint(p) << "\n";
    std::cout << t0.GetUnDistortedPoint(p) << "\n";
    std::cout << t1.GetDistortedPoint(p) << "\n";
    std::cout << t1.GetUnDistortedPoint(p) << "\n";
    return 0;
}
