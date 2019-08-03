/*
 * multi_dim_container.cpp
 *
 *  Created on: Aug 1, 2019
 *      Author: akadar
 */

#include <iostream>
#include <vector>
#include <deque>
#include <assert.h>
#include <ostream>

template<size_t dim_, typename T> class multivec{
public:
	multivec(): dim{dim_}, size{0} {
	};
	void resize(std::deque<size_t> size_){
		assert(!(dim_-size_.size()) && "size dimension mismatch");
		size = size_[0];
		data.resize(size_[0]);
		std::cout<<dim_<<"D vector resized to "<<size<<"\n";
		size_.pop_front();
		for(size_t i=0; i<size; i++){
			data[i].resize(size_);
		}
	}
	void show(){
		for(size_t i=0; i<size; i++){
			data[i].show();
			std::cout<<"\n";
		}
	}
	multivec<dim_-1,T> operator[](size_t i) const{
		return data[i];
	}
	multivec<dim_-1,T>& operator[](size_t i) {
		return data[i];
	}
	size_t getSize(){
		return size;
	}
private:
	size_t dim;
	size_t size;
	std::vector<multivec<dim_-1,T>> data;
};

template<typename T> class multivec<1,T>{
public:
	multivec(): dim{1}, size{0} {
	};
	void resize(std::deque<size_t> size_){
		assert(!(1-size_.size()) && "size dimension mismatch");
		size = size_[0];
		data.resize(size_[0],0);
		std::cout<<"1D vector resized to "<<size<<"\n";
	}
	void show(){
		for (const auto& e : data){
			std::cout<<e<<" ";
		}
	}
	T operator[](size_t i) const{
		return data.at(i);
	}
	T& operator[](size_t i){
		return data.at(i);
	}
	size_t getSize(){
		return size;
	}

private:
	size_t dim;
	size_t size;
	std::vector<T> data;
};


template<typename T, size_t dim_> std::ostream& operator<<(std::ostream& os, multivec<dim_,T> e){
	for(size_t i=0; i<e.getSize(); i++){
		if (dim_==1)
			os << e[i] << " ";
		else
			os << e[i];
	}
	os << "\n";
}

int multi_dim_container(){
	std::cout<<"In main\n";

	std::deque<size_t> size1{5};
	std::deque<size_t> size2{3,5};
	std::deque<size_t> size3{2,3,5};

	multivec<1,double> vec1;
	multivec<2,double> vec2;
	multivec<3,double> vec3;

	vec1.resize(size1);
	vec2.resize(size2);
	vec3.resize(size3);

	vec1[4] = 11;
	vec2[1][2] = 17;
	vec3[1][0][2] = 7;

	std::cout << vec3;

	std::cout<<"\nEnd of main\n";
	return 0;
}
