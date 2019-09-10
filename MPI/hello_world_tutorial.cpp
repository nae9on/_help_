/*
 * hello_world_tutorial.cpp
 *
 *  Created on: Sep 4, 2019
 *      Author: akadar
 */

// References:
// [1] https://computing.llnl.gov/tutorials/mpi
// [2] https://computing.llnl.gov/tutorials/mpi/errorHandlers.pdf

#include <iostream>
#include <mpi.h> // To include the signatures of MPI library function calls.

int hello_world_tutorial(int argc, char* argv[]){

	int size, rank, flag;

	MPI_Initialized(&flag);

	if(flag==0) std::cout<<"MPI_Init not called yet.\n";

	// MPI_Init initializes the MPI execution environment.
	// This function must be called in every MPI program (and only once),
	// It must be called by the main thread only.
	// No MPI calls can be made before call to MPI_Init.
	MPI_Init(&argc, &argv);

	// Measure wall clock time
	double start_time = MPI_Wtime();

	// Get the size of the default communicator (group of participating processes).
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Get the process rank in the communicator.
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	std::cout<<"Hello World!, my rank is "<<rank<<" in communicator of size "<<size<<"\n";

	double stop_time = MPI_Wtime();
	std::cout<<"Total elapsed time = "<<stop_time-start_time<<" sec\n";

	// MPI_Finalize	terminates MPI execution environment.
	// It must be called by the same thread which called MPI_Init.
	// No MPI calls can be made after call to MPI_Finalize.
	int errorCode = MPI_Finalize();

	/*
	 * All MPI routines (except MPI_Wtime and MPI_Wtick) return an error value.
	 * Before the value is returned, the current MPI error handler is called.
	 * By default, this error handler called "MPI_ERRORS_ARE_FATAL" aborts the
	 * MPI job.
	 *
	 * However, the error handler can be changed to "MPI_ERRORS_RETURN". When
	 * this is done, the program will no longer abort on having detected an MPI
	 * error, instead the error will be returned and could be handled by the
	 * user program [2].	 *
	 *
	 * Note that MPI does not guarantee that an MPI program can continue past
	 * an error; however, MPI implementations will attempt to continue whenever
	 * possible.
	 */

	// Note MPI_SUCCESS = 0
	if(errorCode!=MPI_SUCCESS) std::cout<<"MPI routine failed.\n";
	std::cout<<"After calling MPI_Finalize.\n";
	return 0;
}
