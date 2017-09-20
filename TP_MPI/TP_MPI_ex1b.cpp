#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char ** argv)
{
    MPI_Init(&argc, &argv);
    int worldSize;
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    int worldRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
    double t0 = MPI_Wtime();

    if (worldRank == 0)  // master node
    {
        // receive messages from other nodes
        for (int i=1; i<worldSize; i++)
        {
            char inMsg[50];
            MPI_Status status;
            MPI_Recv(&inMsg, sizeof(inMsg), MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status); 
            cout << "Process #" << status.MPI_SOURCE << " sent: " << inMsg << endl;
        }
        double t1 = MPI_Wtime();
        cout << "walltime = " << t1 - t0 << " s" << endl;
    }
    else  // other nodes
    {
        // send message to master node
        char outMsg[] = "hello";
        MPI_Send(outMsg, sizeof(outMsg), MPI_CHAR, 0, 0, MPI_COMM_WORLD);         
    }

    MPI_Finalize();
    return 0;
}

