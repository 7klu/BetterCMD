#include <iostream>
#include "help.h"

void helpCmd() {
    system("cls");
    std::cout << "+------------------------------------------+\n";
    std::cout << "| Commandes disponibles :                  |\n";
    std::cout << "+------------------------------------------+\n";
    std::cout << "| nano   : ouvre un éditeur de texte       |\n";
    std::cout << "| parrot : affiche un perroquet            |\n";
    std::cout << "| htop   : affiche les informations de la  |\n";
    std::cout << "|          mémoire et du CPU               |\n";
    std::cout << "| ls     : liste les fichiers du répertoire|\n";
    std::cout << "|          courant (non implémenté)        |\n";
    std::cout << "| say    : affiche un message              |\n";
    std::cout << "| exit   : quitte le programme             |\n";
    std::cout << "+------------------------------------------+\n";
}