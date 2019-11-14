/*
 * main.cpp
 *
 *  Created on: 13 Nov 2019
 *      Author: ahkad
 */

#include <iostream>
#include <chrono>
#include <omp.h>
#include "omp_call.h"
#include "stdthread_call.h"

using clk = std::chrono::system_clock;
using dt = std::chrono::duration<double>;

int main(){

	int max_threads{omp_get_max_threads()};

	std::cout<<"Max no of threads = "<<max_threads<<std::endl;

	max_threads = 4;

	size_t N{10000000};

	auto t1 = clk::now();
	std::cout<<"Pi = "<<getpi_omp(N,max_threads)<<"\n";
	auto t2 = clk::now();
	std::cout<<"Time taken = "<<dt(t2-t1).count()<<" sec\n";

	auto t3 = clk::now();
	std::cout<<"Pi = "<<getpi_stdthread(N,max_threads)<<"\n";
	auto t4 = clk::now();
	std::cout<<"Time taken = "<<dt(t4-t3).count()<<" sec\n";

	return 0;
}
