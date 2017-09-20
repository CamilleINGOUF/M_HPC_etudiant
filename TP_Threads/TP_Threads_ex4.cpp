
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

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

void calculeTabThread(std::vector<int> & tab, int nbDataDebut, int nbDataFin
		      , int nbThreads)
{
  for (int i = nbDataDebut; i < nbDataFin; i+=nbThreads)
    tab[i] = (FibonacciMod42(i));
}

int main(int argc, char ** argv)
{
    // verifie les arguments de la ligne de commande
    if (argc != 3)
    {
        std::cout << "usage: " << argv[0] << " <nbData> <nbThreads>" << std::endl;
        return -1;
    }

    // cree le tableau de donnees a calculer
    int nbData = std::stoi(argv[1]);
    std::vector<int> data(nbData);

    //cree le tableau de Threads
    int nbThreads = std::stoi(argv[2]);
    std::vector<std::thread> threads(nbThreads);

    //début chrono
    std::chrono::time_point<std::chrono::system_clock> startTime
        = std::chrono::system_clock::now();

    // calcule le tableau de donnees 
    // calculeTab(data, nbData);
    for(int i = 0; i < nbThreads; i++)
      threads[i] = std::thread(calculeTabThread,std::ref(data),
		 i,nbData,nbThreads);

    for(int i = 0; i < nbThreads; i++)
      threads[i].join();
    
    //fin chrono
    std::chrono::time_point<std::chrono::system_clock> endTime
        = std::chrono::system_clock::now();

    std::chrono::duration<double> nbSeconds = endTime - startTime;

    std::cout << "temps de calcul = " << nbSeconds.count() << std::endl;

    // ecrit les donnees calculees dans un fichier
    std::ofstream ofs("output.txt");
    for (int x : data)
    {
        ofs << x << ' ';
    }

    return 0;
}

