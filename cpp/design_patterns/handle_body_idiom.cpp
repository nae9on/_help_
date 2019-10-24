/*
 * handle_body_idiom.cpp
 *
 *  Created on: Aug 12, 2019
 *      Author: akadar
 *
 *  A group of design patterns, in which the implementation of something (the "body")
 *  is separated from its interface by means of a level of indirection (the "handle")
 *  are said to follow the handle/body idiom.
 *
 *  For example, the adapter design pattern uses the handle/body idiom when wrapping a
 *  legacy class to impedance match a client interface class.
 *
 *  How to realize handle/body idiom?
 *  1. Split a design class into two implementation classes.
 *  2. One takes on the role of an identifier and presents the class interface to the user.
 *     We call this first class the handle.
 *  3. The other class embodies the implementation and is called the body.
 *  4. The handle forwards member function invocations to the body.
 */

#include <iostream>
#include <vector>
#include <cmath>

// Body
template<typename T> class sets{
public:
	sets(){}
	void addElem(T elem_){
		elem.push_back(elem_);
	}
	size_t getPowerSetCount(){
		return std::pow(2,elem.size());
	}
private:
	std::vector<T> elem;
};

// Handle
template<typename T> class setInterface{
public:
	setInterface(): s{new sets<T>} {}
	void addSetElem(T elem_){
		s->addElem(elem_);
	}
	size_t getSetCount(){
		return s->getPowerSetCount();
	}
	~setInterface(){
		delete s;
	}
private:
	sets<T>* s;
};

int handle_body_idiom(){
	setInterface<int> s1;
	s1.addSetElem(1);
	s1.addSetElem(2);
	s1.addSetElem(3);
	std::cout<<"Set count = "<<s1.getSetCount();
	return 0;
}
