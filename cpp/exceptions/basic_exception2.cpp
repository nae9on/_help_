/*
 * basic_exception2.cpp
 *
 *  Created on: Oct 13, 2019
 *      Author: akadar
 */

#include <iostream>
#include <stdexcept> // std::runtime_error, std::logic_error
#include <vector>
#include <string>

std::vector<std::string> s;

class A: public std::runtime_error{
public:
	A(): runtime_error("?"){
		s.push_back("A's constructor called");
	}
};

class B: public std::logic_error{
public:
	B(): logic_error("!"){
		s.push_back("B's constructor called");
	}
};

void f(){
	s.push_back("In f pre-throw");
	throw B();
}

void g(){
	try{
		f();
	}catch(const A &a){
		s.push_back("In 1st catch of g pre-throw");
		throw A();
	}
	catch(...){
		s.push_back("In 2nd catch of g pre-throw");
		throw; // re-throws the same original exception
	}
}

int basic_exception2(){

	try{
		g();
	}
	catch(std::logic_error& l){ // B is derived from logic_error
		s.push_back("In 1st catch of main");
	}
	catch(...){
		s.push_back("In 2nd catch of main");
	}

	for(const auto& elem: s)
		std::cout<<elem<<"\n";

	return 0;
}
