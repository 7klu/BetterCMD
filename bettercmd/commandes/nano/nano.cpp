#include <iostream>
#include <fstream>
#include <string>

#define MAX_PATH_LENGTH 260
#define MAX_LINE_LENGTH 1000

void lireFichier(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Impossible d'ouvrir le fichier " << filePath << std::endl;
        return;
    }

    std::cout << "\nContenu du fichier " << filePath << " :" << std::endl;
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}

int nano() {
    char filePath[MAX_PATH_LENGTH];
    char choix;

    do {
        std::cout << "\nEntrez le chemin du fichier (ou 'q' pour quitter) : ";
        if (!std::cin.getline(filePath, MAX_PATH_LENGTH)) {
            std::cout << "Erreur de saisie." << std::endl;
            continue;
        }

        // Vérifier si l'utilisateur veut quitter
        if (strcmp(filePath, "q") == 0) {
            break;
        }

        lireFichier(filePath);

        std::cout << "\nVoulez-vous lire un autre fichier ? (o/n) : ";
        std::cin >> choix;
        std::cin.ignore(); // Pour consommer le caractère newline restant

    } while (choix == 'o' || choix == 'O');

    std::cout << "Au revoir !" << std::endl;
    return 0;
}

