/*
 * object_adapter_pattern.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: akadar
 *
 *  An object adapter pattern is a type of structural design pattern. These design
 *  patterns are all about class and object composition. Within this category, there
 *  are two sub-categories a) structural class-creation patterns which use inheritance
 *  to compose interfaces and b) structural object-creation patterns which compose objects
 *  to obtain new functionality.
 *
 *  object adapter pattern is a type of structural object-creation pattern.
 *
 *  The object adapter pattern is very similar to the class adapter pattern. Both the design
 *  patterns are used to implement a adapter class that can "impedance match" the client
 *  interface to a legacy implementation class. The main difference is that instead of inheriting
 *  the adaptee class, the adapter class allocates object instances of adaptee class to invoke
 *  the relevant methods.
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
class circle: public circleInterface{
public:
	circle(double r): radius{r}, e{ellipse(r,r)} {
		std::cout<<"Circle object constructed\n";
	}
	// Mapping the client interface to the adaptee interface.
	double getArea(){
		return e.getEllipseArea();
	}
	~circle(){
		std::cout<<"Circle object de-constructed\n";
	}
private:
	double radius;
	ellipse e; // This is composition
};

int object_adapter_pattern(){
	// Creating adaptor object
	circle c(5);
	std::cout<<"Area of circle = "<<c.getArea()<<"\n";
	return 0;
}
