#pragma once

#include "BaseList.hpp"

template<typename T>
struct DoublyLinkedListNode {
    T value;
    DoublyLinkedListNode *next;
    DoublyLinkedListNode *prev;
};

template<class T>
class DoublyLinkedList : public BaseList<T> {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
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
    DoublyLinkedListNode<T> *head;
    DoublyLinkedListNode<T> *tail;
    int size = 0;
};