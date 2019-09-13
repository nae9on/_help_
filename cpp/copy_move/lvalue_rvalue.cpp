/*
 * lvalue_rvalue.cpp
 *
 *  Created on: Sep 13, 2019
 *      Author: akadar
 *
 * References:
 * https://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Standard-Template-Library-STL-
 */

int lvalue_rvalue(){

	/*
	 * Note:
	 * 1. expressions and not objects are lvalues or rvalues.
	 * 2. An expression which has a named memory location is an lvalue.
	 * 3. An expression which is a temporary (i.e does not have a named memory location) is an rvalue.
	 * 4. An expression is either an lvalue or an rvalue.
	 * 5.
	 */

	int x1 = 10; // 10 is an rvalue here. x1 is an lvalue.

	// What lvalue-ref can bind to?
	int& y1 = x1; //OK, non-const lvalue-ref can bind to an lvalue.
	const int& y2 = x1; //OK, const lvalue-ref can bind to an lvalue.
	//int& y2 = 10; // Error, non-const lvalue-ref cannot bind to an rvalue.
	const int& y3 = 10; //OK

	// What rvalue-ref can bind to?
	int&& z1 = 10; //OK, const/non-const rvalue-ref can bind to an rvalue.
	//int&& z2 = x1; //Error, const/non-const rvalue-ref cannot bind to an lvalue.
	int&& z3 = x1 + x1; //OK, x1 + x1 is a temporary and thus an rvalue

	return 0;
}
