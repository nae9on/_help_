/*
 * rand.h
 *
 *  Created on: 13 Nov 2019
 *      Author: ahkad
 */

#ifndef RAND_H_
#define RAND_H_

#include <ctime>
#include <random>

class randpoint{
	using randgen = std::mt19937;
	using dist = std::uniform_real_distribution<double>;
public:
	randpoint(){
		rg = randgen(0);
		rd = dist(0,1);
	}
	randpoint(unsigned seed){
		rg = randgen(seed);
		rd = dist(0,1);
	}
	double operator()(){
		double x = rd(rg);
		double y = rd(rg);
		return (x*x+y*y);
	}
private:
	dist rd;
	randgen rg;
};

#endif /* RAND_H_ */
