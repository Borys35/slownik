#include <iostream>

#include "AVLTree.hpp"
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