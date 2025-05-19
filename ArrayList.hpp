#pragma once

#include "BaseList.hpp"

template<class T>
class ArrayList : public BaseList<T> {
public:
    ArrayList();
    ~ArrayList();
    void push_front(T value) override;
    void push_back(T value) override;
    T pop_back() override;
    void insert(T value, int index) override;
    T remove_front() override;
    T remove_back() override;
    T remove(int index) override;
    T& get(int index) override;
    int count() override;
    int search(T value) override;

private:
    T* array;
    int size;
    int max_size;
    void increase_size();
};

template<class T>
ArrayList<T>::ArrayList() {
    size = 0;
    max_size = 4;
    array = new T[max_size];
}

template<class T>
ArrayList<T>::~ArrayList() {
    delete[] array;
}

template<class T>
int ArrayList<T>::count() {
    return size;
}

template<class T>
void ArrayList<T>::increase_size() {
    max_size *= 2;
    T *temp = new T[max_size];
    for (int i = 0; i < size; i++) {
        temp[i] = array[i];
    }
    delete[] array;
    array = temp;
}

template<class T>
void ArrayList<T>::push_back(T value) {
    if (size >= max_size) {
        increase_size();
    }
    array[size] = value;
    size++;
}

template<class T>
void ArrayList<T>::push_front(T value) {
    if (size >= max_size) {
        increase_size();
    }
    for (int i = size; i > 0; i--) {
        array[i] = array[i - 1];
    }
    array[0] = value;
    size++;
}

template<class T>
T ArrayList<T>::pop_back() {
    if (size <= 0) {
        throw std::out_of_range("ArrayList");
    }
    size--;
    return array[size];
}

template<class T>
void ArrayList<T>::insert(T value, int index) {
    if (size >= max_size) {
        increase_size();
    }
    for (int i = size; i > index; i--) {
        array[i] = array[i - 1];
    }
    array[index] = value;
    size++;
}

template<class T>
T ArrayList<T>::remove_front() {
    if (size == 0) {
        throw std::out_of_range("ArrayList");
    }
    T v = array[0];
    for (int i = 1; i < size; i++) {
        array[i - 1] = array[i];
    }
    size--;
    return v;
}

template<class T>
T ArrayList<T>::remove_back() {
    if (size == 0) {
        throw std::out_of_range("ArrayList");
    }
    T v = array[size - 1];
    size--;
    return v;
}


template<class T>
T ArrayList<T>::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("ArrayList");
    }
    T v = array[index];
    for (int i = index; i < size - 1; i++) {
        array[i] = array[i + 1];
    }
    size--;
    return v;
}

template<class T>
T& ArrayList<T>::get(int index) {
    if (index >= size || index < 0) {
        throw std::out_of_range("ArrayList");
    }
    return array[index];
}

template<class T>
int ArrayList<T>::search(T value) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1;
}