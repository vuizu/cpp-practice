#pragma once

#include <vector>
#include <algorithm>

void select_sort(std::vector<int>& arr) {
    for (int i { 0 }; i < arr.size(); i++) {
        int min_idx = i;
        for (int j { i }; j < arr.size(); j++)
            min_idx = arr[min_idx] > arr[j] ? j : min_idx;
        std::swap(arr[i], arr[min_idx]);
    }
}


void bubble_sort(std::vector<int>& arr) {
    bool flag { true };
    for (int e = arr.size() - 1; e >= 0 && flag; e--) {
        flag = false;
        for (int i { 0 }; i < e; i++) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                flag = true;
            }
        }
    }
}


void insert_sort(std::vector<int>& arr) {
    for (int e { 0 }; e < arr.size(); e++) {
        for (int i { e }; i > 0 && arr[i] < arr[i - 1]; i--) {
            std::swap(arr[i], arr[i - 1]);
        }
    }
}

void cxx_lib_sort(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());
    // std::sort_heap(arr.begin(), arr.end());
}