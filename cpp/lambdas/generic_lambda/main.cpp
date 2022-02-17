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
    auto multiplyby2 = [](int a) { return 2*a; };
    auto divideby2 = [](int a) { return a/2; };

    point p(2, 4);
    transform t(multiplyby2, divideby2);
    std::cout << p << "\n";
    std::cout << t.GetDistortedPoint(p) << "\n";
    std::cout << t.GetUnDistortedPoint(p) << "\n";
    return 0;
}
