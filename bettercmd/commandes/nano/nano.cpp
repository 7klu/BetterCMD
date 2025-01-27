#include <iostream>
#include "nano.h"

void nanoCmd(const std::string& filepath) {
    if (!filepath.empty()) {
        system(("notepad " + filepath).c_str());
    } else {
        system("notepad");
    }
}
