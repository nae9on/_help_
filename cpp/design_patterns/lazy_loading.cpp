/*
 * lazy_loading.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: akadar
 *
 *  The idea of lazy loading is to defer object creation until demand.
 */

#include <iostream>
#include <vector>

class A{
public:
	A(){
		std::cout<<"Object of A constructed\n";
	}
	~A(){
		std::cout<<"Object of A de-constructed\n";
	}
	void printX() {
		std::cout<<"X = "<<X<<"\n";
	}
private:
	double X = 100;
};

template<typename T> class lazy_class{
public:
	lazy_class(): data{nullptr} {}
	T* operator->(){
		return getData();
	}
	T operator*(){
		return *getData();
	}
	~lazy_class(){
		if(data!=nullptr)
			delete data;
		data = nullptr;
	}
private:
	T* data;
	T* getData(){
		if(data==nullptr)
			data = new T;
		return data;
	}
};

int main(){

	// A vector with 10 elements created.
	std::vector<lazy_class<A>> lazy_vector(10);

	// Until this point, each element of the vector has its data = nullptr

	for (unsigned i=0; i<10; i+=2){
		// Memory for some elements (i=0,2,4,6,8) is allocated when the getData member
		// function is called for that element.
		lazy_vector[i]->printX();
	}

	return 0;
}
