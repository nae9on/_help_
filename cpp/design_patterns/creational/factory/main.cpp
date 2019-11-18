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
#include <memory>

// Client/Creator class
class Dialog{
public:
	void render(){
		// Abstract button
		Button* okButton = this->createButton();
		okButton->render();
		okButton->onClick();
		std::cout<<"\n";
	}

	/*
	 * 1. Factory Method can be abstract or may return a default product.
	 * 2. It does not have to create new products all the time and can return objects
	 * from a cache, an object pool, or another source.
	 * 3. The return type of the Factory Method should be the same as the product interface.
	 */
	virtual Button* createButton()=0;

	virtual ~Dialog(){}
};

class WindowsDialog: public Dialog{
public:
	WindowsDialog(){
		B = new WindowsButton();
	}

	// Overrides the Factory Method to return a different product.
	Button* createButton() override{
		return B;
	}

	~WindowsDialog(){
		delete B;
	}

private:
	Button* B;
};

class WebDialog: public Dialog{
public:
	WebDialog(){
		B = new HTMLButton();
	}

	Button* createButton() override{
		return B;
	}

	~WebDialog(){
		delete B;
	}

private:
	Button* B;
};

int factory(){

	std::unique_ptr<Dialog> d1(new WindowsDialog());
	d1->render();

	std::unique_ptr<Dialog> d2(new WebDialog());
	d2->render();

	return 0;
}
