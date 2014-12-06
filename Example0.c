#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

/**
 * Basic skeleton for MPI applications. 
 * Each process gets its rank and the total number of processes, and prints this information.
 * Note about C : when the address of a parameter is passed to a function (like &myrank), the function can change its value. 
 * 
 * Can be run with any number of cores
 */
int main(int argc, char *argv[])
{
    int myrank, ntasks;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    
    printf("I have rank %i out of %i\n", myrank, ntasks);
    
    MPI_Finalize();
    return 0;
}
