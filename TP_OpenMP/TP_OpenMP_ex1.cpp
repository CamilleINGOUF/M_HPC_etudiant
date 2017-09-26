
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <omp.h>

// calcule le Nieme terme de la suite de "Fibonacci modulo 42"
// precondition : N >= 0
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

int main(int argc, char ** argv)
{
    // verifie les parametres de la ligne de commande
    if (argc != 3)
    {
        std::cout << "usage: " << argv[0] << " <nbData> <nbThreads>" << std::endl;
        return -1;
    }

    // calcule le tableau de donnees
    int nbData = std::stoi(argv[1]);
    int nbThreads = std::stoi(argv[2]);
    std::vector<int> data(nbData);

    double t0 = omp_get_wtime(); 
    for (int i=0; i<nbData; i++)
	{
	  data[i] = FibonacciMod42(i);
	}
    double t1 = omp_get_wtime();
    double time = t1 - t0;
    std::cout << "Temps exe 1 Threads : " << time << std::endl;
    
    t0 = omp_get_wtime(); 
#pragma omp parallel  num_threads(nbThreads)
    {
#pragma omp for schedule (static,1)
      for (int i=0; i<nbData; i++)
	{
	  data[i] = FibonacciMod42(i);
	}
    }
    t1 = omp_get_wtime();
    double time2 = t1 - t0;
    std::cout << "Temps exe "<< nbThreads << " Threads : " << time2 << std::endl;
    std::cout << "Acceleration : " << time/time2 << std::endl;
    
    // ecrit les donnees calculees dans un fichier
    std::ofstream ofs("output.txt");
    for (int x : data)
    {
        ofs << x << ' ';
    }

    return 0;
}

