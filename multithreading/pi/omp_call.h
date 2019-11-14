/*
 * omp_call.h
 *
 *  Created on: 13 Nov 2019
 *      Author: ahkad
 */

#ifndef OMP_CALL_H_
#define OMP_CALL_H_

#include "rand.h"
#include <omp.h>

double getpi_omp(size_t N, int nthreads){

	double pi{0.0};

#pragma omp parallel num_threads(nthreads) default(none) shared(pi,N)
{
	int id = omp_get_thread_num();
	randpoint rp((id+1)*std::time(0));
	size_t count{0};
	for(size_t i=0; i<N; ++i){
		if(rp()<1.0) ++count;
	}
#pragma omp critical
	pi+=4.0*count/N;
}

	return pi/nthreads;

}

#endif /* OMP_CALL_H_ */
