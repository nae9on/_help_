/*
 * main.cpp
 *
 *  Created on: Sep 17, 2019
 *      Author: akadar
 */

#include <iostream>
#include <fstream> // ofstream class
#include <string> // std::to_string
#include <vector>
#include <algorithm>
#include <mpi.h>

#include "cart_grid.h"
#include "io.h"

#define DIMENSION 3
#define NODES_PER_PROCESS_PER_DIM 120 // Useful when WEAK Scaling is tested
#define MAX_GLOBAL_NODES_PER_DIM 120 // Useful when STRONG Scaling is tested
#define STRONG_OR_WEAK_SCALING 1 // 0 for STRONG, 1 for WEAK (as alpha in the HPC book)

double parabola(double x, double y, double z){
	double val{4*(0.25-(x-0.5)*(x-0.5))};
	return val;
}

int main(int argc, char* argv[]){

	int size, rank;
	MPI_Comm comm;
	double begin_time{0.0}, init_time{0.0}, loop_time{0.0};

	// Domain decomposition
	bool autoCartesianTopology{true};
	std::vector<int> domains(DIMENSION,0); // # of sub-domains
	std::vector<size_t> nodes(DIMENSION,0); // # of nodes in the sub-domain

	MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	begin_time = MPI_Wtime();

	if (autoCartesianTopology) {
		MPI_Dims_create(size, DIMENSION, domains.data());
	} else {
		std::fill(domains.begin(),domains.end(),1);
		domains[0] = size;
	}

	print_vec("Cartesian topology: ",domains);

	// Periodicity of the MPI processors. 0 - non periodic. 1 - periodic
	std::vector<int> periods(DIMENSION,0);

	// Makes a new communicator to which Cartesian topology information is attached
	MPI_Cart_create(MPI_COMM_WORLD, DIMENSION, domains.data(), periods.data(), 1, &comm);

	// Determines new rank in the new communicator
	MPI_Comm_rank(comm, &rank);

	// Determine process coordinates in the newly created Cartesian topology given its rank
	std::vector<int> coords(DIMENSION,0);
	MPI_Cart_coords(comm , rank, DIMENSION, coords.data());

	printf("My rank is %d\n", rank);
	print_vec("My coords are: ",coords);

	std::vector<double> offset(DIMENSION,0);

	// Assign # of nodes and offset for each sub-domain.
	for (int dir = 0; dir < DIMENSION; dir++) {

		if(STRONG_OR_WEAK_SCALING==0){
			int min_nodes = MAX_GLOBAL_NODES_PER_DIM / domains[dir];
			if (coords[dir] == 0){
				nodes[dir] = MAX_GLOBAL_NODES_PER_DIM - min_nodes * (domains[dir] - 1);
				offset[dir] = 0;
			}
			else{
				nodes[dir] = min_nodes;
				offset[dir] = MAX_GLOBAL_NODES_PER_DIM - min_nodes * (domains[dir] - 1);
				offset[dir] += (coords[dir]-1)*min_nodes;
			}
		}

		if(STRONG_OR_WEAK_SCALING==1){
			nodes[dir] = NODES_PER_PROCESS_PER_DIM;
			offset[dir] = coords[dir]*NODES_PER_PROCESS_PER_DIM;
		}
	}

	print_vec("Physical nodes: ",nodes);

	// Fill information about neighboring processors
	std::vector<int> neighbours;
	for (int dir = 0; dir < DIMENSION; dir++) {
		int source_rank; int dest_rank;
		MPI_Cart_shift(comm, dir, 1, &source_rank, &dest_rank);
		neighbours.push_back(source_rank);
		neighbours.push_back(dest_rank);
	}


	/*PHYSICS*************************************************************************************/

	// Grid spacing
	std::vector<double> delta(DIMENSION,0);
	if(STRONG_OR_WEAK_SCALING==0){
		std::fill(delta.begin(),delta.end(),static_cast<double>(1)/(MAX_GLOBAL_NODES_PER_DIM-1));
	}
	else if(STRONG_OR_WEAK_SCALING==1)
	{
		for(int dir=0; dir<DIMENSION; ++dir){
			delta[dir] = static_cast<double>(1)/(domains[dir]*NODES_PER_PROCESS_PER_DIM-1);
		}
	}

	// Time iteration
	auto it = std::min_element(std::begin(delta), std::end(delta));
	double dt{0.1*(*it)*(*it)}; // CFL condition dt = 0.1*dx*dx
	size_t totalIter{100};

	// Physical grid
	std::vector<double> global_origin(DIMENSION,0.0);
	cart_grid<DIMENSION> grid(nodes,neighbours,offset,delta,global_origin,dt);

	// Initial condition (default is zero for all grid points including boundaries)
	//grid.fill(rank); // fill by rank
	//grid.debug_fill(rank); // fill by a sequence of numbers for debugging
	grid.fill_interior(&parabola); // fill by a parabolic profile


	init_time = MPI_Wtime() - begin_time;
	std::cout<<"Time spent before beginning time loop = "<<init_time<<"\n";

	/*TIME LOOP***********************************************************************************/

	double start_time_in_loop{0.0}, comm_time{0.0}, jacobi_time{0.0};

	std::ofstream ofs("timing"+std::to_string(rank)+".csv");
	if(!ofs) {
		std::cout<<"Could not open target for writing";
		std::terminate();
	}

	for(size_t titr=1; titr<=totalIter; ++titr)
	{
		MPI_Barrier(MPI_COMM_WORLD);

		start_time_in_loop = MPI_Wtime();

		// perform a linear shift of data along all positive direction
		for(int dir=0; dir<DIMENSION; ++dir){

			int send_tag{7};
			MPI_Request request;
			MPI_Status status;
			int source_rank{grid.get_neighbour_rank(dir,"left")};
			int dest_rank{grid.get_neighbour_rank(dir,"right")};

			// initiate non-blocking receive from source
			if(source_rank!=MPI_PROC_NULL){
				//The request can be used later to query the status of the communication
				// or wait for its completion.
				MPI_Irecv(grid.get_inbuffer(), grid.get_bsize(dir), MPI_DOUBLE,
						source_rank, MPI_ANY_TAG, comm, &request);
			}

			// send to destination
			if(dest_rank!=MPI_PROC_NULL){
				grid.copy_sendrecv_buf(dir,"send","pos");
				MPI_Send(grid.get_outbuffer(), grid.get_bsize(dir), MPI_DOUBLE,
						dest_rank, send_tag, comm);
			}

			// fill receive buffer
			if(source_rank!=MPI_PROC_NULL){
				// A call to MPI_Wait returns when the operation identified by request is complete.
				MPI_Wait(&request,&status);
				grid.copy_sendrecv_buf(dir,"receive","pos");
			}

		} // end of for

		// perform a linear shift of data along all negative direction
		for(int dir=0; dir<DIMENSION; ++dir){

			int send_tag{7};
			MPI_Request request;
			MPI_Status status;
			int source_rank{grid.get_neighbour_rank(dir,"right")};
			int dest_rank{grid.get_neighbour_rank(dir,"left")};

			// initiate non-blocking receive from source
			if(source_rank!=MPI_PROC_NULL){
				//The request can be used later to query the status of the communication
				// or wait for its completion.
				MPI_Irecv(grid.get_inbuffer(), grid.get_bsize(dir), MPI_DOUBLE,
						source_rank, MPI_ANY_TAG, comm, &request);
			}

			// send to destination
			if(dest_rank!=MPI_PROC_NULL){
				grid.copy_sendrecv_buf(dir,"send","neg");
				MPI_Send(grid.get_outbuffer(), grid.get_bsize(dir), MPI_DOUBLE,
						dest_rank, send_tag, comm);
			}

			// fill receive buffer
			if(source_rank!=MPI_PROC_NULL){
				// A call to MPI_Wait returns when the operation identified by request is complete.
				MPI_Wait(&request,&status);
				grid.copy_sendrecv_buf(dir,"receive","neg");
			}

		} // end of for

		comm_time = MPI_Wtime() - start_time_in_loop;

		grid.exec_jacobi_kernel();

		jacobi_time = MPI_Wtime() - start_time_in_loop - comm_time;

		ofs<<comm_time<<","<<jacobi_time<<"\n";

	} // end of time loop


	loop_time = MPI_Wtime() - begin_time - init_time;
	std::cout<<"Time spent in the time loop = "<<loop_time<<"\n";

	grid.print_info();
	//grid.print_grid_data();

	MPI_Finalize();
	return 0;
}
