#pragma once

#include "PriorityQueueBase.hpp"
#include "ArrayList.hpp"

template <class T>
class HeapPriorityQueue : public PriorityQueueBase<T> {
public:
    void insert(T e, T p) override;
    T extract_max() override;
    T find_max() override;
    void modify_key(T e, T p) override;
    T return_size() override;

private:
    void heapify(int i);
    void heapify_up(int i);
    void build_max_heap();
    void swap(PriorityQueueItem<T>& a, PriorityQueueItem<T>& b);
    int find_element_index(T e);
    ArrayList<PriorityQueueItem<T>> heap;
};

template <class T>
void HeapPriorityQueue<T>::heapify(int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < heap.count() && heap.get(l) > heap.get(largest)) {
        largest = l;
    }
    if (r < heap.count() && heap.get(r) > heap.get(largest)) {
        largest = r;
    }

    if (largest != i) {
        swap(heap.get(i), heap.get(largest));
        heapify(largest);
    }
}

template<class T>
void HeapPriorityQueue<T>::heapify_up(int i) {
    int parent = (i - 1) / 2;
    if (i > 0 && heap.get(i) > heap.get(parent)) {
        swap(heap.get(i), heap.get(parent));
        heapify_up(parent);
    }
}

template <class T>
void HeapPriorityQueue<T>::build_max_heap() {
    for (int i = heap.count() / 2 - 1; i >= 0; i--) {
        heapify(i);
    }
}

template <class T>
void HeapPriorityQueue<T>::swap(PriorityQueueItem<T>& a, PriorityQueueItem<T>& b) {
    PriorityQueueItem<T> temp = a;
    a = b;
    b = temp;
}

template <class T>
int HeapPriorityQueue<T>::find_element_index(T e) {
    for (int i = 0; i < heap.count(); i++) {
        if (heap.get(i).value == e) {
            return i;
        }
    }
    return -1; // nie znaleziono elementu
}

template <class T>
void HeapPriorityQueue<T>::insert(T e, T p) {
    PriorityQueueItem<T> item = {e, p};
    heap.push_back(item);
    heapify_up(heap.count() - 1);
}

template <class T>
T HeapPriorityQueue<T>::extract_max() {
    if (heap.count() == 0) {
        throw std::out_of_range("Kopiec jest pusty");
    }

    swap(heap.get(0), heap.get(heap.count() - 1));
    PriorityQueueItem<T> max = heap.pop_back();

    if (heap.count() > 0) {
        heapify(0);
    }

    return max.value;
}

template <class T>
T HeapPriorityQueue<T>::find_max() {
    if (heap.count() == 0) {
        throw std::out_of_range("Kopiec jest pusty");
    }

    return heap.get(0).value;
}

template <class T>
void HeapPriorityQueue<T>::modify_key(T e, T p) {
    int index = find_element_index(e);

    if (index != -1) {
        int oldPriority = heap.get(index).priority;
        heap.get(index).priority = p;

        if (p > oldPriority) {
            heapify_up(index);
        } else if (p < oldPriority) {
            heapify(index);
        }
    }
}

template <class T>
T HeapPriorityQueue<T>::return_size() {
    return heap.count();
}