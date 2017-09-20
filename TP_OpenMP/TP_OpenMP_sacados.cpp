
// g++ -std=c++11 -O2 -Wall -Wextra -fopenmp TP_OpenMP_sacados.cpp
// ./a.out 20 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include <omp.h>

void printCombo(const std::vector<int> & sources, uint64_t c)
{
    // check every bit of c
    auto iter = sources.begin();
    while (c != 0)
    {
        // display corresponding source if the least-significant bit is 1
        if (c & 1ULL)
            std::cout << *iter << ' ';
        // next bit/source
        c = c >> 1;
        ++iter;
    }
    std::cout << std::endl;
}

std::vector<uint64_t> computeCombosIterative1(
        const std::vector<int> & sources, int target)
{
    int nbSources = sources.size();
    assert(nbSources < 64);
    // generate all combos
    uint64_t kMax = 1ULL << nbSources;
    std::vector<uint64_t> combos;
    for (uint64_t k=0; k<kMax; k++)
    {
        auto iter = sources.begin();
        int s = 0;
        uint64_t c = k;
        // compute the sum of the sources corresponding to ones of c
        while (c != 0)
        {
            // add corresponding source if the least-significant bit is 1
            if (c & 1ULL)
                s += *iter;
            // next bit/source
            c = c >> 1;
            ++iter;
        }
        // store valid combos
        if (s == target)
            combos.push_back(k);
#ifdef DEBUG
        printCombo(sources, k);
#endif
    }
    return combos;
}

std::vector<uint64_t> computeCombosIterative2(
        const std::vector<int> & sources, int /*target*/)
{
    int nbSources = sources.size();
    assert(nbSources < 64);
    std::vector<uint64_t> combos;
    // TODO implementer le calcul avec elagage des sommes trop grandes
    return combos;
}

// WARNING: sort sources !!!
std::vector<uint64_t> computeCombosIterative3(
        std::vector<int> & sources, int /*target*/)
{
    int nbSources = sources.size();
    assert(nbSources < 64);
    std::vector<uint64_t> combos;
    // TODO implementer le calcul avec un tri des sources favorisant l'elagage
    return combos;
}

// WARNING: sort sources !!!
std::vector<uint64_t> computeCombosParallel(
        std::vector<int> & sources, int /*target*/)
{
    int nbSources = sources.size();
    assert(nbSources < 64);
    std::vector<uint64_t> combos;
    // TODO paralleliser en openmp la version tri + elagage
    return combos;
}

void computeCombosRecursive(const std::vector<int> & sources, int target, 
        std::vector<std::vector<int>> & combos, 
        std::vector<int> selectedSources = {}, unsigned depth=0)
{
    for (unsigned i=depth; i<sources.size(); i++)
    {
        selectedSources.push_back(sources[i]);
        int s = std::accumulate(selectedSources.begin(), 
                selectedSources.end(), 0);
        if (s == target)
            combos.push_back(selectedSources);
        computeCombosRecursive(sources, target, combos, selectedSources, i+1);
        selectedSources.pop_back();
    }
}

int main(int argc, char ** argv)
{
    // check arguments
    if (argc < 3)
    {
        std::cout << "usage: " << argv[0] << " <target> <sources...>" 
            << std::endl;
        exit(-1);
    }
    if (argc > 66)
    {
        std::cout << "error: too many sources (max = 64)" << std::endl;
        exit(-1);
    }

    // read arguments
    int target = std::stoi(argv[1]);
    int nbSources = argc - 2;
    std::vector<int> sources(nbSources); 
    for (int i=0; i<nbSources; i++)
        sources[i] = std::stoi(argv[i+2]);

    // compute combos
    std::vector<int> sourcesCopyIterative3(sources); // computeCombosIterative3
    std::vector<int> sourcesCopyParallel(sources);   // computeCombosParallel
    double t0 = omp_get_wtime();
    std::vector<uint64_t> combosIterative1 
        = computeCombosIterative1(sources, target);
    double t1 = omp_get_wtime();
    std::vector<uint64_t> combosIterative2 
        = computeCombosIterative2(sources, target);
    double t2 = omp_get_wtime();
    std::vector<uint64_t> combosIterative3 
        = computeCombosIterative3(sourcesCopyIterative3, target);
    double t3 = omp_get_wtime();
    std::vector<uint64_t> combosParallel 
        = computeCombosParallel(sourcesCopyParallel, target);
    double t4 = omp_get_wtime();
    std::vector<std::vector<int>> combosRecursive;
    computeCombosRecursive(sources, target, combosRecursive);
    double t5 = omp_get_wtime();

    // output data
    std::cout << "combosParallel:" << std::endl;
    for (uint64_t c : combosParallel)
        printCombo(sourcesCopyParallel, c);
    /*
    std::cout << "combosRecursive:" << std::endl;
    for (auto & c : combosRecursive)
    {
        for (int v : c)
            std::cout << v << " ";
        std::cout << std::endl;
    }
    */

    // output stats
    std::cout << "computeCombosIterative1; " << combosIterative1.size() 
        << "; " << t1-t0 << std::endl;
    std::cout << "computeCombosIterative2; " << combosIterative2.size() 
        << "; " << t2-t1 << std::endl;
    std::cout << "computeCombosIterative3; " << combosIterative3.size() 
        << "; " << t3-t2 << std::endl;
    std::cout << "computeCombosParallel;   " << combosParallel.size()   
        << "; " << t4-t3 << std::endl;
    std::cout << "computeCombosRecursive;  " << combosRecursive.size()  
        << "; " << t5-t4 << std::endl;

    return 0;
}

