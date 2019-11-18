/*
 * seeder_example.cpp
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

	static mypair* getDistRngPairPtr(){
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
