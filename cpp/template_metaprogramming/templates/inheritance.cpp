/*
 * inheritance.cpp
 *
 *  Created on: Jul 25, 2019
 *      Author: akadar
 *
 *  Simple example to demonstrate non-template class member functions
 *  and their use in a derived class.
 */

#include <iostream>
#include <string>

using uchar = unsigned char;

// Parameterized type Point2D
template<typename T = double>
class Point2D {
public:
	Point2D(): px{0}, py{0} {
		std::cout << "Default Point2D object constructor called" << "\n";
	}
	Point2D(T x, T y) : px{x}, py{y} {
		std::cout << "Point2D object constructor called" << "\n";
	}
	void printPoint() {
		std::cout << "x " << px << " y " << py;
	}
	T getpx() {
		return px;
	}
	T getpy() {
		return py;
	}
	void setpx(T px_);
	void setpy(T py_);

private:
	T px;
	T py;
};

// class member functions are defined like function templates if
// they are defined outside the class template
// Note no default arguments are used here (syntax error with default arguments)
template<typename T> void Point2D<T>::setpx(T px_) {
	px = px_;
}

template<typename T> void Point2D<T>::setpy(T py_) {
	py = py_;
}

// Parameterized type Point3D (special case z coordinate can be of another type)
// Useful for example when x and y must be higher precision double while z can be float
template<typename T1 = double, typename T2 = float>
class Point3D : public Point2D<T1> {
public:
	Point3D(T1 x, T1 y, T2 z): Point2D<T1>(x,y), pz{z} {
		std::cout << "Point3D object constructor called" << "\n";
	}
	void printPoint() {
		Point2D<T1>::printPoint();
		std::cout << " z " << pz << "\n";
	}
	T2 getpz();
	void setpz(T2 pz_) {
		pz = pz_;
	}
private:
	T2 pz;
};

template<typename T1, typename T2>
T2 Point3D<T1,T2>::getpz() {
	return pz;
}

int main_inheritance() {

	Point2D<> P2D(0.0,0.0);
	Point3D<> P3D(0.0,0.0,10);

	std::cout << "Point in 3D is ";
	P3D.printPoint();

	std::cout<<"\n";

	return 0;
}
