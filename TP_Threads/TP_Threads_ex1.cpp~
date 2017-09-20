
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

    // TODO attend la fin de l'execution des threads

    return 0;
}

