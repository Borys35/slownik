#pragma once

#include <iostream>

template <typename T>
struct LinearHashNode {
    T key;
    T value;
    bool occupied;
    bool deleted;

    LinearHashNode() : occupied(false), deleted(false) {}
    LinearHashNode(T k, T v) : key(k), value(v), occupied(true), deleted(false) {}
};

template <class T>
class LinearProbingHashTable {
public:
    LinearProbingHashTable(size_t capacity);
    ~LinearProbingHashTable();
    void insert(T key, T value);
    void remove(T key);
    void print();

private:
    LinearHashNode<T>* hashTable;
    size_t capacity;
    size_t size;
    size_t hash(T key);
    void rehash();
    bool shouldRehash();
};

template<class T>
LinearProbingHashTable<T>::LinearProbingHashTable(size_t capacity) {
    this->capacity = capacity;
    this->size = 0;
    hashTable = new LinearHashNode<T>[capacity];
}

template<class T>
LinearProbingHashTable<T>::~LinearProbingHashTable() {
    delete[] hashTable;
}

template<class T>
size_t LinearProbingHashTable<T>::hash(T key) {
    return key % capacity;
}

template<class T>
bool LinearProbingHashTable<T>::shouldRehash() {
    return static_cast<float>(size) / capacity >= 0.75;
}

template<class T>
void LinearProbingHashTable<T>::rehash() {
    size_t old_capacity = capacity;
    LinearHashNode<T>* old_table = hashTable;

    capacity *= 2;
    size = 0;
    hashTable = new LinearHashNode<T>[capacity];

    // Przepisz wszystkie elementy do nowej tablicy
    for (size_t i = 0; i < old_capacity; i++) {
        if (old_table[i].occupied && !old_table[i].deleted) {
            insert(old_table[i].key, old_table[i].value);
        }
    }

    delete[] old_table;
}

template<class T>
void LinearProbingHashTable<T>::insert(T key, T value) {
    if (shouldRehash()) {
        rehash();
    }

    size_t index = hash(key);
    size_t original_index = index;

    do {
        // Jeśli pozycja jest wolna lub została usunięta
        if (!hashTable[index].occupied || hashTable[index].deleted) {
            // POPRAWKA: Sprawdź czy to nowy element
            bool isNewElement = !hashTable[index].occupied || hashTable[index].deleted;
            hashTable[index] = LinearHashNode<T>(key, value);
            if (isNewElement) {
                size++;
            }
            return;
        }
            // Jeśli klucz już istnieje, aktualizuj wartość
        else if (hashTable[index].key == key && !hashTable[index].deleted) {
            hashTable[index].value = value;
            return;
        }

        // Linear probing - przejdź do następnej pozycji
        index = (index + 1) % capacity;
    } while (index != original_index);

    // Tablica jest pełna - nie powinno się zdarzyć dzięki rehash
    std::cout << "Blad: Tablica jest pelna!" << std::endl;
}

template<class T>
void LinearProbingHashTable<T>::remove(T key) {
    size_t index = hash(key);
    size_t original_index = index;

    do {
        if (!hashTable[index].occupied) {
            // Element nie istnieje
            return;
        }

        if (hashTable[index].key == key && !hashTable[index].deleted) {
            hashTable[index].deleted = true;
            size--;
            return;
        }

        index = (index + 1) % capacity;
    } while (index != original_index);
}

template<class T>
void LinearProbingHashTable<T>::print() {
    std::cout << "\nLinear Probing Hash Table:\n";
    for (size_t i = 0; i < capacity; i++) {
        if (hashTable[i].occupied && !hashTable[i].deleted) {
            std::cout << "Index " << i << ": " << hashTable[i].key << " -> " << hashTable[i].value << std::endl;
        }
    }
    std::cout << "Size: " << size << "/" << capacity << std::endl;
}