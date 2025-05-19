#pragma once

#include "PriorityQueueBase.hpp"
#include "ArrayList.hpp"

template <class T>
class ArrayPriorityQueue : public PriorityQueueBase<T> {
public:
    ArrayPriorityQueue() = default;

    void insert(T e, T p) override {
        PriorityQueueItem<T> item = {e, p};
        array.push_back(item);
    }

    T extract_max() override {
        if (array.count() == 0) {
            throw std::out_of_range("Kolejka jest pusta");
        }

        int maxIndex = 0;
        for (int i = 1; i < array.count(); i++) {
            if (array.get(i) > array.get(maxIndex)) {
                maxIndex = i;
            }
        }

        T value = array.get(maxIndex).value;
        array.remove(maxIndex);
        return value;
    }

    T find_max() override {
        if (array.count() == 0) {
            throw std::out_of_range("Kolejka jest pusta");
        }

        int maxIndex = 0;
        for (int i = 1; i < array.count(); i++) {
            if (array.get(i) > array.get(maxIndex)) {
                maxIndex = i;
            }
        }

        return array.get(maxIndex).value;
    }

    void modify_key(T e, T p) override {
        for (int i = 0; i < array.count(); i++) {
            if (array.get(i).value == e) {
                array.get(i).priority = p;
                return;
            }
        }
    }

    T return_size() override {
        return array.count();
    }

private:
    ArrayList<PriorityQueueItem<T>> array;
};