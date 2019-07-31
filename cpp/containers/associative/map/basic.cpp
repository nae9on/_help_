/*
 * basic.cpp
 *
 *  Created on: May 22, 2019
 *      Author: akadar
 */

#include <iostream>
#include <map>
#include <string>

class biography{
public:
	biography(): name{"notborn"}, age{0}{};
	short getAge(){
		return age;
	}
	void setName(std::string name_){
		name = name_;
	}
	void setAge(short age_){
		age = age_;
	}
	void printInfo(){
		if(age==0 && name=="notborn") {
			std::cout<<"I have not been created yet"<<std::endl;
			std::cout<<std::endl;
		} else {
			std::cout<<"My full name is "<<name<<std::endl;
			std::cout<<"My age is "<<age<<std::endl;
			std::cout<<std::endl;
		}

	}
private:
	std::string name;
	short age;
};

int basic()
{

	// A map is an associative container and consists of key-value pairs (each key is unique)
	std::map<std::string,biography> myMap;

	myMap.insert(std::make_pair("Ali",biography()));
	myMap.insert(std::make_pair("Kaynat",biography()));
	myMap.insert(std::make_pair("Mom",biography()));

	// Change ages
	if(myMap.count("Ali") > 0) {
		myMap["Ali"].setName("Ali Hussain Kadar");
		myMap["Ali"].setAge(29);
	}

	// Try to add key Ali again but it will fail
	biography x = biography();
	x.setName("x");
	x.setAge(100);
	myMap.insert(std::make_pair("Ali",x));

	// Try to add key Dad which does not exist and it will work
	if(myMap.insert(std::make_pair("Dad",biography())).second) {
		std::cout<<"Adding key Dad for the first time\n";
	}
	else {
		std::cout<<"Trying to add key Dad which already exists\n";
	}

	// Accessing key AliK which does not exist would do nothing
	if(myMap.count("AliK") <= 0) {
		std::cout << "AliK key does not exist\n";
	}

	// Accessing key Dad which does exist
	if(myMap.count("Dad") > 0) {
		std::cout << "Dad key exists\n";
	}

	// Be careful of accidently creating a key value pair
	myMap["Accidental name"].setAge(100);

	std::cout<<"\n";

	for (auto& t : myMap)
	{
		std::cout<<t.first<<"\n";
		t.second.printInfo();

	}

	return 0;
}
