/*
 * main.cpp
 *
 *  Created on: 17 Feb 2022
 *      Author: akadar
 *
 *  Simple example to demonstrate the usage of generic lambdas.
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
