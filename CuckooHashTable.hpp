#pragma once
#include "ArrayList.hpp"

template <typename T>
struct HashNode {
    T key;
    T value;

    bool operator==(const HashNode<T> &other) const {
        return key == other.key;
    }
};

template <class T>
class CuckooHashTable {
public:
    CuckooHashTable(int capacity);
    ~CuckooHashTable();
    void insert(T key, T value);
    void remove(T key);
    void print();
private:
    HashNode<T> **hashTable1;
    HashNode<T> **hashTable2;
    T hash1(T key);
    T hash2(T key);
    void rehash();
    int capacity = 0;
};

template<class T>
CuckooHashTable<T>::CuckooHashTable(int capacity) {
    this->capacity = capacity;
    hashTable1 = new HashNode<T>*[capacity];
    hashTable2 = new HashNode<T>*[capacity];
    for (int i = 0; i < capacity; i++) {
        hashTable1[i] = nullptr;
        hashTable2[i] = nullptr;
    }
}

template<class T>
CuckooHashTable<T>::~CuckooHashTable() {
    // POPRAWKA: Najpierw zwolnij pojedyncze węzły
    for (int i = 0; i < capacity; i++) {
        if (hashTable1[i] != nullptr) {
            delete hashTable1[i];
        }
        if (hashTable2[i] != nullptr) {
            delete hashTable2[i];
        }
    }
    // Potem zwolnij tablice
    delete[] hashTable1;
    delete[] hashTable2;
}

template<class T>
T CuckooHashTable<T>::hash1(T key) {
    return key % capacity;
}

template<class T>
T CuckooHashTable<T>::hash2(T key) {
    return (key / capacity) % capacity;
}

template<class T>
void CuckooHashTable<T>::rehash() {
    int oldCapacity = this->capacity;
    auto **oldHashTable1 = this->hashTable1;
    auto **oldHashTable2 = this->hashTable2;

    this->capacity = this->capacity * 2;
    this->hashTable1 = new HashNode<T>*[this->capacity];
    this->hashTable2 = new HashNode<T>*[this->capacity];

    for (int i = 0; i < this->capacity; i++) {
        this->hashTable1[i] = nullptr;
        this->hashTable2[i] = nullptr;
    }

    for (int i = 0; i < oldCapacity; i++) {
        if (oldHashTable1[i] != nullptr) {
            insert(oldHashTable1[i]->key, oldHashTable1[i]->value);
            delete oldHashTable1[i];
        }
        if (oldHashTable2[i] != nullptr) {
            insert(oldHashTable2[i]->key, oldHashTable2[i]->value);
            delete oldHashTable2[i];
        }
    }

    delete[] oldHashTable1;
    delete[] oldHashTable2;
}

template<class T>
void CuckooHashTable<T>::insert(T key, T value) {
    T i1 = hash1(key);
    T i2 = hash2(key);

    if (hashTable1[i1] != nullptr && hashTable1[i1]->key == key) {
        hashTable1[i1]->value = value;
        return;
    }
    if (hashTable2[i2] != nullptr && hashTable2[i2]->key == key) {
        hashTable2[i2]->value = value;
        return;
    }

    T currKey = key;
    T currValue = value;

    int loop = 0;
    int maxLoop = capacity * 2;

    while (loop < maxLoop) {
        i1 = hash1(currKey);

        if (hashTable1[i1] == nullptr) {
            hashTable1[i1] = new HashNode<T>{currKey, currValue};
            return;
        }

        HashNode<T> *displaced1 = hashTable1[i1];
        hashTable1[i1] = new HashNode<T>{currKey, currValue};
        currKey = displaced1->key;
        currValue = displaced1->value;
        delete displaced1;  // POPRAWKA: Zwolnij pamięć

        i2 = hash2(currKey);

        if (hashTable2[i2] == nullptr) {
            hashTable2[i2] = new HashNode<T>{currKey, currValue};
            return;
        }

        HashNode<T> *displaced2 = hashTable2[i2];
        hashTable2[i2] = new HashNode<T>{currKey, currValue};
        currKey = displaced2->key;
        currValue = displaced2->value;
        delete displaced2;  // POPRAWKA: Zwolnij pamięć

        ++loop;
    }

    rehash();
    insert(currKey, currValue);
}

template<class T>
void CuckooHashTable<T>::remove(T key) {
    T i1 = hash1(key);
    T i2 = hash2(key);

    if (hashTable1[i1] != nullptr && hashTable1[i1]->key == key) {
        delete hashTable1[i1];
        hashTable1[i1] = nullptr;
        return;  // POPRAWKA: Dodano return
    }
    if (hashTable2[i2] != nullptr && hashTable2[i2]->key == key) {
        delete hashTable2[i2];
        hashTable2[i2] = nullptr;
    }
}

template<class T>
void CuckooHashTable<T>::print() {
    std::cout << "\nHash 1\n";
    for (int i = 0; i < capacity; i++) {
        if (hashTable1[i] != nullptr) {
            std::cout << "Index " << i << ": " << hashTable1[i]->key << " -> " << hashTable1[i]->value;
            std::cout << std::endl;
        }
    }
    std::cout << "Hash 2\n";
    for (int i = 0; i < capacity; i++) {
        if (hashTable2[i] != nullptr) {
            std::cout << "Index " << i << ": " << hashTable2[i]->key << " -> " << hashTable2[i]->value;
            std::cout << std::endl;
        }
    }
}