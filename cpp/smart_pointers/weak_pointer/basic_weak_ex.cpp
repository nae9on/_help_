/*
 * basic_weak_ex.cpp
 *
 *  Created on: 12 Nov 2019
 *      Author: ahkad
 *
 * A simple example to demonstrate the use of std::weak_ptr
 * stochastic <---> particle <--- convection
 *
 * Both stochastic and convection need particle (and therefore should own it in a shared ownership)
 * On the contrary, particle needs stochastic but does not want its ownership
 *
 * Note:
 * std::unique_ptr converts to std::shared_ptr which converts to std::weak_ptr
 * But, std::unique_ptr does not convert directly to std::weak_ptr
 *
 * The code below is free of delete and naked raw pointers.
 *
 * References:
 * Item 20, EMC++
 */

#include <iostream>
#include <memory>

class particle;

class stochastic{
public:
	stochastic(std::shared_ptr<particle> ptr_){
		ptr = ptr_;
		std::cout<<"ctor stochastic\n";
	}
	~stochastic(){std::cout<<"dtor stochastic\n";}
	std::shared_ptr<particle> ptr;
};

class particle{
public:

	// Not ok causes a cycle stochastic <----> particle
	//using my_smart_ptr = std::shared_ptr<stochastic>;

	// Ok causes no cycle
	using my_smart_ptr = std::weak_ptr<stochastic>;

	particle(){std::cout<<"ctor particle\n";}
	void setStochastic(my_smart_ptr str_){
		str = str_;
	}
	~particle(){std::cout<<"dtor particle\n";}
	my_smart_ptr str;
};


class convection{
public:
	convection(std::shared_ptr<particle> ptr_){
		ptr = ptr_;
		std::cout<<"ctor convection\n";
	}
	~convection(){std::cout<<"dtor convection\n";}
	std::shared_ptr<particle> ptr;
};

int basic_weak_ex(){

	// shared_ptr since both stochastic and convection needs its ownership
	std::shared_ptr<particle> ptr(new particle);

	// shared_ptr since particle needs it (although does not want its ownership)
	std::shared_ptr<stochastic> str(new stochastic(ptr));
	// std::weak_ptr<stochastic> str(new stochastic(ptr)); // Error

	ptr->setStochastic(str);

	// unique_ptr since no one needs ownership of convection
	std::unique_ptr<convection> ctr(new convection(ptr));

	return 0;
}
