/*
 * proxy.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: akadar
 *
 *  The proxy design pattern is used to communicate with another object that
 *  for some reason cannot be communicated with directly. These reasons could
 *  be due to hardware limitations or maybe the proxy needs to perform some
 *  logic before interacting with the other object. For whatever reason the
 *  proxy is placed in between the client and the final destination for the
 *  communication.
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
// implementation of the singleton hardware class.
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
		delete hardware;
		hardware = nullptr;
	}
private:
	embeddedHardware(){
		numThreads = 1;
	}
	embeddedHardware(embeddedHardware&) = default; // private copy constructor so that it cannot be called from outside.
	embeddedHardware& operator=(embeddedHardware&) = default; // private copy assignment.
	short numThreads;
	static embeddedHardware* hardware;
};

// already defined in another .cpp
//embeddedHardware* embeddedHardware::hardware = nullptr;

// proxy class which provides access to the singleton instance of the embeddedHardware class.
class embeddedProxy: public hardwareInterface{
public:
	embeddedProxy(): hardware{nullptr} {}
	embeddedHardware* getHardwareAccess(){
		if(hardware==nullptr){
			hardware = embeddedHardware::getHardwareAccess();
		}
		return hardware;
	}
	short getNumThreads(){
		return hardware->getNumThreads();
	}
	void setNumThreads(short numThreads_){
		// implement some logic to limit max no of threads to 4.
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
