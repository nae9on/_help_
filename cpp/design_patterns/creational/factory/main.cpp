/*
 * main.cpp
 *
 *  Created on: Oct 4, 2019
 *      Author: akadar
 *
 * Example illustrating how a Factory Method can be used for creating UI elements
 * without coupling the client code to concrete UI classes.
 *
 */

#include "button.h"

// Client/Creator class
class Dialog{
public:
	void render(){
		// Abstract button
		Button* okButton = createButton();
		okButton->render();
		okButton->onClick();
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

	Dialog* d1 = new WindowsDialog();
	d1->render();
	d1->render();
	delete d1;

	return 0;
}
