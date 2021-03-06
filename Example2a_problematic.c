#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

/**
 * This is situation which could deadlock, depending on the MPI implementation and runtime conditions.
 * Both processes are sending at the same time to each other, and only when that is done they start receiving.
 * 
 * It might be that it still works because the message is small and the MPI runtime could buffer the message to be sent and let the program continue.
 * Example2_large is the same, but a larger message is sent.
 * 
 * ##########DO NOT USE THIS CODE!!
 * 
 */
int main(int argc, char *argv[])
{
    int i, myid, ntasks;
    int size = 100;
    int *message;
    int *receiveBuffer;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

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
    } else if (myid == 1) {
        MPI_Send(message, size, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Recv(receiveBuffer, size, MPI_INT, 0, 1, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        printf("Rank %i received %i\n", myid, receiveBuffer[0]);
    }

    free(message);
    free(receiveBuffer);
    MPI_Finalize();
    return 0;
}
