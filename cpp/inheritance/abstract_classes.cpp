/*
 * abstract_classes.cpp
 *
 *  Created on: Aug 9, 2019
 *      Author: akadar
 */

#include <iostream>
#include <ostream>

enum class RGB: char{
	red, blue, green, white
};

std::ostream& operator<<(std::ostream& os, const RGB& rbg_value){
	switch(rbg_value){
	case RGB::red: return os<<"Red";
	case RGB::blue: return os<<"Blue";
	case RGB::green: return os<<"Green";
	default: return os<<"Green";
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
	color() {
		rgb_value = RGB::white;
	}
	color(RGB rgb_value_){
		rgb_value = rgb_value_;
	}
	RGB getColor() const{
		return rgb_value;
	}
protected:
	RGB rgb_value;
};

class square: public shape, public color{
public:
	square(RGB rgb_value_, double x_): color(rgb_value_), x{x_}{
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

// Uses shape interface class without having any knowledge of the shape implementation
void printShapeInfo(shape* s){
	std::cout<<"Area = "<<s->area()<<"\n";
	std::cout<<"Perimeter = "<<s->perimeter()<<"\n";
}

int abstract_classes()
{
	// Manipulation not using pointers
	//shape s; // Not allowed since shape is an abstract/interface class
	square s1(RGB::red,3);
	std::cout<<"Area = "<<s1.area()<<"\n";
	std::cout<<"Perimeter = "<<s1.perimeter()<<"\n";
	std::cout<<"Color = "<<s1.getColor()<<"\n";

	std::cout<<"\n\n";

	// Manipulation using pointers
	shape* s; // Allowed
	s = new square(RGB::blue,4);
	printShapeInfo(s);
	delete s;
	return 0;
}
