/*
 * scope_guard.cpp
 *
 *  Created on: Jul 18, 2019
 *      Author: akadar
 */

/* This example demonstrates the use of exceptions for setting a scope guard.
 * How to ensure vectors v0, v1, v2, .... vn etc are either all updated or none.
 */

#include <iostream>
#include <vector>

using vint = std::vector<int>;

template <typename T> class scope_guard{
public:
	void set(){
		lock = true;
	}
	void release(){
		lock=false;
		std::cout<<"Lock released on "<<id<<"\n";
	}
	scope_guard(T* v_){
		v = v_;
		set();
		id = counter;
		counter++;
		std::cout<<"Lock set on "<<id<<"\n";
	}
	~scope_guard(){
		if(lock) {
			v->pop_back();
			std::cout<<"push_back called on "<<id<<"\n";
		}
	}
private:
	static unsigned counter;
	unsigned id{0};
	bool lock;
	T* v;
};

template <typename t> unsigned scope_guard<t>::counter=0;

int main_scope(){

	vint v0 = {1,2,3}; // initial content of v0
	vint v1 = {11,12,13};
	vint v2 = {101,102,103};

	try{
		v0.push_back(4);
		scope_guard<vint> s0(&v0); // set a guard around v0

		v1.push_back(14);
		scope_guard<vint> s1(&v1); // set a guard around v1

		throw std::bad_alloc(); // to imitate as if v2.push_back() has failed

		v2.push_back(104);
		scope_guard<vint> s2(&v2); // set a guard around v2

		s0.release();
		s1.release();
		s2.release();
	}
	catch(std::exception& e){
		std::cout<<"push_back unsuccessful, unwinding call stack\n";
		std::cout << e.what() << "\n";
	}

	std::cout<<"content of v0 = ";	for (const auto& e:v0) std::cout<<e<<" "; std::cout<<"\n";
	std::cout<<"content of v1 = ";	for (const auto& e:v1) std::cout<<e<<" "; std::cout<<"\n";
	std::cout<<"content of v2 = ";	for (const auto& e:v2) std::cout<<e<<" "; std::cout<<"\n";

	return 0;
}
