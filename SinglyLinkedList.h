//
// Created by User on 14.04.2025.
//
#ifndef SD_1_LISTA_MAIN_SINGLYLINKEDLIST_H
#define SD_1_LISTA_MAIN_SINGLYLINKEDLIST_H
#endif //SD_1_LISTA_MAIN_SINGLYLINKEDLIST_H
#pragma once
#include "BaseList.hpp"

template<typename T>
struct SinglyLinkedListNode {
    T value;
    SinglyLinkedListNode *next;
};

template<class T>
class SinglyLinkedList : public BaseList<T> {
public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    void push_front(T value) override;
    void push_back(T value) override;
    void insert(T value, int index) override;
    T remove_front() override;
    T remove_back() override;
    T remove(int index) override;
    T get(int index) override;
    int count() override;
    int search(T value) override;

private:
    SinglyLinkedListNode<T> *head;
    SinglyLinkedListNode<T> *tail;
    int size;
};