/*
 * member_function_pointers.cpp
 *
 *  Created on: Aug 9, 2019
 *      Author: akadar
 *
 *  A member function pointer holds the offset to the member function
 *  in the list of member functions of a class.
 */

#include <iostream>

// interface class
class big_cats{
public:
	big_cats(){
		count++;
	}
	virtual void noise() const = 0;
	virtual void bio() const = 0;
	static unsigned getCount(){
		return count;
	}
	virtual ~big_cats() {};
private:
	static unsigned count;
};
unsigned big_cats::count = 0;

// implementation class for Cheetah
class Cheetah: public big_cats{
public:
	Cheetah(std::string name_){
		std::cout<<name_<<" Cheetah born :)\n";
		name = name_;
		age = 0;
		count++;
	}
	void noise() const override{
		std::cout<<"Purrr ....\n";
	}
	void bio() const override{
		std::cout<<"I am "<<name<<".\n";
		std::cout<<"I am "<<age<<" years old.\n";
	}
	~Cheetah(){
		std::cout<<name<<" Cheetah dead :(\n";
	}
	// Recall static member functions cannot access non-static data members
	static unsigned getCount(){
		return count;
	}
private:
	std::string name;
	unsigned age;
	static unsigned count;
};
unsigned Cheetah::count = 0;

// implementation class for Leopard
class Leopard: public big_cats{
public:
	Leopard(std::string name_){
		std::cout<<name_<<" Leopard born :)\n";
		name = name_;
		age = 0;
		count++;
	}
	void noise() const override{
		std::cout<<"Purrr ....\n";
	}
	void bio() const override{
		std::cout<<"I am "<<name<<".\n";
		std::cout<<"I am "<<age<<" years old.\n";
	}
	~Leopard(){
		std::cout<<name<<" Leopard dead :(\n";
	}
	// Recall static member functions cannot access non-static data members
	static unsigned getCount(){
		return count;
	}
private:
	std::string name;
	unsigned age;
	static unsigned count;
};
unsigned Leopard::count = 0;

int main(){
	Cheetah c9("T1"), c10("T2");
	Leopard L9("X1"), L10("X2"), L11("X3");

	// Declaring derived_fptr a pointer to some member function of class Cheetah.
	// The member function must accept void and return void.
	// Note the strict syntax for declaring member function pointers.
	// return_type (className::*pointerName)(parameter types) cv-qualifiers
	void (Cheetah::*derived_fptr)(void) const;

	// Note the strict syntax for initializing member function pointers:
	// syntax &className::function_name
	derived_fptr = &Cheetah::noise;

	// Member function pointer is used together with an object of its class.
	// Note the strict syntax for calling member function pointers:
	// result = (object.*memberPointerName)(parameters)
	(c9.*derived_fptr)();



	// Polymorphism example
	// Initializing base class member function pointer.
	void (big_cats::*base_fptr)(void) const = &big_cats::noise;
	// Calling derived class member function using derived class object and base class pointer.
	(c9.*base_fptr)();



    // Function pointers to static member functions are done in the traditional
	// 'C' style because there is no object pointer for this call required.
	unsigned (*derived_fptr2)(void);
	derived_fptr2 = &Cheetah::getCount;
	std::cout<<"Cheetah count = "<<(*derived_fptr2)()<<"\n";


	unsigned (*base_fptr2)(void);
	base_fptr2 = &big_cats::getCount;
	std::cout<<"Big cats count = "<<(*base_fptr2)()<<"\n";

	return 0;
}
