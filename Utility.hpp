#pragma once

#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
// using Clock = std::chrono::steady_clock;

inline void fillArray(int* arr1, int* arr2, int n) {
    for (int i = 0; i < n; i++) {
        arr1[i] = rand() % 1001;
        arr2[i] = rand() % 10001;
    }
}

template<typename Func>
inline void arrayToList(int n, int arr1[], int arr2[], const Func& push) {
    for (int i = 0; i < n; i++) {
        push(arr1[i], arr2[i]);
    }
}

template<typename Func>
inline long long measureTime(const Func& func) {
    auto t1 = Clock::now();
    func();
    auto t2 = Clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
}