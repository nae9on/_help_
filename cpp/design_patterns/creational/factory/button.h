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
	// Interface classes do not have constructors.
	virtual void render() const =0;
	virtual void onClick()const =0;
	virtual ~Button(){} // virtual destructor is a must
private:
	// No data members!
};

class WindowsButton: public Button{
public:
	WindowsButton(){}
	void render() const override{
		std::cout<<"Render windows button\n";
	}
	void onClick() const override{
			std::cout<<"Do something on clicking windows button\n";
	}
	~WindowsButton(){}
};

class HTMLButton: public Button{
public:
	HTMLButton(){}
	void render() const override{
		std::cout<<"Render HTML button\n";
	}
	void onClick() const override{
			std::cout<<"Do something on clicking HTML button\n";
	}
	~HTMLButton(){}
};

#endif /* BUTTON_H_ */
