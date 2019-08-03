/*
 * multi_dim_container.cpp
 *
 *  Created on: Aug 1, 2019
 *      Author: akadar
 *
 * A multi-dimensional container implementation using templates.
 */

#include <iostream>
#include <vector>
#include <deque>
#include <assert.h>
#include <ostream>

template<size_t dim_, typename T> class multivec{
public:
	using value_type = multivec<dim_-1,T>;
	multivec(): dim{dim_}, size{0} {
	};
	void resize(std::deque<size_t> size_){
		assert(!(dim_-size_.size()) && "size dimension mismatch");
		size = size_[0];
		data.resize(size);
		std::cout<<dim_<<"D vector resized to "<<size<<"\n";
		size_.pop_front();
		for(size_t i=0; i<size; i++){
			data[i].resize(size_);
		}
	}
	value_type operator[](size_t i) const{
		return data[i];
	}
	value_type& operator[](size_t i) {
		return data[i];
	}
	size_t getSize() const{
		return size;
	}
private:
	size_t dim;
	size_t size;
	std::vector<value_type> data;
};

// partial template specialization
template<typename T> class multivec<1,T>{
public:
	using value_type = T;
	multivec(): dim{1}, size{0} {
	};
	void resize(std::deque<size_t> size_){
		assert(!(1-size_.size()) && "size dimension mismatch");
		size = size_[0];
		data.resize(size,0);
		std::cout<<"1D vector resized to "<<size<<"\n";
	}
	value_type operator[](size_t i) const{
		return data[i];
	}
	value_type& operator[](size_t i){
		return data[i];
	}
	size_t getSize() const{
		return size;
	}
private:
	size_t dim;
	size_t size;
	std::vector<value_type> data;
};

template<size_t dim_, typename T> std::ostream& operator<<(std::ostream& os, multivec<dim_,T> elem){
	for(size_t i=0; i<elem.getSize(); i++){
		if (dim_==1)
			os << elem[i] << " ";
		else
			os << elem[i];
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

	std::cout << "\n" << vec3;

	std::cout << vec3[1][0];

	// Note that the default copy-constructor works fine even though the class multivec
	// is a resource handle.
	// The default copy-constructor will do a shallow-copy and since the underlying data
	// container is a std::vector, the shallow-copy invokes the copy-constructor of the
	// std::vector container which will do a deep-copy internally.
	multivec<3,double> vec4 = vec3;

	std::cout<<"End of main\n";
	return 0;
}
