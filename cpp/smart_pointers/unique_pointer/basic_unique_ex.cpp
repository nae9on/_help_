/*
 * basic_unique_ex.cpp
 *
 *  Created on: 11 Nov 2019
 *      Author: ahkad
 */

#include <iostream>
#include <memory>
#include <boost/type_index.hpp>

class X{
public:
	X():data{0}{++count; std::cout<<"ctor called\n";};
	X(int data_):data{data_}{++count; std::cout<<"ctor called\n";}
	X(const X& x){
		data = x.data;
	}
	void outData()const{std::cout<<"data = "<<data<<"\n";}
	static int getCount(){return count;}
	~X(){--count; std::cout<<"dtor called\n";}
private:
	int data;
	static int count;
};

int X::count = 0;

int basic_unique_ex(){

	// using C++98 style new and delete
	{
		auto void_ptr = new X(10);
		std::cout<<boost::typeindex::type_id_with_cvr<decltype(void_ptr)>()<<"\n";
		X* ptr{void_ptr};
		std::cout<<"Size of raw pointer = "<<sizeof(decltype(ptr))<<"\n";
		ptr->outData();
		delete ptr;
	}

	// using smart pointers
	{
		std::unique_ptr<X> sptr(nullptr);
		//sptr = new X(10); // Error implicit conversion from raw to unique_ptr not allowed
		sptr.reset(new X(10));
		std::cout<<"Size of unique_ptr = "<<sizeof(decltype(sptr))<<"\n";
		sptr->outData();
		(*sptr).outData();
	}

	std::cout<<"***************************\n";

	// Array form
	// std::array and std::vector should be preferred over array form
	// useful only when taking ownership of an array returned by a C-like API (Item 18, EMC++)
	{
		std::unique_ptr<X[]> sptr_ar(new X[3]);
		std::cout<<"Size of array form of unique_ptr = "<<sizeof(decltype(sptr_ar))<<"\n";
		//sptr_ar->outData(); // Error op* and op-> are not supported
	}

	std::cout<<"Current count = "<<X::getCount()<<"\n";

	return 0;
}
