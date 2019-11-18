/*
 * builder.h
 *
 *  Created on: Oct 5, 2019
 *      Author: akadar
 */

#ifndef CREATIONAL_BUILDER_BUILDER_H_
#define CREATIONAL_BUILDER_BUILDER_H_

#include <iostream>
#include <string>
#include <memory>

class engine{
public:
	virtual void info() = 0;
	virtual ~engine(){}
};

class engineD: public engine{
public:
	void info(){
		std::cout<<"Ordinary engine\n";
	}
};

class engineX: public engine{
public:
	void info(){
		std::cout<<"TurboX engine\n";
	}
};

class engineH: public engine{
public:
	void info(){
		std::cout<<"Heavy duty engine\n";
	}
};

// Abstract builder class
// Declare all the common construction steps here
class builder{
public:
	builder(){
		seats = 0;
		e = nullptr;
	}
	void setSeats(short seats_) {
		seats = seats_;
	}
	void setEngine(engine* e_) {
		e = e_;
	}
	virtual ~builder(){
		if(e!=nullptr) {
			delete e;
		}
	}
protected:
	short seats;
	engine* e;
};

// Concrete builder class for each product representation
class carBuilder: public builder{
public:
	carBuilder(){
		builder();
	}
	void print(){
		std::cout<<"Seats = "<<seats<<"\n";
		e->info();
		std::cout<<"\n";
	}
	carBuilder returncarBuilder(){
		return *this;
	}
	~carBuilder(){}
private:

};

// Concrete builder class for each product representation
class truckBuilder: public builder{
public:
	truckBuilder(){
		builder();
		capacity = 0;
	}
	void setCapacity(int capacity_){
		capacity = capacity_;
	}
	void print(){
		std::cout<<"Seats = "<<seats<<"\n";
		e->info();
		std::cout<<"Capacity = "<<capacity<<"Kg\n";
		std::cout<<"\n";
	}
	truckBuilder returntruckBuilder(){
		return *this;
	}
	~truckBuilder(){}
private:
	short capacity;
};

#endif /* CREATIONAL_BUILDER_BUILDER_H_ */
