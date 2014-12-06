#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

/**
 * An example of a collective operation. The data which is available in node0 is broadcast to all other nodes.
 *
 * Can be run with any number of cores
 */
int main(int argc, char *argv[])
{
    int i, myid, ntasks;
    
    int sendTo, receiveFrom;

    int size = 100;
    int *data;
    
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    

    /* Allocate data */
    data = malloc(sizeof(int) * size);
    /* Put fake data */
    if (myid == 0){
        for (i = 0; i < size; i++)
        {
            data[i] = 5675;
        }
    }
    
    /*
     * Broadcast
     */
     
    MPI_Bcast(data, size, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Rank %i received %i\n", myid, data[45]);

	free(data);
    MPI_Finalize();
    return 0;
}
