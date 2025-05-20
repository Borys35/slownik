#include <iostream>

#include "AVLTree.hpp"
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

    AVLTree<int> avl_tree;
    AVLNode<int>* root = nullptr;
    root = avl_tree.insert(root, 1, 10);
    root = avl_tree.insert(root, 2, 20);
    root = avl_tree.insert(root, 6, 60);
    root = avl_tree.insert(root, 7, 70);
    root = avl_tree.insert(root, 8, 80);
    root = avl_tree.insert(root, 3, 30);
    root = avl_tree.insert(root, 4, 40);
    root = avl_tree.insert(root, 5, 50);

    std::cout << "Preorder traversal : \n";
    preOrder(root);

    root = avl_tree.remove(root, 2);
    root = avl_tree.remove(root, 8);
    root = avl_tree.remove(root, 1);

    std::cout << "\nPreorder traversal after deletion : \n";
    preOrder(root);

    CuckooHashTable<int> cuckoo_hash_table(16);
    cuckoo_hash_table.insert(1, 10);
    cuckoo_hash_table.insert(2, 20);
    cuckoo_hash_table.insert(3, 60);
    cuckoo_hash_table.insert(4, 70);
    cuckoo_hash_table.insert(5, 80);
    cuckoo_hash_table.insert(6, 30);
    cuckoo_hash_table.insert(1, 20);
    cuckoo_hash_table.insert(6, 50);


    // cuckoo_hash_table.remove(1);
    cuckoo_hash_table.remove(4);
    cuckoo_hash_table.remove(3);

    cuckoo_hash_table.print();

    /*
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
    */

    return 0;
}