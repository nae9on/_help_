/*
 * abstract_classes.cpp
 *
 *  Created on: Aug 9, 2019
 *      Author: akadar
 */

#include <iostream>
#include <ostream>
#include <memory>

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

/*
 *  1. A class with at least one pure virtual function is an abstract class.
 *  2. A pure virtual function is also sometimes called an abstract method.
 *  3. A pure virtual function must be overridden in a derived concrete class.
 *  4. A class with all abstract methods is a pure abstract or interface class.
 *  5. An abstract class should have a virtual destructor.
 */
class shape{
public:
	shape(){}
	virtual double area() const = 0;
	virtual double perimeter() const = 0;
	virtual ~shape(){}
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
	// Only manipulation using pointers is allowed since shape is an interface class.
	//shape s; // Error

	square s1(RGB::red,3);
	std::cout<<"Area = "<<s1.area()<<"\n";
	std::cout<<"Perimeter = "<<s1.perimeter()<<"\n";
	std::cout<<"Color = "<<s1.getColor()<<"\n";

	std::cout<<"\n";

	std::unique_ptr<shape> s(new square(RGB::blue,4));

	printShapeInfo(s.get());

	return 0;
}
