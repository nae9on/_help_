/*
 * singleton.cpp
 *
 *  Created on: Aug 12, 2019
 *      Author: akadar
 *
 *  Warning! the below pattern is strictly inferior to the pattern described on SO and C++ Core Guidelines
 *  https://stackoverflow.com/questions/1463707/c-singleton-vs-global-static-object
 *  https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Ri-singleton
 *
 *  Use this instead https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
 *
 *  A singleton design pattern is a type of creational design pattern.
 *  It is used in the following two scenarios:
 *  1. When an application needs one and only one instance of a class.
 *  2. When an application needs global access to that instance.
 *
 *  Since the singleton pattern solves two problems at the same time, it is
 *  also considered to violate Single Responsibility Principle.
 *
 *  Warning: Avoid Singleton's, the best singleton is described here
 *  https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Ri-singleton
 *
 *  References:
 *  https://sourcemaking.com/design_patterns/singleton
 *  https://en.wikipedia.org/wiki/Singleton_pattern
 */

#include <iostream>

/*
 * Consider the following scenario, suppose we are talking to a embedded
 * application that has hardware constraints. To avoid overloading the
 * hardware we only want to have a single instance of the hardware.
 *
 * Note: A similar analogy also applies to a database connection.
 *
 */

class embeddedHardware{
public:
	/*
	 * The following member function ensures that the single object will not be created
	 * until someone requests an instance of it. This is called lazy initialization.
	 * It also provides only one point of entry to access/manipulate the Singleton resource.
	 */
	static embeddedHardware* getHardwareAccess(){
		if(hardware==nullptr){
			std::cout<<"Mounting hardware.\n";
			hardware = new embeddedHardware;
			// Note: special care must be taken in a multi-threaded environment.
		}
		return hardware;
	}

	static void resetHardware(){
		if(hardware!=nullptr){
			std::cout<<"Freeing resources.\n";
			delete hardware;
			hardware = nullptr;
		}
	}

	void hardware_info(){
		std::cout<<hardware_name<<" mounted\n";
	}

	// Note that the destructor cannot call resetHardware to avoid recursive loop.
	~embeddedHardware(){}

private:

	// private members so that they cannot be called from outside the class
	embeddedHardware(){
		hardware_name = "ATMEGA 16";
	}
	embeddedHardware(const embeddedHardware&) = default;
	embeddedHardware& operator=(const embeddedHardware&) = default;

	// static member exists even if no objects of the class have been defined.
	// There is only one instance of the static data member in the entire program with static storage duration
	static embeddedHardware* hardware;
	std::string hardware_name;
};

// Allocating and initializing class's static data member.
// The pointer is being allocated - not the object itself.
embeddedHardware* embeddedHardware::hardware = nullptr;

int singleton(){

	embeddedHardware* Resource = embeddedHardware::getHardwareAccess();

	Resource->hardware_info();

	embeddedHardware::resetHardware(); // This is required to free hardware. What if this is forgotton? Bad design!

	return 0;
}
