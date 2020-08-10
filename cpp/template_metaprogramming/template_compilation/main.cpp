/*
 * main.cpp
 *
 *  Created on: 06 Nov 2019
 *      Author: akadar
 *
 *  Simple example to demonstrate the linking errors that can result when
 *  defining a template class separately from its declaration
 *
 * The same logic also applies to function templates (see [2] below)
 *
 *  References:
 *  [1] https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
 *  [2] https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl
 *
 * The two models are well explained here
 * https://docs.microsoft.com/en-us/cpp/cpp/source-code-organization-cpp-templates?view=vs-2019
 */

#include "header.h"
#include "utility.h"

#include <iostream>

using namespace algebra;

int main()
{
    point<int> p1;
    point<float> p2(2,4);
    std::cout<<p1<<"\n";
    std::cout<<p2<<"\n";

    std::cout<<slope<>(p2)<<"\n";

    return 0;
}
