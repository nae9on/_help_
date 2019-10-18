/*
 * basic.cpp
 *
 *  Created on: May 26, 2019
 *      Author: akadar
 *
 *  Note: Large parts of boost::random were added to the standard library with C++11. Therefore, with
 *  C++11 one can rewrite the Boost.Random examples by including the header file random and accessing
 *  the namespace std
 *
 */

#include <iostream>
#include <time.h>
#include <vector>
#include <random>
#include <boost/random.hpp>

namespace myRandom {

typedef boost::random::mt19937 RNGtype;
typedef boost::random::uniform_int_distribution<size_t> uniform_int;
typedef boost::random::variate_generator<RNGtype&, uniform_int> variate_generator;

class baseSeeder {
	// Note: If a static data member is not of const integral or const enumeration type,
	// its declaration in the class definition is not allowed.
	static const size_t master_seed_init;
	static const RNGtype master_seed;
	static RNGtype master_rng;
	static uniform_int master_dist;
public:
	int dummy = 0;
	static unsigned s_count;
	baseSeeder(int _dummy) : dummy{_dummy} {
		s_count++;
	};
	size_t return_master_seed_init() {
		return master_seed_init;
	}
	size_t return_new_seed_init();
	void printInfo() {
		std::cout << "\n";
		std::cout << "master seed initializer = " << master_seed_init << std::endl;
		//std::cout << "master seed = " << master_seed << std::endl;
		std::cout << "master_dist (min, max) = ("<<master_dist.min() << ", " << master_dist.max() << ")\n";
	}
};

unsigned baseSeeder::s_count = 0;
const size_t baseSeeder::master_seed_init = std::time(0);
const RNGtype baseSeeder::master_seed = RNGtype(baseSeeder::master_seed_init);

// Define the random number generator and initialize with seed
RNGtype baseSeeder::master_rng(baseSeeder::master_seed);

// Define the distribution and initialize with range
uniform_int baseSeeder::master_dist(0,std::numeric_limits<size_t>::max());

size_t baseSeeder::return_new_seed_init(void) {
	// variate_generator combines a generator with a distribution
	variate_generator  init_gen(master_rng, master_dist);
	return init_gen();
	//return master_dist(master_rng); // when <random> from std is used
}

class surfaceSeeder : public baseSeeder {
	size_t surf_seed_init;
	RNGtype surf_seed;
public:
	surfaceSeeder (int _dummy) : baseSeeder(_dummy) {
		surf_seed_init = return_new_seed_init();
		surf_seed = RNGtype(surf_seed_init);
	}
	void printInfo() {
		baseSeeder::printInfo();
		std::cout << "surface seed initializer = " << surf_seed_init << std::endl;
		//std::cout << "surface seed = " << surf_seed << std::endl;
		std::cout <<std::endl;
	}
};

class volumeSeeder : public baseSeeder {
	size_t vol_seed_init;
	RNGtype vol_seed;
public:
	volumeSeeder (int _dummy) : baseSeeder(_dummy) {
		vol_seed_init = return_new_seed_init();
		vol_seed = RNGtype(vol_seed_init);
	}
	void printInfo() {
		baseSeeder::printInfo();
		std::cout << "volume seed initializer = " << vol_seed_init << std::endl;
		//std::cout << "volume seed = " << vol_seed << std::endl;
		std::cout <<std::endl;
	}
};

}

int main() {

	myRandom::surfaceSeeder surfSeed(7);
	myRandom::volumeSeeder volSeed(15);

	surfSeed.printInfo();
	volSeed.printInfo();

	return 0;
}
