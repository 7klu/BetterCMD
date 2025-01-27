#include <iostream>
#include <sstream>

void echo_command(const std::string &input) {
    // Crée un flux de chaîne pour séparer la commande "echo"
    std::istringstream stream(input);
    std::string word;

    // Ignore le premier mot ("echo")
    stream >> word;

    // Affiche le reste de la chaîne
    std::string remaining_input;
    std::getline(stream, remaining_input);

    if (!remaining_input.empty()) {
        std::cout << remaining_input << std::endl;  // Affiche la chaîne restante
    }
}
