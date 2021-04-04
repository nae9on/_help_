/*
 * median.h
 *
 *  Created on: 29 Oct 2019
 *      Author: ahkad
 */

#ifndef MEDIAN_H_
#define MEDIAN_H_

#include <vector>
#include <algorithm>
#include <utility>

#include "particle.h"

namespace DP{

template<typename IT>
auto getMedian(IT begin, IT end){

	size_t np = end-begin;

	size_t mid = static_cast<size_t>(np/2);

	std::nth_element(begin,begin+mid,end,
			[](const auto& p1, const auto& p2){return p1.get(0)<p2.get(0);});

	auto median = *(begin+mid);

	if(np%2==0)
	{
		std::nth_element(begin,begin+mid-1,begin+mid,
				[](const auto& p1, const auto& p2){return p1.get(0)<p2.get(0);});

		median += *(begin+mid-1);
		median /= 2;
	}

	return std::make_pair(mid,median);
}

}
#endif /* MEDIAN_H_ */
