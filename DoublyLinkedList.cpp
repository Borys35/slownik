//
// Created by borys on 02/04/2025.
//

#include "DoublyLinkedList.hpp"

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(): head(nullptr), tail(nullptr) {
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList() = default;

template<class T>
void DoublyLinkedList<T>::push_back(T value) {
    auto *node = new DoublyLinkedListNode<T>;
    node->value = value;
    node->prev = this->tail;
    node->next = nullptr;
    if (this->tail == nullptr) {
        this->head = node;
        this->tail = node;
    } else {
        this->tail->next = node;
        this->tail = node;
    }
    size++;
}

template<class T>
void DoublyLinkedList<T>::push_front(T value) {
    auto *node = new DoublyLinkedListNode<T>;
    node->value = value;
    node->next = this->head;
    node->prev = nullptr;
    if (this->head == nullptr) {
        this->head = node;
        this->tail = node;
    } else {
        this->head->prev = node;
        this->head = node;
    }
    size++;
}

template<class T>
void DoublyLinkedList<T>::insert(T value, int index) {
    if (index == 0) {
        push_front(value);
        return;
    }

    if (index == size) {
        push_back(value);
        return;
    }

    if (this->head == nullptr || index < 0 || index > size) {
        // error;
        return;
    }

    DoublyLinkedListNode<T> *curNode;
    if (index < size / 2) {
        curNode = this->head;
        for (int i = 0; i < index; i++) {
            if (curNode->next != nullptr) {
                curNode = curNode->next;
            } else {
                // error
                return;
            }
        }
    } else {
        curNode = this->tail;
        for (int i = size - 1; i >= index; i--) {
            if (curNode->prev != nullptr) {
                curNode = curNode->prev;
            } else {
                // error
                return;
            }
        }
    }


    auto *newNode = new DoublyLinkedListNode<T>;
    newNode->value = value;
    newNode->prev = curNode->prev;
    newNode->next = curNode;

    curNode->prev->next = newNode;
    curNode->prev = newNode;

    size++;
}

template<class T>
T DoublyLinkedList<T>::remove_front() {
    if (this->head == nullptr) {
        // error
        return -1;
    }
    T v = this->head->value;

    if (this->head == this->tail) {
        delete this->head;
        this->head = nullptr;
        this->tail = nullptr;
    } else {
        DoublyLinkedListNode<T> *temp = this->head;
        this->head = this->head->next;
        this->head->prev = nullptr;
        delete temp;
    }

    size--;
    return v;
}

template<class T>
T DoublyLinkedList<T>::remove_back() {
    if (this->tail == nullptr) {
        // error
        return -1;
    }
    T v = this->tail->value;

    if (this->head == this->tail) {
        delete this->tail;
        this->head = nullptr;
        this->tail = nullptr;
    } else {
        DoublyLinkedListNode<T> *temp = this->tail;
        this->tail = this->tail->prev;
        this->tail->next = nullptr;
        delete temp;
    }

    size--;
    return v;
}

template<class T>
T DoublyLinkedList<T>::remove(int index) {
    if (this->head == nullptr || index < 0 || index >= size) {
        // error
        return -1;
    }

    if (index == 0) {
        return remove_front();
    }

    if (index == size - 1) {
        return remove_back();
    }

    DoublyLinkedListNode<T> *curNode = this->head;
    for (int i = 0; i < index; i++) {
        curNode = curNode->next;
    }

    curNode->next->prev = curNode->prev;
    curNode->prev->next = curNode->next;
    T v = curNode->value;
    delete curNode;

    size--;
    return v;
}

template<class T>
T DoublyLinkedList<T>::get(int index) {
    if (index < 0 || index >= size) {
        // error
        return -1;
    }

    if (index == 0) {
        return this->head->value;
    }

    if (index == size - 1) {
        return this->tail->value;
    }

    DoublyLinkedListNode<T> *curNode = this->head;
    for (int i = 0; i < index; i++) {
        curNode = curNode->next;
    }

    return curNode->value;
}

template<class T>
int DoublyLinkedList<T>::count() {
    return size;
}

template<class T>
int DoublyLinkedList<T>::search(T value) {
    DoublyLinkedListNode<T> *curNode = this->head;
    int index = 0;

    while (curNode != nullptr) {
        if (curNode->value == value) {
            return index;
        }
        curNode = curNode->next;
        index++;
    }

    return -1;
}

template class DoublyLinkedList<int>;