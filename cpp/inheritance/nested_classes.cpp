/*
 * nested_classes.cpp
 *
 *  Created on: Aug 12, 2019
 *      Author: akadar
 *
 *  Nested classes can be useful if we want to hide the implementation of
 *  something in the enclosing class. This enables us to change it later
 *  on without worrying about breaking any dependencies users have constructed
 *  around the enclosing class.
 */

#include <iostream>
#include <ostream>

class complexPlane{
private:
	/*
	 * Nested class is defined as private, this means only friend classes
	 * would be able to see it. So we could make changes to the implementation
	 * and any classes that include the Enclosing class would not be affected.
	 */
	class point{
	public:
		point(): real{0}, imag{0} {}
		point(double r, double i): real{r}, imag{i} {}
		double getReal() const {return real;}
		double getImag() const {return imag;}
		void set(double real_, double imag_){
			real = real_;
			imag = imag_;
		}
		friend bool operator<(const point& p1, const point& p2){
			if (p1.getReal()<p2.getReal() && p1.getImag()<p2.getImag())
				return true;
			else
				return false;
		}
		friend bool operator>(const point& p1, const point& p2){
			if (p1.getReal()>p2.getReal() && p1.getImag()>p2.getImag())
				return true;
			else
				return false;
		}
		// Example to show that we can access the members of the enclosing
		// class from within the nested class.
		void printNested(const complexPlane& c){
			std::cout<<"Origin is ("<<c.getOrigin().getReal()
					<<","<<c.getOrigin().getImag()<<")\n";
		}
	private:
		double real;
		double imag;
	};

public:
	complexPlane(double x1, double y1, double x2, double y2, double x3, double y3){
		origin.set(x1,y1);
		loweLeft.set(x2,y2);
		upperRight.set(x3,y3);
	}
	bool inOut(double x, double y) const{
		point p(x,y);
		if(p<upperRight && p>loweLeft)
			return true;
		else
			return false;
	}
	void printEnclosing() {
		// Note the use of this pointer
		origin.printNested(*this);
	}
	point getOrigin() const{
		return origin;
	}
private:
	point origin;
	point loweLeft;
	point upperRight;
};

int nested_classes(){
	complexPlane plane(0, 0, -4, -4, 4, 4);
	if(plane.inOut(-3,-3))
		std::cout<<"Point is In plane\n";
	else
		std::cout<<"Point is Out of plane\n";
	plane.printEnclosing();
	return 0;
}
