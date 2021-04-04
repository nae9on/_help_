/*
 * closest_pair.h
 *
 *  Created on: 29 Oct 2019
 *      Author: ahkad
 */

#include <utility>
#include "median.h"

namespace DP{

template<typename IT>
std::pair<IT,IT> getClosestIn3(IT begin, IT mid, IT end){
	auto p0 = *begin;
	auto p1 = *mid;
	auto p2 = *end;
	double d01 = p0.getDistSq(p1);
	double d12 = p1.getDistSq(p2);
	double d20 = p2.getDistSq(p0);
	if(d01<d12){
		if(d01<d20) return std::make_pair(begin,mid);
		else return std::make_pair(end,begin);
	}else{
		if(d12<d20) return std::make_pair(mid,end);
		else return std::make_pair(end,begin);
	}
}

template<typename IT>
std::pair<IT,IT> getClosestPair_BruteForce(IT begin, IT end){
	auto pair1 = std::make_pair(begin,end-1);
	double dist1 = (*begin).getDistSq(*(end-1));

	for(auto it1 = begin; it1!=end-1; ++it1){
		for(auto it2 = it1+1; it2!=end; ++it2){
			if((*it1).getDistSq(*it2)<dist1){
				dist1 = (*it1).getDistSq(*it2);
				pair1.first = it1;
				pair1.second = it2;
			}
		}
	}

	return pair1;
}

template<typename IT>
std::pair<IT,IT> getClosestPair(IT begin, IT end){

	size_t np = end-begin;

	if(np<4){
		if(np==1) assert(0 && "1 point is not a pair");
		if(np==2) return std::make_pair(begin,begin+1);
		if(np==3) return getClosestIn3(begin,begin+1,begin+2);
	}

	auto mypair = getMedian(begin,end);

	size_t mid = mypair.first;

	auto pair1 = getClosestPair(begin,begin+mid);

	auto pair2 = getClosestPair(begin+mid,end);

	double dist1 = (*(pair1.first)).getDistSq(*(pair1.second));
	double dist2 = (*(pair2.first)).getDistSq(*(pair2.second));
	double dist3 = dist1 < dist2 ? dist1 : dist2;
	auto pair3 = dist1 < dist2 ? pair1 : pair2;

	// All points in [begin,begin+mid) are placed strictly to the left of mypair.second
	// All points in [begin+mid,end) are placed to the right of mypair.second
	// Replace this kernel with O(N) algorithm such that the total complexity
	// reduces from O(N^2) to O(NlogN).
	for(auto it1 = begin; it1!=(begin+mid); ++it1){
		for(auto it2 = (begin+mid); it2!=end; ++it2){
			if((*it1).getDistSq(*it2)<dist3){
				dist3 = (*it1).getDistSq(*it2);
				pair3.first = it1;
				pair3.second = it2;
			}
		}
	}

	return pair3;
}

}
