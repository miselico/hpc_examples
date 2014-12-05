#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>


int main(int argc, char *argv[])
{
    int i, myid, ntasks;
    
    int sendTo, receiveFrom;

    int size = 100;
    int *bottom;
    int *bottomghost;
    
    int *top;
    int *topghost;
    
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    

    /* Allocate layers */
    top = malloc(sizeof(int) * size);
    bottom = malloc(sizeof(int) * size);
    topghost = malloc(sizeof(int) * size);
    bottomghost = malloc(sizeof(int) * size);
    /* Put fake data */
    for (i = 0; i < size; i++)
    {
        top[i] = myid;
        bottom[i] = myid;
        topghost[i] = -1;
        bottomghost[i] = -1;
    }
    
    /*
     * Sending and receiving
     */
     
     //first top
    if (myid != ntasks - 1){
        sendTo = myid + 1;
    } else {
        sendTo = MPI_PROC_NULL;
    }
    if (myid != 0){
        receiveFrom = myid - 1;
    } else {
        receiveFrom = MPI_PROC_NULL;
    }
        
    MPI_Sendrecv(top, size, MPI_INT, sendTo, 0, topghost, size, MPI_INT, receiveFrom, 0, MPI_COMM_WORLD, &status);

     //then bottom
    if (myid != 0){
        sendTo = myid -1 ;
    } else {
        sendTo = MPI_PROC_NULL;
    }
    if (myid != ntasks - 1){
        receiveFrom = myid + 1;
    } else {
        receiveFrom = MPI_PROC_NULL;
    }

    MPI_Sendrecv(bottom, size, MPI_INT, sendTo, 0, bottomghost, size, MPI_INT, receiveFrom, 0, MPI_COMM_WORLD, &status);

    printf("Rank %i received %i and %i\n", myid, bottomghost[0], topghost[0]);

    free(bottom);
    free(bottomghost);
	free(top);
	free(topghost);
    MPI_Finalize();
    return 0;
}
