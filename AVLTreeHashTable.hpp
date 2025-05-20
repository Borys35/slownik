#pragma once

#include "AVLTree.hpp"

template <class T>
class AVLTreeHashTable {
public:
    AVLTreeHashTable(size_t capacity);
    ~AVLTreeHashTable();
    void insert(T key, T value);
    void remove(T key);

private:
    size_t capacity;
    size_t total_size;
    AVLTree<int> avl_tree;
    AVLTree<int>* buckets;
    size_t hash(T key);
    void rehash();
};

template<class T>
AVLTreeHashTable<T>::AVLTreeHashTable(size_t capacity) {
    this->capacity = capacity;
    buckets = new AVLTree<int>[capacity];
    for (int i = 0; i < capacity; i++) {
        buckets[i] = AVLTree<int>();
    }
}

template<class T>
AVLTreeHashTable<T>::~AVLTreeHashTable() {
}

template<class T>
size_t AVLTreeHashTable<T>::hash(T key) {
    return key % capacity;
}

template<class T>
void AVLTreeHashTable<T>::rehash() {
    size_t old_capacity = this->capacity;
    AVLTree<T> *old_buckets = this->buckets;
    this->total_size = 0;

    this->capacity *= 2;
    this->buckets = new AVLTree<int>[this->capacity];

    for (size_t i = 0; i < capacity; i++) {
        this->buckets[i] = AVLTree<int>();
    }

    for (size_t i = 0; i < old_capacity; i++) {
        if (old_buckets[i].return_size() > 0) {
            auto allNodes = old_buckets[i].getAll();
            for (int j = 0; j < allNodes.count(); j++) {
                int newIndex = hash(allNodes.get(j)->key);
                this->buckets[newIndex].insert(allNodes.get(j)->key, allNodes.get(j)->value);
            }
        }
    }

    delete [] old_buckets;
}

template<class T>
void AVLTreeHashTable<T>::insert(T key, T value) {
    //rehash
    if (static_cast<float>(total_size) / capacity >= 0.75) {
        rehash();
    }

    //insert
    size_t index = hash(key);
    buckets[index].insert(key, value);
    ++total_size;
}

template<class T>
void AVLTreeHashTable<T>::remove(T key) {
    size_t index = hash(key);
    buckets[index].remove(key);
    --total_size;
}


