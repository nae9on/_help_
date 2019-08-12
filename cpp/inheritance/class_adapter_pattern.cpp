/*
 * class_adapter_pattern.cpp
 *
 *  Created on: Aug 12, 2019
 *      Author: akadar
 */

#include <iostream>
#include <vector>
#include <string>

using my_string = std::vector<std::string>;

class lions{
public:
	lions(){}
	lions(std::string name_){
		count++;
		name.push_back(name_);
	}
	static unsigned getCount(){
		return count;
	}
	static my_string getName(){
		return name;
	}
private:
	static unsigned count;
	static my_string name;
};
unsigned lions::count = 0;
my_string lions::name = {};

class tigers{
public:
	tigers(){}
	tigers(std::string name_){
		count++;
		name.push_back(name_);
	}
	static unsigned getCount(){
		return count;
	}
	static my_string getName(){
		return name;
	}
private:
	static unsigned count;
	static my_string name;
};
unsigned tigers::count = 0;
my_string tigers::name = {};

// Adapter interface class
class bigCatsInterface{
public:
	virtual unsigned getTotalCount() const = 0;
	virtual my_string getAllNames() const = 0;
	virtual ~bigCatsInterface(){};
};

// Concrete adaptor class is defined called bigCats which implements
// the bigCatsInterface class defining the pure virtual functions and also inheriting
// the individual classes which it is supposed to wrap.
class bigCats: public bigCatsInterface, public lions, public tigers{
public:
	bigCats(){
		count = lions::getCount()+tigers::getCount();
	}
	unsigned getTotalCount() const override{
		return(count);
	}
	my_string getAllNames() const override{
		my_string name;
		for(const auto& elem : lions::getName()){
			name.push_back(elem);
		}
		for(const auto& elem : tigers::getName()){
			name.push_back(elem);
		}
		return(name);
	}
private:
	unsigned count;
};

int main(){
	lions l1("X"), l2("Y"), l3("Z");
	tigers t1("A"), t2("B"), t3("C"), t4("D");

	std::cout<<"Lions = "<<lions::getCount()<<"\n";
	std::cout<<"Tigers = "<<tigers::getCount()<<"\n";

	bigCats a1;
	std::cout<<"Total big cats count = "<<a1.getTotalCount()<<"\n";
	std::cout<<"All big cats names are \n";
	for(auto& elem : a1.getAllNames()){
		std::cout<<elem<<"\n";
	}

	return 0;
}
