/*
 * derived_datatype.cpp
 *
 *  Created on: Oct 2, 2019
 *      Author: akadar
 *
 * This simple example demonstrates the use of struct derived data type with MPI.
 *
 * Reference:
 * https://computing.llnl.gov/tutorials/mpi/#Derived_Data_Types
 */

#include "mpi.h"
#include <stdio.h>
#define NELEM 25

struct Particle{
	float x, y, z;
	float velocity;
	int n, type;
};

int derived_datatype(int argc, char *argv[]) {

int numtasks, rank, source=0, dest, tag=1, i;

const int num_blocks{2};
Particle     p[NELEM], particles[NELEM];
MPI_Datatype newtype, array_of_types[num_blocks];
int          array_of_blocklengths[num_blocks];

// MPI_Aint is a type in the C language, like int, double or a struct
MPI_Aint    array_of_displacements[num_blocks], extent;

MPI_Status stat;

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

// Setup description of the 4 MPI_FLOAT fields x, y, z, velocity
array_of_displacements[0] = 0;
array_of_types[0] = MPI_FLOAT;
array_of_blocklengths[0] = 4;

// Setup description of the 2 MPI_INT fields n, type
// Need to first figure offset by getting size of MPI_FLOAT
MPI_Type_extent(MPI_FLOAT, &extent);
array_of_displacements[1] = array_of_blocklengths[0] * extent;
array_of_types[1] = MPI_INT;
array_of_blocklengths[1] = 2;

// Define structured type and commit it
MPI_Type_create_struct(num_blocks, array_of_blocklengths, array_of_displacements, array_of_types, &newtype);
MPI_Type_commit(&newtype);

// Task 0 initializes the particle array and then sends it to each task
if (rank == 0) {
 for (i=0; i<NELEM; i++) {
	particles[i].x = i * 1.0;
	particles[i].y = i * -1.0;
	particles[i].z = i * 1.0;
	particles[i].velocity = 0.25;
	particles[i].n = i;
	particles[i].type = i % 2;
	}
 for (i=0; i<numtasks; i++)
	MPI_Send(particles, NELEM, newtype, i, tag, MPI_COMM_WORLD);
}

// All tasks receive newtype data
MPI_Recv(p, NELEM, newtype, source, tag, MPI_COMM_WORLD, &stat);

printf("rank= %d %3.2f %3.2f %3.2f %3.2f %d %d\n", rank,p[3].x,
	p[3].y,p[3].z,p[3].velocity,p[3].n,p[3].type);

// Free datatype when done using it
MPI_Type_free(&newtype);
MPI_Finalize();

return 0;
}
