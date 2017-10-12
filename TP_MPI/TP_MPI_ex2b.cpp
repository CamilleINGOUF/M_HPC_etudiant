#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>

#include <mpi.h>

using namespace std;

// no comment
int FibonacciMod42(int N)
{
    int f_curr = 0;
    int f_prec = 1;
    for (int i=1; i<=N; i++)
    {
        int tmp = f_curr;
        f_curr = (f_curr + f_prec) % 42;
        f_prec = tmp;
    }
    return f_curr;
}

// compute the integral of this function over [0,1] to approximate pi
// FibonacciMod42(x*10000) -> otherwise, it would be too easy
double fPi(double x)
{
    return 4.0 / (1.0 + x*x) + FibonacciMod42(x*10000);
}

// compute numericaly the integral of the function f over the domain [a,b] using step s
// FibonacciMod42(x*10000) -> otherwise, it would be too easy
double computeIntegral(function<double(double)>f, double a, double b, double s)
{
    double r = 0.0;
    unsigned h = 0;
    for (double x=a; x<b; x+=s, h++)
    {
        r += f(x);
        r -= FibonacciMod42(x*10000);
    }
    return r*(b-a)/double(h);
}

int main(int argc, char ** argv)
{
    MPI_Init(&argc, &argv);

    int worldRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
    int worldSize;
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

    

    // parse command line arguments
    double step = 1e-6;
    if (argc < 2)
    {
        cout << "no step specified; using " << step << endl;
    }
    else
    {
        step = stod(argv[1]);
    }
    double borneA = worldRank * (1 /(double)worldSize);
    double borneB = borneA + (1 / (double)worldSize);

	
	
	double localsum;
	double globalsum;

	double t0 = MPI_Wtime();
	localsum = computeIntegral(fPi, borneA, borneB, step);
	
	MPI_Reduce(&localsum,&globalsum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	double t1 = MPI_Wtime();
    
    //Patron
    if(worldRank == 0)
      {
	cout << worldSize << " " << globalsum << " " << t1-t0 << endl;
      }
    
    MPI_Finalize();
    return 0;
}

