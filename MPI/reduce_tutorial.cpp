/*
 * reduce_tutorial.cpp
 *
 *  Created on: Sep 11, 2019
 *      Author: akadar
 *
 * In this tutorial, rank 0 owns an array [0:MAX_SIZE-1] which must be summed up.
 * rank i fills the ith chunk of size MAX_SIZE/SIZE elements. Using reduction,
 * rank 0 sums up all the chunks onto itself. Finally, the remaining chunk is summed
 * up at rank 0 to obtain the final result.
 *
 */

#include <iostream>
#include <mpi.h>
#include <cmath>

#define MAX_SIZE 1234

int reduce_tutorial(int argc, char* argv[]){

	int size, rank;
	double arr[MAX_SIZE], sum{0};

	// Initialize array
	for(int i = 0; i<MAX_SIZE; ++i) arr[i] = i+1;

	int share_others, share_rank0, begin_index;

	int root{0};

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	// Calculate share of processing elements for each rank
	share_others = std::floor(MAX_SIZE/size);
	share_rank0 = MAX_SIZE-share_others*(size-1);

	if(rank==0){
		begin_index = 0;
		// When using MPI_IN_PLACE, send buffer is not relevant for the root process.
		// MPI_Reduce requires separate send and receive buffer on the root.
		// With MPI_IN_PLACE, receive buffer is used as the send buffer, reducing copy overhead.
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Reduce(MPI_IN_PLACE, arr+begin_index, share_others,
		               MPI_DOUBLE, MPI_SUM, root,
					   MPI_COMM_WORLD);
	}

	if(rank!=0){
		begin_index = share_rank0 + (rank-1)*share_others;
		// receive buffer is not relevant for non-root processes.
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Reduce(arr+begin_index, nullptr, share_others,
		               MPI_DOUBLE, MPI_SUM, root,
					   MPI_COMM_WORLD);

	}

	if(rank==0){
		std::cout<<"MAX_SIZE = "<<MAX_SIZE<<" total ranks = "<<size<<"\n";
		std::cout<<"chunk size, rank 0 = "<<share_rank0<<", other ranks = "<<share_others<<"\n";
		//for(const auto& elem : arr) std::cout<<elem<<"\t"; std::cout<<"\n";
		for (int i=0; i<share_rank0; i++) sum+=arr[i];
		std::cout<<"Total sum n(n+1)/2 = "<<sum<<"\n";
	}

	MPI_Finalize();

	return 0;
}
