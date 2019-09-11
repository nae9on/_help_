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

#define MAX_SIZE 100000
#define INCREMENT 10000
#define REPS 1000

struct timeS{
	timeS(int c_, double t1_, double t2_) : count{c_}, time1{t1_}, time2{t2_}{}
	int count; // count of doubles
	double time1; // time taken
	double time2; // time taken
};

int reduce_benchmark(int argc, char* argv[]){

	printf("Rank 0 is sending %d:%d:%d doubles to Rank 1\n",0,INCREMENT,MAX_SIZE);

	int size, rank;

	double arr[MAX_SIZE], sum{0.0};
	std::vector<double> sum_arr;
	std::vector<int> count_arr;
	for(int i = 0; i<MAX_SIZE; ++i) arr[i] = i+1;

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

			count_arr.push_back(count);

			share_others = std::floor(count/size);
			share_rank0 = count-share_others*(size-1);
			begin_index = 0;

			// set the array back to original
			for(int i = 0; i<count; ++i) arr[i] = i+1;

			sumT1 = 0;
			for(itr=1; itr<=REPS; itr++){
				t1 = MPI_Wtime();
				MPI_Reduce(MPI_IN_PLACE, arr+begin_index, share_others,
				               MPI_DOUBLE, MPI_SUM, root,
							   MPI_COMM_WORLD);
				t2 = MPI_Wtime();
				sumT1 += t2 - t1;
			}
			avgT.push_back(timeS(count,sumT1/REPS,0.0));

			sum = 0;
			for (int i=0; i<share_rank0; i++) sum+=arr[i];
			sum_arr.push_back(sum);
			}
		}

	if(rank!=0){

		for(count=0; count<=MAX_SIZE; count+=INCREMENT){

			count_arr.push_back(count);

			share_others = std::floor(count/size);
			share_rank0 = count-share_others*(size-1);
			begin_index = share_rank0 + (rank-1)*share_others;

			sumT1 = 0;
			for(itr=1; itr<=REPS; itr++){
				t1 = MPI_Wtime();
				MPI_Reduce(arr+begin_index, nullptr, share_others,
						   MPI_DOUBLE, MPI_SUM, root,
						   MPI_COMM_WORLD);
				t2 = MPI_Wtime();
				sumT1 += t2 - t1;
			}
			avgT.push_back(timeS(count,sumT1/REPS,0.0));
			}
		}

	if(rank==0){
		int i = 0;
		for(const auto& elem : sum_arr) {
			std::cout<<"Total sum n(n+1)/2, for elements "<<count_arr[i++]<<" = "<<elem<<"\n";
		}
	}

	for(const auto& elem : avgT)
		std::cout<<elem.count<<","<<elem.time1<<","<<elem.time2<<"\n";

	MPI_Finalize();

	return 0;
}
