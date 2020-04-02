/*
 * type_of_inheritance.cpp
 *
 *  Created on: 01 Apr 2020
 *      Author: ahkad
 *
 * Reference: stackoverflow difference-between-private-public-and-protected-inheritance
 */

#include <iostream>

class A
{
public:
    int x;
protected:
    int y;
private:
    int z;
};

class B : public A
{
    // x is public
    // y is protected
    // z is not accessible from B
};

class C : protected A
{
    // x is protected
    // y is protected
    // z is not accessible from C
};

class D : private A    // 'private' is default for classes
{
    // x is private
    // y is private
    // z is not accessible from D
};

int type_of_inheritance(){

	return 0;
}
