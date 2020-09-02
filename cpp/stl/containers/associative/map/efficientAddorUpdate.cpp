/*
 * efficientAddorUpdate.cpp
 *
 *  Created on: Oct 17, 2019
 *      Author: akadar
 *
 * Use insert to insert a new pair and use operator[] to update an existing pair.
 * Do not use insert to update an exiting pair. Do not use operator[] to insert a new pair.
 *
 * References:
 * Scott#24
 * Excellent article
 * https://www.fluentcpp.com/2018/12/11/overview-of-std-map-insertion-emplacement-methods-in-cpp17/
 */

#include <iostream>
#include <map>
#include <utility>

class X{
public:
	X(){
		data = 0;
		std::cout<<"default constructor\n";
	}
	X(int data_){
		data = data_;
		std::cout<<"ordinary constructor\n";
	}
	X(const X& x){
		data = x.data;
		std::cout<<"copy constructor\n";
	}
	X& operator=(const X& x){
		data = x.data;
		std::cout<<"copy assignment\n";
		return *this;
	}
	X(X&& x){
		data = x.data;
		std::cout<<"move constructor\n";
	}
	X& operator=(X&& x){
		data = x.data;
		std::cout<<"move assignment\n";
		return *this;
	}
	int getData() const{
		return data;
	}
	~X(){
		//std::cout<<"de-construct\n";
	}
private:
	int data;
};

template<typename Map, typename Key = typename Map::key_type,
                       typename Value = typename Map::mapped_type>
typename Map::iterator add_or_update(Map& mymap, const Key& k, const Value& v){

    // lower_bound returns iterator pointing to first element equal to or greater than key, or end()
    // upper_bound returns iterator pointing to the first element greater than key, or end().
    // i.e. *lower_bound <= key < *upper_bound
	auto lb = mymap.lower_bound(k);

	if(lb!=mymap.cend() && !(mymap.key_comp()(k,lb->first))) // key found
	{
		std::cout<<"Key found!\n";
		lb->second = v;
		return lb;
	}
	else
	{
		std::cout<<"Key not found!\n";
		using MVT = typename Map::value_type;
		return mymap.insert(lb,MVT(k,v));
	}
}

int efficientAddorUpdate(){

	std::map<int,X> mymap;

	X x1(100); // ordinary-const
	std::cout<<"done 1\n\n";

	// Creating a pair
	std::pair<int,X> p1(1,x1); // copy-const
	std::cout<<"done 2\n\n";

	// Inserting a pair via insert
	// 1. Inserting an existing pair
	mymap.insert(p1); // copy-const
	std::cout<<"done 3\n\n";
	// 2. Inserting a temporary pair
	mymap.insert(std::make_pair(2,X(200))); // ordinary-const, move-const, move-const
	std::cout<<"done 4\n\n";

	// Updating an existing pair with a temp X
	mymap[2] = X(300); // ordinary-const, move-assign
	std::cout<<"done 5\n\n";

	// Inserting a new pair via operator[]
	mymap[3] = X(400); // ordinary-const, default-const, move-assign
	std::cout<<"done\n\n";

	add_or_update(mymap,4,500);
	std::cout<<"done\n\n";

	add_or_update(mymap,4,600);
	std::cout<<"done\n\n";

	std::cout<<"Elements are : ";
	for(const auto& elem:mymap) std::cout<<"("<<elem.first<<","<<elem.second.getData()<<") ";
	std::cout<<"\n";

	return 0;
}
