
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

int main(int argc, char ** argv)
{
    // verifie les parametres de la ligne de commande
    if (argc != 2)
    {
        std::cout << "usage: " << argv[0] << " <nbData>" << std::endl;
        return -1;
    }

    // calcule le tableau de donnees
    int nbData = std::stoi(argv[1]);
    std::vector<int> data(nbData); 
    // TODO
    for (int i=0; i<nbData; i++)
    {
        data[i] = FibonacciMod42(i);
    }

    // ecrit les donnees calculees dans un fichier
    std::ofstream ofs("output.txt");
    for (int x : data)
    {
        ofs << x << ' ';
    }

    return 0;
}

