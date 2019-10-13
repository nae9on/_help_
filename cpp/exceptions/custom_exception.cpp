/*
 * custom_exception.cpp
 *
 *  Created on: Jul 18, 2019
 *      Author: akadar
 */

#include <iostream>
#include <exception> // std::exception

class my_exception: public std::exception
{
public:
	my_exception(){
		message = "Default message from my_exception";
	}
	my_exception(const char* str): message{str}{

	}
	/*
	 *  what() is a virtual function in the base exception class.
	 *
	 *  Note the noexcept qualifier. It is a promise made by the user that the function will
	 *  never throw an exception. The compiler enforces this promise. However, if all good intent
	 *  and planning fails and the function still throws an exception then std::terminate()
	 *  will be called to immediately terminate the program. Therefore, make a function noexcept
	 *  only if all the functions that it calls, either directly or indirectly are also noexcept
	 *  or const.
	 *
	 */
	const char* what() const noexcept(true) override {
		std::cout<<"Exception thrown from my_exception class\n";
		return message;
	}
private:
	const char* message;
};

class derived_exception: public my_exception {
public:
	derived_exception(){
		message = "Default message from derived_exception";
	}
	derived_exception(const char* str): message{str}{

	}
	const char* what() const noexcept(true) override {
		std::cout<<"Exception thrown from derived_exception class\n";
		return message;
	}
private:
	const char* message;

};

int custom_exception(){

	try{
		throw my_exception("dummy exception thrown from my_exception");
	}
	catch(const std::exception& e){
		std::cout<<e.what()<<"\n";
	}

	/*
	 * Note: Its a good practice to catch the exceptions by const& for the following two reasons:
	 * 1. A reference allows one to access the exception polymorphically.
	 * 2. A const increases performance by providing extra info to the compiler.
	 * The latter is not as much important as the former, but the only real reason to drop const
	 * would be to change the exception (usually useful only if one want's to rethrow it with
	 * added context into a higher level).
	 */

	try{
		throw derived_exception("dummy exception thrown from derived_exception");
	}
	catch(const my_exception& e){
			std::cout<<e.what()<<"\n";
	}

	return 0;
}
