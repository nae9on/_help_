/*
 * test_median.cpp
 *
 *  Created on: Oct 24, 2019
 *      Author: akadar
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

#include "particle.h"
#include "median.h"

int test_median(){

	constexpr size_t num_points{10000};
	constexpr short DIM{2};
	using point = DP::randPoint<DIM>;

	std::vector<std::pair<double,double>>
	limits{std::make_pair(-1.0,1.0),
		   std::make_pair(-1.0,1.0)};

	point::Initialize(limits);

	std::vector<point> vecPoints(num_points);

	// Equally dividing plane is defined by the median point

	auto mypair = DP::getMedian(vecPoints.begin(),vecPoints.end());

	size_t count = std::count_if(vecPoints.cbegin(),vecPoints.cend(),
			[&](const auto& p1){return p1.get(0)<mypair.second.get(0);});

	assert(count==mypair.first && "Assertion");

	//for(auto& elem : vecPoints) std::cout<<elem<<"\n";

	std::cout<<"Median point is "<<mypair.second;

	return 0;
}
