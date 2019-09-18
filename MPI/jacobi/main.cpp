/*
 * main.cpp
 *
 *  Created on: Sep 17, 2019
 *      Author: akadar
 */

#include <iostream>
#include <vector>
#include <mpi.h>
#include "cart_grid.h"
#include "io.h"

#define BEGIN 11
#define INCREMENT 10
#define MAX_GLOBAL_NODE_PER_DIM 6
#define REPS 1000
#define epsilon 1e-6

int main(int argc, char* argv[]){

	const int dim{3};

	int size, rank;
	MPI_Comm comm;

	// Domain decomposition
	bool autoCartesianTopology{true};
	std::vector<int> domains(dim,0); // # of sub-domains
	std::vector<size_t> nodes(dim,0); // # of nodes in the sub-domain

	MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (autoCartesianTopology) {
		MPI_Dims_create(size, dim, domains.data());
	} else {
		std::fill(domains.begin(),domains.end(),1);
		domains[0] = size;
	}

	print_vec("Cartesian topology: ",domains);

	// Periodicity of the MPI processors. 0 - non periodic. 1 - periodic
	std::vector<int> periods(dim,0);

	// Makes a new communicator to which Cartesian topology information is attached
	MPI_Cart_create(MPI_COMM_WORLD, dim, domains.data(), periods.data(), 1, &comm);

	// Determines new rank in the new communicator
	MPI_Comm_rank(comm, &rank);

	// Determine process coordinates in the newly created Cartesian topology given its rank
	std::vector<int> coords(dim,0);
	MPI_Cart_coords(comm , rank, dim, coords.data());

	printf("My rank is %d\n", rank);
	print_vec("My coords are: ",coords);

	// Assign # of nodes, cells and offset for each sub-domain.
	for (int dir = 0; dir < dim; dir++) {

		/*unsigned totatCells = (MAX_GLOBAL_NODE_PER_DIM - 1);
		int max_cells = totatCells / domains[dir];
		if (coords[dir] + 1 < domains[dir])
			cells[dir] = max_cells;
		else
			cells[dir] = totatCells - max_cells * (domains[dir] - 1);
		offset[dir] = max_cells * coords[dir];
		nodes[dir] = cells[dir] + 1;*/

		int min_nodes = MAX_GLOBAL_NODE_PER_DIM / domains[dir];
		if (coords[dir] == 0)
			nodes[dir] = MAX_GLOBAL_NODE_PER_DIM - min_nodes * (domains[dir] - 1);
		else
			nodes[dir] = min_nodes;
	}

	print_vec("Physical nodes: ",nodes);

	// Fill information about neighboring processors
	std::vector<int> neighbours;
	for (int dir = 0; dir < dim; dir++) {
		int source_rank; int dest_rank;
		MPI_Cart_shift(comm, dir, 1, &source_rank, &dest_rank);
		neighbours.push_back(source_rank);
		neighbours.push_back(dest_rank);
	}

	cart_grid<dim,1> grid(nodes);
	grid.set_neighbours(neighbours);
	grid.fill(rank);

	// perform a linear shift of data along all positive direction
	for(int dir=0; dir<dim; ++dir){

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

		// send to dest
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

	}

	// perform a linear shift of data along all negative direction
	for(int dir=0; dir<dim; ++dir){

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

		// send to dest
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

	}

	grid.print_info();
	grid.print_grid_data();

	MPI_Finalize();
	return 0;
}
