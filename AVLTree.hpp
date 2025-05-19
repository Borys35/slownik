#pragma once

#include <algorithm>

template<typename T>
struct AVLNode {
    T key;
    T value;
    int height;
    AVLNode *left;
    AVLNode *right;

    AVLNode(T key, T value) {
        this->key = key;
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
};

template<class T>
class AVLTree {
public:

    AVLTree();
    ~AVLTree();
    AVLNode<T>* insert(AVLNode<T> *node, T key, T value);
    AVLNode<T>* remove(AVLNode<T> *node, T key);

private:
    int size = 0;
    AVLNode<T> *root;
    int height(AVLNode<T> *node);
    AVLNode<T>* leftRotate(AVLNode<T> *node);
    AVLNode<T>* rightRotate(AVLNode<T> *node);
};

template<class T>
AVLTree<T>::AVLTree() {

}

template<class T>
AVLTree<T>::~AVLTree() {

}

template<class T>
int AVLTree<T>::height(AVLNode<T> *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

template<class T>
AVLNode<T> *AVLTree<T>::leftRotate(AVLNode<T> *node) {
    AVLNode<T> *y = node->right;
    AVLNode<T> *x = y->left;

    y->left = node;
    node->right = x;

    node->height = std::max(height(node->left), height(node->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

template<class T>
AVLNode<T> *AVLTree<T>::rightRotate(AVLNode<T> *node) {
    AVLNode<T> *x = node->left;
    AVLNode<T> *y = x->right;

    x->right = node;
    node->left = y;

    node->height = std::max(height(node->left), height(node->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}


template<class T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T> *node, T key, T value) {
    ++this->size;

    // BST
    if (node == nullptr) {
        return new AVLNode(key, value);
    }

    if (key < node->key) {
        node->left = insert(node->left, key, value);
    } else if (key > node->key) {
        node->right = insert(node->right, key, value);
    } else {
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = height(node->left) - height(node->right);

    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

template<class T>
AVLNode<T>* AVLTree<T>::remove(AVLNode<T> *node, T key) {
    if (node == nullptr) {
        return node;
    }

    if (key < node->key) {
        node->left = remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key);
    }
    else {
        if (node->left == nullptr || node->right == nullptr) {
            AVLNode<T> *temp = node->left ? node->left : node->right;

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                node = temp;
            }

            delete temp;
        } else {
            AVLNode<T> *temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove(node->right, temp->key);
        }
    }

    if (node == nullptr) {
        return nullptr;
    }

    node->height = std::max(height(node->left), height(node->right)) + 1;

    int balance = height(node->left) - height(node->right);

    // LL
    if (balance > 1 && height(node->left->left) >= height(node->left->right)) {
        return rightRotate(node);
    }
    // LR
    if (balance > 1 && height(node->left->left) < height(node->left->right)) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RL
    if (balance < -1 && height(node->right->left) >= height(node->right->right)) {
        return leftRotate(node);
    }
    // RR
    if (balance < -1 && height(node->right->left) < height(node->right->right)) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}