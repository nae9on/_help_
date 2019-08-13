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

/*
 * Consider the following scenario, suppose we are talking to a embedded
 * application that has hardware constraints. To avoid overloading the
 * hardware we only want to have a single instance of the hardware.
 */

class embeddedHardware{
public:
	// The following member function ensures that the single object
	// will not be created until someone requests an instance of it.
	// This is an example of lazy loading.
	static embeddedHardware* getHardwareAccess(){
		if(hardware==nullptr){
			std::cout<<"Mounting hardware\n";
			hardware = new embeddedHardware;
		}
		return hardware;
	}
	size_t getPorts(){
		return ports;
	}
	static void resetHardware(){
		delete hardware;
		hardware = nullptr;
	}
private:
	embeddedHardware(){
		ports = 10;
	}
	embeddedHardware(embeddedHardware&) = default; // private copy constructor so that it cannot be called from outside.
	embeddedHardware& operator=(embeddedHardware&) = default; // private copy assignment.
	size_t ports;
	static embeddedHardware* hardware;
};

// Allocating and initializing class's static data member.
// The pointer is being allocated - not the object itself.
embeddedHardware* embeddedHardware::hardware = nullptr;

int singleton(){

	embeddedHardware* Resource = embeddedHardware::getHardwareAccess();

	std::cout<<"Ports of embedded hardware are = "<<Resource->getPorts()<<"\n";

    Resource->resetHardware();

	return 0;
}
