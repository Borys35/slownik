#include <iostream>
#include "Menu.h"

int main() {
    srand(time(nullptr));
    std::cout << "Program do testowania struktur danych - kolejki priorytetowe\n";
    std::cout << "=============================================\n\n";

    int wybor;
    std::cout << "Wybierz:\n";
    std::cout << "1. Uruchom menu testow wydajnosci\n";
    std::cout << "2. Uruchom testy funkcjonalne kolejek priorytetowych\n";
    std::cout << "Wybor: ";
    std::cin >> wybor;

    if (wybor == 1) {
        runMenu();
    } else if (wybor == 2) {
        // runAllTests();
    } else {
        std::cout << "Nieprawidlowy wybor.\n";
    }

    return 0;
}