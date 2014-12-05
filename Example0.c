#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>


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
