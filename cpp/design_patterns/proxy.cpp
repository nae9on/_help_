/*
 * proxy.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: akadar
 */

#include <iostream>

class hardwareInterface{
public:
	virtual size_t getPorts() = 0;
	virtual std::string getBarcode() = 0;
	virtual ~hardwareInterface(){}
};

class embeddedHardware: public hardwareInterface{
public:
	embeddedHardware(){
		ports = 10;
	}
	size_t getPorts(){
		return ports;
	}
	std::string getBarcode(){
		return barcode;
	}
private:
	size_t ports;
	std::string barcode;
};

class embeddedProxy: public hardwareInterface{
public:
	embeddedHardware* getHardwareAccess(){
		if(hardware==nullptr){
			std::cout<<"Mounting hardware\n";
			hardware = new embeddedHardware;
		}
		return hardware;
	}
	size_t getPorts(){
		return hardware->getPorts();
	}
	std::string getBarcode(){
		return hardware->getBarcode();
	}
	void resetHardware(){
		delete hardware;
		hardware = nullptr;
	}
private:
	embeddedProxy(){
		hardware = nullptr;
	}
	embeddedProxy(embeddedProxy&) = default; // private copy constructor so that it cannot be called from outside.
	embeddedProxy& operator=(embeddedProxy&) = default; // private copy assignment.
	embeddedHardware* hardware;
};

int main(){

	embeddedProxy ep;

	return 0;
}


