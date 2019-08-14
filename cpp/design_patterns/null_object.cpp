/*
 * null_object.cpp
 *
 *  Created on: Aug 14, 2019
 *      Author: akadar
 *
 * Null object design pattern is a type of behavioral design pattern.
 *
 * A null object design pattern is useful when the absence of functionality represented
 * by null pointers is not desirable. A client code may not be tailored to handle
 * null pointers (as shown in the example below). In such cases, it is better to
 * represent the absence of functionality by a null object (not null pointer)
 * which provides access to functions that does nothing and at the same time makes
 * sure the client code does not break down.
 *
 * Reference: https://sourcemaking.com/design_patterns/null_object
 */

#include <iostream>
#include <vector>

using my_string = std::vector<std::string>;

// interface required by the client.
class hardwareInterface{
public:
	virtual my_string* getUsers() = 0;
	virtual void doSomething() = 0;
	virtual ~hardwareInterface(){}
};

// class implementing the hardware access functions defined by hardwareInterface class.
class embeddedHardware: public hardwareInterface{
public:
	embeddedHardware(){
		users.push_back("memory bus 0");
		users.push_back("memory bus 1");
	}
	my_string* getUsers(){
		return &users;
	}
	void doSomething(){
		std::cout<<"Enabling users:\n";
	}
private:
	my_string users;
};

// class hardwareNotAvailable inherits the hardwareInterface and defines
// a null object version to simulate how the actual hardware interface would work
// in the absence of a real hardware not available.
class hardwareNotAvailable: public hardwareInterface{
public:
	my_string* getUsers(){
		return &users;
	}
	void doSomething(){}
private:
	my_string users;
};

int null_object(){

	std::cout<<"In main\n";

	hardwareNotAvailable ha; // to simulate hardware which does not exist.
	//embeddedHardware ha; // when real hardware exists.

	// client code
	ha.doSomething();

	my_string* usr = ha.getUsers();
	for(auto ptr = usr->begin(); ptr!=usr->end(); ptr++)
		std::cout<<*ptr<<"\n";

	/*
	 * From this example we can see the advantage of the null object pattern.
	 * If the getUsers() function had returned a null or dangling pointer
	 * then the begin()/end() functions would have caused an exception in the
	 * client, however it returns an empty vector which does not cause an
	 * issue in the client.
	 *
	 * This is useful for testing a system which does not have all the available
	 * hardware. In that case we could use an empty object to represent the
	 * missing hardware but still test the communication with the interface design.
	 *
	 */

	std::cout<<"End of main\n";

	return 0;
}
