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
    auto multiplyby2 = [](point a) { return point(2*a.x, 2*a.y); };
    auto divideby2 = [](point a) { return point(a.x/2, a.y/2); };

    point p(2, 4);
    transform t(multiplyby2, divideby2);
    std::cout << p << "\n";
    std::cout << t.GetDistortedPoint(p) << "\n";
    std::cout << t.GetUnDistortedPoint(p) << "\n";
    return 0;
}
