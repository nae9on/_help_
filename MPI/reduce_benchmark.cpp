/*
 * reduce_benchmark.cpp
 *
 *  Created on: Sep 11, 2019
 *      Author: akadar
 */

#include <iostream>
#include <mpi.h>
#include <vector>
#include <iomanip>
#include <cmath>

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

#define MAX_SIZE 1000000
#define INCREMENT 10000
#define REPS 1000
#define epsilon 1e-6

struct timeS{
	timeS(int c_, double t1_, double t2_) : count{c_}, time1{t1_}, time2{t2_}{}
	int count; // count of doubles
	double time1; // time taken
	double time2; // time taken
};

void init_arr(double* arr){
	for(int i = 0; i<MAX_SIZE; ++i) arr[i] = static_cast<double>(i+1)/MAX_SIZE;
}

int reduce_benchmark(int argc, char* argv[]){

	printf("Array length is %d:%d:%d\n",0,INCREMENT,MAX_SIZE);

	int size, rank;

	double arr[MAX_SIZE], sum{0.0};

	init_arr(arr);

	int root{0};

	int itr, count;

	int share_others, share_rank0, begin_index;
	double t1{0.0}, t2{0.0}, sumT1{0.0};
	std::vector<timeS> avgT;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank==0){

		for(count=0; count<=MAX_SIZE; count+=INCREMENT){

			share_others = std::floor(count/size);
			share_rank0 = count-share_others*(size-1);
			begin_index = 0;

			sumT1 = 0;
			for(itr=1; itr<=REPS; itr++){

				// set the array back to original
				init_arr(arr);

				// communication bottleneck -----------------------------------
				MPI_Barrier(MPI_COMM_WORLD);
				t1 = MPI_Wtime();
				MPI_Reduce(MPI_IN_PLACE, arr+begin_index, share_others,
				               MPI_DOUBLE, MPI_SUM, root,
							   MPI_COMM_WORLD);
				t2 = MPI_Wtime();
				sumT1 += t2 - t1;
				// communication bottleneck -----------------------------------

				// Check if results are computed correctly
				sum = 0;
				for (int i=0; i<share_rank0; i++) sum+=arr[i];

				double result =  static_cast<double>(count)*(count+1)/2/MAX_SIZE;

				if(std::fabs(sum-result)>epsilon){
					std::cout<<result<<"\t"<<sum<<"\n";
					std::cout<<"error = "<<std::fabs(sum-result)<<"\n";
					// Note assert is a function-like macro, use braces generously!
					assert(0);
				}
			}
			avgT.push_back(timeS(count,sumT1/REPS,0.0));

			}
		}

	if(rank!=0){

		for(count=0; count<=MAX_SIZE; count+=INCREMENT){

			share_others = std::floor(count/size);
			share_rank0 = count-share_others*(size-1);
			begin_index = share_rank0 + (rank-1)*share_others;

			sumT1 = 0;
			for(itr=1; itr<=REPS; itr++){
				// communication bottleneck -----------------------------------
				MPI_Barrier(MPI_COMM_WORLD);
				t1 = MPI_Wtime();
				MPI_Reduce(arr+begin_index, nullptr, share_others,
						   MPI_DOUBLE, MPI_SUM, root,
						   MPI_COMM_WORLD);
				t2 = MPI_Wtime();
				sumT1 += t2 - t1;
				// communication bottleneck -----------------------------------
			}
			avgT.push_back(timeS(count,sumT1/REPS,0.0));
			}
		}

	for(const auto& elem : avgT)
		std::cout<<elem.count<<","<<elem.time1<<","<<elem.time2<<"\n";

	MPI_Finalize();

	return 0;
}
