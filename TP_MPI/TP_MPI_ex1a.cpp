#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char ** argv)
{
    MPI_Init(&argc, &argv);

    int worldRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
    cout << "Hello, I am process #" << worldRank << endl; 

    MPI_Finalize();
    return 0;
}

