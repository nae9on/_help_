/*
 * const_revision.cpp
 *
 *  Created on: Aug 20, 2019
 *      Author: akadar
 */

#include <iostream>

class Test{
public:
	Test(){ // cannot be const
		p = 10;
		pmut = 100;
	}
	int get() const{
		pmut = 100; // OK since pmut is mutable
		ps = 100; // OK since ps is static
		return p;
	}
	void set(int p_){
		p = p_;
	}
	int getpmut(){
		return pmut;
	}
	void setpmut(int pmut_) const{
		pmut = pmut_;
	}
	static int getps(){
		//pmut = 100; // Error non-static members cannot be accessed in static member functions.
		return ps;
	}
	~Test(){} // cannot be const
private:
	int p;
	mutable int pmut;
	static int ps;
};

int Test::ps = 7;

int const_revision(){

	int a = 10;

	//const int x; x = 10; // Error
	const int x1 = 10;
	const int x2 = 10;
	const int* y = &x1;
	y = &x2;
	//*y = *y + 1; // Error

	const int* const z = &x1;
	//z = &x2; // Error
	//*z = *z + 1; // Error

	Test t1;
	int p1 = t1.get();
	int pmut = t1.getpmut();
	t1.set(100);

	const Test t2;
	int p2 = t2.get();
	//int p2mut = t2.getpmut(); // Error
	//t2.set(100); //Error
	t2.setpmut(100); // OK

	int ps = Test::getps();

	(void) a;
	(void) y;
	(void) z;
	(void) p1;
	(void) pmut;
	(void) p2;
	(void) ps;

	std::cout<<"End of main";

	return 0;
}
