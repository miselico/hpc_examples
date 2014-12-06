#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

/**
 * An non-optimal solution for the ring communication pattern (improvement in Example3c).
 * 
 * The 0th process starts by receiving, all the others by sending. This way each of the communications will take place.
 * However, the overall performance will be low because the send operations happen sequentially.
 * 
 * Can be run with any number of cores
 */
int main(int argc, char *argv[])
{
    int i, myid, ntasks;
    int sendTo;
    int receiveFrom;
    int size = 100000;
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
    if (myid == 0) {
        MPI_Send(message, size, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Recv(receiveBuffer, size, MPI_INT, 1, 2, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        printf("Rank %i received %i\n", myid, receiveBuffer[0]);
    } else {
        MPI_Recv(receiveBuffer, size, MPI_INT, 0, 1, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        MPI_Send(message, size, MPI_INT, 0, 2, MPI_COMM_WORLD);
        printf("Rank %i received %i\n", myid, receiveBuffer[0]);
    }

    free(message);
    free(receiveBuffer);
    MPI_Finalize();
    return 0;
}
