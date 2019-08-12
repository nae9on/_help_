/*
 * singleton.cpp
 *
 *  Created on: Aug 12, 2019
 *      Author: akadar
 *
 *  A singleton design pattern is a type of creational design pattern used when
 *  an application needs one, and only one, instance of an object. Additionally,
 *  lazy initialization and global access are necessary.
 *
 *  Reference: https://sourcemaking.com/design_patterns/singleton
 */

#include <iostream>

class monotheism{
public:
	static monotheism* getGod(){
		if(god==nullptr){
			std::cout<<"Creating god\n";
			god = new monotheism;
		}
		return god;
	}
	size_t getFollowers(){
		return followers;
	}
	static void resetGod(){
		delete god;
		god = nullptr;
	}
private:
	monotheism(){
		followers = 1000000;
	}
	monotheism(monotheism&) = default; // private copy constructor so that it cannot be called from outside.
	monotheism& operator=(monotheism&) = default; // private copy assignment.
	size_t followers;
	static monotheism* god;
};

// Allocating and initializing class's static data member.
// The pointer is being allocated - not the object itself.
monotheism* monotheism::god = nullptr;

int singleton(){

	monotheism* God = monotheism::getGod();

	std::cout<<"Followers of only God are = "<<God->getFollowers()<<"\n";

    God->resetGod();

	return 0;
}
