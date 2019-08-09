/*
 * abstract_classes.cpp
 *
 *  Created on: Aug 9, 2019
 *      Author: akadar
 */

#include <iostream>
#include <ostream>

enum class RGB: char{
	red, blue, green
};

std::ostream& operator<<(std::ostream& os, const RGB& rbg_value){
	switch(rbg_value){
	case RGB::red: return os<<"Red";
	case RGB::blue: return os<<"Blue";
	case RGB::green: return os<<"Green";
	}
}

class shape{
public:
	shape(){}
	virtual double area() const = 0; // pure virtual function must be overridden
	virtual double perimeter() const = 0; // pure virtual function must be overridden
	virtual ~shape(){} // virtual destructor
private:
};

class color{
public:
	RGB getColor() const{
		return rgb_value;
	}
protected:
	RGB rgb_value;
};

class square: public shape, public color{
public:
	square(double x_, RGB rgb_value_): x{x_}{
		rgb_value = rgb_value_;
	}
	double area() const override {
		return x*x;
	}
	double perimeter() const override {
		return 4*x;
	}
private:
	double x;
};

// Uses shape interface class without having any knowledge of the implementation
void printShapeInfo(shape* s){
	std::cout<<"Area = "<<s->area()<<"\n";
	std::cout<<"Perimeter = "<<s->perimeter()<<"\n";
}

int abstract_classes()
{
	// Manipulation not using pointers
	//shape s; // Not allowed since shape is an abstract class
	square s1(3,RGB::red);
	std::cout<<"Area = "<<s1.area()<<"\n";
	std::cout<<"Perimeter = "<<s1.perimeter()<<"\n";
	std::cout<<"Color = "<<s1.getColor()<<"\n";

	std::cout<<"\n\n";

	// Manipulation using pointers
	shape* s; // Allowed
	s = new square(4,RGB::blue);
	printShapeInfo(s);
	delete s;
	return 0;
}
