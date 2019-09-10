/*
 * blocking_Sendrecv_1to1_benchmark.cpp
 *
 *  Created on: Sep 10, 2019
 *      Author: akadar
 *
 * In this example, round trip timing test is performed.
 * rank 0 communicates with rank 1 using Sendrecv communication routine.
 * The experiment is repeated "REPS" number of times to calculate an ensemble average.
 * The experiment is also repeated for several message lengths.
 *
 * The send-receive operations combine in one call the sending of a message to one
 * destination and the receiving of another message, from another process. The two
 * (source and destination) are possibly the same. A message sent by a send-receive
 * operation can be received by a regular receive operation; a send-receive operation
 * can receive a message sent by a regular send operation.
 *
 * Reference:
 * https://www.mpi-forum.org/docs/mpi-1.1/mpi-11-html/node52.html
 *
 */

#include <iostream>
#include <mpi.h>
#include <vector>
#include <iomanip>

#define MAX_SIZE 1000000
#define INCREMENT 1000
#define REPS 1000

struct timeS{
	timeS(int c_, double t1_, double t2_) : count{c_}, time1{t1_}, time2{t2_}{}
	int count; // count of doubles
	double time1; // time taken
	double time2; // time taken
};

int blocking_Sendrecv_1to1_benchmark(int argc, char* argv[]){

	printf("Rank 0 is sending %d:%d:%d doubles to Rank 1\n",0,INCREMENT,MAX_SIZE);

	int size, rank;

	std::vector<double> outData(MAX_SIZE,0.0);
	std::vector<double> inData(MAX_SIZE,0.0);

	double* outmsg = outData.data();
	double* inmsg = inData.data();

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int dest, source, sendtag, recvtag;
	int itr, count;

	double t1{0.0}, t2{0.0}, t3{0.0}, sumT1{0.0}, sumT2{0.0};
	std::vector<timeS> avgT;

	if(rank==0){

		dest = 1;
		source = 1;
		sendtag = 100;
		recvtag = 200;

		for(count=0; count<=MAX_SIZE; count+=INCREMENT){
			sumT1 = 0;
			for(itr=1; itr<=REPS; itr++){
				t1 = MPI_Wtime();
				MPI_Sendrecv(outmsg,count,MPI_DOUBLE,dest,sendtag,
						      inmsg,count,MPI_DOUBLE,
						      source, recvtag,
						      MPI_COMM_WORLD, &status);
				t2 = MPI_Wtime();
				sumT1 += t2 - t1;
			}
			avgT.push_back(timeS(count,sumT1/REPS, 0.0));
		}

	}

	if(rank==1){

		source = 0;
		dest = 0;
		sendtag = 200;
		recvtag = 100;

		for(count=0; count<=MAX_SIZE; count+=INCREMENT){
			sumT1 = 0; sumT2 = 0;
			for(itr=1; itr<=REPS; itr++){
				t1 = MPI_Wtime();
				MPI_Recv(inmsg,count,MPI_DOUBLE,source,recvtag,MPI_COMM_WORLD,&status);
				t2 = MPI_Wtime();
				// calculate outmsg = f(inmsg)
				MPI_Send(outmsg,count,MPI_DOUBLE,dest,sendtag,MPI_COMM_WORLD);
				t3 = MPI_Wtime();
				sumT1 += t2 - t1;
				sumT2 += t3 - t2;
			}
			avgT.push_back(timeS(count,sumT1/REPS, sumT2/REPS));
		}

	}

	for(const auto& elem : avgT)
		std::cout<<std::left<<std::setw(15)<<elem.count
		         <<std::left<<std::setw(15)<<elem.time1
	             <<std::left<<std::setw(15)<<elem.time2<<"\n";

	MPI_Finalize();
	return 0;
}


