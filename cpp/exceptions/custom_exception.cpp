/*
 * custom_exception.cpp
 *
 *  Created on: Jul 18, 2019
 *      Author: akadar
 */

#include <iostream>
#include <exception>

class my_exception: public std::exception
{
public:
	my_exception(const char* str): message{str}{}

	// what() is a virtual function in the base exception class
	// note the const noexcept qualifiers
	const char*	what() const noexcept{
		std::cout<<"Exception thrown from my_exception class\n";
		return message;
	}
private:
	const char* message;
};

int main_custom(){

	try{
		throw my_exception("dummy exception thrown");
	}
	catch(std::exception& e){
		std::cout<<e.what();
	}

	return 0;
}
