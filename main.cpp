#include <iostream>

#include "AVLTree.hpp"
#include "AVLTreeHashTable.hpp"
#include "CuckooHashTable.hpp"
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

    /*AVLTreeHashTable<int> avl_tree_hash_table(16);

    for (int i = 0; i < 100; i++) {
        avl_tree_hash_table.insert(i, i*100);
    }

    avl_tree_hash_table.remove(5);
    avl_tree_hash_table.remove(2);*/

    int wybor;
    std::cout << "Wybierz:\n";
    std::cout << "1. Uruchom menu testow wydajnosci\n";
    // std::cout << "2. Uruchom testy funkcjonalne kolejek priorytetowych\n";
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