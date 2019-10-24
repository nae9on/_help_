/*
 * equally_dividing_plane.cpp
 *
 *  Created on: Oct 24, 2019
 *      Author: akadar
 */

#include <iostream>
#include <array>
#include <vector>
#include <numeric>
#include <random>
#include <memory>

namespace myalgo{

template<typename T = double>
class randGen{
	static_assert(std::is_floating_point<T>::value,
			    "template argument not a floating point type");
public:
	using dist_type = std::uniform_real_distribution<T>;
	randGen(T min = -1, T max = 1){
		seed = static_cast<unsigned>(time(0));
		rng_engine = std::mt19937(seed);
		dist = dist_type(min,max);
	}
	randGen(T min, T max, unsigned seed_){
		seed = static_cast<unsigned>(seed_);
		rng_engine = std::mt19937(seed);
		dist = dist_type(min,max);
	}
	T getNum() {
		return dist(rng_engine);
	}
private:
	unsigned seed;
	std::mt19937 rng_engine;
	dist_type dist;
};

}

template<short DIM, typename T = double>
class randPoint{
public:
	using randPointGenType = myalgo::randGen<T>;
	randPoint(){

		if(randPointGen.get()==nullptr){
		}

		x.resize(DIM);
		for(short i = 0; i<DIM; ++i){
			x[i] = 1;
		}
	}
private:
	std::vector<T> x;
	std::unique_ptr<randPointGenType> randPointGen;;
};

int main(){

	constexpr size_t num_points{100};

	std::vector<randPoint<1,double>> vecPoints(num_points);

	return 0;
}
