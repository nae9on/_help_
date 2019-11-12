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

auto lmb = [](UI* ptr){
		std::cout<<"In custom deleter using a state-less lambda\n";
		delete ptr;
	};

template<typename... T>
std::unique_ptr<UI,decltype(lmb)> make_widget(T&&... params){

	std::unique_ptr<UI,decltype(lmb)> temp(nullptr, lmb);

	// Assign a derived class object
	temp.reset(new Wid(std::forward<T>(params)...));

	return temp;
}

template<typename... T>
std::unique_ptr<UI> make_widget_simple(T&&... params){

	std::unique_ptr<UI> temp(nullptr);

	// Assign a derived class object
	temp.reset(new Wid(std::forward<T>(params)...));

	return temp;
}

int return_unique_ptr(){

	auto widgetptr1 = make_widget("button",10);

	// A unique_ptr easily and efficiently converts to a shared_ptr to allow shared ownership
	// of otherwise uniquely owned resource. This is the reason why factory functions return
	// unique_ptr (Ref Item 18, EMC++)
	std::shared_ptr<UI> widgetptr2 = make_widget_simple("button",10);

	widgetptr1->out();

	widgetptr2->out();

	return 0;
}
