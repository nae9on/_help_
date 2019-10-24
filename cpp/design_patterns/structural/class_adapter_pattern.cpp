/*
 * class_adapter_pattern.cpp
 *
 *  Created on: Aug 12, 2019
 *      Author: akadar
 *
 *  A class adapter pattern is a type of structural design pattern. These design
 *  patterns are all about class and object composition. Within this category, there
 *  are two sub-categories a) structural class-creation pattern which use inheritance
 *  to compose interfaces and b) structural object-creation pattern which compose objects
 *  to obtain new functionality.
 *
 *  class adapter pattern is a type of structural class-creation pattern.
 *
 *  It can be used to adapt a legacy interface into a desired client interface. How it works?
 *  1. Adapter class acts as a wrapper or modifier of an existing legacy class. It provides a
 *  different or translated view of that class required by the client.
 *  2. Client calls methods on the Adapter object which redirects them into calls to
 *  the legacy component.
 *
 *  Similar to a class adapter pattern is object adapter pattern. Instead of the adapter class
 *  inheriting the adaptee, in this pattern the adapter contains an explicit instance of the
 *  adaptee class.
 *
 *  Reference: https://sourcemaking.com/design_patterns/adapter
 */
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

// Adaptee: legacy class that needs to adapt. It also provides the main functionality.
class ellipse{
public:
	ellipse(double a, double b): major{a}, minor{b} {
		std::cout<<"Ellipse object constructed\n";
	}
	~ellipse(){
		std::cout<<"Ellipse object de-constructed\n";
	}
protected:
	double getEllipseArea(){
		return M_PI*major*minor;
	}
private:
	double major;
	double minor;
};

// Interface: class that defines the client interface.
class circleInterface{
public:
	virtual double getArea() = 0;
	virtual ~circleInterface(){}
};

// Adapter: wrapper class that can "impedance match" the client interface to the adaptee interface.
// Adapter class implements the client interface.
class circle: public circleInterface, public ellipse{ // Multiple inheritance
public:
	circle(double r): ellipse(r,r), radius{r} {
		std::cout<<"Circle object constructed\n";
	}
	// Mapping the client interface to the adaptee interface.
	double getArea(){
		return getEllipseArea();
	}
	~circle(){
		std::cout<<"Circle object de-constructed\n";
	}
private:
	double radius;
};

int class_adapter_pattern(){
	// Creating adaptor object
	circle c(5);
	std::cout<<"Area of circle = "<<c.getArea()<<"\n";
	return 0;
}
