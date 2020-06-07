/*
 * basic_unique_ex.cpp
 *
 *  Created on: 11 Nov 2019
 *      Author: ahkad
 */

#include <iostream>
#include <memory>
#include <boost/type_index.hpp>
#include <vector>
#include <algorithm>

class X{
public:
	X():data{0}{++count; std::cout<<"ctor called\n";};
	X(int data_):data{data_}{++count; std::cout<<"ctor called for data = "<<data_<<"\n";}
	X(const X& x){
		data = x.data;
	}
	void outData()const{std::cout<<"output data = "<<data<<"\n";}
	static int getCount(){return count;}
	~X(){--count; std::cout<<"dtor called for data = "<<data<<"\n";}
private:
	int data;
	static int count;
};

int X::count = 0;

void scanvec(std::vector<std::unique_ptr<X>>& uptrvec){
    for(const auto& elem:uptrvec){
        if(elem==nullptr)
            std::cout<<"nullptr"<<"\t";
        else
            std::cout<<"notnullptr"<<"\t";
    }
    std::cout<<std::endl;
}

int basic_unique_ex(){

    // using raw pointers
	{
		auto rptr{new X(10)};
		std::cout<<boost::typeindex::type_id_with_cvr<decltype(rptr)>()<<"\n";
		X* ptr{rptr};
		std::cout<<"Size of raw pointer = "<<sizeof(decltype(ptr))<<"\n";
		ptr->outData();
		delete ptr;
	}

	std::cout<<"***************************\n";

	// ways to initialize unique_ptr's
	{
	    // 1. not recommended
	    X* xptr = new X(12);
	    std::unique_ptr<X> uptr(xptr);
	    //std::unique_ptr<X> uptr2(xptr); // disaster

	    // 2. recommended
	    auto uptr2{std::make_unique<X>(34)}; // Note requires c++14 support

	    // 3. ok
	    std::unique_ptr<X> uptr3(new X(56));

	    // 4. also ok
	    std::unique_ptr<X> uptr4(nullptr); // Note: it is set to nullptr when not initialized
	    //uptr4 = new X(789); // Error Implicit conversion from raw pointer to unique_ptr is not allowed
	    uptr4.reset(new X(78));
	    std::cout<<"End of block\n";
	}

	std::cout<<"***************************\n";

	// using unique pointer for exclusive ownership
	{
	    auto uptr1{std::make_unique<X>(10)};
	    std::unique_ptr<X> uptr2;
		std::cout<<"Size of unique_ptr = "<<sizeof(decltype(uptr1))<<"\n";

		// unique_ptr's are move only and cannot be copied
		//uptr2 = uptr1; // Error
		uptr2 = std::move(uptr1);
		if(uptr1==nullptr) std::cout<<"uptr1 is now nullptr\n";

		// unique_ptr is a wrapper around raw pointer and thus acts like one
		uptr2->outData();
		(*uptr2).outData();

		// moving around std::unique_ptr
		std::vector<std::unique_ptr<X>> uptrvec, uptrvec_copy;
		uptrvec.push_back(std::move(uptr1));
		uptrvec.push_back(std::move(uptr2));
		//std::copy(uptrvec.begin(), uptrvec.end(), std::back_inserter(uptrvec_copy)); // Error
		std::move(uptrvec.begin(), uptrvec.end(), std::back_inserter(uptrvec_copy));
		scanvec(uptrvec);
		scanvec(uptrvec_copy);
		std::cout<<"End of block\n";
	}

	std::cout<<"***************************\n";

	// Array form
	// std::array and std::vector should be preferred over array form
	// useful only when taking ownership of an array returned by a C-like API (Item 18, EMC++)
	{
		std::unique_ptr<X[]> uptr_ar(new X[3]);
		std::cout<<"Size of array form of unique_ptr = "<<sizeof(decltype(uptr_ar))<<"\n";
		//uptr_ar->outData(); // Error op* and op-> are not supported, only operator[] is supported
		std::cout<<"End of block\n";
	}

	std::cout<<"Current count = "<<X::getCount()<<"\n";

	return 0;
}
