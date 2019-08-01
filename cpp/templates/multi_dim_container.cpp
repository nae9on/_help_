/*
 * multi_dim_container.cpp
 *
 *  Created on: Aug 1, 2019
 *      Author: akadar
 */

#include <iostream>
#include <vector>

template<size_t dim_, typename T> class multivec{
public:
	multivec(std::vector<size_t> size_): dim{dim_}, size{size_[dim_]} {
	};

private:
	size_t dim;
	size_t size;
	multivec<dim_-1,T> data;
};

template<typename T> class multivec<1,T>{
public:
	multivec(std::vector<size_t> size_): dim{1}, size{size_[1]} {
		data.resize(size_[1]);
	};

private:
	size_t dim;
	size_t size;
	std::vector<T> data;
};

int main(){
	std::cout<<"In main\n";
	const int dim = 1;
	std::vector<size_t> size{1};

	multivec<dim,double> vec(size);
	std::cout<<"End of main\n";
	return 0;
}
