#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>


int main(int argc, char *argv[])
{
    int i, myid, ntasks;
    int sendTo;
    int receiveFrom;
    int size = 100;
    int *message;
    int *receiveBuffer;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    
    sendTo = (myid + 1) % ntasks;
    receiveFrom = (myid - 1) % ntasks;

    /* Allocate message */
    message = malloc(sizeof(int) * size);
    receiveBuffer = malloc(sizeof(int) * size);
    /* Initialize message */
    for (i = 0; i < size; i++)
        message[i] = myid;

    /* Send and receive messages */
    MPI_Send(message, size, MPI_INT, sendTo, 0, MPI_COMM_WORLD);
    MPI_Recv(receiveBuffer, size, MPI_INT, receiveFrom, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    printf("Rank %i received %i\n", myid, receiveBuffer[0]);

    free(message);
    free(receiveBuffer);
    MPI_Finalize();
    return 0;
}
