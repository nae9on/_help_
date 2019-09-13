/*
 * allGather_tutorial.cpp
 *
 *  Created on: Sep 13, 2019
 *      Author: akadar
 *
 * In this tutorial, all ranks own an array [0:MAX_SIZE-1] which must be filled with
 * integers 1,2.. MAX_SIZE. rank i fills the ith chunk of size MAX_SIZE/SIZE elements.
 * Each rank then sends its chunk to all other ranks via MPI_Allgather.
 *
 * Note that all ranks should get equal chunk size = MAX_SIZE/SIZE elements.
 * Check MPI_Allgatherv which gathers data from all processes and delivers it to all.
 * Each process may contribute a different amount of data.
 *
 * Reference:
 * https://www.open-mpi.org/doc/v3.0/man3/MPI_Allgather.3.php
 *
 */

#include <iostream>
#include <mpi.h>
#include <cmath>
#include <cassert>

#define MAX_SIZE 20

int allGather_tutorial(int argc, char* argv[]){

	int size, rank;
	double outmsg[MAX_SIZE], inmsg[MAX_SIZE];

	// Initialize array
	for(int i = 0; i<MAX_SIZE; ++i) {outmsg[i] = 0; inmsg[i] = 0;}

	int my_share, share_others, share_rank0, begin_index;

	double* sendbuf; int sendcount; double* recvbuf; int recvcount;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	// Calculate share of processing elements for each rank
	share_others = std::floor(MAX_SIZE/size);
	share_rank0 = MAX_SIZE-share_others*(size-1);

	if(rank==0){
		begin_index = 0;
		my_share = share_rank0;
		sendbuf = outmsg+begin_index+share_rank0-share_others;
	}

	if(rank!=0){
		begin_index = share_rank0 + (rank-1)*share_others;
		my_share = share_others;
		sendbuf = outmsg+begin_index;
		}

	// Each rank fills its own share
	for(int i = begin_index; i<(begin_index+my_share); ++i) outmsg[i] = i+1;

	sendcount = share_others;
	recvcount = share_others;

	bool USE_MPI_IN_PLACE = true;

	if(USE_MPI_IN_PLACE){
		recvbuf = outmsg+share_rank0-share_others;
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Allgather(MPI_IN_PLACE, sendcount, MPI_DOUBLE,
				   recvbuf, recvcount, MPI_DOUBLE,
				   MPI_COMM_WORLD);
	}else{
		recvbuf = inmsg+share_rank0-share_others;
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Allgather(sendbuf, sendcount, MPI_DOUBLE,
				   recvbuf, recvcount, MPI_DOUBLE,
				   MPI_COMM_WORLD);
	}

	std::cout<<"MAX_SIZE = "<<MAX_SIZE<<" total ranks = "<<size<<"\n";
	std::cout<<"My chunk size = "<<my_share<<"\n";

	for(const auto& elem : outmsg) std::cout<<elem<<" ";
	std::cout<<"\n";
	for(const auto& elem : inmsg) std::cout<<elem<<" ";

	std::cout<<"\n";

	if(share_rank0!=share_others)
		std::cout<<"Since the elements are not equally divisible by total ranks,"
				" the first few elements are not gathered.";

	MPI_Finalize();

	return 0;
}
