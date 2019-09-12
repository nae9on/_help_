/*
 * gather_tutorial.cpp
 *
 *  Created on: Sep 12, 2019
 *      Author: akadar
 *
 * In this tutorial, rank 0 owns an array [0:MAX_SIZE-1] which must be filled with
 * integers 1,2.. MAX_SIZE. rank 0 fills the first MAX_SIZE/SIZE elements.
 * rank i fills the ith chunk of size MAX_SIZE/SIZE elements. rank 0 finally gathers
 * all the chunks to fill the complete array.
 *
 * Note that all ranks should get equal chunk size = MAX_SIZE/SIZE elements.
 * In a special case, root process can have a different chunk size than the rest (having
 * the same chunk size).
 *
 * Reference:
 * https://www.open-mpi.org/doc/v3.0/man3/MPI_Gather.3.php
 *
 */

#include <iostream>
#include <mpi.h>
#include <cmath>
#include <cassert>

#define MAX_SIZE 10

int gather_tutorial(int argc, char* argv[]){

	int size, rank;
	double outmsg[MAX_SIZE], inmsg[MAX_SIZE];

	// Initialize array
	for(int i = 0; i<MAX_SIZE; ++i) {outmsg[i] = 0; inmsg[i] = 0;}

	int my_share, share_others, share_rank0, begin_index;

	int root{0};

	double* sendbuf;
	int  sendcount;
	double* recvbuf;
	int recvcount;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	// Calculate share of processing elements for each rank
	share_others = std::floor(MAX_SIZE/size);
	share_rank0 = MAX_SIZE-share_others*(size-1);

	if(rank==0){

		begin_index = 0;
		my_share = share_rank0;

		// Each rank fills its own share
		for(int i = begin_index; i<(begin_index+my_share); ++i) outmsg[i] = i+1;

		/*
		 * MPI_IN_PLACE option converts the receive buffer into a send-and-receive buffer.
		 * When MPI_IN_PLACE is not used the root also sends contents of its send buffer
		 * to itself.
		 */

		bool USE_MPI_IN_PLACE = true;

		if(USE_MPI_IN_PLACE){
			// sendbuf, sendcount and sendtype are ignored in this case.
			sendbuf = nullptr;
			sendcount = -1;
			recvbuf = outmsg+share_rank0-share_others; // carefully note this!
			recvcount = share_others; // the number of items it receives from each process.
			MPI_Barrier(MPI_COMM_WORLD);
			MPI_Gather(MPI_IN_PLACE, sendcount, MPI_DOUBLE,
					  recvbuf, recvcount, MPI_DOUBLE,
					  root, MPI_COMM_WORLD);
		}else{
			sendbuf = outmsg+begin_index;
			sendcount = my_share;
			recvbuf = inmsg;
			recvcount = share_others; // the number of items it receives from each process.
			assert(sendcount==recvcount);  // Note share_rank0 and share_others must be equal
			MPI_Barrier(MPI_COMM_WORLD);
			MPI_Gather(sendbuf, sendcount, MPI_DOUBLE,
					  recvbuf, recvcount, MPI_DOUBLE,
					  root, MPI_COMM_WORLD);
		}
	}

	if(rank!=0){

		begin_index = share_rank0 + (rank-1)*share_others;
		my_share = share_others;

		// Each rank fills its own share
		for(int i = begin_index; i<(begin_index+my_share); ++i) outmsg[i] = i+1;

		// Each process sends the contents of its send buffer to the root process.
		sendbuf = outmsg+begin_index;
		sendcount = my_share; // the number of items each process sends to root must be equal.
		recvbuf = nullptr; // the receive buffer is ignored for all non-root processes.
		recvcount = 0; // the receive buffer is ignored for all non-root processes.

		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Gather(sendbuf, sendcount, MPI_DOUBLE,
		           recvbuf, recvcount, MPI_DOUBLE,
				   root, MPI_COMM_WORLD);
		}

	std::cout<<"MAX_SIZE = "<<MAX_SIZE<<" total ranks = "<<size<<"\n";
	std::cout<<"My chunk size = "<<my_share<<"\n";

	for(const auto& elem : outmsg) std::cout<<elem<<" ";
	std::cout<<"\n";
	for(const auto& elem : inmsg) std::cout<<elem<<" ";

	std::cout<<"\n";

	MPI_Finalize();

	return 0;
}
