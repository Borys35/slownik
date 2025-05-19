#pragma once

template<class T>
class BaseList {
public:
    virtual ~BaseList() = default;

    virtual void push_front(T value) = 0;
    virtual void push_back(T value) = 0;
    virtual T pop_back() = 0;
    virtual void insert(T value, int index) = 0;
    virtual T remove_front() = 0;
    virtual T remove_back() = 0;
    virtual T remove(int index) = 0;
    virtual T& get(int index) = 0;
    virtual int count() = 0;
    virtual int search(T value) = 0;
};
