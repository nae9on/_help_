/*
 * pass_by_copy.cpp
 *
 *  Created on: May 22, 2019
 *      Author: akadar
 */

#include <iostream>
#include <vector> // mem allocation on heap, pass by value allowed
#include <valarray> // mem allocation on heap, pass by value allowed
#include <array> // mem allocation on stack, pass by value not possible because
// arrays decay into pointers, when passed to a function
#include <chrono>

const int MAX = 100000000; // 1'000'000'00 not supported in c++11
const int LOOP = 1;

using namespace std::chrono;

// Try different opt flags to see the difference between pass by value and pass by ref
// With -O3 flag the difference between the two is maximum

template<typename T> void doNothingRef(const T&);
template<typename T> void doNothingValue(const T);

int pass_by_copy()
{
	auto start = system_clock::now();
	std::vector<double> arr; arr.resize(MAX);
	//std::valarray<double> arr; arr.resize(MAX);
	//std::array<double,MAX> arr;
	auto stop = system_clock::now();
	std::cout << "Initialization time in milliseconds = "
			<<duration_cast<milliseconds>(stop-start).count()<<std::endl;

	start = system_clock::now();
	for (size_t ctr = 0; ctr < LOOP; ctr++) {
		doNothingRef(arr);
	}
	stop = system_clock::now();
	std::cout << "Time taken in milliseconds by pass by ref = "
			<<duration_cast<milliseconds>(stop-start).count()<<std::endl;

	start = system_clock::now();
	for (size_t ctr = 0; ctr < LOOP; ctr++) {
		doNothingValue(arr);
	}
	stop = system_clock::now();
	std::cout << "Time taken in milliseconds by pass by value = "
			<<duration_cast<milliseconds>(stop-start).count() << "\n\n";

	return 0;
}

template<typename T> void doNothingRef(const T& arr) {
}

template<typename T> void doNothingValue(const T arr) {
}
