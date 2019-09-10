/*
 * blocking_send_tutorial.cpp
 *
 *  Created on: Sep 4, 2019
 *      Author: akadar
 *
 * References:
 * [1] https://www.mcs.anl.gov/research/projects/mpi/sendmode.html
 * [2] https://computing.llnl.gov/tutorials/mpi_performance/
 */

#include <iostream>
#include <mpi.h>
#include <vector>
#include <cmath>

/*
 * MPI_Send performs a standard-mode, blocking send. MPI_Send will only "return" after it is
 * safe to modify sender's application buffer (also called send buffer) for reuse.
 *
 * Blocking imply that send will wait for the actual message transfer to take place before
 * the application buffer can be reused.
 *
 * Note that a blocking send can be synchronous or asynchronous. A synchronous send means
 * handshaking occurring with the receive task to confirm a safe send. The data is not
 * buffered (either at the sender or receiver end) in this case. An asynchronous send means
 * a system buffer (either at sender or receiver end) is used to hold the data.
 * 
 * Note: MPI_Send depending on the implementation can operate in both synchronous and asynchronous
 * mode. On the contrary, MPI_Ssend operates only in synchronous mode. Replace MPI_Send by
 * MPI_Ssend in the program to see the difference.
 *
 * Another type of blocking send is MPI_Bsend. MPI_Bsend returns immediately regardless of the
 * state of the receiver. It is dependent on the availability of a system buffer at the sender's
 * end and therefore is called "Buffered Send". It should only be used when absolutely
 * necessary [1].
 *
 * To learn more about other types of blocking send refer [1,2].
 */

void waste_time(size_t n){
	double sum{0.0};
	for (size_t i=1; i<=n; i++) sum+=std::pow(i,1/3);
}

// A test program where rank 0 sends x to all other participating ranks and
// receive's x^rank from them.
int blocking_send_tutorial(int argc, char* argv[]){

	int size, rank, dest, count = 1, tag1 = 7, tag2 = 11, errorCode;
	double inmsg, outmsg;
	MPI_Status status;
	std::vector<double> input = {0,1,2,3,4,5,6,7};
	std::vector<double> result(8,-1);
	double sumSquares{0.0};

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank==0){
		std::cout<<"I am master process\n";

		sumSquares = std::pow(input[0],2);

		// Sending work to the workers.
		for(dest=1; dest<size; dest++){
			outmsg = input[dest];
			// MPI_Send(buffer,count,type,dest,tag,comm)
			errorCode = MPI_Send(&outmsg,count,MPI_DOUBLE,dest,tag1,MPI_COMM_WORLD);
			if (errorCode!=MPI_SUCCESS) {
				std::cout<<"MPI_Send failed\n";
				MPI_Abort(MPI_COMM_WORLD, errorCode);
				std::terminate();
				}
		}

		// Receiving work from workers
		for(int itr=1; itr<size; itr++){
			// MPI_Recv(buffer,count,type,source,tag,comm,status)
			errorCode = MPI_Recv(&inmsg,count,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
			if (errorCode!=MPI_SUCCESS) {
				std::cout<<"MPI_Recv failed\n";
				MPI_Abort(MPI_COMM_WORLD, errorCode);
				std::terminate();
				}
			result[status.MPI_SOURCE] = inmsg;
			printf("Received %f from worker %d\n",inmsg,status.MPI_SOURCE);
			sumSquares = sumSquares + inmsg;
		}

		/*
		 * Master plans to continue its work here, but it will have to wait to return from
		 * size-1 MPI_Recv calls from the for-loop above, i.e. computation cannot overlap
		 * with communication. This problem is solved by non-blocking send-receive.
		 */

		// Finally printing sum of squares.
		std::cout<<"Sum of squares = "<<sumSquares<<"\n";
	}
	
	if(rank!=0){

		// Receiving work from master
		int expectedCount = 100;
		errorCode = MPI_Recv(&inmsg,expectedCount,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
		if (errorCode!=MPI_SUCCESS) {
			std::cout<<"MPI_Recv failed\n";
			MPI_Abort(MPI_COMM_WORLD, errorCode);
			std::terminate();
			}

		/*
		 * 	Points to be noted about MPI_Recv:
		 * 	1. MPI_ANY_SOURCE can be substituted by an expected source rank.
		 * 	2. MPI_ANY_TAG can be substituted by an expected tag.
		 * 	3. The status object can be queried to get the source rank and tag when the
		 * 	   wildcards MPI_ANY_SOURCE and MPI_ANY_TAG are used.
		 * 	4. The message received may be shorter than the expected count.
		 * 	5. The received count can be queried using MPI_Get_count function.
		 */

		MPI_Get_count(&status, MPI_DOUBLE, &count);
		printf("Rank %d received %f from rank=%d with tag %d and count %d.\n"
				,rank,inmsg,status.MPI_SOURCE,status.MPI_TAG,count);

		// Sending result to master
		outmsg = std::pow(inmsg,2);
		dest = 0;

		// rank 3 wasting time;
		if(rank==3) {
			waste_time(1000000);
			std::cout<<"Rank "<<rank<<" wastine time\n";
		}

		errorCode = MPI_Send(&outmsg,count,MPI_DOUBLE,dest,tag2,MPI_COMM_WORLD);
		if (errorCode!=MPI_SUCCESS) {
			std::cout<<"MPI_Send failed\n";
			MPI_Abort(MPI_COMM_WORLD, errorCode);
			std::terminate();
			}
	}
	
	MPI_Finalize();
	return 0;
}
