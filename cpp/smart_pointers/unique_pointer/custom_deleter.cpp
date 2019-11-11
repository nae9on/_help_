/*
 * custom_deleter.cpp
 *
 *  Created on: 11 Nov 2019
 *      Author: ahkad
 *
 *  When using default deleter (i.e. delete), std::unique_ptr objects are the same
 *  size as raw pointers.
 *
 *  When using a state-less functor or lambda with no-capture, std::unique_ptr objects
 *  incur no size penalty.
 *
 *  When using a state-full functor or lambda with value-capture, std::unique_ptr objects
 *  incur size penalty = size of stored state.
 *
 *  When using a lambda with reference-capture, std::unique_ptr objects incur size
 *  penalty by = 1 word.
 *
 *  References: Item 18, EMC++
 *
 */

#include <iostream>
#include <memory>

class X{};

// custom deleter using a functor
class fo{
public:
	void operator()(X* ptr){
		std::cout<<"In custom deleter using a functor\n";
		delete ptr;
	}
private:
	double data[100];
};

int custom_deleter(){

	// custom deleter using a state-less lambda
	auto lmb_sl = [](X* ptr){
		// do something
		std::cout<<"In custom deleter using a state-less lambda\n";
		delete ptr;
	};

	{
		std::unique_ptr<X,decltype(lmb_sl)> ptr_sl(new X, lmb_sl);
		std::cout<<"Size of ptr_sl = "<<sizeof(decltype(ptr_sl))<<"\n";
	}

	// custom deleter using a state-full lambda
	char data[100]{0};
	auto lmb_sf = [&data](X* ptr){
		// do something
		std::cout<<"In custom deleter using a state-full lambda\n";
		delete ptr;
	};

	{
		std::unique_ptr<X,decltype(lmb_sf)> ptr_sf(new X, lmb_sf);
		std::cout<<"Size of ptr_sf = "<<sizeof(decltype(ptr_sf))<<"\n";
	}

	// custom deleter using a functor
	{
		std::unique_ptr<X,fo> ptr_fo(new X, fo());
		std::cout<<"Size of ptr_fo = "<<sizeof(decltype(ptr_fo))<<"\n";
	}

	return 0;
}
