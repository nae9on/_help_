/*
 * biography.h
 *
 *  Created on: Sep 3, 2019
 *      Author: akadar
 */

#ifndef ASSOCIATIVE_MAP_BIOGRAPHY_H_
#define ASSOCIATIVE_MAP_BIOGRAPHY_H_

#include <iostream>

class biography{
public:
	biography(): name{"notborn"}, age{0}{};
	biography(std::string name_, short age_) : name{name_}, age{age_} {}
	short getAge() const{
		return age;
	}
	std::string getName() const{
		return name;
	}
	void setName(std::string name_){
		name = name_;
	}
	void setAge(short age_){
		age = age_;
	}
	void printInfo(){
		if(age==0 && name=="notborn") {
			std::cout<<"I have not been created yet."<<std::endl;
			std::cout<<std::endl;
		} else {
			std::cout<<"My full name is "<<name<<"."<<std::endl;
			std::cout<<"My age is "<<age<<"."<<std::endl;
			std::cout<<std::endl;
		}
	}
private:
	std::string name;
	short age;
};

#endif /* ASSOCIATIVE_MAP_BIOGRAPHY_H_ */
