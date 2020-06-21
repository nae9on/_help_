/*
 * button.h
 *
 *  Created on: Oct 4, 2019
 *      Author: akadar
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <iostream>

class Button{ // Product interface class
public:
	virtual void render() const=0;
	virtual void onClick() const=0;
	virtual ~Button(){}
private:
	// No data members!
};

class WindowsButton: public Button{
public:
	WindowsButton(){}
	void render() const override{
		std::cout<<"Render Windows button\n";
	}
	void onClick() const override{
			std::cout<<"Do something on clicking Windows button\n";
	}
	~WindowsButton(){}
};

class LinuxButton: public Button{
public:
	LinuxButton(){}
	void render() const override{
		std::cout<<"Render Linux button\n";
	}
	void onClick() const override{
			std::cout<<"Do something on clicking Linux button\n";
	}
	~LinuxButton(){}
};

#endif /* BUTTON_H_ */
