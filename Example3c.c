#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

/**
 * The preferred solution for the ring communication patters.
 * 
 * Each process is sending and receiving at the same time using Sendrecv
 *
 * Can be run with any number of cores
 */
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

    /* Send and receive messages at the same time*/
    
    //MPI_Sendrecv(content to be send, amount to be send, type to be send, destination, tag,
    //               buffer for receiving, amount to be received, type to be received, sender rank, tag,
    //               communicator, status)
    MPI_Sendrecv(message, size, MPI_INT, sendTo, 0, receiveBuffer, size, MPI_INT, receiveFrom, 0, MPI_COMM_WORLD, &status);

    printf("Rank %i received %i\n", myid, receiveBuffer[0]);

    free(message);
    free(receiveBuffer);
    MPI_Finalize();
    return 0;
}
