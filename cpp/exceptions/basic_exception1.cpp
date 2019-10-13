/*
 * basic_exception1.cpp
 *
 *  Created on: Oct 13, 2019
 *      Author: akadar
 */

#include <iostream>

class X{
public:
	X(){
		data = new int[5]();
		++count;
		id = count;
		std::cout<<"Memory allocated and my id = "<<id<<std::endl;
	}
	~X(){
		delete[] data;
		--count;
		std::cout<<"Memory de-allocated and my id = "<<id<<std::endl;
	}
	static int count;
private:
	int* data;
	int id;
};

int X::count = 0;

int basic_exception1(){

	/*
	 * The throw statement transfers control to a handler for exception.
	 * In order to do that, the implementation unwinds the function call stack as needed
	 * to get back to the context of that caller. That is, the exception handling mechanism
	 * will exit scopes and functions as needed to get back to a handler that has expressed
	 * interest in handling that kind of exception, invoking destructors as shown below.
	 */
	try{
		X x;
		X y;
		X z;
		throw 1;
	}
	catch(const int& e){ // handler
		std::cout<<"Int exception caught 1\n";
	}\
	std::cout<<"Total count = "<<X::count<<"\n";

	std::cout<<"\n\n";


	/*
	 * When the implementation unwinds the function call stack, scopes are exited but
	 * actions are retained.
	 */
	int ctr{0};
	try{
		++ctr; // ctr is updated to 1
		throw 1;
		++ctr; // control does not reach this point
	}
	catch(const int& e){ // handler
		std::cout<<"Int exception caught 2\n";
	}
	std::cout<<"ctr = "<<ctr<<"\n";

	return 0;
}
