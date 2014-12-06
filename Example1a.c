#include<stdio.h>
#include "mpi.h"

//Adapted from : http://www.mpi-forum.org/docs/mpi-3.0/mpi30-report.pdf

/**
 * Minimal MPI program
 * 
 * Process 0 sends a message to process 1, containing the text "Hello, there".
 * MPI_Send and MPI_Recv are blocking operations.
 * 
 * Run with two cores
 * 
 */
int main( int argc, char *argv[])
{
    char message[20];
    int myrank;
    MPI_Status status;
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
    if (myrank == 0)
     /* code for process zero */
    {
        strcpy(message,"Hello, there");
        //MPI_Send(content, length of content, type of elements, rank of destination, tag, communicator)
        MPI_Send(message, strlen(message)+1, MPI_CHAR, 1, 99, MPI_COMM_WORLD);
    }
    else if (myrank == 1) /* code for process one */
    {
        //MPI_Recv(content, max length, type of elements, rank of sender, tag, communicator, status-out)
        MPI_Recv(message, 20, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status);
        printf("received :%s:\n", message);
    }
    MPI_Finalize();
    return 0;
}
