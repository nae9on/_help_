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

int main(){

	std::vector<XX> vec;
	vec.reserve(100);

	XX x(1,"a");

	std::cout<<"\n";

	vec.push_back(x);

	std::cout<<"\n";

	vec.push_back(XX(2,"b"));

	std::cout<<"\n";

	vec.emplace_back(x);

	std::cout<<"\n";

	vec.emplace_back(XX(2,"b"));

	std::cout<<"\n";

	vec.emplace_back(2,"b");

	return 0;
}


