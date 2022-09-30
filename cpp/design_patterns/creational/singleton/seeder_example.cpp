/*
 *  seeder_example.cpp
 *   
 *  Warning: This pattern is not thread safe!
 *  Use instead this pattern
 *  https://stackoverflow.com/questions/1463707/c-singleton-vs-global-static-object
 *  https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
 *
 *  Created on: 16 Nov 2019
 *      Author: ahkad
 */

#include <iostream>
#include <utility>
#include <random>
#include <memory>
#include <ctime>

using dist = std::uniform_int_distribution<int>;
using rng = std::mt19937;

class randGen{
public:
	using mypair = std::pair<dist,rng>;

	static mypair* getDistRngPairPtr()
	{
		
		// This is not thread-safe!
		if(dist_rng_pair==nullptr)
		{
			std::cout<<"Initializing random generator\n";
			dist_rng_pair = std::unique_ptr<mypair>(new mypair);
			dist_rng_pair->first = dist(0,100);
			dist_rng_pair->second = rng(0);
		}
		return dist_rng_pair.get();
	}
private:
	randGen() = default;
	randGen(const randGen&) = default;
	randGen& operator=(const randGen&) = default;
	
	// It has static storage duration. It is created at program start-up even before main is executed.
	// It is destroyed at end of program.
	static std::unique_ptr<mypair> dist_rng_pair;
};

std::unique_ptr<randGen::mypair> randGen::dist_rng_pair = nullptr;

int seeder_example(){

	{
		auto p1 = randGen::getDistRngPairPtr();

		for(size_t i=0; i<5; ++i)
			std::cout<<p1->first(p1->second)<<"\n";
	}

	std::cout<<"\n";

	{
		auto p2 = randGen::getDistRngPairPtr();

		for(size_t i=0; i<5; ++i)
			std::cout<<p2->first(p2->second)<<"\n";
	}

	std::cout<<"End of main";
	return 0;
}
