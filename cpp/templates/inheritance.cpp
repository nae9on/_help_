/*
 * inheritance.cpp
 *
 *  Created on: Jul 25, 2019
 *      Author: akadar
 */

#include <iostream>
#include <string>
#include <typeinfo>

// Parameterized type Point
template<typename T = double, short attr_ = 2>
class Point {
public:
	Point(): px(0), py(0), attr(0) {
		std::cout << "Default Point object constructor called" << "\n";
	}
	Point(T x, T y) : px(x), py(y), attr(attr_) {
		std::cout << "Point object constructor called" << "\n";
	}
	void printPoint() {
		std::cout << "X " << px << " Y " << py;
	}
	T getpx() {
		return px;
	}
	T getpy() {
		return py;
	}
	void setpx(T px_) {
		px = px_;
	}
	void setpy(T py_) {
		py = py_;
	}
private:
	T px;
	T py;
	short attr;

};

// Parameterized type Point3D (special case Z coordinate can be of another type)
template<typename T = double, typename T2 = double, short attr_ = 3>
class Point3D : public Point<T,2> {
public:
	Point3D(T x, T y, T2 z) : pz(z), attr(attr_) {
		Point<T,2>::setpx(x);
		Point<T,2>::setpy(y);
		std::cout << "Point3D object constructor called" << "\n";
	}
	void printPoint() {
		Point<T,2>::printPoint();
		std::cout << " Z " << pz << "\n";
	}
	T getpz() {
		return pz;
	}
	void setpz(T pz_) {
		pz = pz_;
	}
private:
	T2 pz;
	short attr;
};

int main_inheritance() {

	Point<int> P2D(5,5);
	Point3D<double, unsigned, 3> P3D(99.9,99.9,10);

	std::cout << "Point in 3D is ";
	P3D.printPoint();

	std::cout<<"\n";

	return 0;
}
