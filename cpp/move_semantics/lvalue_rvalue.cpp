/*
 * lvalue_rvalue.cpp
 *
 *  Created on: Sep 13, 2019
 *      Author: akadar
 *
 * References:
 * Effective Modern C++ Item 1, 2, 23-30
 * https://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Standard-Template-Library-STL-
 * https://github.com/nae9on/_help_/wiki/Move-semantics
 */

#include <iostream>

int main_lvalue_rvalue(){

    // Recall prototypes of special member functions
    // 1. copy ctor                Widget(const Widget&)
    // 2. copy assignment  Widget& Widget(const Widget&)
    // 3. move ctor                Widget(Widget&&)
    // 4. move assignment  Widget& Widget(Widget&&)

    int x{10};
    const int y{10};
    int&& z = 10;
    const int&& t = 10;

    // Binding
    // non-const lvalue-ref can bind to non-const lvalue.
    int& xref = x;

    // const lvalue-ref can bind to non-const/const lvalue, non-const/const rvalue.
    // Since const lvalue-ref can also bind to non-const/const rvalue, copy ctor/copy assignment
    // are called in the absence of move semantics.
    const int& cxref = x;
    const int& cyref = y;
    const int& czref = z;
    const int& ctref = t;

    // non-const rvalue-ref can only bind to non-const rvalue.
    // Therefore, move ctor/move assignment (if they exist) are invoked for non const-rvalue arguments
    int&& z1 = 10;

    // const rvalue-ref can bind to non-const/const rvalue.
    const int&& z2 = 10;
    const int&& z3 = std::move(t);

    (void) x;
    (void) y;
    (void) z;
    (void) t;
    (void) xref;
    (void) cxref;
    (void) cyref;
    (void) czref;
    (void) ctref;
    (void) z1;
    (void) z2;
    (void) z3;

    std::cout << "End of main" << std::endl;

    return 0;
}
