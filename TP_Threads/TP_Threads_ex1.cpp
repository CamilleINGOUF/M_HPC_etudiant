
#include <iostream>
#include <thread>

// fonction qui affiche l'id du thread qui l'execute
void noyauCalcul() 
{
    std::thread::id idThread = std::this_thread::get_id();
    std::cout << "Bonjour, je suis le thread " << idThread << std::endl;
}

int main(int , char ** )
{
    // affiche l'id du thread principal
    noyauCalcul();

    // TODO cree deux threads qui affiche leur id
    std::thread t1(noyauCalcul);
    std::thread t2(noyauCalcul);

    // TODO attend la fin de l'execution des threads
    t1.join();
    t2.join();

    
    return 0;
}

