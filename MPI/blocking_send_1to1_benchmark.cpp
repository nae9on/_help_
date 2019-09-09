/*
 * blocking_send_1to1_benchmark.cpp
 *
 *  Created on: Sep 9, 2019
 *      Author: akadar
 *
 * In this example, round trip timing test is performed.
 * rank 0 sends a message to rank 1 following which rank 1 sends the same message back to rank 0.
 * The experiment is repeated "REPS" number of times to calculate an ensemble average.
 * The experiment is also repeated for several message lengths.
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

int blocking_send_1to1_benchmark(int argc, char* argv[]){

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

	int dest, tag;
	int itr, count;

	double t1{0.0}, t2{0.0}, t3{0.0}, sumT1{0.0}, sumT2{0.0};
	std::vector<timeS> avgT;

	if(rank==0){

		dest = 1;
		tag = 100;

		for(count=0; count<=MAX_SIZE; count+=INCREMENT){
			sumT1 = 0; sumT2 = 0;
			for(itr=1; itr<=REPS; itr++){
				t1 = MPI_Wtime();
				MPI_Send(outmsg,count,MPI_DOUBLE,dest,tag,MPI_COMM_WORLD);
				t2 = MPI_Wtime();
				MPI_Recv(inmsg,count,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
				t3 = MPI_Wtime();
				sumT1 += t2 - t1;
				sumT2 += t3 - t2;
			}
			avgT.push_back(timeS(count,sumT1/REPS, sumT2/REPS));
		}

	}

	if(rank==1){

		dest = 0;
		tag = 200;

		for(count=0; count<=MAX_SIZE; count+=INCREMENT){
			sumT1 = 0; sumT2 = 0;
			for(itr=1; itr<=REPS; itr++){
				t1 = MPI_Wtime();
				MPI_Recv(inmsg,count,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
				t2 = MPI_Wtime();
				MPI_Send(outmsg,count,MPI_DOUBLE,dest,tag,MPI_COMM_WORLD);
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
