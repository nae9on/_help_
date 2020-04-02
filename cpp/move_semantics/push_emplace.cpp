/*
 * push_emplace.cpp
 *
 *  Created on: 14 Nov 2019
 *      Author: ahkad
 */

#include <iostream>
#include <vector>

class XX{
public:
	XX() = delete;
	XX(short id_, std::string name_):id{id_},name{name_}{
		std::cout<<"ordinary-const\n";
	}
	XX(const XX& x){
		id = x.id;
		name = x.name;
		std::cout<<"ctor\n";
	}
	XX& operator=(const XX& x){
			id = x.id;
			name = x.name;
			std::cout<<"cassign\n";
			return *this;
	}
	XX(XX&& x){
		id = x.id;
		name = x.name;
		std::cout<<"move\n";
	}
	XX& operator=(XX&& x){
			id = x.id;
			name = x.name;
			std::cout<<"move-assign\n";
			return *this;
	}
private:
	short id;
	std::string name;
};

int push_emplace(){

	std::vector<XX> vec;
	vec.reserve(100);

	// ordinary-const
	XX x(1,"a");

	std::cout<<"\n";

	// ctor
	vec.push_back(x);

	std::cout<<"\n";

	// ordinary-const and move
	vec.push_back(XX(2,"b"));

	std::cout<<"\n";

	// ctor
	vec.emplace_back(x);

	std::cout<<"\n";

	// ordinary-const and move
	vec.emplace_back(XX(2,"b"));

	std::cout<<"\n";

	// ordinary-const
	vec.emplace_back(2,"b"); // in place construction avoiding move

	return 0;
}
