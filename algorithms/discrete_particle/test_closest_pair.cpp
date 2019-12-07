/*
 * test_closest_pair.cpp
 *
 *  Created on: 29 Oct 2019
 *      Author: ahkad
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "particle.h"
#include "closest_pair.h"

int main(){

	constexpr size_t num_points{1000};
	constexpr short DIM{3};
	using point = DP::randPoint<DIM>;

	std::vector<std::pair<double,double>>
	limits{std::make_pair(0.0,10.0),std::make_pair(-10.0,20.0),std::make_pair(10.0,30.0)};

	point::Initialize(limits);

	std::vector<point> vecPoints(num_points);

	auto cpair = getClosestPair(vecPoints.begin(),vecPoints.end());

	auto cpair_bf = getClosestPair_BruteForce(vecPoints.cbegin(),vecPoints.cend());

	//for(auto& elem : vecPoints) std::cout<<elem<<"\n";

	std::cout<<"Closest pair is "<<*(cpair.first)<<" "<<*(cpair.second)
			<<" with dist = "<<cpair.first->getDistSq(*(cpair.second))<<"\n";

	std::cout<<"Closest pair is "<<*(cpair_bf.first)<<" "<<*(cpair_bf.second)
			<<" with dist = "<<cpair_bf.first->getDistSq(*(cpair_bf.second))<<"\n";

	if((cpair.first==cpair_bf.first && cpair.second==cpair_bf.second) ||
			(cpair.first==cpair_bf.second && cpair.second==cpair_bf.first)){
		std::cout<<"PASS\n";
	}else{
		assert(false && "FAIL");
	}

	return 0;
}
