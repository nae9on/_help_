/*
 * main.cpp
 *
 *  Created on: Oct 4, 2019
 *      Author: akadar
 *
 * A factory design pattern is a creational design pattern that provides an interface for
 * creating objects in a superclass, but allows subclasses to alter the type of objects that
 * will be created.
 *
 * Example illustrating how a Factory Method can be used for creating UI elements
 * without coupling the client code to concrete UI classes.
 *
 */

#include "button.h"
#include "UI.h"
#include <memory>

class WindowsUI: public UI{
public:
	WindowsUI(){}
	// Overrides the Factory Method to return a different product.
	std::unique_ptr<Button> createButton() const override{
		//return std::unique_ptr<Button>(new WindowsButton());
		return std::make_unique<WindowsButton>();
		// The two statements above are equivalent? Which one is better?
		// See stackoverflow
		// Why does unique_ptr<Derived> implicitly cast to unique_ptr<Base>?
	}
	~WindowsUI(){}
};

class LinuxUI: public UI{
public:
	LinuxUI(){}
	std::unique_ptr<Button> createButton() const override{
	    return std::unique_ptr<Button>(new LinuxButton());
	}
	~LinuxUI(){}
};

int main_factory(){//main_factory

	std::unique_ptr<UI> d1(new WindowsUI());
	d1->doSomething();

	std::unique_ptr<UI> d2(new LinuxUI());
	d2->doSomething();

	std::cout<<"end of main"<<std::endl;

	return 0;
}
