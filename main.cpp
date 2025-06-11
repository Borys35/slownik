#include <iostream>

#include "AVLTree.hpp"
#include "AVLTreeHashTable.hpp"
#include "CuckooHashTable.hpp"
#include "LinearProbingHashTable.h"
#include "Menu.h"

void preOrder(AVLNode<int> *root) {
    if (root != nullptr) {
        std::cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    srand(time(nullptr));
    std::cout << "Program do testowania slownika\n";
    std::cout << "=============================================\n\n";

    // Przykład użycia wszystkich trzech struktur
    std::cout << "Demonstracja struktur:\n\n";

    // AVL Tree Hash Table
    std::cout << "1. AVL Tree Hash Table:\n";
    AVLTreeHashTable<int> avl_tree_hash_table(8);
    for (int i = 0; i < 10; i++) {
        avl_tree_hash_table.insert(i, i*100);
    }
    avl_tree_hash_table.remove(5);
    std::cout << "   Dodano elementy 0-9, usunieto klucz 5\n";

    // Cuckoo Hashing
    std::cout << "2. Cuckoo Hash Table:\n";
    CuckooHashTable<int> cuckoo_table(8);
    for (int i = 0; i < 10; i++) {
        cuckoo_table.insert(i, i*200);
    }
    cuckoo_table.remove(3);
    std::cout << "   Dodano elementy 0-9, usunieto klucz 3\n";

    // Linear Probing Hash Table
    std::cout << "3. Linear Probing Hash Table:\n";
    LinearProbingHashTable<int> linear_table(8);
    for (int i = 0; i < 10; i++) {
        linear_table.insert(i, i*300);
    }
    linear_table.remove(7);
    std::cout << "   Dodano elementy 0-9, usunieto klucz 7\n";

    std::cout << "\n=============================================\n\n";

    int wybor;
    std::cout << "Wybierz:\n";
    std::cout << "1. Uruchom menu testow wydajnosci\n";
    std::cout << "2. Wyswietl przykladowe dane ze struktur\n";
    std::cout << "Wybor: ";
    std::cin >> wybor;

    if (wybor == 1) {
        runMenu();
    } else if (wybor == 2) {
        std::cout << "\nPrzykladowe dane:\n";
        std::cout << "Cuckoo Hash Table:\n";
        cuckoo_table.print();
        std::cout << "\nLinear Probing Hash Table:\n";
        linear_table.print();
    } else {
        std::cout << "Nieprawidlowy wybor.\n";
    }

    return 0;
}