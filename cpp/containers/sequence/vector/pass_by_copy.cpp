/*
 * pass_by_copy.cpp
 *
 *  Created on: May 22, 2019
 *      Author: akadar
 */

#include <iostream>
#include <vector> // mem allocation on heap, pass by value allowed
#include <valarray> // mem allocation on heap, pass by value allowed
#include <array> // mem allocation on stack, pass by value not allowed
#include <chrono>

const int MAX = 100000000; // 1'000'000'00 not supported in c++11
const int LOOP = 1;

using namespace std::chrono;

// Try different opt flags to see the difference between pass by value and pass by ref
// With -O3 flag the difference between the two is maximum

template<typename T> void initialize(T&);
template<typename T> double getSumByRef(const T&);
template<typename T> double getSumByValue(const T);

int pass_by_copy()
{
	double sum {0.0};

	auto start = system_clock::now();
	std::vector<size_t> arr; arr.resize(MAX);
	//std::valarray<size_t> arr; arr.resize(MAX);
	//std::array<size_t,MAX> arr;
	initialize(arr);
	auto stop = system_clock::now();
	std::cout << "Initialization time = " << duration_cast<milliseconds>(stop-start).count() << "\n\n";

	start = system_clock::now();
	sum = 0.0;
	for (size_t ctr = 0; ctr < LOOP; ctr++) {
		sum += getSumByRef(arr);
	}
	std::cout << "Sum by ref =   " << sum << "\n";
	stop = system_clock::now();
	std::cout << "Time taken in milliseconds by pass by ref = "
			<< duration_cast<milliseconds>(stop-start).count();

	start = system_clock::now();
	sum = 0.0;
	for (size_t ctr = 0; ctr < LOOP; ctr++) {
		sum += getSumByValue(arr);
	}
	std::cout << "\n\nSum by value = " << sum << "\n";
	stop = system_clock::now();
	std::cout << "Time taken in milliseconds by pass by value = "
			<< duration_cast<milliseconds>(stop-start).count() << "\n\n";

	return 0;
}

template<typename T> void initialize(T& arr) {
	size_t i = 1;
	for (auto& t : arr) {
		t = i++;
	}
}

template<typename T> double getSumByRef(const T& arr) {
	double sum { 0.0 };
	for (const auto& t : arr) {
		sum += t;
	}
	return sum;
}

template<typename T> double getSumByValue(const T arr) {
	double sum { 0.0 };
	for (const auto& t : arr) {
		sum += t;
	}
	return sum;
}
