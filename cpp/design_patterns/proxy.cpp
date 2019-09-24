/*
 * proxy.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: akadar
 *
 *  A proxy design pattern is a type of structural design pattern.
 *
 *  The proxy design pattern is used to communicate with a real object that
 *  for some reason cannot be communicated with directly. These reasons could
 *  be due to hardware limitations or to protect the real component from undue
 *  complexity. For this reason a proxy object is placed in between the
 *  client and the real object. The proxy object instantiates the real object
 *  the first time the client makes a request to the proxy. The proxy remembers
 *  the identity of this real object, and simply forwards directly to the
 *  encapsulated real object for all future calls.
 *
 *  A shared_pointer class is an example of proxy pattern.
 *
 *  Reference: https://sourcemaking.com/design_patterns/proxy
 *
 */

#include <iostream>

// interface required by the client.
class hardwareInterface{
public:
	virtual short getNumThreads() = 0;
	virtual void setNumThreads(short) = 0;
	virtual ~hardwareInterface(){}
};

/*
 * Consider the following scenario, suppose we are talking to a embedded
 * application that has hardware constraints. To avoid overloading the
 * hardware we only want to have a single instance of the hardware.
 */
// implementation of the singleton hardware class (refer singleton.cpp)
class embeddedHardware: public hardwareInterface{
public:
	static embeddedHardware* getHardwareAccess(){
		if(hardware==nullptr){
			std::cout<<"Mounting hardware\n";
			hardware = new embeddedHardware;
		}
		return hardware;
	}
	short getNumThreads(){
		return numThreads;
	}
	void setNumThreads(short numThreads_){
		numThreads = numThreads_;
	}
	static void resetHardware(){
		if(hardware!=nullptr){
			std::cout<<"Freeing resources.\n";
			delete hardware;
			hardware = nullptr;
		}
	}
private:
	embeddedHardware(){
		numThreads = 1;
	}
	embeddedHardware(embeddedHardware&) = default;
	embeddedHardware& operator=(embeddedHardware&) = default;
	short numThreads;
	static embeddedHardware* hardware;
};

// already defined in singleton.cpp
//embeddedHardware* embeddedHardware::hardware = nullptr;

// proxy or surrogate class which provides access to the singleton instance of the real class.

class embeddedProxy: public hardwareInterface{
public:
	embeddedProxy(): hardware{nullptr} {}

	embeddedHardware* getHardwareAccess(){

		// Receiver embeddedProxy delegates the call to the real class.
		// Also an example of Lazy loading.
		// Often the "surrogate" object checks that the caller has the access permissions
		// required prior to forwarding the request to the real object.
		if(hardware==nullptr){
			hardware = embeddedHardware::getHardwareAccess();
		}

		return hardware;

	}

	short getNumThreads(){
		return hardware->getNumThreads();
	}

	void setNumThreads(short numThreads_){
		/*
		 * Implement some logic to limit max no of threads to 4. In this way proxy
		 * design pattern allows distributed, controlled, or intelligent access
		 * to the actual resource.
		 */
		if(numThreads_>4){
			std::cout<<"Requested threads exceed 4\n";
			std::cout<<"Setting number of threads to 4\n";
			hardware->setNumThreads(4);
		}
		else
			hardware->setNumThreads(numThreads_);
	}

	~embeddedProxy(){
		hardware->resetHardware();
	}

private:
	embeddedHardware* hardware;
};

int proxy(){

	// embeddedHardware eh; // Error

	embeddedProxy ep1;
	std::cout<<ep1.getHardwareAccess()<<"\n";
	std::cout<<"Num threads = "<<ep1.getNumThreads()<<"\n";

	ep1.setNumThreads(8);

	embeddedProxy ep2; // provides access to the same hardware as ep1
	std::cout<<ep2.getHardwareAccess()<<"\n";
	std::cout<<"Num threads = "<<ep2.getNumThreads()<<"\n";

	return 0;
}
