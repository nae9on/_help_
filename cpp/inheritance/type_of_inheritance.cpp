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

class B : public A // used when implementing an interface
{
    // x is public
    // y is protected
    // z is not accessible from B
    // because B doesn't inherit access to private data members of A.
    // However, it does inherit a full object of A (containing all its public and private members).
};

class C : protected A // used when extending a concrete class + allows extendind further to sub-classes of C
{
    // x is protected
    // y is protected
    // z is not accessible from C
};

class D : private A  // used when extending a concrete class but does not allow extendind further to sub-classes of D
{
    // x is private
    // y is private
    // z is not accessible from D
};

int type_of_inheritance(){

	return 0;
}
