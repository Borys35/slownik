//
// Created on 14/04/2025.
//
#include "SinglyLinkedList.h"

template<class T>
SinglyLinkedList<T>::SinglyLinkedList(): head(nullptr), tail(nullptr), size(0) {
}

template<class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    SinglyLinkedListNode<T> *current = head;
    while (current != nullptr) {
        SinglyLinkedListNode<T> *next = current->next;
        delete current;
        current = next;
    }
}
template<class T>
void SinglyLinkedList<T>::push_back(T value) {
    auto *node = new SinglyLinkedListNode<T>;
    node->value = value;
    node->next = nullptr;

    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        tail = node;
    }

    size++;
}
template<class T>
void SinglyLinkedList<T>::push_front(T value) {
    auto *node = new SinglyLinkedListNode<T>;
    node->value = value;
    node->next = head;

    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        head = node;
    }

    size++;
}
template<class T>
void SinglyLinkedList<T>::insert(T value, int index) {
    if (index < 0 || index > size) {
        // error
        return;
    }
    if (index == 0) {
        push_front(value);
        return;
    }
    if (index == size) {
        push_back(value);
        return;
    }
    SinglyLinkedListNode<T> *current = head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    auto *node = new SinglyLinkedListNode<T>;
    node->value = value;
    node->next = current->next;
    current->next = node;
    size++;
}

template<class T>
T SinglyLinkedList<T>::remove_front() {
    if (head == nullptr) {
        // error
        return 0;
    }
    T value = head->value;
    SinglyLinkedListNode<T> *temp = head;
    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = head->next;
    }

    delete temp;
    size--;
    return value;
}

template<class T>
T SinglyLinkedList<T>::remove_back() {
    if (tail == nullptr) {
        // error
        return 0;
    }
    T value = tail->value;
    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        SinglyLinkedListNode<T> *current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    size--;
    return value;
}

template<class T>
T SinglyLinkedList<T>::remove(int index) {
    if (index < 0 || index >= size) {
        // error
        return 0;
    }
    if (index == 0) {
        return remove_front();
    }
    if (index == size - 1) {
        return remove_back();
    }

    SinglyLinkedListNode<T> *current = head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    SinglyLinkedListNode<T> *temp = current->next;
    T value = temp->value;
    current->next = temp->next;

    delete temp;
    size--;
    return value;
}

template<class T>
T SinglyLinkedList<T>::get(int index) {
    if (index < 0 || index >= size) {
        // error
        return 0;
    }
    if (index == 0) {
        return head->value;
    }
    if (index == size - 1) {
        return tail->value;
    }
    SinglyLinkedListNode<T> *current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
}

template<class T>
int SinglyLinkedList<T>::count() {
    return size;
}

template<class T>
int SinglyLinkedList<T>::search(T value) {
    SinglyLinkedListNode<T> *current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->value == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

template class SinglyLinkedList<int>;