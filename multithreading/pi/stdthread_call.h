/*
 * stdthread_call.h
 *
 *  Created on: 14 Nov 2019
 *      Author: ahkad
 */

#ifndef STDTHREAD_CALL_H_
#define STDTHREAD_CALL_H_

#include <thread>
#include <vector>

class calcPi{
public:
	calcPi(size_t N_, int id_):N{N_},id{id_}{
		rp = randpoint((id+1)*std::time(0));
	}
	inline void operator()(){
		size_t count{0};
		for(size_t i=0; i<N; ++i){
			if(rp()<1.0) ++count;
		}
		pi+=4.0*count/N;
	}
	static double getpi(){
		return pi;
	}
private:
	size_t N;
	int id;
	randpoint rp;
	static double pi;
};

double calcPi::pi = 0.0;

double getpi_stdthread(size_t N, int nthreads){

	std::vector<std::thread> th;

	for(int i=0; i<nthreads; ++i)
	{
		// spinning thread i
		th.push_back(std::thread{calcPi(N,i)});
	}

	// joining all threads
	for(auto& elem : th) elem.join();

	return calcPi::getpi()/nthreads;

}

#endif /* STDTHREAD_CALL_H_ */
