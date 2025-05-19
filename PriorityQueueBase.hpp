#pragma once

template<typename T>
struct PriorityQueueItem {
    T value;
    int priority;

    bool operator==(const PriorityQueueItem &a) const {
        return value == a.value;
    }

    bool operator<(const PriorityQueueItem &a) const {
        return priority < a.priority;
    }

    bool operator>(const PriorityQueueItem &a) const {
        return priority > a.priority;
    }

    bool operator<=(const PriorityQueueItem &a) const {
        return priority <= a.priority;
    }

    bool operator>=(const PriorityQueueItem &a) const {
        return priority >= a.priority;
    }
};

template<class T>
class PriorityQueueBase {
public:
    virtual ~PriorityQueueBase() = default;

    virtual void insert(T e, T p) = 0;
    virtual T extract_max() = 0;
    virtual T find_max() = 0;
    virtual void modify_key(T e, T p) = 0;
    virtual T return_size() = 0;
};