/*
 * return_unique_ptr.cpp
 *
 *  Created on: 11 Nov 2019
 *      Author: ahkad
 */

#include <iostream>
#include <memory>

class UI{
public:
	virtual void out() = 0;
	virtual ~UI(){}
};
class Wid: public UI{
public:
	Wid() = delete;
	Wid(std::string str_, double data_):str{str_}, data{data_}{
		std::cout<<"ctor called\n";
	}
	void out() override{
		std::cout<<"str = "<<str<<", data = "<<data<<"\n";
	}
	~Wid(){
		std::cout<<"dtor called\n";
	}
private:
	std::string str;
	double data;
};

template<typename... T>
auto make_widget(T&&... params){

	auto lmb = [](UI* ptr){
		std::cout<<"In custom deleter using a state-less lambda\n";
		delete ptr;
	};

	std::unique_ptr<UI,decltype(lmb)> temp(nullptr, lmb);

	//temp = new Wid(std::forward<T>(params)...); // Error

	temp.reset(new Wid(std::forward<T>(params)...));

	return temp;
}

int main(){

	auto widgetptr = make_widget("button",10);

	widgetptr->out();

	return 0;
}
