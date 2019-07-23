/*
 * badAlloc.cpp
 *
 *  Created on: Jul 22, 2019
 *      Author: akadar
 */

#include <iostream>
#include <exception>
#include <vector>

class error_log{
public:
	void log(const std::string& s) {
		message.push_back(s);
	}
	void print_log(){
		for(const auto& c : message)
			std::cout<<c<<"\n";
	}
private:
	std::vector<std::string> message;
};

int main() {

	error_log er;

	try{
		throw std::bad_alloc();
	}
	catch(const std::exception& e){
		std::cout<<"Dummy exception thrown "<<e.what()<<"\n";
		er.log("exception 1");
	}

	try{
		double* d = new double[1000000000000]();
		/*while(1){
			int* intarray = new int[99999ul];
		}*/
	}
	catch(const std::exception& e){
		std::cout<<"Out of memory "<<e.what()<<"\n";
		er.log("exception 2");
	}

	er.print_log();
	std::cout<<"End of main \n";
	return 0;
}
